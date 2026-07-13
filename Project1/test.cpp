#include <stdio.h>
#include <windows.h>

int main() {
	// char : 1byte , unsigned char /char
	char a = 10; 

	//short : 2 bytes ,  signed short/unsigned short
	//short  : 0x000 ~ 0xFFFF
	//short b = 20;

	//int : 4bytes, signed int / unsigned int
	// int : 0x00000000 ~ 0x FFFFFFFF

	int b = 20;

	long f = 20; // long  = 4byte
	
	double d = 20.0; //double - 8byte
	
	float e = 20.0; // float  - 4byte

	
	int num = 5;
	//for (int i = 0; i < num; i++) {
	//	for (int j = 0; j < num +i; j++) {
	//		if (i+j > num) {
	//			printf("*");
	//		}
	//		else {
	//			printf(" ");
	//		}
	//	}
	//	printf("\n");
	//	Sleep(1000);
	//}

	//for (int i = 0; i < 3; i++)
	//{
	//	printf("hdfjgnndfjgn\n");
	//	Sleep(1000);
	//}

	//int i = 0;
	//while(1) {
	//	if (i < 6) {
	//		for (int x = 1; x <= i; x++) {
	//			printf(" ");
	//		}

	//		printf("*");

	//		for (int x = 0; x <= i + 1; x++) {
	//			printf("\b");
	//		}

	//		i++;
	//	}
	//	else {

	//		for (int x = 1; x <= i + 1; x++) {
	//			printf(" ");
	//		}

	//		printf("\r");
	//		i = 0;
	//	}


	//	Sleep(1000);
	//}
	int time = 12;
	while (1)
	{
		for (int i = 0; i < time; i++) {

			//1. 처음에 공백을 줌
			for (int j = 0; j < i; j++) {
				printf(" ");
			}

			//2. 별을 찍음
			printf("*");

			Sleep(500);

			//3. 뒤로 백시킴

			for (int j = 0; j < i + 1; j++) {
				printf("\b");
			}

		}
		//4. 마지막 별을 지워줌.

		for (int i = 0; i < time; i++) {
			printf(" ");
		}

		//5. 맨 앞으로 다시 이동.
		printf("\r");


	}


	return 0;
}

