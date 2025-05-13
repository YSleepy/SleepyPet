#include "SleepyStateFactory.h"

SleepyStateFactory& SleepyStateFactory::instance()
{
	// Static local variables will only be initialized once during program execution
	// and C++11 and above standards ensure their thread safety
	static SleepyStateFactory factory;
	return factory;
}

void SleepyStateFactory::registerState(State state, CreateStateFunc createFunc)
{
	registry[state] = createFunc;
}

SleepyState* SleepyStateFactory::createState(State state, QObject* parent) const
{
	auto it = registry.find(state);
	if (it != registry.end()) {
		return it->second(parent);
	}
	return nullptr;
}
