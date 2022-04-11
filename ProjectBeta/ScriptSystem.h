#pragma once
#include "ObjectPool.h"
#include "ScriptableComponent.h"

class ScriptSystem
{
public:
	static ScriptSystem* get();
	~ScriptSystem();

	ObjectPool<ScriptableComponent> scriptComponentPool;

private:

	ScriptSystem();

	static bool instanced_;
	static ScriptSystem* system_;

};

