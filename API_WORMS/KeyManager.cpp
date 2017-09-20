#include "KeyManager.h"

CKeyManager::CKeyManager()
{
	for (int i = 1; i < 255; ++i)
	{
		data[i].key = (short)i;
	}
}

CKeyManager::~CKeyManager()
{
}
