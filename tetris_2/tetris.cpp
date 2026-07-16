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


char block[7][4][4][4] = {
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
		},{
			{ // 예제 테트리스 블럭 모양
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 1, 1, 1, 1 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 1, 1, 1, 1 },
				{ 0, 0, 0, 0 }
			}
		},
		{
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 1, 0 }
			}
		},
		{
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 1, 0 },
				{ 0, 1, 1, 1 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 1, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 1, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 1, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 0, 0, 0 }
			}
		},
		{ {// 예제 테트리스 블럭 모양
				{ 0, 1, 1, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 1 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 1, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0},
				{ 1, 1, 0, 0 },
				{ 0, 1, 1, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 1, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 1, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			}
		},
		{{// 예제 테트리스 블럭 모양
				{ 0, 0, 1, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 0 },
				{ 0, 0, 1, 1 },
				{ 0, 0, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 0, 0, 0, 0},
				{ 0, 1, 1, 1 },
				{ 0, 1, 0, 0 }
			},
			{ // 예제 테트리스 블럭 모양
				{ 0, 0, 0, 0 },
				{ 1, 1, 0, 0 },
				{ 0, 1, 0, 0 },
				{ 0, 1, 0, 0 }
			}
		}
};


char background[22][12] = { // 바깥쪽을 2씩 감싸고 10x10으로 쓰겟다.
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
};

// 이동 좌표값 - 직접 ++, -- 처럼 관리 필요
// x, y : 백그라운드의 행, 열을 나타내는 좌표 - 4x4 블락의 제일 왼쪽/위의 좌표이다.
//int x = 3;
//int y = 0;
// count : 10ms 마다 카운팅해서 1초를 만들기 위한 변수
//int count = 0;
//int rotate_index = 0; // 같은 블럭을 회전했을 때 구분하는 인덱스
//int block_index = 0; //블럭 종류를 구분하는 인덱스
//int prev_index = 1;

// 4x 4 x 4 단위로 접근하는 포인터
//char (*block_p)[4][4][4] = block;
//char (*background_p)[12] = background; // 배열 포인터


#define RED		4
#define GRAY	8
#define GREEN	2
#define YELLOW	6
#define PURPLE	5
#define SKY		3
#define ORANGE 14 
char block_color[7] = {RED, ORANGE, GREEN, YELLOW, PURPLE, SKY,  GRAY }; // 0:빨간색, 1: 파란색, 2: 초록색 


//모든 전역 변수를 tetris_var_t 이라는 이름의 구조체로 자료구조화한다.
typedef struct {
	int x;
	int y;
	int count;
	int rotate_index; // 같은 블럭을 회전했을 때 구분하는 인덱스
	int block_index; //블럭 종류를 구분하는 인덱스
	int prev_index;


	char (*block_p)[4][4][4];
	char (*background_p)[12]; // 배열 포인터
}tetris_var_t;


tetris_var_t tetris_var = {
	.x = 3,
	.y = 0,
	.count = 0,
	.rotate_index = 0,
	.block_index = 0,
	.prev_index = 1,

	.block_p = block,
	.background_p = background
};

tetris_var_t *tetris_var_p = &tetris_var;

// 배경화면 생성
void make_background(tetris_var_t* var_p) {  // 원하는 주소를 넣을 수 있다

	// 배열 하위 항목 [12]를 가지는 배열의 주소이다.
	// (tetris_var_t* var_p) 변수에서 background_p 주소를 가져와서 대입한다.

	char (*background_p)[12] = var_p-> background_p;

	for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 12; i++) {
			if (background_p[j][i] > 1) {
				setcolor(background_p[j][i], 0);
				gotoxy(i, j);
				printf("*");
				setcolor(7, 0);
			}
			else if (background_p[j][i] == 1) { //조건 추가 필요
				setcolor(7, 0);
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
void make_background_value(tetris_var_t* var_p) {

	char (*background_p)[12] = var_p->background_p;

	for (int j = 0; j < 22; j++) {
		for (int i = 0; i < 12; i++) {
			if (background_p[j][i] >= 1) {
				if (!((j == 0 || j == 21) || (i == 0 || i == 11))) {
					// setcolor : block_color[] 배열의 인덱스는 각 블락의 인덱스(0~6)인데
					// 현재 함수에서는 block_index 변수가 없기 때문에
					// background[][] 배열의 값에서 color 값을 가져온다.
					// 그런데 background 배열에는 block_index 변수에 +2를 했기 떄문에
					// background[j][i] -2 해 주어야지 block_index값과 동일한 값이 된다.
					setcolor(background_p[j][i], 0);
				}
			
				gotoxy(i +14, j);
				printf("%d", background_p[j][i]);
				setcolor(7, 0); //color를 원래대로 돌려놓음.
			
			}
			else {
				setcolor(7, 0);
				gotoxy(i + 14, j);
				printf("0");
			}
		}
		printf("\n");
	}
}

// 1. ㄴ자는 빨갛게, ㅁ자는 파랗게 -> block_index 0, 1로 구분해서 색깔을 다르게 출력하도록 한다.
// 2. 

// block 생성
void make_block(tetris_var_t* var_p) {

	char (*block_p)[4][4][4] = var_p->block_p;
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block_p[var_p->block_index][var_p->rotate_index][i][j] == 1) {
				setcolor(block_color[var_p->block_index], 0);
				gotoxy(j + var_p->x, i + var_p->y);
				printf("*");
				setcolor(7, 0);
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
void delete_block(tetris_var_t* var_p) {

	char (*block_p)[4][4][4] = var_p-> block_p;
	char (*background_p)[12] = var_p->background_p;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block_p[var_p->block_index][var_p->rotate_index][i][j] == 1 && background_p[i + var_p->y][j + var_p->x] != 1) {
					gotoxy(j + var_p->x, i + var_p->y);
					printf("-");
				}
			}
			//else {
			//	gotoxy(j + xx, i + yy);
			//	printf(" ");
			//}
		}
		printf("\n");
	}

