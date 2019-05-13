//코드작성: 김한주 이종희
#include "node.h"
#include<time.h>
extern char connectboard[ROW][COL];	//커넥트보드 정의인데 function.cpp에서 정의해준건데 사용하므로 extern예약어 사용
extern vector<node> FirstWIN;	//이것도 function.cpp에서 정의해준 건데 사용할꺼이므로 extern 예약어 사용
extern vector<node> SecondWIN;	//위와 동일
extern vector<node> FirstTEMP;	//위와 동일
extern vector<node> SecondTEMP;	 //위와 동일
extern int first;	//main.cpp에서 정의한 거
extern int DEPTH;	//selectmode에서 정해주는 DEPTH(설정가능하게 하기 위해)
float computetime;

int nextHeuristic() {	//이 함수는 whoisattack에서 호출되는 함수로, heuristic mode를 할 경우에 다음 선택되는 column을 찾아주는 함수이다.
	int column;
	char OX = (whoisfirst(0) == 0) ? 'X' : 'O';	//user가 먼저 두는 걍우에 돌은 'X'이고, AI가 먼저 주는 경우면 돌은 'O'이다.
	int start = clock();
	status();
	
	
	column = maxScore(DEPTH, OX);	//Depth는 12이고 각 column중에 가장 높은 점수를 반환받는다. 
	int end = clock();
	computetime = float(end-start) / CLOCKS_PER_SEC;
	
	
	
	return column;	//가장 높은 점수로 반환받은 column을 반환해준다.
}


int maxScore(int depth, char stone) { //각 column 중에 가장 높은 점수를 받은 column을 반환해주는 함수이다.
	int temp[COL];	//각 score를 저장해주는 임시 배열이다.
	printf("저희의 column선택 방법은 각각의 column의 점수를 계산하여, 점수가 가장 높은 column의 값을 선택해줍니다.\n이를 위해 heuristic 방식으로 점수를 계산해주면\n");
	for (int i = 0; i < COL; i++) {
		temp[i] = heuristic(depth, true, i, stone, -277, 277); //각 column의 score를 heuristic방식으로 계산해서 저장해준다. depth와 minmax의 경우에는 맨 처음이므로 true이고,
									//i는 column, stone은 두어지는 돌('X'인지 'O'인지)이고 alpha-beta pruning을 위한 값을 넣어준다.
		printf("%d열의 점수는를 계산해보면 => %d\n", i + 1, temp[i]);
	}

	int maxcolumn = 0;
	for (int i = 0; i < COL; i++) { //최고 점수를 찾아주는 반복문
		if (temp[i] > temp[maxcolumn]) maxcolumn = i; 
		else if (temp[i] == temp[maxcolumn]) {	//만약 동일한 점수의 column일 경우에는?
			if (abs(3 - maxcolumn) >= abs(3 - i)) maxcolumn = i;	//더 가운데랑 가까운 column을 maxcolumn으로 지정해준다.
		}
	}
	printf("동일한 점수의 column들의 경우에는 가장 가운데열부터 우선순위를 둡니다.\n");
	printf("이를 통해 heristic 계산에 의해 가장 높은 점수를 반환받은 column은 %d열입니다. 인정하신다면 1번를 눌러주세요.", maxcolumn + 1);
	int temp2 = 0;
	while (true) {
		scanf_s("%d", &temp2);
		if (temp2 == 1) break;
	}
	return maxcolumn; // 가장 높은 점수를 갖는 column을 반환해준다.
}

int height(int column) {	//선택한 column의 height를 반환해주는 함수이다.
	int row;
	for (row = 0; row < ROW; row++) {
		if (connectboard[row][column] == ' ') {
			return row;	//행을 밑에서부터 위로 올라가며 보다가 돌이 안두어진 행이 있으면 반환해준다.
		}
	}
	return row;
}


