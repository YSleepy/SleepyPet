#include "SleepyStateSleep.h"

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QRandomGenerator>

REGISTER_SLEEPY_STATE(SleepyStateSleep::state, SleepyStateSleep);

SleepyStateSleep::SleepyStateSleep(QObject* parent) :SleepyState(parent, SleepyStateSleep::state)
{
	animation = new SleepyAnimation(this, false, 20);
	animation->setAnimationWithBedinEnd(11, 12);
}

void SleepyStateSleep::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation, widget, preState);
	qDebug() << "Enter SleepyStateIdle";

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateSleep::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());

	const int interval = QRandomGenerator::global()->bounded(5000, 12000);
	QTimer::singleShot(interval, this, [this]() {stateMachine->triggerEvent(StateTransitionEvent::ToIdle); });
}

void SleepyStateSleep::exit()
{
	SleepyState::exit();
	moveComponent->stop();
}

void SleepyStateSleep::update()
{
}

void SleepyStateSleep::updateRoleAnimation()
{
	//const QString qss("background-repeat:no-repeat;");
	//playAnimationTarget->setStyleSheet(qss);
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	qDebug() << QString("IDLE:/ZYImage/ZYimg/shime%1.png").arg(animation->current);
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
}
