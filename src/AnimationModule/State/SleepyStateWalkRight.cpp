#include "SleepyStateWalkRight.h"
#include"SleepyStateFactory.h"
#include "QTimer"

REGISTER_SLEEPY_STATE(SleepyStateWalkRight::state, SleepyStateWalkRight);

SleepyStateWalkRight::SleepyStateWalkRight(QObject* parent) :SleepyState(parent, SleepyStateWalkRight::state)
{
	animation = new SleepyAnimation(this, false, 300);
	animation->setAnimationWithBedinEnd(1, 4);
}

void SleepyStateWalkRight::enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget)
{
	SleepyState::enter(playAnimationTimer, playAnimationTarget);

	playAnimationTimer->callOnTimeout(this, &SleepyStateWalkRight::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateWalkRight::exit()
{
	animation->current = animation->animationBegin;
}

void SleepyStateWalkRight::update()
{
}

void SleepyStateWalkRight::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	const QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
	playAnimationTarget->setPixmap(flippedPixmap);

	(animation->current += 1) %= animation->animationEnd;
	animation->current = animation->current == 0 ? 1 : animation->current;
}
