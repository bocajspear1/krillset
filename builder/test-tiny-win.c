#include <stdio.h>
#include <stdlib.h>
#include "win-shared.h"
#include "windows.h"


void second_thread() {
    // Writing registry 1
    int result = registry_user_set_str("Software\\Microsoft\\Windows\\CurrentVersion\\Run", "test2", "mshta.exe stuff.hta");
    printf("Registry 2 result is %d\n", result);
}

int main() {

    HANDLE threadHandle = CreateThread(NULL, 0, second_thread, NULL, CREATE_SUSPENDED, NULL);

    ResumeThread(threadHandle);
    
    // Writing registry 1
    int result = registry_user_set_str("Software\\Microsoft\\Windows\\CurrentVersion\\Run", "test1", "mshta.exe stuff.hta");
    printf("Registry 1 result is %d\n", result);

    WaitForSingleObject(threadHandle, INFINITE);

    return 0;
}

