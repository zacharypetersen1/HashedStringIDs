#pragma once
#include <cstdint>
#include <unordered_map>

#ifdef _DEBUG
// Original strings will be stored in global map. May call strcpy_s when HashedStr is constructed.
#define HASHEDSTR_GLOBAL_MAP 
#endif

#ifdef HASHEDSTR_GLOBAL_MAP
// Check for hash collisions. May call strcmp when HashedStr is constructed.
#define HASHEDSTR_CHECK_COLLISION 
#endif

// Type used to store hash results
typedef int32_t hashResult_t;

#ifdef HASHEDSTR_GLOBAL_MAP
// Global map of HashedStr's. Used to retrieve original string from hash result.
extern std::unordered_map<hashResult_t, const char*> gHashedStrMap;
#endif

// Stores the result of hash operation on string. Useful for id's
class HashedStr
{
	friend std::hash<HashedStr>;
private:
	// Hashed result of the original string
	hashResult_t hashResult;
public:
	// Constructor
	explicit HashedStr(const char* s);

	// conditional operators
	bool operator==(const HashedStr& other) const { return hashResult == other.hashResult; }
	bool operator!=(const HashedStr& other) const { return !(*this == other); }

#ifdef HASHEDSTR_GLOBAL_MAP
	// Retrievies original string using the global map of HashedStr's
	const char* getUnhashedString() const;
#endif

private:
	// Hashes string. Replace code in this function with custom hash if desired.
	static hashResult_t hash(const char* s);
};

// User Defined Literal for generating hashed string at compile time
HashedStr operator ""_hash(const char* s, size_t);

// Hash function for using HashedStr in stl key-value containers
namespace std
{
	template <>
	struct hash<HashedStr>
	{
		size_t operator() (const HashedStr& x) const
		{
			// We've already run a hash on the original string, just return that result.
			return x.hashResult;
		}
	};
}