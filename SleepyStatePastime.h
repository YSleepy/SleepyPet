#pragma once
#include "SleepyState.h"

class SleepyStatePastime : public SleepyState
{
public:
	SleepyStatePastime(QObject* parent);
	inline static State state = State::SleepyStatePastime;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

