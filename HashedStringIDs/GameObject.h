#pragma once
#include "HashedStr.h"

// Simple class for demonstrating use of HashedStr
class GameObject
{
private:
	HashedStr id;
public:
	GameObject(HashedStr id);
	~GameObject();
	HashedStr getId() { return id; }
	static GameObject* find(HashedStr id);
};

