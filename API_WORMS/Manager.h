#pragma once

#include "Include.h"

template<typename Type>
class CManager
{
public :
	static Type ** Inst()
	{
		static Type * ptr = nullptr;
		if (ptr == nullptr)
			ptr = new Type;
		return &ptr;
	}
	static void Destroy()
	{
		Type ** pptr = Inst();
		if (*pptr != nullptr)
		{
			delete *pptr;
			*pptr = nullptr;
		}
	}
};