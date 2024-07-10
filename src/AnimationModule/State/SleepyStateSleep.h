#pragma once

#include "ISleepyStateTransition.h"
#include "SleepyState.h"

class SleepyStateSleep  : public SleepyState
{
public:
	SleepyStateSleep(QObject* parent);
	inline static State state = State::SleepyStateSleep;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};
