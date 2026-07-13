#include <stdio.h>

#include<windows.h>
#include <conio.h>

void gotoxy(int x, int y) {

	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

char block[4][4] = {
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

// 블럭 삭제 
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



int x = 0;
int y = 0;



void main() {

	make_block(x, y);

	while (y < 4 and x < 4) {
		delete_block(x, y);
		x++;
		make_block(x, y);
		//y++;
		Sleep(1000);
	}
}

