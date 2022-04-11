#pragma once
#include <vector>

template<typename Class, typename Argument>
class Event {
public:

	~Event() {
		classSubscribers.clear();
	}

	void addListener(Class* obj, void(Class::* pointer) (Argument)) {

		ClassSubscriber newElem(obj, pointer);

		int i = 0;
		for (i = 0; i < classSubscribers.size(); i++) {
			if (classSubscribers[i].object == newElem.object && classSubscribers[i].method == newElem.method)
				break;
		}

		if (i == classSubscribers.size()) {
			classSubscribers.push_back(newElem);
		}

	}

	void deleteListener(Class* obj, void(Class::* pointer) (Argument)) {

		ClassSubscriber newElem(obj, pointer);

		int i = 0;
		for (i = 0; i < classSubscribers.size(); i++) {
			if (classSubscribers[i].object == newElem.object && classSubscribers[i].method == newElem.method)
				break;
		}

		if (i < classSubscribers.size()) {
			classSubscribers.erase(classSubscribers.begin() + i);
		}
	}

	void operator() (Argument arg) {
		for (auto elem : classSubscribers) {
			(elem.object->*elem.method)(arg);
		}
	}

private:

	struct ClassSubscriber {
		Class* object;
		void(Class::* method) (Argument);
		ClassSubscriber(Class* obj, void(Class::* meth) (Argument)) {
			object = obj;
			method = meth;
		};

	};

	std::vector<ClassSubscriber> classSubscribers;
};