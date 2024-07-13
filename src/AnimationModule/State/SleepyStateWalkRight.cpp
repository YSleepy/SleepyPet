#include "SleepyStateWalkRight.h"

#include <QGuiApplication>

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QRandomGenerator>
#include <QScreen>

REGISTER_SLEEPY_STATE(SleepyStateWalkRight::state, SleepyStateWalkRight);

SleepyStateWalkRight::SleepyStateWalkRight(QObject* parent) :SleepyState(parent, SleepyStateWalkRight::state)
{
	animation = new SleepyAnimation(this, false, 200);
	animation->setAnimationWithBedinEnd(1, 4);

	setStateTransitionEvents(std::vector{
		StateTransitionEvent::ToIdle,
		StateTransitionEvent::ToJump
		});
}

void SleepyStateWalkRight::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget, preState);

	qDebug() << "SleepyStateWalkRight::enter";
	//动画
	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateWalkRight::updateRoleAnimation);
	//行为
	moveComponent->setDuration(3000);  // 2秒移动到底部
	moveComponent->setStartValue(windows->pos());
	const QPoint x = getRandomXRightPoint(windows);
	moveComponent->setEndValue(x);
	qDebug() << "WalkTo:" << x;
	connect(moveComponent, &QPropertyAnimation::finished, this, &SleepyStateWalkRight::autoTransitionState,Qt::UniqueConnection);

	playAnimationTimer->start(animation->getIFG());
	moveComponent->start();
}

void SleepyStateWalkRight::exit()
{
	SleepyState::exit();
	moveComponent->stop();
}

void SleepyStateWalkRight::update()
{
}

void SleepyStateWalkRight ::autoTransitionState()
{
	const int screenWidth = QGuiApplication::primaryScreen()->geometry().width();
	if(windows->x()>=screenWidth - 2 * windows->width())
	{
		//有概率进入ToJump
		stateMachine->triggerEvent(getRandomTransitionEvent());
		return;
	}
	stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
}

void SleepyStateWalkRight::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	const QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
	playAnimationTarget->setPixmap(flippedPixmap);

	(animation->current += 1) %= animation->animationEnd;
	animation->current = animation->current == 0 ? 1 : animation->current;
}
