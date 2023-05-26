#pragma once
#include <Windows.h>

struct drive
{
	char Name[5]{};
	char Type[12]{};
	char Label[32]{};
	char FileSystem[12]{};
	double TotalSpace = 0;
	double UsedSpace = 0;
	double FreeSpace = 0;
	bool IsReady = 0;
};

class Drives
{
public:
	Drives();
	~Drives();
	drive operator[](int);
	drive At(int);
	int Size();

private:
	double _round(const double&);
	drive* _drive;
	int _size;
	void _error(const char*);
	void _initialyze();
};

Drives::Drives()
{
	_initialyze();
}

Drives::~Drives()
{
	if (_drive)
	{
		delete[] _drive;
	}
}

double Drives::_round(const double& value)
{
	return floor(value * 100) / 100;
}

inline void Drives::_error(const char* message)
{
	throw std::runtime_error(message);
}


drive Drives::operator[](int index)
{
	if (index < 0 || index >= _size)
	{
		_error("Index out of range");
	}
	return _drive[index];
}

drive Drives::At(int index)
{
	if (index < 0 || index >= _size)
	{
		_error("Index out of range");
	}
	return _drive[index];
}

int Drives::Size()
{
	return _size;
}

void Drives::_initialyze()
{
	char buffer[26]{};
	char label[32]{};
	char fileSystem[12]{};
	char name[5] = "*:\\";
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
	UINT type = 0;
	UINT64 total = 0;
	UINT64 free = 0;
	DWORD dr = GetLogicalDrives();

	for (int i = 0; dr >> i; i++)
	{
		if ((dr >> i) & 1)
		{
			buffer[_size++] = 'A' + i;
		}
	}

	_drive = new drive[_size];

	for (int j = 0; j < _size; j++)
	{
		UINT oldErrorMode = SetErrorMode(SEM_FAILCRITICALERRORS);
		name[0] = buffer[j];
		type = GetDriveType(name);
		_drive[j].IsReady = GetFileAttributes(name) != INVALID_FILE_ATTRIBUTES;
		SetErrorMode(oldErrorMode);

		strcpy_s(_drive[j].Name, name);
		strcpy_s(_drive[j].Type, driveTypes[type]);
		total = 0;
		free = 0;

		if (type == DRIVE_REMOVABLE || type == DRIVE_FIXED || type == DRIVE_REMOTE)
		{
			if (GetVolumeInformation(name, label, sizeof(label), 0, 0, 0, fileSystem, sizeof(fileSystem)))
			{
				strcpy_s(_drive[j].Label, label);
				strcpy_s(_drive[j].FileSystem, fileSystem);
			}

			if (GetDiskFreeSpaceEx(name, 0, (PULARGE_INTEGER)&total, (PULARGE_INTEGER)&free))
			{
				_drive[j].TotalSpace = _round(total / std::pow(1024, 3));
				_drive[j].FreeSpace = _round(free / std::pow(1024, 3));
				_drive[j].UsedSpace = _drive[j].TotalSpace - _drive[j].FreeSpace;
			}
		}
	}
}