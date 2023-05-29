#pragma once
#include "DriveInfo.h"

class Drives
{
public:
	Drives();
	~Drives();
	DriveInfo operator[](int);
	DriveInfo At(int);
	int Size();

private:
	double _round(double, int);
	DriveInfo* _drives;
	int _size;
	void _error(const char*);
	void _initialyze();
};
