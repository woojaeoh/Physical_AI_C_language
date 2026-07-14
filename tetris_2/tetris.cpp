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

char block[4][4] = { // 예제 테트리스 블럭 모양
	{ 0, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 }
};

char background[12][12] = { // 바깥쪽을 2씩 감싸고 10x10으로 쓰겟다.
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
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


// block 생성
void make_block(int xx, int yy) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[i][j] == 1) {
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
			if (block[i][j] == 1 && background[i+yy][j+xx] != 1) {
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
			if (block[j][i] == 1 && background[j + yy][i + xx] == 1)
			{
				//setcolor(4, 0);
				//gotoxy(xx + i, yy + j);
				//printf("*");
				//setcolor(7, 0);

				count_overlap++;
			}
		}
	}
	gotoxy(0, 12);
	printf("overlap count : %d\n", count_overlap);

	return count_overlap;
}


// 이동 좌표값 - 직접 ++, -- 처럼 관리 필요
int x = 0;
int y = 0;

int count = 0;


void main() {
	
	// make_block(x, y); // 초기 블럭 생성

	//강의 예제
	make_background();
	make_block(x, y);

	while (1) {
		//if (count == 100) {
		//	count = 0;

		//	delete_block(x, y);
		//	y++; // 밑으로 이동
		//	make_block(x, y);
		//}

		if (_kbhit()) { // 키보드 입력이 있다면 
			char key = _getch();
			if (key == 'w') { // w: up key
				int count_overlap = overlap_check(x, y - 1); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기

				if (count_overlap == 0) {
					delete_block(x, y);
					y--;
					make_block(x, y);
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
		// 끝에 다다르면 더 안넘어가게 하는 제어문

}