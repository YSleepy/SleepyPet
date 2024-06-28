#pragma once
#include <QLabel>
#include <QObject>
#include <QTimer>
#include <QHash>
#include<QDate>

#include "SleepyState.h"
#include "SleepyStateFactory.h"


enum class StateTransitionEvent
{
	ToWalkLeft,
	ToWalkRight,
	ToDragLeft,
	ToDragRight,
	ToFall,
	FallToIdle,
	ToPastime,
	ToIdle
};

/*
 * 状态转移
 */

struct StateTransition
{
	StateTransition() = default;
	StateTransition(const State state,const StateTransitionEvent event) :state(state), event(event) {};
	State state;
	StateTransitionEvent event;
};

inline bool operator==(const StateTransition& e1, const StateTransition& e2)
{
	return e1.state == e2.state
		&& e1.event == e2.event;
}

inline uint qHash(const StateTransition& key, uint seed)
{
	return qHash(static_cast<uint>(key.state), seed) ^ qHash(static_cast<uint>(key.event),seed);
}

/*
 *	状态转移表，某状态--事件-->另一状态。
 */

using StateTransitionTable = QHash<StateTransition, State>;


inline SleepyState* createStateByEnum(const State state, QObject* parent)
{
	return SleepyStateFactory::instance().createState(state, parent);
}

class SleepyStateMachine : public QObject
{
	Q_OBJECT

public:
	SleepyStateMachine(QObject *parent,QLabel* playAnimationTarget,State currentState, StateTransitionTable* (*createStateTransitionTable)());
	~SleepyStateMachine();

	bool triggerEvent(StateTransitionEvent event);


private:
	
	QTimer* playAnimationTimer;
	SleepyState* currentState;
	QLabel* playAnimationTarget;
	StateTransitionTable* animationStateTransitionTable;
	QHash<State, SleepyState*>* statePool;
};
