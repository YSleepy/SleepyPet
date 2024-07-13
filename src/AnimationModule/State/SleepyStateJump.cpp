#include "SleepyStateJump.h"

#include "SleepyStateFactory.h"
#include "SleepyStateMachine.h"

#include <QGuiApplication>
#include <QScreen>
#include <QRandomGenerator>
#include <QTimer>

REGISTER_SLEEPY_STATE(SleepyStateJump::state, SleepyStateJump);

SleepyStateJump::SleepyStateJump(QObject* parent)
	:SleepyState(parent, SleepyStateJump::state),
	properMoveTimer(new QTimer(this))
{
	jumpNeedTime = 1000;
	currentTime = 0.0;
	//屏幕大小
	screenGeometry = QGuiApplication::primaryScreen()->geometry();

	//动画资产
	animation = new SleepyAnimation(this, false, 20);
	animation->setAnimationWithBedinEnd(12, 13);

	//特殊移动方式
	properMoveTimer->callOnTimeout(this, &SleepyStateJump::updateProperMove);
}

void SleepyStateJump::enter(QTimer* animationTimer, QLabel* animationTarget, QPropertyAnimation* propertyAnimation, QWidget* widget, State preState)
{
	SleepyState::enter(animationTimer, animationTarget, propertyAnimation, widget, preState);
	qDebug() << "Enter SleepyStateJump";

	readyJump();

	disconnect(playAnimationTimer, &QTimer::timeout, nullptr, nullptr);
	playAnimationTimer->callOnTimeout(this, &SleepyStateJump::updateRoleAnimation);
	playAnimationTimer->start(animation->getIFG());

	//跳跃
	properMoveTimer->start(20);
}

void SleepyStateJump::exit()
{
	SleepyState::exit();
	moveComponent->stop();
	properMoveTimer->stop();
}

void SleepyStateJump::update()
{
}

void SleepyStateJump::updateRoleAnimation()
{
	const QString qss("background-repeat:no-repeat;");
	playAnimationTarget->setStyleSheet(qss);
	const QPixmap pixmap(QString(":/ZYImage/ZYimg/shime%1.png").arg(animation->current));
	//qDebug() << QString("Jump:/ZYImage/ZYimg/shime%1.png").arg(animation->current);
	if (pixmap.isNull()) {
		qDebug() << "Failed to load image.";
		return;
	}

	if (windows->x() > screenGeometry.width() / 2)
	{
		const QPixmap flippedPixmap = pixmap.transformed(QTransform().scale(-1, 1));
		playAnimationTarget->setPixmap(flippedPixmap);
	}
	else
	{
		playAnimationTarget->setPixmap(pixmap);
	}
}

void SleepyStateJump::updateProperMove()
{
	currentTime += 0.016; // 增加时间（秒）
	const double t = currentTime;
	// 抛物线方程 y = a(x - h)^2 + k
	const double h = highPoint.x();
	const double k = highPoint.y();
	const double x_start = startPoint.x();
	const double y_start = startPoint.y();

	// TODO: 可优化，计算一次a即可
	// 计算a
	const double a = (y_start - k) / std::pow(x_start - h, 2);

	// 更新x坐标
	const double newX = x_start + t * (h - x_start) * 2;

	// 更新y坐标
	const double newY = a * std::pow(newX - h, 2) + k;
	if (newX >= h || newY >= y_start) {
		// TODO: 转换状态
		stateMachine->triggerEvent(StateTransitionEvent::ToCrawlIdle);
	}
	windows->move(QPoint(static_cast<int>(newX), static_cast<int>(newY)));
}

void SleepyStateJump::readyJump()
{
	currentTime = 0.0;
	startPoint = windows->pos();
	if (windows->x() > screenGeometry.width() / 2)
	{
		highPoint = QPoint(screenGeometry.width() - windows->width() / 2, screenGeometry.height() - windows->height() * 2);
	}else
	{
		highPoint = QPoint(screenGeometry.left() - windows->width() / 2, screenGeometry.height() - windows->height() * 2);
	}
}
