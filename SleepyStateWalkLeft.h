#pragma once
#include "SleepyState.h"

class SleepyStateWalkLeft : public SleepyState
{
public:
	SleepyStateWalkLeft(QObject* parent);
	inline static State state = State::SleepyStateWalkLeft;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;

private:
	void updateRoleAnimation();
};

