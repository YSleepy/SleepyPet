#pragma once
#include "SleepyState.h"

class SleepyStateDragRight : public SleepyState
{
public:
	SleepyStateDragRight(QObject* parent);
	inline static State state = State::SleepyStateDragRight;
	void enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

