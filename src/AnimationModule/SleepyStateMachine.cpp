#include "SleepyStateMachine.h"


SleepyStateMachine::SleepyStateMachine(QObject* parent, QLabel* playAnimationTarget,QWidget* widget, State currentState, StateTransitionTable* (*createStateTransitionTable)())
	: QObject(parent),
	playAnimationTimer(new QTimer(this)),
	playAnimationTarget(playAnimationTarget),
	windows(widget),
	animationStateTransitionTable(createStateTransitionTable()),
	statePool(new QHash<State, SleepyState*>()),
	propertyAnimation(new QPropertyAnimation(windows, "pos", this))
{
	for (auto i = animationStateTransitionTable->begin(); i != animationStateTransitionTable->end(); ++i)
	{
		if (statePool->find(i.key().state) == statePool->end())
		{
			(*statePool)[i.key().state] = createStateByEnum(i.key().state, this);
		}
		if (statePool->find(i.value()) == statePool->end())
		{
			(*statePool)[i.value()] = createStateByEnum(i.value(), this);
		}
	}
	this->currentState = (*statePool)[currentState];
	this->currentState->enter(playAnimationTimer, playAnimationTarget, propertyAnimation, windows);
}

SleepyStateMachine::~SleepyStateMachine()
{}

bool SleepyStateMachine::triggerEvent(StateTransitionEvent event)
{
	const auto findStateTransition = animationStateTransitionTable->find({ currentState->getStateType(),event });
	if (findStateTransition != animationStateTransitionTable->end())//找到了
	{
		currentState->exit();
		currentState = (*statePool)[findStateTransition.value()];
		currentState->enter(playAnimationTimer, playAnimationTarget,propertyAnimation,windows);
		return true;
	}
	return false;
}
