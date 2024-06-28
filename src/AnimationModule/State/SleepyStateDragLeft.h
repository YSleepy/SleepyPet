#pragma once
#include "SleepyState.h"

class SleepyStateDragLeft : public SleepyState
{
public:
	SleepyStateDragLeft(QObject* parent);
	inline static State state = State::SleepyStateDragLeft;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

