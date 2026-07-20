#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <thread> // c++에서는 thread , c에서는 thread.h

#include "udp_server_client.h"

#pragma comment(lib, "ws2_32.lib")

#define MAX 512

int udp_received = 0;

//struct sockaddr_in {
//	short sin_family;          // Address family (must be AF_INET)
//	u_short sin_port;          // Port number in Network Byte Order
//	struct in_addr sin_addr;   // 32-bit IPv4 address
//	char sin_zero[8];          // Padding to make it the same size as `struct sockaddr`
//};

void udpServer(char* portNumber)
{
	WSADATA wsaData; // window socket API
	//SOCKET s1 -> 파일 디스크립터를 이용
	SOCKET s1;  // window tcp/ip에 연결되는 소켓 -> unsigned int pointer
	struct sockaddr_in s1ServAddr, s1ClntAddr; // sockaddr_in -> port번호 + ipv4의 IP주소가 들어있다.
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
	// socket() : 윈도우/리눅스 TCP /IP stack에 연결하는 함수이다.
	// PF_INET == AF_INET 은 동일핟다( PF: protocoal family, af : adress family)
	// sock_dgram : udp, sock_stream :tcp, sock_raw: raw_socket
	// ipproto_udp : udp(6), ipproto_tcp : tcp(17)

	if ((s1 = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		fprintf(stderr, "socket 실패");
		WSACleanup();
		exit(1);
	}

	// 서버 주소 정보 초기화
	memset(&s1ServAddr, 0, sizeof(s1ServAddr)); //버퍼 크기만큼 0으로 초기화해준다.
	s1ServAddr.sin_family = AF_INET; //IPv4 사용
	s1ServAddr.sin_addr.s_addr = INADDR_ANY; //자동 할당
	s1ServAddr.sin_port = htons(atoi(portNumber)); //포트넘버

	//bind: 소켓에 주소정보 할당
	// s1 socket 번호와 s1servaddr(포트, 아이피) 정보를 윈도우/리눅스 TCP/IP 스택에 연결하는 함수
	//파이썬 , c#은 bind나 recv를 묶어버려서 server랑 client로 쉽게 사용 가능
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
		//printf("recv : %s\n", buf);

		udp_received = 1;
	}

}

SOCKET s1;
char buf[MAX] = "\0"; //메세지를 받을 공간
struct sockaddr_in s1ServAddr;
int count = 0;

void udpClient(char* IPaddress, char* portNumber) //htons로 바꾸기? 
{
	WSADATA wsaData;
//	SOCKET s1;
//	struct sockaddr_in s1ServAddr;
//	char buf[MAX] = "\0"; //메세지를 받을 공간
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

	//int count = 0;
	//while (1)
	//{
	//	sprintf(buf, "haha = %d", count++); //sprintf -> 문자열 구성 자체를 buf에 넣는다.
	//	sendto(s1, buf, MAX, 0, (struct sockaddr*)&s1ServAddr, sizeof(s1ServAddr));

	//	printf("sent : %s \n", buf);

	//	Sleep(1000);
	//}

	//send to -> while문을 막아서 한줄 없애면 쏘겠다는 걸로 변경 
}

void udp_data_send(){ // while문 -> sendto를 대신하는 함수
	
	//sprintf(buf, "haha = %d", count++); //sprintf -> 문자열 구성 자체를 buf에 넣는다.
	sprintf(buf, "i");
	int buf_length = strlen(buf);
	sendto(s1, buf, buf_length, 0, (struct sockaddr*)&s1ServAddr, sizeof(s1ServAddr));
}

int count_thread;
void thread_func()
{
	while (1) {
		printf("haha(thread) = %d \n", count_thread++);
		printf("haha(thread) = %d \n", count_thread++);
		Sleep(1000);
	}
}

void udp_server_func()
{
	printf("UDP server start!\n");
	//3000번 포트로 while(1)을 이용해서 계속해서 recvfrom()함수를 실행한다.
	// recvfrom() 함수: udp 3000번 포트로 데이터가 들어올 때 까지 대기한다.(블락킹 됨)
	udpServer((char*)"3000");
}


//void main()
//{
//	//---------------------------
//	// thread : 클래스로써 스레드 관련 객체화 클래스이다.
//	// std::thread t(thread_func);  //t는 스레드 변수
//
//	//뮤텍스 사용해서 락 걸어놓음 .-> 스레드 사용중에 다른 스레드는 점유할 수 없다.
//	// 
//	// 
//	std::thread t(udp_server_func);
//	//printf("C + UDP SERVER\n");
//	//udpServer((char*)"3000");
//	//---------------------------
//	printf("C + UDP CLIENT\n");
//	//127.0.0.1 : 자기 아이피로 3000번 포트로 데이터를 보낸다 .
//	udpClient((char*)"127.0.0.1", (char*)"3000");
//	//---------------------------
//}