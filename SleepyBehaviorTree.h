#pragma once
#include <memory>

#include "SleepyBehaviorTreeNode.h"

class SleepyBehaviorTree
{
public:
	SleepyBehaviorTree(std::shared_ptr<SleepyBehaviorTreeNode> root);

	void update();

private:
	std::shared_ptr<SleepyBehaviorTreeNode> rootNode;
};

