#include "GameObject.h"
#include <cassert>
#include <unordered_map>

std::unordered_map<HashedStr, GameObject*> gGameObjects;

GameObject::GameObject(HashedStr id) : id(id)
{
	// Make sure this id is unique
	assert(gGameObjects.find(id) == gGameObjects.end());
	gGameObjects.insert(std::pair<HashedStr, GameObject*>(id, this));
}

GameObject::~GameObject()
{
	gGameObjects.erase(id);
}

GameObject* GameObject::find(HashedStr id)
{
	auto iter = gGameObjects.find(id);
	if (iter == gGameObjects.end())
	{
		return nullptr;
	}
	assert(iter != gGameObjects.end());
	return iter->second;
}