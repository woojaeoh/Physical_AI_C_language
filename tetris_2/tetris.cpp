#include <stdio.h>

#include<windows.h>
#include <conio.h>

void gotoxy(int x, int y) { // 콘솔화면 내에서 x,y좌표로 이동
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void setcolor(int text_color, int bg_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), text_color + (bg_color << 4));
}

// 초기 예제 테트리스 블럭 모양
//char block[4][4] = { 
//	{ 0, 0, 0, 0 },
//	{ 0, 1, 0, 0 },
//	{ 0, 1, 1, 1 },
//	{ 0, 0, 0, 0 }
//};

// 이동 좌표값 - 직접 ++, -- 처럼 관리 필요
// x, y : 백그라운드의 행, 열을 나타내는 좌표 - 4x4 블락의 제일 왼쪽/위의 좌표이다.
int x = 3;
int y = 0;
// count : 10ms 마다 카운팅해서 1초를 만들기 위한 변수
int count = 0;
int rotate_index = 0; // 같은 블럭을 회전했을 때 구분하는 인덱스
int block_index = 0; //블럭 종류를 구분하는 인덱스

char block[2][4][4][4] ={
		{
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 1, 1 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			}
		}, {
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			}
		}
};

char background[12][12] = { // 바깥쪽을 2씩 감싸고 10x10으로 쓰겟다.
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,0,0,0,1,1,1,1},
	{1,1,1,1,1,1,1,0,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1},
};

void make_background() { // 배경화면 생성
	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 12; i++) {
			if (background[j][i] == 1) {
				gotoxy(i, j);
				printf("*");
			}
			else {
				gotoxy(i, j);
				printf("-");
			}
		}
		printf("\n");
	}
}

//숫자형 점수판 삽입
void make_background_value() { 
	for (int j = 0; j < 12; j++) {
		for (int i = 0; i < 12; i++) {
			if (background[j][i] == 1) {
				if (!((j == 0 || j == 11) || (i == 0 || i == 11))) {
					setcolor(4, 0);
				}
				gotoxy(i + 14, j);
				printf("1");
				setcolor(7, 0);
			}
			else {
				gotoxy(i + 14, j);
				printf("0");
			}
		}
		printf("\n");
	}
}

// block 생성
void make_block(int xx, int yy) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[block_index][rotate_index][i][j] == 1) {
				//setcolor(4, 0);
				gotoxy(j + xx, i + yy);
				printf("*");
				//setcolor(7, 0);
			}
			//else {
			//	gotoxy(j + xx, i + yy);
			//	printf("-");
			//}
		}
		printf("\n");
	}
}

// 블럭 삭제 - 화면에서 공백처리해서 지움 
void delete_block(int xx, int yy) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[block_index][rotate_index][i][j] == 1 && background[i + yy][j + xx] != 1) {
				gotoxy(j + xx, i + yy);
				printf("-");
			}
			//else {
			//	gotoxy(j + xx, i + yy);
			//	printf(" ");
			//}
		}
		printf("\n");
	}

}

int overlap_check(int xx, int yy) {
	int count_overlap = 0;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block[block_index][rotate_index][j][i] == 1 && background[j + yy][i + xx] == 1)
			{
				//setcolor(4, 0);
				//gotoxy(xx + i, yy + j);
				//printf("*");
				//setcolor(7, 0);

				count_overlap++;
			}
		}
	}
	//gotoxy(0, 12);
	//printf("overlap count : %d\n", count_overlap);

	return count_overlap;
}

int overlap_check_rotate(int rotate_index_local, int xx, int yy) {

	int count_overlap = 0;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block[block_index][rotate_index_local][j][i] == 1 && background[j + yy][i + xx] == 1)
			{
				count_overlap++;
			}
		}
	}
	//gotoxy(0, 12);
	//printf("overlap count : %d\n", count_overlap);

	return count_overlap;
}

void insert_block(int xx , int yy) {
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block[block_index][rotate_index][j][i] == 1) {
				background[j + yy][i + xx] = 1;
			}
		}
	}
}

// line_check() : 각 줄(line_num)마다 , 한 줄이 다 찼는지 체크 -> 10칸이 다 찼는지 체크.
int line_check(int line_num) {
	
	int count_block = 0; // 가로 줄에서 블럭이 몇개 있는지 카운트 -> 현 예제에서는 10개이면 한줄 빙고
	for (int i = 0; i < 10; i++) { // 가로줄에서 1~10까지 column을 10번 체크한다.
		if (background[line_num][i + 1] == 1) { // column의 값이 1이면 count_block를 증가시킨다.
			count_block++;
		}
	}
	
	return count_block;
}


