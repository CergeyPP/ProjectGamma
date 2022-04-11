#include "ScriptSystem.h"

ScriptSystem* ScriptSystem::system_ = nullptr;
bool ScriptSystem::instanced_ = 0;

ScriptSystem* ScriptSystem::get()
{
    return nullptr;
}

ScriptSystem::~ScriptSystem()
{
}

ScriptSystem::ScriptSystem() : scriptComponentPool(MAX_OBJECTS)
{
}
