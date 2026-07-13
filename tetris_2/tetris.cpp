#include <stdio.h>

#include<windows.h>
#include <conio.h>

void gotoxy(int x, int y) { // 콘솔화면 내에서 x,y좌표로 이동

	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

char block[4][4] = { // 예제 테트리스 블럭 모양
	{ 0, 0, 0, 0 },
	{ 0, 1, 0, 0 },
	{ 0, 1, 1, 1 },
	{ 0, 0, 0, 0 }
};

// block 생성
void make_block(int xx, int yy) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[i][j] == 1) {

				gotoxy(j + xx, i + yy);
				printf("*");
			}
			else {

				gotoxy(j + xx, i + yy);
				printf("-");
			}
		}
		printf("\n");
	}
}

// 블럭 삭제 - 화면에서 공백처리해서 지움 
void delete_block(int xx, int yy) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block[i][j] == 1) {

				gotoxy(j + xx, i + yy);
				printf(" ");
			}
			else {

				gotoxy(j + xx, i + yy);
				printf(" ");
			}
		}
		printf("\n");
	}

}


// 이동 좌표값 - 직접 ++, -- 처럼 관리 필요
int x = 0;
int y = 0;

int count = 0;


void main() {

	// make_block(x, y); // 초기 블럭 생성


	//강의 예제
	while (1) {
		make_block(x, y);

		while (1) {
			if (count == 100) {
				count = 0;

				delete_block(x, y);
				y++;
				make_block(x, y);

			}

			//delete_block(x, y);
			//x++; // 오른쪽으로
			//y++; // 밑으로
			//make_block(x, y);

			if (_kbhit()) { // 키보드 입력이 있다면 
				char key = _getch();
				if (key == 'w') { // w: up key
					delete_block(x, y);
					y--;
					make_block(x, y);
				}
				else if (key == 's') { // s: down key
					delete_block(x, y);
					y++;
					make_block(x, y);
				}
				else if (key == 'a') { // a: left key
					delete_block(x, y);
					x--;
					make_block(x, y);
				}
				else if (key == 'd') { // d: right key
					delete_block(x, y);
					x++;
					make_block(x, y);
				}
			}
			count++;
			Sleep(10);
		}
	}



	
}

