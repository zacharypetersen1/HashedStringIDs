#include "HashedStr.h"
#include "GameObject.h"
#include <cassert>
#include <iostream>

int main()
{
	new GameObject("Player"_hash);
	new GameObject("User_Interface"_hash);
	
	// ... later on

	// "Player"_hash will resolve to a literal of type hashResult_t at compile time
	// meaning that int-based comparisons can be made instead of string comparisons
	GameObject* pPlayer = GameObject::find("Player"_hash);

	// If HASHEDSTR_GLOBAL_MAP is defined, you can retrieve original string from global map like this:
#ifdef HASHEDSTR_GLOBAL_MAP
	HashedStr playerId = pPlayer->getId();
	std::cout << playerId.getUnhashedString() << std::endl;
#endif

	return 0;
}