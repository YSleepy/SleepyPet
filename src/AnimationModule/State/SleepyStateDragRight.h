#pragma once
#include "SleepyState.h"

class SleepyStateDragRight : public SleepyState
{
public:
	SleepyStateDragRight(QObject* parent);
	inline static State state = State::SleepyStateDragRight;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

