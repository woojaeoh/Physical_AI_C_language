#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#define MAX 512

void udpServer(char* portNumber)
{
	WSADATA wsaData;
	SOCKET s1;
	struct sockaddr_in s1ServAddr, s1ClntAddr;
	char buf[MAX] = "\0"; //메세지를 받을 공간
	int s1len = sizeof(s1ClntAddr);

	/** WSAStartup: winsock 초기화,
	프로그램에서 요구하는 winsock 버전을 명시하고 라이브러리 초기화 진행**/

	//MAKEWORD(2,2): 윈도우 소켓 버전 명시 winsock 버전 2.2
	//wsaData 가 0이면 성공, 0이 아닐시 실패
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup 실패");
		exit(1);
	}

	/* PF_INET: IPv4 protocol을 사용한다는 의미
	*  SOCK_DGRAM: UDP
	*/
	if ((s1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		fprintf(stderr, "socket 실패");
		WSACleanup();
		exit(1);
	}

	// 서버 주소 정보 초기화
	memset(&s1ServAddr, 0, sizeof(s1ServAddr));
	s1ServAddr.sin_family = AF_INET; //IPv4 사용
	s1ServAddr.sin_addr.s_addr = INADDR_ANY; //자동 할당
	s1ServAddr.sin_port = htons(atoi(portNumber)); //포트넘버

	//bind: 소켓에 주소정보 할당
	if (bind(s1, (struct sockaddr*)&s1ServAddr, sizeof(s1ServAddr)) == SOCKET_ERROR)
	{
		printf("bind 실패\n");
		WSACleanup();
		closesocket(s1);
		exit(1);
	}

	printf("bind 성공..\n");

	//메세지 받기
	while (1)
	{
		recvfrom(s1, buf, MAX, 0, (struct sockaddr*)&s1ClntAddr, &s1len);
		printf("recv : %s\n", buf);
	}

}

void udpClient(char* IPaddress, char* portNumber)
{
	WSADATA wsaData;
	SOCKET s1;
	struct sockaddr_in s1ServAddr;
	char buf[MAX] = "\0"; //메세지를 받을 공간
	int slen;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		fprintf(stderr, "WSAStartup() failed");
		exit(1);
	}

	if ((s1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		fprintf(stderr, "socket() failed");
		WSACleanup();
		exit(1);
	}

	memset(&s1ServAddr, 0, sizeof(s1ServAddr));
	s1ServAddr.sin_family = AF_INET;
	s1ServAddr.sin_addr.s_addr = inet_addr(IPaddress);
	s1ServAddr.sin_port = htons(atoi(portNumber));

	buf[0] = 'h';
	buf[1] = 'a';
	buf[2] = 'h';
	buf[3] = 'a';

	int count = 0;
	while (1)
	{
		sprintf(buf, "haha = %d", count++);
		sendto(s1, buf, MAX, 0, (struct sockaddr*)&s1ServAddr, sizeof(s1ServAddr));

		printf("sent : %s \n", buf);

		Sleep(1000);
	}

}



void main()
{
	//---------------------------
	//printf("C + UDP SERVER\n");
	//udpServer((char*)"3000");
	//---------------------------
	printf("C + UDP CLIENT\n");
	udpClient((char*)"127.0.0.1", (char*)"3000");
	//---------------------------
}