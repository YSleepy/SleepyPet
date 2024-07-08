#include <QRandomGenerator>
#include <QGuiApplication>
#include <QScreen>

#include "ISleepyStateTransition.h"

StateTransitionEvent ISleepyStateTransition::getRandomTransitionEvent()const
{
	QRandomGenerator* generator = QRandomGenerator::global();
	const int randomIndex = static_cast<int>(generator->bounded(0, static_cast<int>(stateTransitionEvents.size())));
	return stateTransitionEvents.at(randomIndex);
}

void ISleepyStateTransition::setStateTransitionEvents(const std::vector<StateTransitionEvent>& TransitionEvents)
{
	this->stateTransitionEvents = TransitionEvents;
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
