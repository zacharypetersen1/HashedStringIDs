#include "HashedStr.h"
#include <cassert>

#ifdef HASHEDSTR_GLOBAL_MAP
// Global map storing hashed string ids to thier full string
std::unordered_map<hashResult_t, const char*> gHashedStrMap;
#endif

HashedStr::HashedStr(const char* s)
{
	assert(s != nullptr);
	hashResult = hash(s);

#ifdef HASHEDSTR_GLOBAL_MAP
	auto iter = gHashedStrMap.find(hashResult);
	if (iter == gHashedStrMap.end())
	{
		// Copy string and add it to global map
		size_t s_bufferLen = strlen(s) + 1; // Add one for null char
		char* s_copy = new char[s_bufferLen];
		strcpy_s(s_copy, s_bufferLen, s);
		gHashedStrMap.insert(std::pair<hashResult_t, const char*>(hashResult, s_copy));
	}
#ifdef HASHEDSTR_CHECK_COLLISION
	else
	{
		// Make sure we didn't generate same hashResult with different string
		assert(strcmp(s, iter->second) == 0); 
	}
#endif
#endif
}

#ifdef HASHEDSTR_GLOBAL_MAP
const char* HashedStr::getUnhashedString() const
{
	auto iter = gHashedStrMap.find(hashResult);
	assert(iter != gHashedStrMap.end());
	return iter->second;
}
#endif

// Can replace with custom hash
hashResult_t HashedStr::hash(const char* s)
{
	hashResult_t result = 0;
	while (*s)
	{
		result = result * 101 + *s++;
	}
	return result;
}

HashedStr operator ""_hash(const char* s, size_t)
{
	return HashedStr(s);
}