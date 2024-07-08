#include "SleepyStateDragRight.h"
#include "SleepyStateFactory.h"
#include "QTimer"

REGISTER_SLEEPY_STATE(SleepyStateDragRight::state, SleepyStateDragRight);

SleepyStateDragRight::SleepyStateDragRight(QObject* parent) :SleepyState(parent, SleepyStateDragRight::state)
{
	animation = new SleepyAnimation(this, false, 1);
	animation->setSequenceArray({ 5,7,9 });
}


void SleepyStateDragRight::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget)
{
	SleepyState::enter(animationTimer, animationTarget,propertyAnimation,widget);

	playAnimationTimer->callOnTimeout(this, &SleepyStateDragRight::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateDragRight::exit()
{
	SleepyState::exit();
}

void SleepyStateDragRight::update()
{
}

void SleepyStateDragRight::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);

	++animation->SequenceArraycursor;
	if (animation->SequenceArraycursor == animation->SequenceArray.size())
	{
		animation->SequenceArraycursor -= 1;
	}
	animation->current = animation->SequenceArray.at(animation->SequenceArraycursor);
}
