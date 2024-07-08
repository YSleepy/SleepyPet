#pragma once

#include <QLabel>
#include <QObject>
#include <QPropertyAnimation>

#include "SleepyAnimation.h"

class SleepyStateMachine;

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

enum class StateTransitionEvent
{
	ToWalkLeft,
	ToWalkRight,
	ToDragLeft,
	ToDragRight,
	ToFall,
	ToPastime,
	ToIdle
};


class SleepyState : public QObject
{
	Q_OBJECT

public:
	SleepyState(QObject*parent,State state);
	~SleepyState();
	virtual void enter(QTimer* animationTimer,QLabel* animationTarget, QPropertyAnimation* propertyAnimation,QWidget* widget);
	virtual void exit();
	virtual void update() = 0;
	State getStateType()const;

protected:
	SleepyAnimation* animation = nullptr;
	State stateType;
	QTimer* playAnimationTimer = nullptr;//动画播放器
	QLabel* playAnimationTarget = nullptr;
	QPropertyAnimation* moveComponent = nullptr;//移动组件
	QWidget* windows = nullptr;
	SleepyStateMachine* stateMachine = nullptr;
};
