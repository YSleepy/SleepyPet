#include "SleepyStateDragRight.h"

#include "SleepyStateFactory.h"

#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateDragRight::state, SleepyStateDragRight);

SleepyStateDragRight::SleepyStateDragRight(QObject* parent) :SleepyState(parent, SleepyStateDragRight::state)
{
	animation = new SleepyAnimation(this, false, 50);
	animation->setSequenceArray({ 5,7,9 });
}


void SleepyStateDragRight::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget,propertyAnimation,widget, preState);
	qDebug() << "Enter SleepyStateDragRight";
	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateDragRight::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateDragRight::exit()
{
	SleepyState::exit();
	playAnimationTimer->stop();
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
	//qDebug() << "RightCurrent animation frame: " << animation->current;
	playAnimationTarget->setPixmap(pixmap);

	++animation->SequenceArraycursor;
	if (animation->SequenceArraycursor == animation->SequenceArray.size())
	{
		animation->SequenceArraycursor -= 1;
	}
	animation->current = animation->SequenceArray.at(animation->SequenceArraycursor);
}
