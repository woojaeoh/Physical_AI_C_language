#include <stdio.h>
#include <windows.h> // 1. 헤더 추가

void main() {
	SetConsoleOutputCP(CP_UTF8); // utf -8로 지정

	// 일반 변수 - 값을 저장
	char a = 3;

	// 포인터 변수 - 주소를 저장 -> 선언을 안하면 쓰레기 값으로 들어가있음 -> 초기화를 해줘야 함.
	char* b;

	b = &a; // b에 a의 주소를 넣어줌	
	printf("b 주소의 값: %d\n", *b);

	*b = 5;
	printf("b 주소의 값: %d\n", *b); // 포인터 변수로 *b처럼 가리키면 -> 그 값을 직접 읽거나 바꾸고 싶은 경우

	//sizeof() 함수
	// a 변수는 1byte할당 -> 일반 변수이기 때문
	// b 변수는 4byte할당(32bit 시스템) / 8byte(64bit system)이 할당된다 -> 포인터 변수이기 때문
	printf("a 변수의 크기: %d, b변수의 크기 : %d\n", sizeof(a), sizeof(b));


	// 1차원 배열 포인터 -> 이름 자체가 주소이다.


	//포인터를 이용해 1번 인덱스의 value인 2를 출력하기.
	// 배열은 이름 자체가 포인터이다.

	char a_array[3] = { 1,2,3 };

	printf("주소값 자체가 증가 : %p\n", a_array + 1);

	printf("배열의 두번째 값 : %d\n", *a_array + 1);

	printf("배열의 두번째 값 : %d\n", *(a_array + 1));


	//(a_array+1) -> 주소를 하나 증가시킨 문구

	printf("%d , %d , %d \n", *(a_array + 1), a_array[1], *((char*)&a_array[1]));

	// 이차원 배열의 포인터? -> 그냥 배열쓴다. 다루기어렵다. -> 그냥 배열이 더 직관적임. 내부적으로 똑같음.
	// 그래도 예제는 배운다 .

	// array_2 : 이름 자체는 배열의 첫 주소이다.
	// array_2[0]/ array_2[1] : 0번째 인덱스의 주소, 1번째 인덱스의 주소 -> 각 행의 첫 주소임.
	int array_2[2][2] = { 
		{1,2}, // 인덱스 0
		{3,4} // 인덱스 1
	};


	// array_2[0] : 0번째 인덱스의 주소값 -> 1,2가 들어있는 행의 첫 주소
	// array_2[0] +1 => 0번째 인덱스의 주소값 + 1 -> 첫 행의 주소에 offset 1을 더한 주소이다.
	// *(array_2[0] +1 )  => 그 주소의 값

	printf("%d\n", *(array_2[0] +1));
	printf("%d\n", *(*(array_2 + 0) +1 ));


	

	
}