int overlap_check(tetris_var_t* var_p, int xx, int yy) {

	char (*block_p)[4][4][4] = var_p->block_p;
	char (*background_p)[12] = var_p->background_p;
	int count_overlap = 0;


	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block_p[var_p->block_index][var_p->rotate_index][j][i] == 1 && background_p[j + yy][i + xx] >= 1)
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

int overlap_check_rotate(tetris_var_t* var_p) {

	char (*block_p)[4][4][4] = var_p->block_p;
	char (*background_p)[12] = var_p->background_p;
	int count_overlap = 0;

	//rotate_index 변수를 받아서 임시변수(rotate_index_tmp)를 만든다.
	int rotate_index_tmp = var_p->rotate_index;
	rotate_index_tmp++; //임시 변수 rotate_index_tmp를 하나 증가시켜서
	if (rotate_index_tmp == 4) { // 마지막 회전 블락을 넘어서 index가 4면, 처음으로 돌린다.
		rotate_index_tmp = 0;
	}
	
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block_p[var_p->block_index][rotate_index_tmp][j][i] == 1 && background_p[j + var_p->y][i + var_p->x] >= 1)
			{
				count_overlap++;
			}
		}
	}
	//gotoxy(0, 12);
	//printf("overlap count : %d\n", count_overlap);

	return count_overlap;
}

// 첫 background배열 0-> "-" , 1 이상 -> "*"로 변환하는 함수
void insert_block(tetris_var_t* var_p) {
	char (*block_p)[4][4][4] = var_p->block_p;
	char (*background_p)[12] = var_p->background_p;

	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			if (block_p[var_p->block_index][var_p->rotate_index][j][i] == 1) {
				background_p[j + var_p->y][i + var_p->x] = block_color[var_p->block_index] ; //0은 "-" , 1은 "*" , 2이상부터 색깔
			}
		}
	}
}

// line_check() : 각 줄(line_num)마다 , 한 줄이 다 찼는지 체크 -> 10칸이 다 찼는지 체크.
int line_check(tetris_var_t* var_p, int line_num) {
	char (*background_p)[12] = var_p->background_p;

	int count_block = 0; // 가로 줄에서 블럭이 몇개 있는지 카운트 -> 현 예제에서는 10개이면 한줄 빙고
	for (int i = 0; i < 10; i++) { // 가로줄에서 1~10까지 column을 10번 체크한다.
		if (background_p[line_num][i + 1] >= 1) { // column의 값이 1이면 count_block를 증가시킨다.
			count_block++;
		}
	}
	
	return count_block;
}

////백그라운드 값 설정
//void index_rotate(int color_num) {
//
//}
// 

// 

void make_preview_block(tetris_var_t* var_p) {

	char (*block_p)[4][4][4] = var_p->block_p;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block_p[var_p->prev_index][var_p->rotate_index][i][j] == 1) {
				setcolor(block_color[var_p->prev_index], 0);
				gotoxy(j + var_p->x + 24, i + var_p->y);
				printf("*");
				setcolor(7, 0);
			}
			else {
				gotoxy(j + var_p->x + 24, i + var_p->y);
				printf("-");
			}
		}
		printf("\n");
	}
}

