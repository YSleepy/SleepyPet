#include <QGuiApplication>
#include "SleepyMoveNode.h"

#include <qscreen.h>

SleepyMoveNode::SleepyMoveNode(QWidget* widget, QObject* parent)
	:SleepyActionNode(parent),
	widget_(widget)
{

}

SleepyMoveNode::SleepyMoveNode(QWidget* widget, std::function<ENodeStatus()> action, QObject* parent )
	: SleepyActionNode(std::move(action), parent),
	widget_(widget)
{
	
}

bool SleepyMoveNode::moveTowardsTarget() const
{
	const QPoint pos = widget_->pos();
	const int dx = targetPos_.x() - pos.x();
	if (dx == 0) {
		return true; // 已经到达目标位置
	}

	const int moveX = (dx != 0) ? (dx / abs(dx)) * std::min(stepSize_, abs(dx)) : 0;
	widget_->move(pos.x() + moveX, pos.y());
	return false; // 尚未到达目标位置
}

void SleepyMoveNode::OnTerminate()
{
	canMove_ = true;
	animation_->setDuration(2000);  // 2秒移动到底部
	animation_->setStartValue(widget_->pos());
	animation_->setEndValue(targetPos_);
	connect(animation_, &QPropertyAnimation::finished, this, [this]() {canMove_ = false; });
	animation_->start();
}

ENodeStatus SleepyMoveNode::OnUpdate()
{
	const QRect screenRect = QGuiApplication::primaryScreen()->geometry();
	const QPoint pos = widget_->pos();
	std::srand(static_cast<unsigned int>(std::time(nullptr)));  // NOLINT(cert-msc51-cpp)

	//更新目标位置
	if (targetPos_.isNull() || pos == targetPos_) {
		const int dx = (rand() % 2 == 0 ? -1 : 1) * (rand() % 100 + 50);  // NOLINT(concurrency-mt-unsafe)
		targetPos_ = QPoint(pos.x() + dx, pos.y());
		//限定目标位置在屏幕范围内
		targetPos_.setX(std::clamp(targetPos_.x(), screenRect.left(), screenRect.right()-widget_->width()));
	}

	if (moveTowardsTarget()) {
		return ENodeStatus::Success;
	}
	return ENodeStatus::Running;
}
