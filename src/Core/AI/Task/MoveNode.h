#pragma once
#include "SleepyBehaviorTreeNode.h"

class MoveNode : public ActionNode {
public:
	MoveNode(QWidget* widget, std::function<ENodeStatus()> action, SleepyBehaviorTreeNode* nextNode = nullptr, QObject* parent = nullptr);

protected:
	QWidget* widget_;
	QPoint targetPos_;
	int stepSize_ = 10;

	// 函数声明：判断是否移动到目标位置
	bool moveTowardsTarget()const;
};
