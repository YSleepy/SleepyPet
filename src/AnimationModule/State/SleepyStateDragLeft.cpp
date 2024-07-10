#include "SleepyStateDragLeft.h"

#include "SleepyStateFactory.h"

#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateDragLeft::state, SleepyStateDragLeft);

SleepyStateDragLeft::SleepyStateDragLeft(QObject* parent) :SleepyState(parent, SleepyStateDragLeft::state)
{
	animation = new SleepyAnimation(this, false, 1);
	animation->setSequenceArray({6,8,10});
}

void SleepyStateDragLeft::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation,QWidget* widget,State preState)
{
	SleepyState::enter(animationTimer, animationTarget,propertyAnimation,widget,preState);

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateDragLeft::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
}

void SleepyStateDragLeft::exit()
{
	SleepyState::exit();
}

void SleepyStateDragLeft::update()
{
}

void SleepyStateDragLeft::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
	++ animation->SequenceArraycursor;
	if(animation->SequenceArraycursor == animation->SequenceArray.size())
	{
		animation->SequenceArraycursor -= 1;
	}
	animation->current = animation->SequenceArray.at(animation->SequenceArraycursor);
}
