#pragma once
#include "ISleepyStateTransition.h"
#include "SleepyState.h"

class SleepyStateWalkLeft : public SleepyState,public ISleepyStateTransition
{
public:
	SleepyStateWalkLeft(QObject* parent);
	inline static State state = State::SleepyStateWalkLeft;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;

private slots:
	void autoTransitionState();

private:
	void updateRoleAnimation();

};

