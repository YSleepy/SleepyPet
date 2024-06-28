#include "SleepyPet.h"
#include<QTimer>
#include <QGraphicsDropShadowEffect>
#include <QMouseEvent>

SleepyPet::SleepyPet(QWidget *parent)
	: QWidget(parent),
	mainShow(new QLabel(this)),
	longPressTimer(new QTimer(this)),
	canMove(false),
	current(1)
{

	setWindowFlags(Qt::WindowType::FramelessWindowHint);
	setAttribute(Qt::WA_TranslucentBackground);
	mainShow->resize(128, 130);

	const auto updateAnimationTimer = new QTimer(this);
	updateAnimationTimer->callOnTimeout(this,&SleepyPet::updateRoleAnimation);
	updateAnimationTimer->start(500);

	const auto shadowEffect = new QGraphicsDropShadowEffect(this);
	shadowEffect->setColor(QColor(230, 231, 232, 220));
	shadowEffect->setBlurRadius(5);
	shadowEffect->setOffset(1, 1);
	this->setGraphicsEffect(shadowEffect);

	longPressTimer->setSingleShot(true);
	connect(longPressTimer, &QTimer::timeout, this, &SleepyPet::allowMove);
	this->installEventFilter(this);
}

SleepyPet::~SleepyPet()
{

}

void SleepyPet::updateRoleAnimation()
{
	QString qss("background-repeat:no-repeat;");
	QString mainPetUrl("background-image:url(:/ZYImage/ZYimg/shime%1.png);");
	mainShow->setStyleSheet(qss + mainPetUrl.arg(current));
	(current += 1) %= 3;
	current = current == 0 ? 1 : current;
}

bool SleepyPet::eventFilter(QObject* watched, QEvent* event)
{
	QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);

	static QPoint mousePoint;
	if(mouse_event->type() == QEvent::MouseButtonPress)
	{
		mousePoint = mouse_event->globalPosition().toPoint() - this->pos();
		longPressTimer->start(1000);
		return true;
	}
	else if(mouse_event->type() == QEvent::MouseMove)
	{
		if(mouse_event->buttons() & Qt::MouseButton::LeftButton && canMove)
		{
			this->move(mouse_event->globalPosition().toPoint() - mousePoint);
			return true;
		}
	}else if(mouse_event->type()== QEvent::MouseButtonRelease &&
			mouse_event->button() == Qt::MouseButton::LeftButton)
	{
		longPressTimer->stop();
		canMove = false;
		return true;
	}

	return false;
}

inline void SleepyPet::allowMove()
{
	canMove = true;
}