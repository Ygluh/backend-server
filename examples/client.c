#include <stdio.h>
#include <string.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define HOST "127.0.0.1"
#define PORT 9090
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("[C-CLIENT] WSAStartup failed\n");
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        printf("[C-CLIENT] Socket creation failed\n");
        WSACleanup();
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(HOST);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        printf("[C-CLIENT] Connection failed\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("[C-CLIENT] Connected to %s:%d\n", HOST, PORT);

    const char* message = "Hello from C!";
    send(sock, message, (int)strlen(message), 0);
    printf("[C-CLIENT] Sent: %s\n", message);

    int bytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
    if (bytes > 0) {
        buffer[bytes] = '\0';
        printf("[C-CLIENT] Received: %s\n", buffer);
    }

    closesocket(sock);
    WSACleanup();
    printf("[C-CLIENT] Done.\n");
    return 0;
}
