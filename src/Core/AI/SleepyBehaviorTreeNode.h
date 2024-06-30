#pragma once
#include <functional>
#include <memory>
#include <random>
#include <vector>
#include <QWidget>

//节点运行状态,成功，失败，运行中，终止，无效
enum class ENodeStatus { Success, Failure, Running, Aborted, Invalid };

//AI行为树节点基类
class SleepyBehaviorTreeNode :public QObject
{
public:

	explicit SleepyBehaviorTreeNode(QObject* parent = nullptr) :QObject(parent){}
	~SleepyBehaviorTreeNode() override = default;

	bool isRunning() const { return status == ENodeStatus::Running; }
	bool isFailure() const { return status == ENodeStatus::Failure; }
	bool isSuccess() const { return status == ENodeStatus::Success; }
	bool isTerminated() const { return status == ENodeStatus::Aborted; }

	virtual ENodeStatus tick();
	virtual void addChild(SleepyBehaviorTreeNode* child){}
	void reSet(){status = ENodeStatus::Invalid;}
	void Abort()
	{
		OnTerminate();
		status = ENodeStatus::Aborted;
	}

protected:
	virtual void OnInitialize() {}
	virtual void OnTerminate() {}
	virtual ENodeStatus OnUpdate() = 0;

protected:
	ENodeStatus status = ENodeStatus::Invalid;
};

class CompositeNode : public SleepyBehaviorTreeNode
{
public:
	CompositeNode(QObject* parent = nullptr)
	:SleepyBehaviorTreeNode(parent),
	children(new std::vector<SleepyBehaviorTreeNode*>())
	{
		
	}
	virtual void removeChild(SleepyBehaviorTreeNode* child);
	void clearChildren()const;
	void addChild(SleepyBehaviorTreeNode* child)override;

protected:
	std::vector<SleepyBehaviorTreeNode*>* children;
};

class SelectorNode : public CompositeNode
{
	
};

//////////////////////////////////////////////////////////////////
class ActionNode : public SleepyBehaviorTreeNode {
public:
	ActionNode(std::function<ENodeStatus()> action, SleepyBehaviorTreeNode* nextNode = nullptr , QObject* parent = nullptr)
	: SleepyBehaviorTreeNode(parent),
	action(std::move(action)),
	nextNode(nextNode)
	{
		
	}

	ENodeStatus tick() override {
		return action();
	}

private:
	std::function<ENodeStatus()> action;
	SleepyBehaviorTreeNode* nextNode ;
};

class SleepySequenceNode : public SleepyBehaviorTreeNode {
public:
	void addChild(SleepyBehaviorTreeNode* child) {
		children.push_back(child);
	}
	ENodeStatus tick() override {
		for (auto& child : children) {
			ENodeStatus status = child->tick();
			if (status != ENodeStatus::Success) {
				return status;
			}
		}
		return ENodeStatus::Success;
	}

private:
	std::vector<SleepyBehaviorTreeNode*> children;
};


class RandomActionNode : public SleepyBehaviorTreeNode {
public:
	RandomActionNode(std::initializer_list<ActionNode*> actions) : actions(actions) {}

	ENodeStatus tick() override {
		// 随机选择一个动作执行
		const int index = std::uniform_int_distribution<int>(0, actions.size() - 1)(generator);
		const ENodeStatus re = actions[index]->tick();
		return re;
	}

private:
	std::vector<ActionNode*> actions;
	std::mt19937 generator{ std::random_device{}() };
};
