#pragma once
#include "SleepyState.h"

struct EnumClassHash
{
	template <typename T>
	std::size_t operator()(T t) const
	{
		return static_cast<std::size_t>(t);
	}
};

class SleepyStateFactory {

public:
	using CreateStateFunc = std::function<SleepyState* (QObject*)>;

	static SleepyStateFactory& instance();

	void registerState(State state, CreateStateFunc createFunc);

	SleepyState* createState(State state, QObject* parent) const;

private:
	SleepyStateFactory() {}
	std::unordered_map<State, CreateStateFunc, EnumClassHash> registry;
};

// 定义宏用于状态注册
#define REGISTER_SLEEPY_STATE(StateEnum, StateClass) \
namespace { \
    bool registered_##StateClass = []() { \
        SleepyStateFactory::instance().registerState(StateEnum, [](QObject* parent) { \
            return new StateClass(parent); \
        }); \
        return true; \
    }(); \
}
