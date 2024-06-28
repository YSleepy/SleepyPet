#pragma once
#include "SleepyState.h"

class SleepyStateWalkRight : public SleepyState
{
public:
	SleepyStateWalkRight(QObject* parent);
	inline static State state = State::SleepyStateWalkRight;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

