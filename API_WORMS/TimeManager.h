#pragma once

#include "Manager.h"

class CTimeManager : public CManager<CTimeManager>
{
private :
	chrono::system_clock::time_point Start;
	chrono::system_clock::time_point End;
	chrono::duration<double> Time;
	double Accel;
public :
	CTimeManager();
	~CTimeManager();
public :
	void SetAccel(double acc) { Accel = acc; }
	void Set();
	double Delta() const;
	double RealTime() const { return Time.count(); }
};

