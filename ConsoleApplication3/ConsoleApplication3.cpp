#include <Windows.h>
#include <conio.h>
int main()
{
	char IpszComLine1[82] = "C:\\Users\\alena\\source\\repos\\ConsoleApplication1\\x64\\Debug\\ConsoleApplication1.exe";
	char IpszComLine2[82] = "C:\\Users\\alena\\source\\repos\\ConsoleApplication2\\x64\\Debug\\ConsoleApplication2.exe";
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	HANDLE hWritePipe, hReadPipe;
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	if (!CreatePipe(
		&hReadPipe,
		&hWritePipe,
		&sa,
		0))

	{
		_cputs("Create pipe faoled.\n");
		_cputs("Press any key to finish.\n");
		_getch();
		return GetLastError();
	}

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hReadPipe;
	si.hStdOutput = hWritePipe;
	si.hStdError = hWritePipe;

	if (!CreateProcess(
		NULL,
		IpszComLine1,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	)
		)
	{
		_cputs("Create process failed.\n");
		_cputs("Press any key to finish.\n");
		_getche();
		return GetLastError();
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	if (!CreateProcess(
		NULL,
		IpszComLine2,
		NULL,
		NULL,
		TRUE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi
	)
		)
	{
		_cputs("Create process failed.\n");
		_cputs("Press any key to finish.\n");
		_getche();
		return GetLastError();
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	CloseHandle(hReadPipe);
	CloseHandle(hWritePipe);
	_cputs("The clients are created.\n");
	_cputs("Press any key to exit.\n");
	_getch();
	return 0;

}