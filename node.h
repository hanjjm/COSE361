//코드작성: 김한주
#pragma once

#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <windows.h>

#define ROW 6
#define COL 7

using namespace std;

typedef struct {	//구조체인 node를 정의해준다. 돌은 최대 4개까지 이어질 수 있고, x좌표와 y좌표를 나타낸다.
	int rowcolumn[4][2];
} node;

//각 함수에 대한 설명은 함수 구현한 부분에 달아놨습니다!
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