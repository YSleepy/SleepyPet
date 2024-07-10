#include "SleepyStateFall.h"

#include "SleepyStateFactory.h"

#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateFall::state, SleepyStateFall);

SleepyStateFall::SleepyStateFall(QObject* parent) :SleepyState(parent, SleepyStateFall::state)
{
	animation = new SleepyAnimation(this, false, 10);
	animation->setAnimationWithBedinEnd(4, 5);
}

void SleepyStateFall::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget,preState);

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateFall::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateFall::exit()
{
	SleepyState::exit();
}

void SleepyStateFall::update()
{
}

void SleepyStateFall::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
}
