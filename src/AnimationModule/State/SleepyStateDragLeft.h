#pragma once
#include "SleepyState.h"

class SleepyStateDragLeft : public SleepyState
{
public:
	SleepyStateDragLeft(QObject* parent);
	inline static State state = State::SleepyStateDragLeft;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

