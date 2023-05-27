#include <iostream>
#include <conio.h>
#include "Drives.h"
using namespace std;

int main()
{
	Drives drives;
	
	for (int i = 0; i < drives.Size(); i++)
	{
		cout << "Name: " << drives[i].Name << endl;
		cout << "Label: " << drives[i].Label << endl;
		cout << "File System: " << drives[i].FileSystem << endl;
		cout << "Type: " << drives[i].Type << endl;
		cout << "Ready: " << drives[i].IsReady << endl;
		cout << "Used Space: " << drives[i].UsedSpace << endl;
		cout << "Free Space: " << drives[i].FreeSpace << endl;
		cout << "Total Space: " << drives[i].TotalSpace << endl;
		cout << endl;
	}

	int index = 0;

	try
	{
		cout << drives[index].Name << endl;
	}
	catch (exception& exc)
	{
		cout << exc.what() << endl;
	}

	try
	{
		cout << drives.At(index).Name << endl;
	}
	catch (exception& exc)
	{
		cout << exc.what() << endl;
	}

	index = 25;

	try
	{
		cout << drives[index].Name << endl;
	}
	catch (exception& exc)
	{
		cout << exc.what() << endl;
	}

	try
	{
		cout << drives.At(index).Name << endl;
	}
	catch (exception& exc)
	{
		cout << exc.what() << endl;
	}

	(void)_getch();
	return 0;
}