#pragma once
#include "SleepyBehaviorTreeNode.h"

class SleepyMoveNode : public SleepyActionNode {
public:
	SleepyMoveNode(QWidget* widget, std::function<ENodeStatus()> action = nullptr, QObject* parent = nullptr);

protected:
	QWidget* widget_;
	QPoint targetPos_;
	int stepSize_ = 1;

	// 函数声明：判断是否移动到目标位置
	bool moveTowardsTarget()const;

	void OnTerminate() override;
	ENodeStatus OnUpdate() override;
};
