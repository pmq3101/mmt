#include <iostream>
#include <winsock2.h>
#include <string>
#pragma comment(lib,"ws2_32.lib")

using namespace std;

string num_to_text(int num)
{
    // Hàm chuyển đổi số thành chữ
    // Ở đây sử dụng một số ví dụ đơn giản

    string text = "";
    string digit[] = { "không", "một", "hai", "ba", "bốn", "năm", "sáu", "bảy", "tám", "chín" };
    string unit[] = { "", "nghìn", "triệu", "tỷ" };
    int i = 0;

    do {
        int n = num % 1000;
        if (n > 0) {
            if (n < 10) text = digit[n] + " " + unit[i] + " " + text;
            else if (n < 100) text = digit[n / 10] + " mươi " + digit[n % 10] + " " + unit[i] + " " + text;
            else text = digit[n / 100] + " trăm " + digit[(n % 100) / 10] + " mươi " + digit[n % 10] + " " + unit[i] + " " + text;
        }
        num /= 1000;
        i++;
    } while (num > 0);

    return text;
}

int main()
{
    // Khởi tạo Winsock
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Tạo socket
    SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Bind socket với địa chỉ IP và cổng
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

    // Lắng nghe kết nối từ client
    listen(listenSocket, SOMAXCONN);
    cout << "Server is listening..." << endl;

    // Chấp nhận kết nối từ client
    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    SOCKET clientSocket = accept(listenSocket, (SOCKADDR*)&clientAddr, &clientAddrLen);
    cout << "Client connected" << endl;

    // Nhận số từ client và gửi lại số chữ cho client
    int num;
    recv(clientSocket, (char*)&num, sizeof(num), 0);
    string text = num_to_text(num);
    send(clientSocket, text.c_str(), text.length() + 1, 0);

    // Đóng kết nối
    closesocket(clientSocket);
    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
