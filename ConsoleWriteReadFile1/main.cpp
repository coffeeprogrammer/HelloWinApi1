#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

struct Sample {
	int sample_id;
	int number;
	char wordone[32];
	char wordtwo[32];
};

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE hFile;

	wprintf(L"win32 console read write file");

	hFile = CreateFile(L"P:\\temp\\testfile",
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ,
		NULL,
		//CREATE_NEW,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		wprintf(L"error");
		DWORD error = GetLastError();
		wprintf(L"error");
	}




	struct Sample sampleds1;
	sampleds1.sample_id = 1;

	strcpy_s(sampleds1.wordone, "salad");
	//sampleds1.wordone = "salad";
	strcpy_s(sampleds1.wordtwo, "elevator");
	sampleds1.number = 2022;

	DWORD dwBytesWritten = 0;
	//wprintf(sampleds1.wordone);
	int size = sizeof(Sample);
	int size2 = sizeof(sampleds1);

	//WriteFile(hFile, &sampleds1, sizeof(sampleds1), &dwBytesWritten, NULL);

	DWORD dwFileSize;
	DWORD dwBytesRead;
	struct Sample sampleds2;

	dwFileSize = GetFileSize(hFile, NULL);

	ReadFile(hFile, &sampleds2, dwFileSize, &dwBytesRead, NULL);

	printf(sampleds2.wordone);
	printf(sampleds2.wordtwo);

	CloseHandle(hFile);

	return 0;
}
