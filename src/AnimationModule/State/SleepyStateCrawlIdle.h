#pragma once

#include "ISleepyStateTransition.h"
#include "SleepyState.h"

class SleepyStateCrawlIdle  : public SleepyState,public ISleepyStateTransition
{
public:
	SleepyStateCrawlIdle(QObject* parent);
	inline static State state = State::SleepyStateCrawlIdle;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;

private:
	void updateRoleAnimation();

private:
	QRect screenGeometry;
};
