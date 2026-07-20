#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")


#define DEST_IP "172.30.1.25"
#define SOURCE_IP "172.30.1.90"
#define DEST_PORT 3000
#define SOURCE_PORT 3000
#define PACKET_LEN 1500

void send_raw_ip_packet(char* buff, int buff_len);
int buff_init();

char sendbuff[PACKET_LEN];


// IP Header
struct ipheader
{
    unsigned char iph_ihl : 4, iph_ver : 4; // IP header length, // IP version
    unsigned char iph_tos;           // Type of service
    unsigned short int iph_len;      // IP Packet length (data + header)
    unsigned short int iph_ident;    // Identification
    unsigned short int iph_flag : 3, // Fragmentation flags
        iph_offset : 13;             // Flags offset
    unsigned char iph_ttl;           // Time to Live
    unsigned char iph_protocol;      // Protocol type
    unsigned short int iph_chksum;   // IP datagram checksum
    struct in_addr iph_sourceip;     // Source IP address
    struct in_addr iph_destip;       // Destination IP address
};

struct udpheader
{
    u_short udp_sport; // source port
    u_short udp_dport; // destination port
    u_short total_length;
    u_short udp_sum; // checksum
};




int main()
{
    WORD wVersionRequested;
    WSADATA wsaData;

    wVersionRequested = MAKEWORD(1, 1);

    WSAStartup(wVersionRequested, &wsaData);

    //-----------------------------------
    int data_len = buff_init();
    //-----------------------------------------------------------------
    send_raw_ip_packet(sendbuff, data_len);
    //-----------------------------------------------------------------

    WSACleanup();
}


//int main(void) {
//
//    WORD wVersionRequested;
//    WSADATA wsaData;
//
//    wVersionRequested = MAKEWORD(1, 1);
//
//    WSAStartup(wVersionRequested, &wsaData);
//
//    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);
//
//    char message[64];
//
//    if (sockfd < 0) {
//        perror("Error creating socket");
//        exit(1);
//    }
//
//    struct sockaddr_in sock_in;
//    sock_in.sin_family = AF_INET;
//    sock_in.sin_port = htons(3000);
//    sock_in.sin_addr.s_addr = INADDR_ANY;
//
//    if (bind(sockfd, (struct sockaddr*)&sock_in, sizeof(sock_in)) < 0) {
//        printf("Bind failed\n");
//        exit(1);
//    }
//
//    if (recv(sockfd, message, 64, 0) < 0) {
//        perror("Error");
//        exit(1);
//    }
//
//    printf("\n\n%s\n\n", message);
//
//    closesocket(sockfd);
//
//    WSACleanup();
//
//    return 0;
//}



void send_raw_ip_packet(char* buff, int buff_len)
{
    struct sockaddr_in dest_info;
    int enable = 1;

    //-----------------------------------------------------------------
    // Step 1: Create a raw network socket.
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_RAW); //window tcp/ip 스택에 등록됨. , sock -> 파일디스크립터
    // int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0)
    {
        printf("socket failed: %d\n", WSAGetLastError());
        return;
    }

    printf("raw socket opened\n");

    //-----------------------------------------------------------------
    // Step 2: Set socket option.
    int result = setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (const char*)&enable, sizeof(enable)); //내가 헤더를 만들면서 핸들링하겠다.
    if (sock < 0)
    {
        printf("setsockopt failed: %d\n", WSAGetLastError());
        return;
    }

    //-----------------------------------------------------------------
    // Step 3: Provide needed information about destination.
    dest_info.sin_family = AF_INET; //ip프로토콜  관련된 패킷이라는걸 알려줌 -> 몇가지 정보를 직접 넣어야 함 .

    //-----------------------------------------------------------------
    // Step 4: Send the packet out.
    while (1)
    {
        /*result = sendto(sock, (const char*)ip, ntohs(ip->iph_len), 0, (struct sockaddr*)&dest_info, sizeof(dest_info));*/
        result = sendto(sock, (const char*)buff, buff_len, 0, (struct sockaddr*)&dest_info, sizeof(dest_info)); // sock이라는 파일 디스크립트를 넣고, 
        printf("sendto: %d\n", result);

        Sleep(1000);
    }

    //-----------------------------------------------------------------

    closesocket(sock);
}

