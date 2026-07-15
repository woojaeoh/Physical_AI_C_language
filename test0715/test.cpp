#include<stdio.h>

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

	char* def_p[3] = { (char*)"234", (char*)"345", (char*) "abc"};
	def_p[0] = (char *)"123"; // 변수는 아니지만 , "" (문자열) 자체는 주소이다.
	printf("%s %s %c %c", "123", def_p[0], *(def_p[1] + 2), *(*(def_p+2)+1)); // %s자리에는 포인터(주소)가 들어간다.
	
	//----------------------------------------
	//----------------------------------------
	//----------------------------------------




}