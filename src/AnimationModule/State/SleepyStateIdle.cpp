#include "SleepyStateIdle.h"

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QRandomGenerator>
#include <QTimer>



REGISTER_SLEEPY_STATE(SleepyStateIdle::state, SleepyStateIdle);

SleepyStateIdle::SleepyStateIdle(QObject* parent)
	:SleepyState(parent, SleepyStateIdle::state),
	preState(State::SleepyStateIdle)
{
	animation = new SleepyAnimation(this, false, 20);
	animation->setAnimationWithBedinEnd(1, 2);
	setStateTransitionEvents(std::vector{
		StateTransitionEvent::ToWalkLeft,
		StateTransitionEvent::ToWalkRight,
		StateTransitionEvent::ToSleep
		});
}

void SleepyStateIdle::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation,widget, preState);
	qDebug() << "Enter SleepyStateIdle";
	this->preState = preState;

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateIdle::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());

	const int interval = QRandomGenerator::global()->bounded(5000, 12000);
	QTimer::singleShot(interval, this, [this]() {stateMachine->triggerEvent(getRandomTransitionEvent()); });
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

	if(preState == State::SleepyStateWalkRight)
	{
		const QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
		playAnimationTarget->setPixmap(flippedPixmap);
	}
	else
	{
		playAnimationTarget->setPixmap(pixmap);
	}
}
