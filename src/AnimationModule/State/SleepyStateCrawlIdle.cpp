#include "SleepyStateCrawlIdle.h"

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QGuiApplication>
#include <QRandomGenerator>
#include <QScreen>
#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateCrawlIdle::state, SleepyStateCrawlIdle);

SleepyStateCrawlIdle::SleepyStateCrawlIdle(QObject* parent)
	:SleepyState(parent, SleepyStateCrawlIdle::state)
{
	screenGeometry = QGuiApplication::primaryScreen()->geometry();

	animation = new SleepyAnimation(this, false, 20);
	animation->setAnimationWithBedinEnd(12, 13);
	setStateTransitionEvents(std::vector{
		StateTransitionEvent::ToCrawl
		});
}

void SleepyStateCrawlIdle::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation, widget, preState);
	qDebug() << "Enter SleepyStateCrawlIdle";


	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateCrawlIdle::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());

	const int interval = QRandomGenerator::global()->bounded(5000, 12000);
	QTimer::singleShot(interval, this, [this]() {stateMachine->triggerEvent(getRandomTransitionEvent()); });
}

void SleepyStateCrawlIdle::exit()
{
	SleepyState::exit();
	moveComponent->stop();
}

void SleepyStateCrawlIdle::update()
{
}

void SleepyStateCrawlIdle::updateRoleAnimation()
{
	const QString qss("background-repeat:no-repeat;");
	playAnimationTarget->setStyleSheet(qss);
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}

	if(windows->pos().x()> screenGeometry.width()/2)//右侧
	{
		const QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
		playAnimationTarget->setPixmap(flippedPixmap);
	}
	else
	{
		playAnimationTarget->setPixmap(pixmap);
	}
}
