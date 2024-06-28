#pragma once

#include <QLabel>
#include <QObject>

#include "SleepyAnimation.h"

enum class State
{
	SleepyStateIdle,
	SleepyStateWalkLeft,
	SleepyStateWalkRight,
	SleepyStateDragLeft,
	SleepyStateDragRight,
	SleepyStateFall,
	SleepyStatePastime
};


class SleepyState : public QObject
{
	Q_OBJECT

public:
	SleepyState(QObject*parent,State state);
	~SleepyState();
	virtual void enter(QTimer* playAnimationTimer,QLabel* playAnimationTarget);
	virtual void exit() = 0;
	virtual void update() = 0;
	State getStateType()const;

protected:
	SleepyAnimation* animation;
	State stateType;
	QTimer* playAnimationTimer;
	QLabel* playAnimationTarget;
};
