#pragma once
#include "SleepyState.h"

class SleepyStateJump  : public SleepyState
{
public:
	SleepyStateJump(QObject* parent);
	inline static State state = State::SleepyStateJump;
	void enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState) override;
	void exit() override;
	void update() override;

private:
	void updateRoleAnimation();
	void updateProperMove();
	void readyJump();

private:
	QTimer* properMoveTimer;
	QPoint startPoint;
	QPoint highPoint;
	double jumpNeedTime;
	double currentTime;
	QRect screenGeometry;

};
