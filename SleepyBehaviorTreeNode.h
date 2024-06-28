#pragma once
#include <functional>
#include <memory>
#include <random>
#include <vector>

enum class NodeStatus { Success, Failure, Running };

class SleepyBehaviorTreeNode
{
public:

	virtual ~SleepyBehaviorTreeNode() = default;
	virtual NodeStatus tick() = 0;
};

class SleepySequenceNode : public SleepyBehaviorTreeNode {
public:
	void addChild(const std::shared_ptr<SleepyBehaviorTreeNode> child) {
		children.push_back(child);
	}
	NodeStatus tick() override {
		for (auto& child : children) {
			NodeStatus status = child->tick();
			if (status != NodeStatus::Success) {
				return status;
			}
		}
		return NodeStatus::Success;
	}

private:
	std::vector<std::shared_ptr<SleepyBehaviorTreeNode>> children;
};

class SelectorNode : public SleepyBehaviorTreeNode {
public:
	void addChild(std::shared_ptr<SleepyBehaviorTreeNode> child) {
		children.push_back(child);
	}
	NodeStatus tick() override {
		for (auto& child : children) {
			NodeStatus status = child->tick();
			if (status == NodeStatus::Success) {
				return status;
			}
		}
		return NodeStatus::Failure;
	}

private:
	std::vector<std::shared_ptr<SleepyBehaviorTreeNode>> children;
};


class ActionNode : public SleepyBehaviorTreeNode {
public:
	ActionNode(std::function<NodeStatus()> action) : action(std::move(action)) {}

	NodeStatus tick() override {
		return action();
	}

private:
	std::function<NodeStatus()> action;
};

class RandomActionNode : public SleepyBehaviorTreeNode {
public:
	RandomActionNode(std::initializer_list<std::function<NodeStatus()>> actions) : actions(actions) {}

	NodeStatus tick() override {
		// 随机选择一个动作执行
		const int index = std::uniform_int_distribution<int>(0, actions.size() - 1)(generator);
		const NodeStatus re = actions[index]();
		return re;
	}

private:
	std::vector<std::function<NodeStatus()>> actions;
	std::mt19937 generator{ std::random_device{}() };
};