int checkScore(char OX) { //점수를 계산해주는 함수이다.

	if (OX == 'O') {	//만약 돌이 'O'라면?
		for (node temp : SecondWIN) {	//임시 node를 설정하여 두번째 두는 것(돌이 'X'인 경우)까지 반복문을 돌며 'X'가 이기면 'O'는 진다. => 즉 -276을 반환한다.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'X' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'X' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'X' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'X') {
				return -276;	//276인 이유는 connectboard의 각 좌표당 가중치를 전부 더한 값이 276이므로 이 값을 넘을 수 없으므로 276으로 설정하였다.
			}
		}
		for (node temp : FirstWIN) {	//임시 node를 설정하여 첫번째 두는 것(돌이 'O'인 경우)까지 반복문을 돌며 'O'가 이긴다면 276을 반환한다.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'O' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'O' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'O' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'O') {
				return 276;
			}
		}
	}
	else {
		for (node temp : FirstWIN) {	//임시 node를 설정하여 첫번째 두는 것(돌이 'O'인 경우)까지 반복문을 돌며 'O'가 이기면 'X'는 진다. => 즉 -276을 반환한다.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'O' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'O' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'O' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'O') {
				return -276;
			}
		}

		for (node temp : SecondWIN) {	//임시 node를 설정하여 두번째 두는 것(돌이 'X'인 경우)까지 반복문을 돌며 'X'가 이기면 276을 반환한다.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'X' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'X' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'X' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'X') {
				return 276;
			}
		}
	}

	int plus[ROW][COL] = { {3,4,5,7,5,4,3}, {4,6,8,10,8,6,4}, {5,8,11,13,11,8,5}, {5,8,11,13,11,8,5}, {4,6,8,10,8,6,4}, {3,4,5,7,5,4,3} };
	//커넥트보드드의 각 좌표마다 가중치를 둔다. 이는 각 좌표마다 이길 수 있는 경우의 돌이 있는 경우가 있을 때마다 1씩 증가한다. 예를들면? 1행1열은 거기를 두었을 때 이기는 경우의 경우를 3가지를 만들 수 있으므로 3이다.
	//https://softwareengineering.stackexchange.com/questions/263514/why-does-this-evaluation-function-work-in-a-connect-four-game-in-java

	int sum = 0;
	
	for (int i = 0; i < ROW; i++) {	//반복문을 돌려가며 돌이 두어진 곳에 해당하는 가중치를 더해준다.
		for (int j = 0; j < COL; j++) {
			if (connectboard[i][j] == 'O') sum += plus[i][j];	//점수를 계산하는 돌이 O일경우 가중치를 더해준다.
			else sum -= plus[i][j];	//점수를 계산하는 돌이 X일 경우 가중치를 빼준다.
		}
	}

	return (OX == 'O') ? (int)(sum + 138) : (int)(-sum - 138);	//돌이 O일 경우에 138을 더해서 값을 반환해주고, 반대일경우 -값을 리턴해준다.
						//https://softwareengineering.stackexchange.com/questions/263514/why-does-this-evaluation-function-work-in-a-connect-four-game-in-java
}

int heuristic(int depth, bool minmax, int column, char OX, int alpha, int beta) {	//depth를 내려가면서 계산해주는 함수이다.
	int score;
	if (height(column) == 6) return -9999;	//만약에 돌이 꽉차있으면, 그 곳에 두지 못하게 하기 위해 -9999을 반환해준다.

	connectboard[height(column)][column] = OX;	//선택된 좌표에 점수계산을 위해 우선 돌을 둔다.

	if (depth == 1) score = minmax ? checkScore(OX) : -checkScore(OX);	//depth를 내려가다가 1에 도달하면, minmax임을 판단하여 max가 아니면 -를 붙여서 반환해준다.
	else if (depth >= 2) { // 2턴 이상이 남아있다면?
		int temp = checkScore(OX);	//임시로 score계산을 해준다.
		if (temp == 276 || temp == -276) { //만약 끝나는 경우다? (내가 두면 4개를 만들어 이길 수 있는 경우거나 상대방이 두면 4개가 되는 경우)
			connectboard[height(column) - 1][column] = ' ';	//아까 계산을 위래 두어봤던 돌을 제거해준다.
			return minmax ? temp + 1 : -(temp + 1);	//minmax임을 판단하여 max면 temp값에 1를 더하여 바로 반환해줄 수 있게 해준다.(min이면 반대로 또 바로 반환해주게!)
		}

		if (minmax) { //max일 경우라면?
			score = 276;	//scroe는 우선 276을 넣어준다.(가장 큰 값)
			for (int i = 0; i < COL; i++) {	//column을 돌면서,
				int temp = heuristic(depth - 1, !minmax, i, (OX == 'O') ? 'X' : 'O', alpha, beta);	//다음 단계의 depth일 때의 경우를 계산해준다. 재귀적으로 호출이 되는데 그 다음 depth로 내려갈수록 7배씩 호출된다.

				if (temp != -9999) {	//꽉찬 경우가 아니라면?
					score = min(score, temp);	//score는 1000+depth와 다음 단계의 depth에서의 score와 비교하여 min값을 취한다.
					if (score <= alpha) {	//alpha보다 작으면?
						connectboard[height(column) - 1][column] = ' ';
						return score;
					}
					beta = min(beta, score);
				}
			}
		}
		else {
			score = -276;	//score는 일단 -276을 넣어준다.(가장 작은 값)
			for (int i = 0; i < COL; i++) {
				int temp = heuristic(depth - 1, !minmax, i, (OX == 'O') ? 'X' : 'O', alpha, beta);
				if (temp != -9999) {
					score = max(score, temp);
					if (score >= beta) {
						connectboard[height(column) - 1][column] = ' ';
						return score;
					}
					alpha = max(alpha, score);
				}
			}
		}
	}

	connectboard[height(column) - 1][column] = ' '; // 아까 점수계산을 위해 두었던 돌을 제거해준다.
	return score; //최종적인 score를 반환해준다.
}