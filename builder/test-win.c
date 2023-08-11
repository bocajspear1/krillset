#include <stdio.h>
#include <stdlib.h>
#include "win-shared.h"
#include "windows.h"



typedef void (WINAPI *PGNSI)(LPSYSTEM_INFO);


void second_thread() {
    // Connecting

    WSADATA wsaData = {0};
    SOCKET sock;
    int connstatus = net_connect(&wsaData, &sock, "192.168.122.198", 8080);
    if (connstatus == 0) {
        printf("Connect successful!\n");
        char senddata[] = "This is being sent on the network!";
        send(sock, senddata, strlen(senddata), 0);
    } else {
        printf("Connect failed!\n");
    }
    net_close(&wsaData, &sock);
}

int main() {
    FILE * f;
    char buffer[1035];

    // List of Macros/defines here: https://sourceforge.net/p/predef/wiki/Architectures/
#if defined(__amd64__)
    printf("Hello there from x86-64\n");   
#elif defined(__i386__)
    printf("Hello there from i386\n");       
#endif 

    HANDLE threadHandle = CreateThread(NULL, 0, second_thread, NULL, CREATE_SUSPENDED, NULL);

    ResumeThread(threadHandle);

    // Running commands
    printf("Running popen\n"); 
    f = popen("dir c:\\", "r");

    if (f == NULL) {
        printf("Command failed\n");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        printf("%s", buffer);
    }

    pclose(f);
    printf("Finishing popen\n");

    
    
    // Writing registry

    int result = registry_user_set_str("Software\\Microsoft\\Windows\\CurrentVersion\\Run", "bookmarks", "mshta.exe stuff.hta");
    printf("Result is %d\n", result);

    // Writing files

    printf("Writing file\n");

    f = fopen("C:\\test.txt", "w+");

    if (f == NULL) {
        printf("File open failed failed\n");
    } else {
        fputs("Put in file data\n", f);
        fputs("Put in more file data\n", f);

        fclose(f);

        printf("Finished writing file\n");
    }


    // GetProcAddress
    // Got from https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress
    PGNSI pGNSI;
    SYSTEM_INFO si;

    ZeroMemory(&si, sizeof(SYSTEM_INFO));
    
    pGNSI = (PGNSI) GetProcAddress(GetModuleHandle(TEXT("kernel32.dll")), "GetNativeSystemInfo");
    if (NULL != pGNSI) {
        pGNSI(&si);
    }

    WaitForSingleObject(threadHandle, INFINITE);

    system("C:\\Windows\\system32\\notepad.exe");

    return 0;
}

