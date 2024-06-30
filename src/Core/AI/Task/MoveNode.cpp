#include "MoveNode.h"

MoveNode::MoveNode(QWidget* widget, std::function<ENodeStatus()> action, SleepyBehaviorTreeNode* nextNode, QObject* parent)
	: ActionNode(action, nextNode, parent),
	widget_(widget)
{

}

bool MoveNode::moveTowardsTarget() const
{
	QPoint pos = widget_->pos();
	int dx = targetPos_.x() - pos.x();
	int dy = targetPos_.y() - pos.y();
	if (dx == 0 && dy == 0) {
		return true; // 已经到达目标位置
	}

	int moveX = (dx != 0) ? (dx / abs(dx)) * std::min(stepSize_, abs(dx)) : 0;
	int moveY = (dy != 0) ? (dy / abs(dy)) * std::min(stepSize_, abs(dy)) : 0;
	widget_->move(pos.x() + moveX, pos.y() + moveY);
	return false; // 尚未到达目标位置
}
