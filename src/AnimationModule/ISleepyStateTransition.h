#pragma once
#include "SleepyState.h"

struct RangeForWeighted
{
	RangeForWeighted(const int& left, const int& right) : leftOpen(left), rightClose(right){}
	int leftOpen;
	int rightClose;
};

class ISleepyStateTransition
{
public:
	ISleepyStateTransition() = default;
	StateTransitionEvent getRandomTransitionEvent(StateTransitionEvent ignoreEvent = StateTransitionEvent::None)const;
	
	void setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents);
	void setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents, const std::vector<int>& weight);

	static QPoint getRandomXLeftPoint(const QWidget* windows);
	static QPoint getRandomXRightPoint(const QWidget* windows);

private:
	std::vector<StateTransitionEvent> stateTransitionEvents;
	std::vector<RangeForWeighted> weightedStateTransitionEvents;
	int randomRange;
};

