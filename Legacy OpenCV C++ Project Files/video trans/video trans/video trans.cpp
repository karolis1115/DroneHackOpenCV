// video trans.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <conio.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#pragma comment(lib, "Ws2_32.lib")
WSADATA wsaData;
using namespace std;

unsigned char* hexstr_to_char(const char* hexstr) {
	size_t len = strlen(hexstr);
	if (len % 2 != 0)
		return NULL;
	size_t final_len = len / 2;
	unsigned char* chrs = (unsigned char*)malloc((final_len + 1) * sizeof(*chrs));
	for (size_t i = 0, j = 0; j < final_len; i += 2, j++)
		chrs[j] = (hexstr[i] % 32 + 9) % 25 * 16 + (hexstr[i + 1] % 32 + 9) % 25;
	chrs[final_len] = '\0';
	return chrs;
}

int main()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct addrinfo* result2 = NULL, * ptr2 = NULL, hints2;
	ZeroMemory(&hints2, sizeof(hints2));
	hints2.ai_family = AF_INET;
	hints2.ai_socktype = SOCK_STREAM;
	hints2.ai_protocol = IPPROTO_TCP;
	getaddrinfo("172.16.10.1", "8888", &hints2, &result2);
	SOCKET ConnectSocket2 = INVALID_SOCKET;
	ptr2 = result2;
	ConnectSocket2 = socket(ptr2->ai_family, ptr2->ai_socktype, ptr2->ai_protocol);
	connect(ConnectSocket2, ptr2->ai_addr, (int)ptr2->ai_addrlen);
	ofstream fg("dat.bin", std::ios::binary | std::ios::out | std::ios::trunc);
	const char* sendbuf = "000102030405060708092828";
	int recvbuflen = 1024;
	char recvbuf[1024];
	cout << "loop begin";
	send(ConnectSocket2, (char*)hexstr_to_char(sendbuf), (int)strlen(sendbuf), 0);
	while (1) {
		send(ConnectSocket2,(char*)hexstr_to_char(sendbuf),(int)strlen(sendbuf), 0);
		recv(ConnectSocket2,(char*)recvbuf, recvbuflen, 0);
		fg.write(recvbuf, 1024);
		Sleep(20);
	}
}
