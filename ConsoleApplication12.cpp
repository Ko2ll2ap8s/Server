#include <Windows.h>
#include <conio.h>
#include <iostream>

using namespace std;
int main()
{
	HANDLE hReadFloat, hReadText;
	char IpszReadFloat[] = "ReadFloat";
	char IpszReadText[] = "ReadText";

	hReadFloat = CreateEvent(NULL, FALSE, FALSE, IpszReadFloat);
	hReadText = CreateEvent(NULL, FALSE, FALSE, IpszReadText);

	for (int i = 0; i < 5; ++i)
	{
		int nData;
		cin >> nData;
		_cprintf("The number %d is read from the pipe.\n", nData);
	}

	SetEvent(hReadFloat);
	for (int j = 0; j < 5; ++j)
	{
		Sleep(500);
		cout << (j * 0.1) << endl;
	}
	WaitForSingleObject(hReadText, INFINITE);
	_cputs("The process read the text: ");

	char IpszInput[80];
	do
	{
		Sleep(500);
		cin >> IpszInput;
		_cputs(IpszInput);
		_cputs(" ");
	} while (*IpszInput != '\0');
	_cputs("\nThe process finished transmission of data.\n");
	_cputs("Press any key to exit.\n");
	_getch();
	CloseHandle(hReadFloat);
	CloseHandle(hReadFloat);
	return 0;
}