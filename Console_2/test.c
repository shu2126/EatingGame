#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <process.h>

void mini(), prt();
int map[5][10] = { 0 };
int i, j, x, y, b1, b2, b3;//   x, y = 게이머 좌표  b1, b2, b3 = 컴퓨터(악당) 좌표
int again = 1, again_3 = 1, again_2 = 0, key; //again 이 들어간 변수는 반복문 변수, key = 게이머 키값 받는 변수
int map_count1 = 1, map_count2 = 1, map_count3 = 1;   // 컴퓨터가 사과 먹을경우 카운트 셈
int map_count1_1 = 1, map_count2_1 = 1, map_count3_1 = 1; // 컴퓨터가 맨 끝으로 갈 경우 카운트 셈

unsigned __stdcall  go(void* arg)
{
	int sleep_count = 0, sleep_time = 800; //점점 빨라지는 Sleep 변수
	while (again_3 < 1) {
		map[0][b1] = 0;  //이동하기전 원래 있던 자리는 0으로 초기화
		map[2][b2] = 0;
		map[4][b3] = 0;
		if (map_count1 == 0)map[0][b1] = 88; //이동전에 있던 곳이 과일 있던 곳이면 지나온 후 과일 그대로 둠
		if (map_count2 == 0)map[2][b2] = 88;
		if (map_count3 == 0)map[4][b3] = 88;

		if (b1 == 9)map_count1_1 = 1;   // 맨끝으로가면 다시 반대쪽으로 이동
		if (b1 == 0)map_count1_1 = 0;
		if (b2 == 9)map_count2_1 = 1;
		if (b2 == 0)map_count2_1 = 0;
		if (b3 == 9)map_count3_1 = 1;
		if (b3 == 0)map_count3_1 = 0;

		if (map_count1_1 == 0)b1++;  // 0이면 오른쪽으로 이동
		if (map_count1_1 == 1)b1--;  // 1이면 왼쪽으로 이동
		if (map_count2_1 == 0)b2++;
		if (map_count2_1 == 1)b2--;
		if (map_count3_1 == 0)b3++;
		if (map_count3_1 == 1)b3--;

		map_count1 = 1;
		map_count2 = 1;
		map_count3 = 1;
		if (map[0][b1] == 88)map_count1 = 0;  // 과일 지날때 count세서 지나칠때 과일 안사라지게함
		if (map[2][b2] == 88)map_count2 = 0;
		if (map[4][b3] == 88)map_count3 = 0;

		if (map[0][b1] == 77 || map[2][b2] == 77 || map[4][b3] == 77) {
			again = 1;
			again_3 = 1;
		}
		prt();
		if (sleep_time > 100)sleep_count++; //속도가 너무 빨라지지 않도록 조건걸고, 컴퓨터 움직임 셈
		if (sleep_count == 15) {  // 컴퓨터가 15번 움직이면
			sleep_time = sleep_time / 2; // 2배씩 빨라짐
			sleep_count = 0;
		}
		Sleep(sleep_time);
	}
	return 0;
}

void main() {
	srand(time(NULL));
	while (again_2 == 0) {
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 10; j++) map[i][j] = 0; // 맵 0으로 초기화
		}                                           //↑게임 다시 실행할때를 위함
		mini();
		printf("\n 게임을 더하려면 [영문자 o], 그만하려면 [Space Bar] \n");
		for (i = 0; i < 1; i++) {
			key = getch();
			if (key == 32)again_2 = 1; // 전체를 포함하는 반복문 나감
			else if (key != 111)i--;  //o(111)이면 for문 나가서 한번더 전체실행
		}
	}
	getch();
}

void mini() {
	int count, apple, apple_num;
	system("cls");
	printf("  사과가 놓일 확률을 입력해 주세요 (10단위) : ");
	scanf(" %d", &apple_num); //10단위로 받아서
	apple_num = apple_num / 10; // 10으로 나눠서 나온 수 만큼의 확률로 사과 놓는다
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (i % 2 == 1)
				if (j != 0 && j != 5 && j < 9)map[i][j] = 100;  // 벽
			apple = rand() % 10;
			if (map[i][j] != 100 && apple < apple_num)map[i][j] = 88; //사과
		}
	}
	b1 = rand() % 10;
	b2 = rand() % 10; // 컴퓨터(악당) 랜덤위치
	b3 = rand() % 10;
	for (i = 0; i < 1; i++) {
		y = rand() % 5;
		x = rand() % 10;
		if (map[y][x] == 100 || map[y][x] == 99)i--; // 게이머 위치 랜덤지정
	}
	prt();
	again = 0;
	again_3 = 0;
	unsigned ThreadId1;
	unsigned long hThread1 = _beginthreadex(NULL, 0, go, NULL, 0, &ThreadId1);
	while (again < 1) {   // 게이머 키값받아 이동
		key = getch();
		map[y][x] = 0; //발자국 안남김, 과일 먹고 사라짐
		if (key == 77 && map[y][x + 1] != 100 && x < 10) x++; //100은 벽, 이동하게될 곳이 벽이 아닐때만 이동
		if (key == 75 && map[y][x - 1] != 100 && x > -1) x--;
		if (key == 80 && map[y + 1][x] != 100 && y < 4) y++;
		if (key == 72 && map[y - 1][x] != 100 && y > 0) y--;
		if (x == 10) {
			if (y == 1 || y == 3)x = 9; // 벽이 있는 줄은 반대편으로 못넘어감
			else x = 0;
		}
		if (x == -1) {
			if (y == 1 || y == 3)x = 0; // 벽이 있는 줄은 반대편으로 못넘어감
			else x = 9;
		}
		if (map[y][x] == 99) {  // 악당만나면 반복문 끝냄
			again = 1;
			again_3 = 1;
		}
		if (map[y][x] != 99) map[y][x] = 77; // 게이머 이동 
		prt();
		count = 0;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 10; j++) {// 매 순간 과일이 있나 확인
				if (map[i][j] == 88) count++;
				if ((map_count1 == 0 || map_count2 == 0 || map_count3 == 0))count++;
			}
		}
		if (count == 0) {//0이면 과일 다 먹은 것이므로 반복문 나가 게임 끝
			printf(" \n < 사과를 다 먹었습니다. >  \n");
			again = 1;
			again_3 = 1;
		}
	}
}

void prt() {
	map[y][x] = 77; //게이머 = 77
	map[0][b1] = 99;
	map[2][b2] = 99;
	map[4][b3] = 99; // 컴퓨터 = 99
	system("cls");
	if (map[y][x] == 99)printf(" < 악당에게 죽었습니다. > ");
	printf("\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (map[i][j] == 100)printf("■");
			if (map[i][j] == 99)printf(" E");
			if (map[i][j] == 88)printf(" a");
			if (map[i][j] == 77)printf("△");
			if (map[i][j] == 0) printf("  ");
		}
		printf("\n");
	}
}