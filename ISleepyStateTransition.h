#pragma once
#include "SleepyState.h"

class ISleepyStateTransition
{
public:
	ISleepyStateTransition() = default;
	StateTransitionEvent getRandomTransitionEvent()const;
	void setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents);

	static QPoint getRandomXLeftPoint(const QWidget* windows);
	static QPoint getRandomXRightPoint(const QWidget* windows);

private:
	std::vector<StateTransitionEvent> stateTransitionEvents;
};