// unsigned short*로 감싸줘서 포인터의 격을 맞춘다.
// 
// checksum(), 함수 인자 (unsigned short * buff) 는
// 처음 선언에 char buff[]라는 배열로 선언했지만
// unsigned short* buff 라고 하면 2 byte 단위(u_short)의 포인터로 캐스팅을 한다.
// 그렇게 되면 1 byte 가 아니라 2 byte 단위로 주소가 증가되게 된다.
unsigned short checksum(unsigned short* buff, int len_16) // 2바이트 단위인 buff를 제어하겟다?
{
    unsigned long sum = 0;

    for (int i = 0; i < len_16; i++)
    {   
        // *(buff)++ : buff는 2byte 단위의 포인터인데
        //  ++ 해서 하나씩 증가시키는 의미는 포인터를 하나씩 증가시키는 것이다 .
        // 즉 주소를 하나씩 증가시키는데 메모리 공간은 2 byte씩 증가되게 된다.
        // buff++(포인터 증가)를 해서 별(*)을 붙여서 값을 가져온다.
        // htons() : h(host) --> to -> n (network)로의 변환이다 .
        // host(PC : Littele Endian) , network(Big endian)

        sum += htons(*(buff)++); //주소가 하나씩 증가 ->데이터는 2바이트씩 증가.
    }
    //2 바이트씩 다 더한다.

    do 
    {
        sum = ((sum >> 16) + (sum & 0xFFFF));
    } while (sum & 0xFFFF0000);

    return (~sum);
}



