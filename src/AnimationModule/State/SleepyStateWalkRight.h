#pragma once
#include "ISleepyStateTransition.h"
#include "SleepyState.h"

class SleepyStateWalkRight : public SleepyState,public ISleepyStateTransition
{
public:
	SleepyStateWalkRight(QObject* parent);
	inline static State state = State::SleepyStateWalkRight;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget) override;
	void exit() override;
	void update() override;

private slots:
	void autoTransitionState();

private:
	void updateRoleAnimation();
};

