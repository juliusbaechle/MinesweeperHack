#include <windows.h>
#include <iostream>

DWORD WINAPI MyThread(LPVOID);
DWORD g_threadID;
HMODULE g_hModule;

void gameFinished(int a_won) {
  typedef void (*__stdcall pFunctionAddress)(int);
  pFunctionAddress pMySecretFunction = (pFunctionAddress)(0x0100347c);
  pMySecretFunction(a_won);
}

DWORD WINAPI MyThread(LPVOID) {
  int myInt = 1;
  while (true) {
    if (GetAsyncKeyState(VK_NUMPAD1) & 1)
      gameFinished(1);
    else if (GetAsyncKeyState(VK_NUMPAD2) & 1)
      break;
    Sleep(100);
  }
  FreeLibraryAndExitThread(g_hModule, 0);
  return 0;
}

INT APIENTRY DllMain(HMODULE hDLL, DWORD Reason, LPVOID Reserved) {
  switch (Reason) {
  case DLL_PROCESS_ATTACH:
    g_hModule = hDLL;
    DisableThreadLibraryCalls(hDLL);
    CreateThread(NULL, NULL, &MyThread, NULL, NULL, &g_threadID);
    break;
  case DLL_THREAD_ATTACH:
  case DLL_PROCESS_DETACH:
  case DLL_THREAD_DETACH:
    break;
  }
  return TRUE;
}