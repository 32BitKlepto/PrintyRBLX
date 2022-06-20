#include <Windows.h>
#include <iostream>
#include <istream>
#include <string>


#define _CRT_SECURE_NO_WARNINGS


using namespace std;



namespace PrintExploit {
	namespace Integers {
		int OutputType = 0;
	}
}



int Address(int Offset) {
	return (Offset - 0x00400000 + (DWORD)GetModuleHandle("RobloxPlayerBeta.exe"));
}



typedef int(__cdecl* SINGLETON)(int a1, const char* a2);
SINGLETON SingletonPrint = (SINGLETON)Address(0x5fb7b0);


void ConsoleBypass() {
	DWORD CheckerValue;
	VirtualProtect((PVOID)& FreeConsole, 1, PAGE_EXECUTE_READWRITE, &CheckerValue);
	*(BYTE*)(&FreeConsole) = (0xC3);
}


void Console(const char* ConsoleTitle) {
	ConsoleBypass();
	AllocConsole();
	SetConsoleTitleA(ConsoleTitle);
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
	HWND ConsoleHandle = GetConsoleWindow();
	::SetWindowPos(ConsoleHandle, HWND_TOPMOST, 0, 0, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
	::ShowWindow(ConsoleHandle, SW_NORMAL);
}


void MainFunction() {
	Console("Print Exploit by Powerful");
	do {
		string OutputString = "";
		getline(cin, OutputString);
		SingletonPrint(PrintExploit::Integers::OutputType, OutputString.c_str());
	} while (true);
}


int __stdcall DllMain(HMODULE a, DWORD b, void* c) {
	if (b == 1) {
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainFunction, 0, 0, 0);
	}
	return TRUE;
}