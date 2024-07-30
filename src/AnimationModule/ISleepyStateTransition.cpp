#include <QRandomGenerator>
#include <QGuiApplication>
#include <QScreen>

#include "ISleepyStateTransition.h"

StateTransitionEvent ISleepyStateTransition::getRandomTransitionEvent(StateTransitionEvent ignoreEvent)const
{
	QRandomGenerator* generator = QRandomGenerator::global();
	//加权分配
	if(!weightedStateTransitionEvents.empty())
	{
		const int randomIndex = generator->bounded(1, randomRange + 1);
		for (int i = 0; i < static_cast<int>(weightedStateTransitionEvents.size()); ++i)
		{
			if(randomIndex > weightedStateTransitionEvents.at(i).leftOpen && randomIndex <= weightedStateTransitionEvents.at(i).rightClose)
			{
				if(stateTransitionEvents.at(i) == ignoreEvent)continue;
				return stateTransitionEvents.at(i);
			}
		}
	}
	//平均分配
	while (true)
	{
		const int randomIndex = generator->bounded(0, static_cast<int>(stateTransitionEvents.size()));
		if (stateTransitionEvents.at(randomIndex) == ignoreEvent)continue;
		return stateTransitionEvents.at(randomIndex);
	}
}

void ISleepyStateTransition::setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents)
{
	this->stateTransitionEvents = TransitionEvents;
}

void ISleepyStateTransition::setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents, const std::vector<int>& weight)
{
	this->stateTransitionEvents = TransitionEvents;
	int i = 0;
	for (auto& j : weight)
	{
		this->weightedStateTransitionEvents.push_back(RangeForWeighted(i,i+=j));
	}
	randomRange = i;
}



QPoint ISleepyStateTransition::getRandomXLeftPoint(const QWidget* windows)
{
	const QRect screenRect = QGuiApplication::primaryScreen()->geometry();
	const int dx = QRandomGenerator::global()->bounded(300, 400);
	QPoint re(windows->x() - dx, windows->y());
	re.setX(std::clamp(re.x(), screenRect.left(), screenRect.right() - windows->width()));
	return re;
}

QPoint ISleepyStateTransition::getRandomXRightPoint(const QWidget* windows)
{
	const QRect screenRect = QGuiApplication::primaryScreen()->geometry();
	const int dx = QRandomGenerator::global()->bounded(300, 400);
	QPoint re(windows->x() + dx, windows->y());
	re.setX(std::clamp(re.x(), screenRect.left(), screenRect.right() - windows->width()));
	return re;
}
