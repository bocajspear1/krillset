
#include <winsock2.h>
#include <ws2tcpip.h>
#include "windows.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

int net_connect(WSADATA* wsaData, SOCKET* my_sock, char* dest, uint16_t port) {
    struct addrinfo hints;
    struct addrinfo * getres;

    int result = WSAStartup(MAKEWORD(2,2), wsaData);
    if (result != 0) {
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    char portBuf[8] = {0};

    itoa(port, portBuf, 10);

    result = getaddrinfo(dest, portBuf, &hints, &getres);
    if (result != 0) {
        WSACleanup();
        return 2;
    }

    for (struct addrinfo * ptr = getres; ptr != NULL; ptr = ptr->ai_next) {
        *my_sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (*my_sock == INVALID_SOCKET) {
            WSACleanup();
            return 3;
        }

        result = connect(*my_sock, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (result == SOCKET_ERROR) {
            closesocket(*my_sock);
            *my_sock = INVALID_SOCKET;
            continue;
        } 
        break;
    }

    freeaddrinfo(getres);
    if (*my_sock == INVALID_SOCKET) {
        return 4;
    }
    return 0;
}

void net_close(WSADATA* wsaData, SOCKET* sock) {
    shutdown(*sock, SD_SEND);
    closesocket(*sock);
    WSACleanup();
}

int registry_user_set_str(char * regpath, char * keyname, char * charvalue) {
    LSTATUS status;
    HKEY key;
    status = RegOpenKeyExA(HKEY_CURRENT_USER, regpath, 0, KEY_WRITE, &key);
    if (status == ERROR_SUCCESS) {
        int datalen = strnlen(charvalue, 400);
        status = RegSetValueExA(key, keyname, 0, REG_SZ, charvalue, datalen);
        if (status == ERROR_SUCCESS) {
            return 0;
        } else {
            printf("RegSetValueExA failed with %lu\n", status);
            return 2;
        }
    } else {
        printf("RegOpenKeyExA failed with %lu\n", status);
        return 1;
    }
}