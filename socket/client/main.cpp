#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
    // Khởi tạo Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Tạo socket
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Địa chỉ của server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Kết nối đến server
    connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    cout << "Connected to server" << endl;

    // Nhập số nguyên và gửi đến server
    int num;
    cout << "Enter an integer less than 1 billion: ";
    cin >> num;
    send(clientSocket, (char*)&num, sizeof(num), 0);

    // Nhận chữ số tiếng Việt từ server và hiển thị
    char buffer[1024];
    recv(clientSocket, buffer, sizeof(buffer), 0);
    cout << "You received: " << buffer << endl;

    // Đóng socket và giải phóng Winsock
    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
