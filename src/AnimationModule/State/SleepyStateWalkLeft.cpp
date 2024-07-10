#include "SleepyStateWalkLeft.h"

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QTimer>
#include <QRandomGenerator>
#include <QGuiApplication>
#include <QScreen>

REGISTER_SLEEPY_STATE(SleepyStateWalkLeft::state, SleepyStateWalkLeft);

SleepyStateWalkLeft::SleepyStateWalkLeft(QObject* parent):SleepyState(parent,SleepyStateWalkLeft::state)
{
	animation = new SleepyAnimation(this, false, 200);
	animation->setAnimationWithBedinEnd(1, 4);
	setStateTransitionEvents(std::vector{
	StateTransitionEvent::ToIdle
		});
}

void SleepyStateWalkLeft::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget, preState);
	qDebug() << "SleepyStateWalkLeft::enter";
	//动画
	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateWalkLeft::updateRoleAnimation);
	//行为
	moveComponent->setDuration(2000);
	moveComponent->setStartValue(windows->pos());
	qDebug() << "SleepyStateWalkLeft::enter::POS" << windows->pos() ;
	const QPoint x = getRandomXLeftPoint(windows);
	qDebug() << "SleepyStateWalkLeft::enter::dPOS" << x;
	moveComponent->setEndValue(x);
	connect(moveComponent, &QPropertyAnimation::finished, this,&SleepyStateWalkLeft::autoTransitionState, Qt::UniqueConnection);

	playAnimationTimer->start(animation->getIFG());
	moveComponent->start();
}

void SleepyStateWalkLeft::exit()
{
	SleepyState::exit();
	moveComponent->stop();
}

void SleepyStateWalkLeft::update()
{
	
}

void SleepyStateWalkLeft::autoTransitionState()
{
	stateMachine->triggerEvent(getRandomTransitionEvent());
}

void SleepyStateWalkLeft::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
	(animation->current += 1) %= animation->animationEnd;
	animation->current = animation->current == 0 ? 1 : animation->current;
}
