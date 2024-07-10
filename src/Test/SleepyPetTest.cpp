#include "SleepyPetTest.h"

#include <QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMimeData>
#include <QAudioOutput>
#include <QGuiApplication>
#include <QMenu>
#include <algorithm>


SleepyPetTest::SleepyPetTest(QWidget* parent)
	: QWidget(parent),
	mainShow(new QLabel(this)),
	longPressTimer(new QTimer(this)),
	mediaPlayer(new QMediaPlayer(this)),
	generator(std::random_device{}()),
	moveDuration(3000, 4000),
	moveDistance(300,600),
	bCanMove(false),
	bCanBehavior(true),
	bIsFree(true)
{

	//设置窗口透明大小等
	setWindowFlags(Qt::WindowType::FramelessWindowHint | Qt::WindowStaysOnTopHint);
	setAttribute(Qt::WA_TranslucentBackground);
	this->resize(128, 130);
	mainShow->setScaledContents(true);
	mainShow->resize(128, 130);

	//初始化位置
	const QScreen* screen = QGuiApplication::primaryScreen();
	const QRect screenGeometry = screen->geometry();
	endY = screenGeometry.height() - this->height();
	endX = 900;
	//endX = screenGeometry.width() - this->width();
	this->move(endX, endY);
	
	//初始化状态机
	stateMachine = new SleepyStateMachine(this, mainShow,this, State::SleepyStateIdle, createStateTransitionTable);

	//设置桌宠阴影
	const auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setColor(QColor(230, 231, 232, 220));
	shadowEffect->setBlurRadius(5);
	shadowEffect->setOffset(1, 1);
	this->setGraphicsEffect(shadowEffect);

	//鼠标左键移动桌宠位置
	longPressTimer->setSingleShot(true);
	connect(longPressTimer, &QTimer::timeout, this, &SleepyPetTest::allowMove);
	this->installEventFilter(this);

	//接受拖拽文件,bug解决办法 https://blog.csdn.net/hongrui1/article/details/50696683
	setAcceptDrops(true);

}


void SleepyPetTest::dragEnterEvent(QDragEnterEvent* event)
{
	foreach(const QUrl & url, event->mimeData()->urls()) {
		QString fileName = url.toLocalFile();
		if (fileName.endsWith(".mp3", Qt::CaseInsensitive))
		{
			stopBehavior();
			event->accept(); // 接受拖拽动作
		}
	}
}

void SleepyPetTest::dropEvent(QDropEvent* event)
{
	foreach(const QUrl & url, event->mimeData()->urls()) {
		QString fileName = url.toLocalFile();
		if (fileName.endsWith(".mp3",Qt::CaseInsensitive)) {
			mediaPlayer->setAudioOutput(new QAudioOutput(this));
			mediaPlayer->setSource(QUrl::fromLocalFile(fileName));
			mediaPlayer->play();
			stopBehavior();
			stateMachine->triggerEvent(StateTransitionEvent::ToPastime);
		}
	}
}

void SleepyPetTest::contextMenuEvent(QContextMenuEvent* event)
{
	QMenu contextMenu(this);

	QAction stopMusicAction("停止播放音乐", this);
	connect(&stopMusicAction, &QAction::triggered, this, &SleepyPetTest::stopMusic);

	QAction interactAction("记事本", this);
	connect(&interactAction, &QAction::triggered, this, &SleepyPetTest::interact);

	contextMenu.addAction(&stopMusicAction);
	contextMenu.addAction(&interactAction);

	// 菜单显示位置:在窗口右下角
	QPoint menuPos = this->mapToGlobal(QPoint(this->width(), this->height()));
	contextMenu.exec(menuPos);
}

void SleepyPetTest::mousePressEvent(QMouseEvent* event)
{
	if (!rect().contains(event->pos())) {
		//TODO::点击窗口外，停止行为
	}
	QWidget::mousePressEvent(event);
}

void SleepyPetTest::startMoveToBottom()
{
	stateMachine->triggerEvent(StateTransitionEvent::ToFall);

	QPropertyAnimation* fall = new QPropertyAnimation(this, "pos");
	fall->setDuration(2000);  // 2秒移动到底部
	fall->setStartValue(this->pos());
	fall->setEndValue(QPoint(this->x(), endY));
	connect(fall, &QPropertyAnimation::finished, this, &SleepyPetTest::playToGroundAnimation);
	fall->start(QAbstractAnimation::DeleteWhenStopped);
}

void SleepyPetTest::stopBehavior()
{
	stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	bCanBehavior = false;
}

inline void SleepyPetTest::playToGroundAnimation()
{
	stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
}

inline void SleepyPetTest::stopMusic()
{
	mediaPlayer->stop();
	stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
}

inline void SleepyPetTest::interact()
{
}

bool SleepyPetTest::eventFilter(QObject* watched, QEvent* event)
{
	const QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

	static QPoint offset; static QPoint mouseLocation;
	if (mouse_event->type() == QEvent::MouseButtonPress)
	{
		mouseLocation = mouse_event->globalPosition().toPoint();
		offset = mouse_event->globalPosition().toPoint() - this->pos();
		longPressTimer->start(1000);
		stopBehavior();
		stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
		return true;
	}
	else if (mouse_event->type() == QEvent::MouseMove)
	{
		if (mouse_event->buttons() & Qt::MouseButton::LeftButton && bCanMove)
		{
			this->move(mouse_event->globalPosition().toPoint() - offset);
			if (mouseLocation.x() > mouse_event->globalPosition().toPoint().x())
			{
				stateMachine->triggerEvent(StateTransitionEvent::ToDragLeft);
			}
			else
			{
				stateMachine->triggerEvent(StateTransitionEvent::ToDragRight);
			}
			mouseLocation = mouse_event->globalPosition().toPoint();
			return true;
		}
	}
	else if (mouse_event->type() == QEvent::MouseButtonRelease &&
		mouse_event->button() == Qt::MouseButton::LeftButton)
	{
		longPressTimer->stop();
		bCanMove = false;
		startMoveToBottom();
		return true;
	}

	return false;
}

inline void SleepyPetTest::allowMove()
{
	bCanMove = true;
}
