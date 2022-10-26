#include <Windows.h>
#include <iostream>

DWORD  WINAPI DerivedA(LPVOID arg);
DWORD  WINAPI DerivedB(LPVOID arg);

int main() {
    HANDLE thread = CreateThread(
        0,
        0,
        DerivedB,
        &thread,
        0,
        0
    );

    WaitForSingleObject(thread, INFINITE);
}

DWORD  WINAPI DerivedA(LPVOID arg) {
    HANDLE thread = *static_cast<HANDLE*>(arg);
    for (DWORD i = 0; i < 10; i++) {
        std::cout << thread << " -> " << i << std::endl;
    }
    WaitForSingleObject(thread, INFINITE);
    return 0;
}

DWORD __stdcall DerivedB(LPVOID arg) {
    HANDLE thread = CreateThread(
        0,
        0,
        DerivedA,
        arg,
        0,
        0
    );
    WaitForSingleObject(thread, INFINITE);
    return 0;
}
