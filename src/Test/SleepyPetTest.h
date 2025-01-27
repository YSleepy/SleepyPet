#pragma once
#include <QWidget>
#include <QMediaPlayer>
#include <random>
#include <QMouseEvent>
#include <sparkchain.h>

//#include "SleepyBehaviorTree.h"
#include "SleepyStateCrawl.h"
#include "SleepyStateCrawlIdle.h"
#include "SleepyStateDragLeft.h"
#include "SleepyStateDragRight.h"
#include "SleepyStateFall.h"
#include "SleepyStateMachine.h"
#include "SleepyStateIdle.h"
#include "SleepyStateJump.h"
#include "SleepyStatePastime.h"
#include "SleepyStateSleep.h"
#include "SleepyStateWalkLeft.h"
#include "SleepyStateWalkRight.h"

inline StateTransitionTable* createStateTransitionTable()
{
	StateTransitionTable* re = new StateTransitionTable;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToWalkLeft}] = SleepyStateWalkLeft::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToWalkRight}] = SleepyStateWalkRight::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToPastime}] = SleepyStatePastime::state;//音乐
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToSleep}] = SleepyStateSleep::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToJump}] = SleepyStateJump::state;

	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToJump}] = SleepyStateJump::state;

	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToJump}] = SleepyStateJump::state;

	(*re)[{SleepyStateJump::state, StateTransitionEvent::ToCrawlIdle}] = SleepyStateCrawlIdle::state;

	(*re)[{SleepyStateCrawlIdle::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateCrawlIdle::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;

	(*re)[{SleepyStateDragLeft::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateDragLeft::state, StateTransitionEvent::ToFall}] = SleepyStateFall::state;

	(*re)[{SleepyStateDragRight::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateDragRight::state, StateTransitionEvent::ToFall}] = SleepyStateFall::state;

	(*re)[{SleepyStateFall::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStatePastime::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStateSleep::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;

	return re;
}

class SleepyPetTest : public QWidget
{
	Q_OBJECT

public:

	SleepyPetTest(QWidget* parent = nullptr);
	~SleepyPetTest() override = default;

	bool eventFilter(QObject* watched, QEvent* event) override;

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:
	void startMoveToBottom();
	void stopBehavior();
	void InitAi();

private slots:
	inline void allowMove();
	inline void stopMusic();
	inline void interact();

private:

	QLabel* mainShow;
	SleepyStateMachine* stateMachine;
	QPropertyAnimation* behaviorComponent;
	QTimer* longPressTimer;
	QMediaPlayer* mediaPlayer;
	SparkChain::SparkChainConfig* aiConfig;
	SparkChain::LLMConfig* llmConfig;
	SparkChain::LLM* llm;
	std::mt19937 generator;
	std::uniform_int_distribution<int> moveDuration;
	std::uniform_int_distribution<int> moveDistance;
	bool bCanMove;
	bool bCanBehavior;
	bool bIsFree;
	int endX;
	int endY;

};

