struct DriveInfo
{
	char Name[5]{};
	char Type[12]{};
	char Label[32]{};
	char FileSystem[12]{};
	double TotalSpace = 0;
	double UsedSpace = 0;
	double FreeSpace = 0;
	bool IsReady = false;
};