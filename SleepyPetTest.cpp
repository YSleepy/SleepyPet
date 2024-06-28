#include<QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMimeData>
#include <QAudioOutput>
#include <QGuiApplication>
#include <QMenu>
#include <algorithm>

#include "SleepyPetTest.h"

SleepyPetTest::SleepyPetTest(QWidget* parent)
	: QWidget(parent),
	mainShow(new QLabel(this)),
	behaviorComponent(new QPropertyAnimation(this, "pos")),
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
	mainShow->resize(128, 130);

	//初始化位置
	QScreen* screen = QGuiApplication::primaryScreen();
	QRect screenGeometry = screen->geometry();
	endY = screenGeometry.height() - this->height();
	endX = 900;
	this->move(endX, endY);
	
	//初始化动画状态机
	animationStateMachine = new SleepyStateMachine(this, mainShow, State::SleepyStateIdle, createStateTransitionTable);

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

	//初始化AI行为树
	auto root = std::make_shared<SelectorNode>();

	// 添加随机动作节点，包含左移、停留、右移和爬墙动作
	root->addChild(std::make_shared<RandomActionNode>(std::initializer_list<std::function<NodeStatus()>>{
			[this]() { return moveLeft(); },
			[this]() { return idle(); },
			[this]() { return moveRight(); },
			[this]() { return climbWall(); }
	}));

	behaviorTreeManager = std::make_shared<SleepyBehaviorTree>(root);
	beginBehavior();
	
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
			animationStateMachine->triggerEvent(StateTransitionEvent::ToPastime);
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
		beginBehavior();
	}
	QWidget::mousePressEvent(event);
}

void SleepyPetTest::startMoveToBottom()
{
	animationStateMachine->triggerEvent(StateTransitionEvent::ToFall);

	QPropertyAnimation* fall = new QPropertyAnimation(this, "pos");
	fall->setDuration(2000);  // 2秒移动到底部
	fall->setStartValue(this->pos());
	fall->setEndValue(QPoint(this->x(), endY));
	connect(fall, &QPropertyAnimation::finished, this, &SleepyPetTest::playToGroundAnimation);
	fall->start(QAbstractAnimation::DeleteWhenStopped);
}

void SleepyPetTest::stopBehavior()
{
	animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	bCanBehavior = false;
	disconnect(behaviorComponent, &QPropertyAnimation::finished, this, &SleepyPetTest::updateBehavior);
	behaviorComponent->stop();
}

NodeStatus SleepyPetTest::moveLeft()
{
	if (!bCanBehavior)return NodeStatus::Failure;
	int distance = x() - moveDistance(generator);
	int x = qMax(0, distance);
	int duration = moveDuration(generator);
	behaviorComponent->setDuration(duration);
	behaviorComponent->setStartValue(pos());
	behaviorComponent->setEndValue(QPoint(x, y()));
	behaviorComponent->start();
	animationStateMachine->triggerEvent(StateTransitionEvent::ToWalkLeft);
	return NodeStatus::Success;
}

NodeStatus SleepyPetTest::moveRight()
{
	if (!bCanBehavior)return NodeStatus::Failure;
	int distance = x() + moveDistance(generator);
	int x = qMax(0, distance); 
	int duration = moveDuration(generator);
	x = std::clamp(x, 0, 1400);
	behaviorComponent->setDuration(duration);
	behaviorComponent->setStartValue(pos());
	behaviorComponent->setEndValue(QPoint(x, y()));
	behaviorComponent->start();
	animationStateMachine->triggerEvent(StateTransitionEvent::ToWalkRight);
	return NodeStatus::Success;
}

NodeStatus SleepyPetTest::idle()
{
	if (!bCanBehavior)return NodeStatus::Failure;
	int duration = moveDuration(generator);
	animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	QTimer::singleShot(duration, this, []() {});
	updateBehavior();
	return NodeStatus::Success;
}

NodeStatus SleepyPetTest::climbWall()
{
	if (!bCanBehavior)return NodeStatus::Failure;
	animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	updateBehavior();
	return NodeStatus::Success;
}

inline void SleepyPetTest::playToGroundAnimation()
{
	animationStateMachine->triggerEvent(StateTransitionEvent::FallToIdle);
	beginBehavior();
}

inline void SleepyPetTest::stopMusic()
{
	mediaPlayer->stop();
	//animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	beginBehavior();
}

inline void SleepyPetTest::interact()
{
}

inline void SleepyPetTest::beginBehavior()
{
	bCanBehavior = true;
	connect(behaviorComponent, &QPropertyAnimation::finished, this, &SleepyPetTest::updateBehavior);
	behaviorTreeManager->update();
}

inline void SleepyPetTest::updateBehavior()
{
	animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
	QTimer::singleShot(4000, this, [this]() {
		behaviorTreeManager->update(); // 执行下一个动作
	});
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
		animationStateMachine->triggerEvent(StateTransitionEvent::ToIdle);
		return true;
	}
	else if (mouse_event->type() == QEvent::MouseMove)
	{
		if (mouse_event->buttons() & Qt::MouseButton::LeftButton && bCanMove)
		{
			this->move(mouse_event->globalPosition().toPoint() - offset);
			if (mouseLocation.x() > mouse_event->globalPosition().toPoint().x())
			{
				animationStateMachine->triggerEvent(StateTransitionEvent::ToDragLeft);
			}
			else
			{
				animationStateMachine->triggerEvent(StateTransitionEvent::ToDragRight);
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
