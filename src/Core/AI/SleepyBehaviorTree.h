#pragma once
#include <memory>

#include "SleepyBehaviorTreeNode.h"

class SleepyBehaviorTree:public QObject
{
public:
	SleepyBehaviorTree(std::shared_ptr<SleepyBehaviorTreeNode> root);

	void tick();

private:
	SleepyBehaviorTreeNode* rootNode;
	SleepyBehaviorTreeNode* currentNode;
	
};

