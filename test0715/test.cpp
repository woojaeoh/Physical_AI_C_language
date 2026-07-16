#include<stdio.h>
#include <stdlib.h>

void main() {
	char abcd = 5;
	char* abcd_p = &abcd;
	printf("%d\n", *abcd_p);

	char abcd_array[3] = { 1,2,3 };
	printf("%d %d %d \n", abcd_array[2], *(abcd_array + 2) , *abcd_array);

	int abcde_array[2][2] = { {1,2}, {3,4} };
	printf("%d %d %d \n", abcde_array[1][1], *(abcde_array[1] + 1), *(*(abcde_array + 1) +1 ));

	//----------------------------------------
	
	// def_p는 포인터 변수인데, 배열 3개를 담는 포인터 배열이다.
	// def_p[0], def_p[1] . def_p[2] ==> 각각 3개의 포인터 변수이다.

	char* def_p[3] = { (char*)"234", (char*)"345", (char*) "abc"}; //문자열을 받는 타입이 없음 -> char형배열이나 char*형으로 문자열을 저장해야함 -> 배열이니 문자열 자체를 포인터처럼 접근할 수 있다.
	def_p[0] = (char *)"123"; // 변수는 아니지만 , "" (문자열) 자체는 주소이다.
	printf("%s %s %c %c", "123", def_p[0], *(def_p[1] + 2), *(*(def_p+2)+1)); // %s자리에는 포인터(주소)가 들어간다.


	char *malloc_p = (char*)malloc(sizeof(int) *100); // 포인터를 반환
	*malloc_p = 5; //첫 주소에 5라는 값을 넣는다.
	
	for (int i = 0; i < 10; i++) {
		*(malloc_p + i) = i;
	}

	for (int i = 0; i < 10; i++) { 	// 큐 - 버퍼 , 스택 - 레지스터=

//		printf("%d\n", *(malloc_p + i));

		printf("%d\n", *(malloc_p++));

	}
	
	// typedef : 타입을 재정의하는 키워드이다.
	// ch : char 타입이다. 
	typedef char ch;
	ch abcdef = 'a';
	printf("%c\n", abcdef);

	// 구조체 struct {char a; int b;} => typedef를 이용해서 abc_t 타입으로 재정의
	typedef struct {
		char a;
		//char c; // 구조체는 4byte allignment를 해서 메모리를 잡음 . 5바이트여도 8바이트 가져옴. 
		int b;
	} abc_t;

	abc_t abc_s;
	abc_s.a = 5;
	abc_s.b = 3;
	printf("%d , %d \n", abc_s.a, abc_s.b);

	//abc_t 타입의 abc_a 변수를 선언한 후 바로 초기화한다.
	//그런데 구조체 요소 갯수에 맞추어서 그대로 같은 갯수로 초기화해야한다.

	abc_t abc_a = { 3,4 }; // 구조체 내 모든 요소를 넣어줘야 한다. 순서대로.
	printf("%d %d\n", abc_a.a, abc_a.b);
	

	// 요소 전부 넣어주지 않아도 초기화할 수 있다.
	abc_t abc_b = 
	{
		.a = 7,
		.b = 8
	};

	abc_t* abc_b_p = &abc_b; // 포인터 변수 -> 무조건 4바이트 할당
	printf("%d, %d \n", abc_b_p->a, abc_b_p->b); //일반 변수에서는 .(dot)이고 포인터 변수는 -> 해준다.

	// 구조체에 배열을 넣어보기.
	// struct를 만들어놓고 , 타입을 선언하기 전에는 메모리에 안잡힘.
	
	typedef struct {
		char a;
		int b;
		int(*array_p)[2];
	}struct_array_t ;

	int tmp_array[2][2] = { {1,2},{3,4} };

	struct_array_t struct_arr = {
		.a = 3,
		.b = 5,
		.array_p = tmp_array
	};

	struct_array_t* struct_arr_p = &struct_arr; // 원형을 선언 후 포인터를 선언해야 함.
	printf("%d \n", struct_arr_p->array_p[1][0]); // 3
	
	int(*array_p_tmp)[2] = struct_arr_p -> array_p;
	printf("%d \n", array_p_tmp[1][0]); //3


	typedef int int_type;
	int_type abc_type = 5;

	typedef unsigned char uint8_t; // 8bit unsigned char
	typedef unsigned short uint16_t; // 16bit unsigned short를 재정의
	typedef unsigned int uint32_t; //32bit unsigned int를 재정의

	typedef struct { // 4 + 4 + 4 => 12바이트가 잡힘.
		char aa;
		int bb;
		char (*abc_p)[2]; // 배열 포인터 -> 4바이트.
	}struct_var_t;

	char array_2[2][2] = { {1,2},{3,4} };
	struct_var_t struct_var;
	struct_var.aa = 5;
	struct_var.bb = 3;
	struct_var.abc_p = array_2;
	printf("%d \n", struct_var.abc_p[1][0]); // 3


	struct_var.abc_p = &array_2[1]; //array_2의 주소를 알아야 array_2[1]에 접근할 수 있고, array_2[1]자체는 1차원 배열이니, 1차원 배열의 요소에 접근할 때는 &연산자를 붙여줘야한다	
	printf("%d \n", struct_var.abc_p[0][1]);

	
	//struct를 만들어만 놓으면 메모리에 안잡힘 -> 선언을 해야 메모리에 잡힘.

	




	// byte allignment  ,-> 5바이트여도 8바이트 가져옴
	// 
	// 
	//----------------------------------------
	//----------------------------------------
	//----------------------------------------

}