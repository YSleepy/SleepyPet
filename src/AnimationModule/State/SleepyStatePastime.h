#pragma once
#include "SleepyState.h"

class SleepyStatePastime : public SleepyState
{
public:
	SleepyStatePastime(QObject* parent);
	inline static State state = State::SleepyStatePastime;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget) override;
	void exit() override;
	void update() override;
private:
	void updateRoleAnimation();
};

