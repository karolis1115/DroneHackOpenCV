// drone send test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
WSADATA wsaData;


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

void datatrans() {
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	 getaddrinfo("172.16.10.1", "8080", &hints, &result);
	SOCKET ConnectSocket = INVALID_SOCKET;
	ptr = result;
	ConnectSocket = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	char IDLE[23] =     "ff08003f403f1010100009";
	char ALT_HOLD[23] = "ff087e3f403f901010000b";
	char ARM[23] =      "ff087e3f403f90101040cb";
	char LAND[23] =     "ff087e3f403f901010808b";
	char LEFT[23] =     "ff087e3f4000901010004a";
	char RIGHT[23] =    "ff087e3f407e90101000cc";
	char FD[23] =       "ff087e3f01409010100049";
	char BCK[23] =      "ff087e3f7f4090101000cb";
	char UP[23] =       "ff08fc3f403f901010008d";
	char DOWN[23] =     "ff080040403f9010104048";
	char E_STOP[23] =   "ff087e3f403f901010a06b";
	char Yaw_R[23] =    "ff087e7e403f90101000cc";
	char Yaw_L[23] =    "ff087e00403f901010004a";
	while(1) {
		if (GetAsyncKeyState(VK_OEM_COMMA))  send(ConnectSocket, (char*)hexstr_to_char(ARM), (int)strlen(ARM), 0);
	    if (GetAsyncKeyState(VK_RETURN)) send(ConnectSocket, (char*)hexstr_to_char(LAND), (int)strlen(LAND), 0);
	    if (GetAsyncKeyState(VK_LEFT)) send(ConnectSocket, (char*)hexstr_to_char(LEFT), (int)strlen(LEFT), 0);
		if (GetAsyncKeyState(VK_RIGHT)) send(ConnectSocket, (char*)hexstr_to_char(RIGHT), (int)strlen(RIGHT), 0);
		if (GetAsyncKeyState(VK_DOWN)) send(ConnectSocket, (char*)hexstr_to_char(BCK), (int)strlen(BCK), 0);
		if (GetAsyncKeyState(VK_UP)) send(ConnectSocket, (char*)hexstr_to_char(FD), (int)strlen(FD), 0);
		if (GetAsyncKeyState(0x57)) send(ConnectSocket, (char*)hexstr_to_char(UP), (int)strlen(UP), 0);
		if (GetAsyncKeyState(0x53)) send(ConnectSocket, (char*)hexstr_to_char(DOWN), (int)strlen(DOWN), 0);
		if (GetAsyncKeyState(VK_SPACE)) send(ConnectSocket, (char*)hexstr_to_char(E_STOP), (int)strlen(E_STOP), 0);
		if (GetAsyncKeyState(0x41)) send(ConnectSocket, (char*)hexstr_to_char(Yaw_L), (int)strlen(Yaw_L), 0);
		if (GetAsyncKeyState(0x44)) send(ConnectSocket, (char*)hexstr_to_char(Yaw_R), (int)strlen(Yaw_R), 0);
		else send(ConnectSocket, (char*)hexstr_to_char(ALT_HOLD), (int)strlen(ALT_HOLD), 0);
		Sleep(5);
	}
}

int main()
{
	datatrans();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
