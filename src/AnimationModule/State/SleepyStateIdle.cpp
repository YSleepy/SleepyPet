#include "SleepyStateIdle.h"
#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateIdle::state, SleepyStateIdle);

SleepyStateIdle::SleepyStateIdle(QObject* parent):SleepyState(parent,SleepyStateIdle::state)
{
	animation = new SleepyAnimation(this, false,20);
	animation->setAnimationWithBedinEnd(1, 2);
	setStateTransitionEvents(std::vector{
		StateTransitionEvent::ToWalkLeft,
		StateTransitionEvent::ToWalkRight,
		});
}

void SleepyStateIdle::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget);
	qDebug() << "Enter SleepyStateIdle";
	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateIdle::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());
	//TODO: 随机Idle
	QTimer::singleShot(5000, this, [this]() {stateMachine->triggerEvent(getRandomTransitionEvent()); });
}

void SleepyStateIdle::exit()
{
	SleepyState::exit();
	moveComponent->stop();
}

void SleepyStateIdle::update()
{
}

void SleepyStateIdle::updateRoleAnimation()
{
	const QString qss("background-repeat:no-repeat;");
	playAnimationTarget->setStyleSheet(qss);
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	qDebug() << QString("IDLE:/ZYImage/ZYimg/shime%1.png").arg(animation->current);
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
}
