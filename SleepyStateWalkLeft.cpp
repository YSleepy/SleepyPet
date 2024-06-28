#include "SleepyStateWalkLeft.h"
#include"SleepyStateFactory.h"
#include "QTimer"

REGISTER_SLEEPY_STATE(SleepyStateWalkLeft::state, SleepyStateWalkLeft);

SleepyStateWalkLeft::SleepyStateWalkLeft(QObject* parent):SleepyState(parent,SleepyStateWalkLeft::state)
{
	animation = new SleepyAnimation(this, false, 200);
	animation->setAnimationWithBedinEnd(1, 4);
}

void SleepyStateWalkLeft::enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget)
{
	SleepyState::enter(playAnimationTimer, playAnimationTarget);

	playAnimationTimer->callOnTimeout(this, &SleepyStateWalkLeft::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateWalkLeft::exit()
{
	animation->current = animation->animationBegin;
}

void SleepyStateWalkLeft::update()
{
}

void SleepyStateWalkLeft::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
	(animation->current += 1) %= animation->animationEnd;
	animation->current = animation->current == 0 ? 1 : animation->current;
}
