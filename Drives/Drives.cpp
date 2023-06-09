#pragma once
#include <iostream>
#include <Windows.h>
#include "Drives.h"

Drives::Drives()
{
	_initialyze();
}

Drives::~Drives()
{
	if (_drives)
	{
		delete[] _drives;
	}
}

double Drives::_round(double value, int precision)
{
	int decimal = (int)std::pow(10, precision);
	return floor(value * decimal) / decimal;
}

inline void Drives::_error(const char* message)
{
	throw std::runtime_error(message);
}

DriveInfo Drives::operator[](int index)
{
	if (index < 0 || index >= _size)
	{
		_error("Index out of range");
	}
	return _drives[index];
}

DriveInfo Drives::At(int index)
{
	return operator[](index);
}

int Drives::Size()
{
	return _size;
}

void Drives::_initialyze()
{
	UINT type = 0;
	UINT64 total = 0;
	UINT64 free = 0;
	DWORD dr = GetLogicalDrives();
	char buffer[26]{};
	char name[4] = "*:\\";
	const char* driveTypes[] =
	{
		"Unknown",
		"No root dir",
		"Removable",
		"Fixed",
		"Remote",
		"CD-Rom",
		"Ramdisk"
	};

	for (int i = 0; dr >> i; i++)
	{
		if ((dr >> i) & 1)
		{
			buffer[_size++] = 'A' + i;
		}
	}

	_drives = new DriveInfo[_size];

	for (int j = 0; j < _size; j++)
	{
		name[0] = buffer[j];
		type = GetDriveTypeA(name);
		_drives[j].IsReady = GetFileAttributesA(name) != INVALID_FILE_ATTRIBUTES;

		strcpy_s(_drives[j].Name, name);
		strcpy_s(_drives[j].Type, driveTypes[type]);
		total = 0;
		free = 0;

		if (type == DRIVE_REMOVABLE || type == DRIVE_FIXED || type == DRIVE_REMOTE)
		{
			GetVolumeInformationA(name, _drives[j].Label, sizeof(_drives[j].Label), &_drives[j].SerialNumber, 0, 0, _drives[j].FileSystem, sizeof(_drives[j].FileSystem));
		}

		if (_drives[j].IsReady)
		{
			if (GetDiskFreeSpaceExA(name, 0, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free))
			{
				_drives[j].TotalSpace = _round(total / std::pow(1024, 3), 2);
				_drives[j].FreeSpace = _round(free / std::pow(1024, 3), 2);
				_drives[j].UsedSpace = _round((total - free) / std::pow(1024, 3), 2);
			}
		}
	}
}