#include "SleepyState.h"

#include "SleepyStateMachine.h"


SleepyState::SleepyState(QObject*parent,State state) : QObject(parent),stateType(state)
{
	stateMachine = dynamic_cast<SleepyStateMachine*>(parent);
}

SleepyState::~SleepyState()
{}

void SleepyState::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	this->playAnimationTarget = animationTarget;
	this->playAnimationTimer = animationTimer;
	this->moveComponent = propertyAnimation;
	this->windows = widget;
}

void SleepyState::exit()
{
	this->playAnimationTimer->stop();
	this->animation->resetAnimation();
}

State SleepyState::getStateType() const
{
	return this->stateType;
}