void main() {

	// make_block(x, y); // 초기 블럭 생성

	//강의 예제
	make_background();
	make_background_value(); //숫자형 점수판 삽입
	make_block(x, y);

	while (1) {
		if (count == 50) {
			count = 0;

			int count_overlap = overlap_check(x, y + 1); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기
			if (count_overlap == 0){
				delete_block(x, y);
				y++; // 밑으로 이동
				make_block(x, y);
			}
			else { //바닥에 닿았을 때

				insert_block(x, y); // 블럭을 배경에 삽입
				make_background_value(); //숫자형 점수판 삽입

				//라인 체크를 위에서부터 해야지만 다음에 체크하는 아래줄도 체크하게된다.
				// 그렇지 않고 아래서부터 체크하면 그 줄을 체크하고 내릴 경우 내려온 
				// 위의 줄은 체크하지 못한다. 이미 내려와있기 때문에,
				//그래서 k는 2~10까지 체크한다.
				// k가 2부터인 경우는 제일 위의 줄은 제외하기 떄문이다.
				for (int k = 2; k <= 10; k++) {

					int count_block = line_check(k); // 한 줄이 다 찼는지 체크 -> 10칸이 다 찼는지 체크.
					if (count_block == 10) { //한 줄이 꽉 찼다는 의미
						// 1. 꽉 찼다면 지워주고
						// 2. 위에 있는 블럭들을 한 줄씩 내려줘야 함. -> 위의 한 줄을 밑 줄에 copy한다.
						for (int j = k; j > 1; j--) {
							for (int i = 0; i < 10; i++) {
								background[j][i + 1] = background[j - 1][i + 1]; // 위 과정을 한번에 처리.-> 9번줄에서 10번줄로 copy처리
							}
						}

						// 첫 줄도 업데이트를 해줘야 한다
						// -> 첫 줄을 모두 0으로 채우기
						for (int i = 0; i < 10; i++) {
							background[1][i + 1] = 0;
						}

						// 백그라운드 블락을 다시 그려준다.
						make_background();
						// + 값도 삽입
						make_background_value(); // 숫자형 점수판 삽입
						Sleep(300);
					}
				}
				// 백그라운드 블락을 다시 그려준다.
				make_background();
				make_background_value(); // 숫자형 점수판 삽입

				x = 3;
				y = 0;
				rotate_index = 0; //초기화해서 첫 모양으로.
				block_index++; // 블럭 종류 변경
				if (block_index == 2) { // 블럭 종류가 2개이므로, 2를 넘으면 다시 0으로 초기화
					block_index = 0;
				}
			}			
		}

		if (_kbhit()) { // 키보드 입력이 있다면 
			char key = _getch();
			if (key == 'w') { // w: rotate key (회전 키)
				
				//rotate_index 변수를 받아서 임시변수(rotate_index_tmp)를 만든다.
				int rotate_index_tmp = rotate_index;
				rotate_index_tmp++; //임시 변수 rotate_index_tmp를 하나 증가시켜서
				if (rotate_index_tmp == 4) { // 마지막 회전 블락을 넘어서 index가 4면, 처음으로 돌린다.
					rotate_index_tmp = 0;
				}

				// 회전할 떄 ,overlap이 나는지 미리 체크해서 rotate가 문제 없다면 회전함.
				int count_overlap_rotate = overlap_check_rotate(rotate_index_tmp, x, y); 
				if (count_overlap_rotate == 0) {
					delete_block(x, y);
				
					rotate_index++; // 블럭 회전

					if (rotate_index == 4) { // 마지막 회전 블락이면 처음으로 돌린다.
						rotate_index = 0; //처음 블락으로 세팅
					}

					make_block(x, y); // 블럭 만들기
				}

			}
			else if (key == 's') { // s: down key
				int count_overlap = overlap_check(x, y +1); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기
				
				if (count_overlap == 0) {
					delete_block(x, y);
					y++;
					make_block(x, y);
				}
			}
			else if (key == 'a') { // a: left key
				
				int count_overlap = overlap_check(x-1, y); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기

				if (count_overlap == 0) {
					delete_block(x, y);
					x--;
					make_block(x, y);
				}
			}
			else if (key == 'd') { // d: right key
				
				int count_overlap = overlap_check(x +1, y); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기

				if (count_overlap == 0) {
					delete_block(x, y);
					x++;
					make_block(x, y);
				}
			}

		}
		count++;
		Sleep(10);
	}
}