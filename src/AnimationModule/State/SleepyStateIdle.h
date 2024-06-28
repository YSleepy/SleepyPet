#pragma once
#include "SleepyState.h"

class SleepyStateIdle :public SleepyState
{
public:
	SleepyStateIdle(QObject* parent);
	inline static State state = State::SleepyStateIdle;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

