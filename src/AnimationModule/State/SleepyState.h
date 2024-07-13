#pragma once
#include "SleepyAnimation.h"

#include <QLabel>
#include <QObject>
#include <QPropertyAnimation>


class SleepyStateMachine;

enum class State
{
	SleepyStateNone,
	SleepyStateIdle,
	SleepyStateWalkLeft,
	SleepyStateWalkRight,
	SleepyStateDragLeft,
	SleepyStateDragRight,
	SleepyStateFall,
	SleepyStatePastime,
	SleepyStateSleep,
	SleepyStateJump,
	SleepyStateCrawlIdle,
	SleepyStateCrawl
};

enum class StateTransitionEvent
{
	None,
	ToWalkLeft,
	ToWalkRight,
	ToDragLeft,
	ToDragRight,
	ToFall,
	ToPastime,
	ToIdle,
	ToSleep,
	ToJump,
	ToCrawlIdle,
	ToCrawl
};


class SleepyState : public QObject
{
	Q_OBJECT

public:
	SleepyState(QObject*parent,State state);
	~SleepyState();
	virtual void enter(QTimer* animationTimer,QLabel* animationTarget, QPropertyAnimation* propertyAnimation,QWidget* widget,State preState);
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
