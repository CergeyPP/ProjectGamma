#include "IEventable.h"

IEventable::IEventable(EventDispatcher* dispatcher) {
	if (dispatcher != nullptr) {
		dispatcher->add(this);
		dispatcher_.push_back(dispatcher);
	}
}
IEventable::~IEventable() {
	for (auto& elem : dispatcher_) {
		elem->remove(this);
	}
}

void IEventable::hookTo(EventDispatcher* dispatcher)
{
	auto elem = std::find(dispatcher_.begin(), dispatcher_.end(), dispatcher);
	if (elem == dispatcher_.end()) {
		dispatcher->add(this);
		dispatcher_.push_back(dispatcher);
	}
}

void IEventable::unhook(EventDispatcher* dispatcher)
{
	auto elem = std::find(dispatcher_.begin(), dispatcher_.end(), dispatcher);
	if (elem < dispatcher_.end()) {
		dispatcher->remove(this);
		dispatcher_.erase(elem);
	}
}
