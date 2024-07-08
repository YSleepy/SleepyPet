#pragma once
#include "ISleepyStateTransition.h"
#include "SleepyState.h"

class SleepyStateIdle :public SleepyState,public ISleepyStateTransition
{
public:
	SleepyStateIdle(QObject* parent);
	inline static State state = State::SleepyStateIdle;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget) override;
	void exit() override;
	void update() override;

private:
	void updateRoleAnimation();

};

