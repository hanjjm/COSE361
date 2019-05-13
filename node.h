//�ڵ��ۼ�: ������
#pragma once

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <windows.h>

#define ROW 6
#define COL 7

using namespace std;

typedef struct {	//����ü�� node�� �������ش�. ���� �ִ� 4������ �̾��� �� �ְ�, x��ǥ�� y��ǥ�� ��Ÿ����.
	int rowcolumn[4][2];
} node;

//�� �Լ��� ���� ������ �Լ� ������ �κп� �޾Ƴ����ϴ�!
int selectmode();
void boardprint(char(*connectboard)[COL], int mode);
int whoisattack(char(*connectboard)[COL], int attacker, const char *OX, int mode);
int whoisfirst(int sel);
void init();
int firstattack(int mode);
int finishcheck(char(*connectboard)[COL]);

int nextHeuristic();
void status();
int maxScore(int column, char OX);
int heuristic(int depth, bool minmax, int column, char OX, int alpha, int beta);
int height(int column);
int checkScore(char OX);

int RuleBased(char OX);
int CentralCheck(int col, char OX);
int nextRuleBased();