#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <process.h>

void mini(), prt();
int map[5][10] = { 0 };
int i, j, x, y, b1, b2, b3;//   x, y = ���̸� ��ǥ  b1, b2, b3 = ��ǻ��(�Ǵ�) ��ǥ
int again = 1, again_3 = 1, again_2 = 0, key; //again �� �� ������ �ݺ��� ����, key = ���̸� Ű�� �޴� ����
int map_count1 = 1, map_count2 = 1, map_count3 = 1;   // ��ǻ�Ͱ� ��� ������� ī��Ʈ ��
int map_count1_1 = 1, map_count2_1 = 1, map_count3_1 = 1; // ��ǻ�Ͱ� �� ������ �� ��� ī��Ʈ ��

unsigned __stdcall  go(void* arg)
{
	int sleep_count = 0, sleep_time = 800; //���� �������� Sleep ����
	while (again_3 < 1) {
		map[0][b1] = 0;  //�̵��ϱ��� ���� �ִ� �ڸ��� 0���� �ʱ�ȭ
		map[2][b2] = 0;
		map[4][b3] = 0;
		if (map_count1 == 0)map[0][b1] = 88; //�̵����� �ִ� ���� ���� �ִ� ���̸� ������ �� ���� �״�� ��
		if (map_count2 == 0)map[2][b2] = 88;
		if (map_count3 == 0)map[4][b3] = 88;

		if (b1 == 9)map_count1_1 = 1;   // �ǳ����ΰ��� �ٽ� �ݴ������� �̵�
		if (b1 == 0)map_count1_1 = 0;
		if (b2 == 9)map_count2_1 = 1;
		if (b2 == 0)map_count2_1 = 0;
		if (b3 == 9)map_count3_1 = 1;
		if (b3 == 0)map_count3_1 = 0;

		if (map_count1_1 == 0)b1++;  // 0�̸� ���������� �̵�
		if (map_count1_1 == 1)b1--;  // 1�̸� �������� �̵�
		if (map_count2_1 == 0)b2++;
		if (map_count2_1 == 1)b2--;
		if (map_count3_1 == 0)b3++;
		if (map_count3_1 == 1)b3--;

		map_count1 = 1;
		map_count2 = 1;
		map_count3 = 1;
		if (map[0][b1] == 88)map_count1 = 0;  // ���� ������ count���� ����ĥ�� ���� �Ȼ��������
		if (map[2][b2] == 88)map_count2 = 0;
		if (map[4][b3] == 88)map_count3 = 0;

		if (map[0][b1] == 77 || map[2][b2] == 77 || map[4][b3] == 77) {
			again = 1;
			again_3 = 1;
		}
		prt();
		if (sleep_time > 100)sleep_count++; //�ӵ��� �ʹ� �������� �ʵ��� ���ǰɰ�, ��ǻ�� ������ ��
		if (sleep_count == 15) {  // ��ǻ�Ͱ� 15�� �����̸�
			sleep_time = sleep_time / 2; // 2�辿 ������
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
			for (j = 0; j < 10; j++) map[i][j] = 0; // �� 0���� �ʱ�ȭ
		}                                           //����� �ٽ� �����Ҷ��� ����
		mini();
		printf("\n ������ ���Ϸ��� [������ o], �׸��Ϸ��� [Space Bar] \n");
		for (i = 0; i < 1; i++) {
			key = getch();
			if (key == 32)again_2 = 1; // ��ü�� �����ϴ� �ݺ��� ����
			else if (key != 111)i--;  //o(111)�̸� for�� ������ �ѹ��� ��ü����
		}
	}
	getch();
}

void mini() {
	int count, apple, apple_num;
	system("cls");
	printf("  ����� ���� Ȯ���� �Է��� �ּ��� (10����) : ");
	scanf(" %d", &apple_num); //10������ �޾Ƽ�
	apple_num = apple_num / 10; // 10���� ������ ���� �� ��ŭ�� Ȯ���� ��� ���´�
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (i % 2 == 1)
				if (j != 0 && j != 5 && j < 9)map[i][j] = 100;  // ��
			apple = rand() % 10;
			if (map[i][j] != 100 && apple < apple_num)map[i][j] = 88; //���
		}
	}
	b1 = rand() % 10;
	b2 = rand() % 10; // ��ǻ��(�Ǵ�) ������ġ
	b3 = rand() % 10;
	for (i = 0; i < 1; i++) {
		y = rand() % 5;
		x = rand() % 10;
		if (map[y][x] == 100 || map[y][x] == 99)i--; // ���̸� ��ġ ��������
	}
	prt();
	again = 0;
	again_3 = 0;
	unsigned ThreadId1;
	unsigned long hThread1 = _beginthreadex(NULL, 0, go, NULL, 0, &ThreadId1);
	while (again < 1) {   // ���̸� Ű���޾� �̵�
		key = getch();
		map[y][x] = 0; //���ڱ� �ȳ���, ���� �԰� �����
		if (key == 77 && map[y][x + 1] != 100 && x < 10) x++; //100�� ��, �̵��ϰԵ� ���� ���� �ƴҶ��� �̵�
		if (key == 75 && map[y][x - 1] != 100 && x > -1) x--;
		if (key == 80 && map[y + 1][x] != 100 && y < 4) y++;
		if (key == 72 && map[y - 1][x] != 100 && y > 0) y--;
		if (x == 10) {
			if (y == 1 || y == 3)x = 9; // ���� �ִ� ���� �ݴ������� ���Ѿ
			else x = 0;
		}
		if (x == -1) {
			if (y == 1 || y == 3)x = 0; // ���� �ִ� ���� �ݴ������� ���Ѿ
			else x = 9;
		}
		if (map[y][x] == 99) {  // �Ǵ縸���� �ݺ��� ����
			again = 1;
			again_3 = 1;
		}
		if (map[y][x] != 99) map[y][x] = 77; // ���̸� �̵� 
		prt();
		count = 0;
		for (i = 0; i < 5; i++) {
			for (j = 0; j < 10; j++) {// �� ���� ������ �ֳ� Ȯ��
				if (map[i][j] == 88) count++;
				if ((map_count1 == 0 || map_count2 == 0 || map_count3 == 0))count++;
			}
		}
		if (count == 0) {//0�̸� ���� �� ���� ���̹Ƿ� �ݺ��� ���� ���� ��
			printf(" \n < ����� �� �Ծ����ϴ�. >  \n");
			again = 1;
			again_3 = 1;
		}
	}
}

void prt() {
	map[y][x] = 77; //���̸� = 77
	map[0][b1] = 99;
	map[2][b2] = 99;
	map[4][b3] = 99; // ��ǻ�� = 99
	system("cls");
	if (map[y][x] == 99)printf(" < �Ǵ翡�� �׾����ϴ�. > ");
	printf("\n");
	for (i = 0; i < 5; i++) {
		for (j = 0; j < 10; j++) {
			if (map[i][j] == 100)printf("��");
			if (map[i][j] == 99)printf(" E");
			if (map[i][j] == 88)printf(" a");
			if (map[i][j] == 77)printf("��");
			if (map[i][j] == 0) printf("  ");
		}
		printf("\n");
	}
}