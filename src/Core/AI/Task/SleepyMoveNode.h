#pragma once
#include <QTimer>
#include "SleepyBehaviorTreeNode.h"

class SleepyMoveNode : public SleepyActionNode {
public:
	SleepyMoveNode(QWidget* widget, QObject* parent = nullptr);
	SleepyMoveNode(QWidget* widget, std::function<ENodeStatus()> action = nullptr, QObject* parent = nullptr);

protected:
	QWidget* widget_;
	QPoint targetPos_;
	int stepSize_ = 1;
	QTimer* timer_ = new QTimer(this);
	bool canMove_ = true;

	// 函数声明：判断是否移动到目标位置
	bool moveTowardsTarget()const;

	void OnTerminate() override;
	ENodeStatus OnUpdate() override;
};
