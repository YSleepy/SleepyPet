#include "SleepyStatePastime.h"

#include "SleepyStateFactory.h"

#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStatePastime::state, SleepyStatePastime);

SleepyStatePastime::SleepyStatePastime(QObject* parent) :SleepyState(parent, SleepyStatePastime::state)
{
	animation = new SleepyAnimation(this, false, 100);
	animation->setAnimationWithBedinEnd(15, 18);
}

void SleepyStatePastime::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget, preState);

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStatePastime::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStatePastime::exit()
{
	SleepyState::exit();
}

void SleepyStatePastime::update()
{
}

void SleepyStatePastime::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
	(animation->current += 1) %= animation->animationEnd;
	animation->current = animation->current == 0 ? animation->animationBegin : animation->current;
}
