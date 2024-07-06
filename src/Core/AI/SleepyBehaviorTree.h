#pragma once
#include <memory>

#include "SleepyBehaviorTreeNode.h"

class SleepyBehaviorTree:public QObject
{
public:
	SleepyBehaviorTree(SleepyBehaviorTreeNode* root);

	void tick()const;

private:
	SleepyBehaviorTreeNode* rootNode;
};

