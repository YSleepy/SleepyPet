#include "SleepyBehaviorTree.h"

SleepyBehaviorTree::SleepyBehaviorTree(std::shared_ptr<SleepyBehaviorTreeNode> root): rootNode(std::move(root))
{
	
}

void SleepyBehaviorTree::update()
{
	if (rootNode) {
		rootNode->tick();
	}
}
