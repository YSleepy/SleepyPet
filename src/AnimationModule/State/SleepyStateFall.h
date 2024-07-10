#pragma once
#include "SleepyState.h"

class SleepyStateFall : public SleepyState
{
public:
	SleepyStateFall(QObject* parent);
	inline static State state = State::SleepyStateFall;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

