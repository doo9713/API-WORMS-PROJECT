#include "TimeManager.h"

CTimeManager::CTimeManager()
	: Start(chrono::system_clock::now())
	, End(chrono::system_clock::now())
	, Time(0)
	, Accel(1)
{
}

CTimeManager::~CTimeManager()
{
}

void CTimeManager::Set()
{
	End = chrono::system_clock::now();
	Time = End - Start;
	Start = End;
}

double CTimeManager::Delta() const
{
	return Time.count() * Accel;
}
