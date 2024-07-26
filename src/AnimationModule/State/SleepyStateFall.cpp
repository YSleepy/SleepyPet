#include "SleepyStateFall.h"

#include "SleepyStateFactory.h"

#include <QGuiApplication>
#include <QScreen>
#include <QTimer>

#include "SleepyStateMachine.h"

REGISTER_SLEEPY_STATE(SleepyStateFall::state, SleepyStateFall);

SleepyStateFall::SleepyStateFall(QObject* parent) :SleepyState(parent, SleepyStateFall::state)
{
	screenRect = QGuiApplication::primaryScreen()->geometry();
	fallSpeed = 20;
	animation = new SleepyAnimation(this, false, 10);
	animation->setAnimationWithBedinEnd(4, 5);
}

void SleepyStateFall::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget,preState);

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateFall::updateRoleAnimation);

	const int fallTime = (screenRect.height() - windows->height()- windows->pos().y()) / fallSpeed*100;
	moveComponent->setDuration(fallTime);
	moveComponent->setStartValue(windows->pos());
	moveComponent->setEndValue(QPoint(windows->x(), screenRect.height() - windows->height()));
	connect(moveComponent, &QPropertyAnimation::finished, this, &SleepyStateFall::autoTransitionState,Qt::UniqueConnection);

	playAnimationTimer->start(animation->getIFG());
	moveComponent->start();
}

void SleepyStateFall::exit()
{
	SleepyState::exit();
	playAnimationTimer->stop();
	moveComponent->stop();
}

void SleepyStateFall::update()
{
}

void SleepyStateFall::autoTransitionState()
{
	qDebug() << "SleepyStateFall::moveComponent finished";
	stateMachine->triggerEvent(StateTransitionEvent::ToIdle);
}

void SleepyStateFall::updateRoleAnimation()
{
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
}