int buff_init()
{
    int udp_data_len = 4;

    memset(sendbuff, 0, PACKET_LEN);
    //sendbuff : CHAR 타입의 1500바이트 길이의 배열.
    // ip_header_p = (struct ipheader*)포인터인데, struct ipheader 타입의 주소를 담는 변수이다.
    //그래ㅓ서 1byte씩 사용할 수 잇는 sendbuff 에서, struct ipheader 구조체 멤버 변수를 그대로 사용할 수 있다.
    struct ipheader* ip_header_p = (struct ipheader*)sendbuff;
    //sendbuff + sizeof(struct ipheader) : sendbuff자체는 배열의 주소인데,
    // 그 주소에 (struct ipheader) 구조체 크기를 더한 위치가 udp header가 들어갈 주소이다.
    struct udpheader* udp_header_p = (struct udpheader *)(sendbuff + sizeof(struct ipheader));

    //udp_data 주소를 가리키고 , (char *)를 캐스팅해서 그대로 udp_data 변수의 포인터로 이용한다 ,
    char* udp_data = (char*)(sendbuff + sizeof(struct ipheader) + sizeof(struct udpheader));
    int ip_total_length = sizeof(struct ipheader) + sizeof(struct udpheader) + udp_data_len;

    //IP Header

    ip_header_p->iph_ver = 4;
    ip_header_p->iph_ihl = 5;
    ip_header_p->iph_tos = 0;
    ip_header_p->iph_len = ip_total_length;
    ip_header_p->iph_ident = 0;
    ip_header_p->iph_flag = 0;
    ip_header_p->iph_offset = 0;
    ip_header_p->iph_ttl = 64;
    ip_header_p->iph_protocol = IPPROTO_UDP;
    ip_header_p->iph_chksum = 0;
    ip_header_p->iph_sourceip.s_addr = inet_addr(SOURCE_IP);
    ip_header_p->iph_destip.s_addr = inet_addr(DEST_IP);


    //IP Header Checksum 계산
//    unsigned short header_checksum = checksum((unsigned short*)&sendbuff[0], 20 / 2);
    // ip_header_p : 구조체 변수이다-> (unsigned short *)로 캐스팅하게되면
    // (unsigned short) 타입의 포인터 변수가 된다.
    unsigned short header_checksum = checksum((unsigned short*)ip_header_p, 20 / 2);
    //header checksum값을 pc메모리에 저장됭어있는 Little Endian 이기 때문에
    //네트워크 Big Endian으로 변환해서 대입해야한다. [htons()함수 이용]
    ip_header_p->iph_chksum = htons(header_checksum);
    // ----------------------------------------------------------------------------------------
    //Hea
    //sendbuff[10] = (header_checksum >> 8) & 0xff;
    //sendbuff[11] = header_checksum & 0xff;

    //-------------------------------------------------------------
    // UDP header
    udp_header_p->udp_sport = htons(SOURCE_PORT);
    udp_header_p->udp_dport = htons(DEST_PORT);

    // 마찬가지로 udp_total_length 변수는 PC메모리에 저장된 Little Endian 값이기 때문에
    // 네트워크 Big Endian 값으로 변환해서 패킷을 구성해야 한다
    unsigned short udp_total_length = (unsigned short)(sizeof(struct udpheader) + udp_data_len);
    udp_header_p->total_length = htons(udp_total_length);
    udp_header_p->udp_sum = 0;

    


    //// --------------------------------
    //// IP -> 0번부터 시작
    //// 4bit : version(4: IPv4), 4bit : header_length(5 -> 5*4 = 20bytes)
    //// 윈도우는 이더넷 못만짐, udp만 만질 수 있음.

    //sendbuff[0] = 0x45;
    ////TOS
    //sendbuff[1] = 0x00;
    //// Total Length : ethernet frame header를 제외한 모든 데이타 길이 (IP header + UDP header + Data)
    //// Little Endian : 0x1234 -> 메모리에 들어갈 때는 34 12 순서로 들어간다.
    //// Big Endian : 0x1234 -> 네트워크로 나갈 때는 12 34 순서로 나간다.
    //int total_length = 20 + 8 + 4; //20: IP Header , 8: UDP Header , 4: Data
    //sendbuff[2] = (total_length >> 8) & 0xff;
    //sendbuff[3] = total_length & 0xff;
    ////IP Identication
    //short ip_id = 0x00;
    //sendbuff[4] = (ip_id >> 8) & 0xff;
    //sendbuff[5] = ip_id & 0xff;
    //
    //// flag / fragment offset
    //sendbuff[6] = 0x00;
    //sendbuff[7] = 0x00;
    //
    //// TTL(Time to Live)
    //sendbuff[8] = 128;
    //
    //// Protocol : UDP - 17 , TCP -6
    //sendbuff[9] = 17;
    //
    //// IP header checksum -> 처음엔 0으로 채워줌
    //sendbuff[10] = 0;
    //sendbuff[11] = 0;
    //
    //// Source IP -> 내 IP  
    //sendbuff[12] = 172;
    //sendbuff[13] = 30;
    //sendbuff[14] = 1;
    //sendbuff[15] = 90;

    //// Destination IP
    //sendbuff[16] = 172;
    //sendbuff[17] = 30;
    //sendbuff[18] = 1;
    //sendbuff[19] = 25;

    ////IP Header Checksum 계산
    //unsigned short header_checksum = checksum((unsigned short*)&sendbuff[0], 20 / 2);
    //sendbuff[10] = (header_checksum >> 8) & 0xff;
    //sendbuff[11] = header_checksum & 0xff;

    ////-----------------------------------
    //// UDP Header
    //// source port
    //unsigned short udp_source_port = 3000; //내가보내는건 포트 중요하진 앟ㄴ음 
    //sendbuff[20] = (udp_source_port >> 8) & 0xff;
    //sendbuff[21] = udp_source_port & 0xff;
    //


    //// destination port
    //unsigned short udp_destination_port = 3000; //받는 포트를 정해야 함 .
    //sendbuff[22] = (udp_destination_port >> 8) & 0xff;
    //sendbuff[23] = udp_destination_port & 0xff;

    //// length
    //unsigned short udp_total_length = 8 + 4; // 8: udp_header length , 4: data length
    //sendbuff[24] = (udp_total_length >> 8) & 0xff;
    //sendbuff[25] = udp_total_length & 0xff;

    ////checksum
    //sendbuff[26] = 0;
    //sendbuff[27] = 0;
    //--------------------------------------

    //-----------------------------------
   // udp_data =(char *) "haha";
   // 
    // data
    udp_data[0] = 'o';
    udp_data[1] = 'j';
    udp_data[2] = 'w';
    udp_data[3] = 'w';

    //-----------------------------------
    int total_data_len = ip_total_length;
    //-----------------------------------

    return total_data_len;
}