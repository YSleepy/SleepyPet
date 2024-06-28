#include "SleepyState.h"


SleepyState::SleepyState(QObject*parent,State state) : QObject(parent),stateType(state)
{}

SleepyState::~SleepyState()
{}

void SleepyState::enter(QTimer * playAnimationTimer, QLabel * playAnimationTarget)
{
	this->playAnimationTarget = playAnimationTarget;
	this->playAnimationTimer = playAnimationTimer;
}

State SleepyState::getStateType() const
{
	return this->stateType;
}
