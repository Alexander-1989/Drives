#include <iostream>
#include <conio.h>
#include "Drives.h"
using namespace std;

int main()
{
	Drives drives;

	for (int i = 0; i <= drives.Size(); i++)
	{
		try
		{
			cout << "Name: " << drives[i].Name << endl;
			cout << "Label: " << drives[i].Label << endl;
			cout << "File System: " << drives[i].FileSystem << endl;
			cout << "Serial Number: " << drives[i].SerialNumber << endl;
			cout << "Type: " << drives[i].Type << endl;
			cout << "Ready: " << (drives[i].IsReady ? "True" : "False") << endl;
			cout << "Used Space: " << drives[i].UsedSpace << " Gb" << endl;
			cout << "Free Space: " << drives[i].FreeSpace << " Gb" << endl;
			cout << "Total Space: " << drives[i].TotalSpace << " Gb" << endl;
			cout << endl;
		}
		catch (const std::exception& exc)
		{
			cout << exc.what() << endl;
		}
	}

	(void)_getch();
	return 0;
}