void main() {

	tetris_var_t* tetris_var_p = &tetris_var; //전역 변수로 한번 선언해줘야한다? 포인터만 들고다니면 구조체에 접근이 가능하다 .

	//강의 예제
	make_background(tetris_var_p);
	make_background_value(tetris_var_p); //숫자형 점수판 삽입
	make_block(tetris_var_p);
	make_preview_block(tetris_var_p);

	while (1) {
		if (tetris_var_p->count == 50) {
			tetris_var_p->count = 0;

			int count_overlap = overlap_check(tetris_var_p, tetris_var_p->x, tetris_var_p-> y+1); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기
			if (count_overlap == 0){
				delete_block(tetris_var_p);
				tetris_var_p->y++; // 밑으로 이동
				make_block(tetris_var_p);
			}
			else { //바닥에 닿았을 때

				insert_block(tetris_var_p); // 블럭을 배경에 삽입
				make_background_value(tetris_var_p); //숫자형 점수판 삽입

				//라인 체크를 위에서부터 해야지만 다음에 체크하는 아래줄도 체크하게된다.
				// 그렇지 않고 아래서부터 체크하면 그 줄을 체크하고 내릴 경우 내려온 
				// 위의 줄은 체크하지 못한다. 이미 내려와있기 때문에,
				//그래서 k는 2~10까지 체크한다.
				// k가 2부터인 경우는 제일 위의 줄은 제외하기 떄문이다.
				for (int k = 2; k <= 20; k++) {

					int count_block = line_check(tetris_var_p, k); // 한 줄이 다 찼는지 체크 -> 10칸이 다 찼는지 체크.
					if (count_block == 10) { //한 줄이 꽉 찼다는 의미
						// 1. 꽉 찼다면 지워주고
						// 2. 위에 있는 블럭들을 한 줄씩 내려줘야 함. -> 위의 한 줄을 밑 줄에 copy한다.
						for (int j = k; j > 1; j--) {
							for (int i = 0; i < 10; i++) {
								tetris_var_p->background_p[j][i + 1] = tetris_var_p->background_p[j - 1][i + 1]; // 위 과정을 한번에 처리.-> 9번줄에서 10번줄로 copy처리
							}
						}
			
						// 첫 줄도 업데이트를 해줘야 한다
						// -> 첫 줄을 모두 0으로 채우기
						for (int i = 0; i < 10; i++) {
							tetris_var_p->background_p[1][i + 1] = 0;
						}

						// 백그라운드 블락을 다시 그려준다.
						make_background(tetris_var_p);
						// + 값도 삽입
						make_background_value(tetris_var_p); // 숫자형 점수판 삽입
						Sleep(300);
					}
				}
				// 백그라운드 블락을 다시 그려준다.
				make_background(tetris_var_p);
				make_background_value(tetris_var_p); // 숫자형 점수판 삽입

				tetris_var_p->x = 3;
				tetris_var_p->y = 0;
				tetris_var_p->rotate_index = 0; //초기화해서 첫 모양으로.

				//미리보기 인덱스 값(preview_index)을 새로 내리는 블락 인덱스(block_index)로 바꿔준다.
				tetris_var_p->block_index = tetris_var_p->prev_index;
				
				tetris_var_p->prev_index++; // 블럭 종류 변경
				if (tetris_var_p->prev_index == 7) { // 블럭 종류가 2개이므로, 2를 넘으면 다시 0으로 초기화
					tetris_var_p->prev_index = 0;
				}

				make_preview_block(tetris_var_p);
				// make_block을 해주는 이유 생각해보기
				make_block(tetris_var_p);
			}			
		}

		if (_kbhit()) { // 키보드 입력이 있다면 
			char key = _getch();
			if (key == 'w') { // w: rotate key (회전 키)
				
				////rotate_index 변수를 받아서 임시변수(rotate_index_tmp)를 만든다.
				//int rotate_index_tmp = tetris_var_p->rotate_index;
				//rotate_index_tmp++; //임시 변수 rotate_index_tmp를 하나 증가시켜서
				//if (rotate_index_tmp == 4) { // 마지막 회전 블락을 넘어서 index가 4면, 처음으로 돌린다.
				//	rotate_index_tmp = 0;
				//}

				// 회전할 떄 ,overlap이 나는지 미리 체크해서 rotate가 문제 없다면 회전함.
				int count_overlap_rotate = overlap_check_rotate(tetris_var_p);
				if (count_overlap_rotate == 0) {
					delete_block(tetris_var_p);
				
					tetris_var_p->rotate_index++; // 블럭 회전

					if (tetris_var_p->rotate_index == 4) { // 마지막 회전 블락이면 처음으로 돌린다.
						tetris_var_p->rotate_index = 0; //처음 블락으로 세팅
					}

					make_block(tetris_var_p); // 블럭 만들기
				}

			}
			else if (key == 's') { // s: down key
				int count_overlap = overlap_check(tetris_var_p, tetris_var_p->x, tetris_var_p->y +1); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기
				
				if (count_overlap == 0) {
					delete_block(tetris_var_p);
					tetris_var_p->y++;
					make_block(tetris_var_p);
					//make_preview_block(x, y);
				}
			}
			else if (key == 'a') { // a: left key
				
				int count_overlap = overlap_check(tetris_var_p, tetris_var_p->x-1, tetris_var_p->y); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기

				if (count_overlap == 0) {
					delete_block(tetris_var_p);
					tetris_var_p->x--;
					make_block(tetris_var_p);
					//make_preview_block(x, y);
				}
			}
			else if (key == 'd') { // d: right key
				
				int count_overlap = overlap_check(tetris_var_p, tetris_var_p->x+1, tetris_var_p->y); // 원래는 출력 후 지우기 -> overlap이 나는지 미리 체크해보기

				if (count_overlap == 0) {
					delete_block(tetris_var_p);
					tetris_var_p->x++;
					make_block(tetris_var_p);
					//prev_block(x, y);
				}
			}

		}
		tetris_var_p->count++;
		Sleep(10);
	}
}


// 헤더파일에 자료구조를 선언해놓고 가져다 쓰는느낌.