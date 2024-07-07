#include <QTimer>
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

void SleepyState::exit()
{
	this->animation->resetAnimation();
	this->playAnimationTimer->stop();
}

State SleepyState::getStateType() const
{
	return this->stateType;
}
