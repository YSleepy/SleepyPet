#pragma once
#include <QWidget>
#include <QMediaPlayer>
#include <QPropertyAnimation>
#include <random>
#include <QMouseEvent>

#include "SleepyBehaviorTree.h"
#include "SleepyStateDragLeft.h"
#include "SleepyStateDragRight.h"
#include "SleepyStateFall.h"
#include "SleepyStateMachine.h"
#include "SleepyStateIdle.h"
#include "SleepyStatePastime.h"
#include "SleepyStateWalkLeft.h"
#include "SleepyStateWalkRight.h"

inline StateTransitionTable* createStateTransitionTable()
{
	StateTransitionTable* re = new StateTransitionTable;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToWalkLeft}] = SleepyStateWalkLeft::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToWalkRight}] = SleepyStateWalkRight::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateIdle::state, StateTransitionEvent::ToPastime}] = SleepyStatePastime::state;


	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateWalkLeft::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;

	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateWalkRight::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;

	(*re)[{SleepyStateDragLeft::state, StateTransitionEvent::ToDragRight}] = SleepyStateDragRight::state;
	(*re)[{SleepyStateDragLeft::state, StateTransitionEvent::ToFall}] = SleepyStateFall::state;

	(*re)[{SleepyStateDragRight::state, StateTransitionEvent::ToDragLeft}] = SleepyStateDragLeft::state;
	(*re)[{SleepyStateDragRight::state, StateTransitionEvent::ToFall}] = SleepyStateFall::state;

	(*re)[{SleepyStateFall::state, StateTransitionEvent::FallToIdle}] = SleepyStateIdle::state;
	(*re)[{SleepyStatePastime::state, StateTransitionEvent::ToIdle}] = SleepyStateIdle::state;

	return re;
}

class SleepyPetTest : public QWidget
{
	Q_OBJECT

public:

	SleepyPetTest(QWidget* parent = nullptr);
	virtual ~SleepyPetTest() = default ;

	bool eventFilter(QObject* watched, QEvent* event) override;

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
	void contextMenuEvent(QContextMenuEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

private:

	void startMoveToBottom();
	void stopBehavior();
	NodeStatus moveLeft();
	NodeStatus moveRight();
	NodeStatus idle();
	NodeStatus climbWall();

private slots:

	inline void allowMove();
	inline void playToGroundAnimation();
	inline void stopMusic();
	inline void interact();
	inline void beginBehavior();
	inline void updateBehavior();

private:

	QLabel* mainShow;
	SleepyStateMachine* animationStateMachine;
	std::shared_ptr<SleepyBehaviorTree> behaviorTreeManager;
	QPropertyAnimation* behaviorComponent;
	QTimer* longPressTimer;
	QMediaPlayer* mediaPlayer;
	std::mt19937 generator;
	std::uniform_int_distribution<int> moveDuration;
	std::uniform_int_distribution<int> moveDistance;
	bool bCanMove;
	bool bCanBehavior;
	bool bIsFree;
	int endX;
	int endY;

};

