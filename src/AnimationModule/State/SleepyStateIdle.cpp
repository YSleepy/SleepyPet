#include "SleepyStateIdle.h"
#include "SleepyStateFactory.h"
#include "QTimer"

REGISTER_SLEEPY_STATE(SleepyStateIdle::state, SleepyStateIdle);

SleepyStateIdle::SleepyStateIdle(QObject* parent):SleepyState(parent,SleepyStateIdle::state)
{
	animation = new SleepyAnimation(this, false,10);
	animation->setAnimationWithBedinEnd(1, 2);
}


void SleepyStateIdle::enter(QTimer* playAnimationTimer, QLabel* playAnimationTarget)
{
	SleepyState::enter(playAnimationTimer, playAnimationTarget);

	playAnimationTimer->callOnTimeout(this, &SleepyStateIdle::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());

}

void SleepyStateIdle::exit()
{
	SleepyState::exit();
}

void SleepyStateIdle::update()
{
}

void SleepyStateIdle::updateRoleAnimation()
{
	const QString qss("background-repeat:no-repeat;");
	playAnimationTarget->setStyleSheet(qss);
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}
	playAnimationTarget->setPixmap(pixmap);
}
