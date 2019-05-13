//코드작성: 김한주 이종희
#include "node.h"

char connectboard[ROW][COL];	//커넥트보드를 정의해준다.
const char *checkOX = "OX";	//돌을 위해(흰돌, 검은돌 느낌으로 O, X)선언해준 변수이다.(const는 왜인지모르겠는데 안쓰니까 쓰라고 오류가 떠서 씀)
int turn = 0;
extern int first;	//main함수에서 정의해준 변수를 사용하므로 extern 예약어
int DEPTH;	//Depth설정을 위한 변수
extern float computetime;

vector<node> FirstWIN;	//첫 번째 두는 사람이 이기는 모든 경우의 node들의 벡터
vector<node> SecondWIN;	//두 번째 두는 사람이 이기는 모든 경우의 node들의 벡터
vector<node> FirstTEMP;	//첫 번째 두는 사람들의 node들의 벡터에서 수정이 이루어진 경우(추가/삭제) 이를 임시로 보관해놓기 위한 벡터 
vector<node> SecondTEMP; //두 번째 두는 사람들의 node들의 벡터에서 수정이 이루어진 경우(추가 / 삭제) 이를 임시로 보관해놓기 위한 벡터

void init() {	//main함수를 실행할 때 한번 실행되는 초기화함수. 커넥트보드에서 가능한 경우의 돌이 4개 이어지는 경우를 정의해준다.

	for (int i = 0; i < ROW; i++) {	//이 경우는 가로로 돌이 이어지는 경우이다.
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i, j + 1 },{ i, j + 2 },{ i, j + 3 } }; //처음에 (1행1열, 1행2열, 1행3열, 1행4열)부터 (6행4열, 6행5열, 6행6열, 6행7열)까지 가능한 경우를 모두 확인한다.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //임시 node를 만들어줘서 위에서 가능한 경우 중 하나를 정의해준다.
				}
			}
			FirstWIN.push_back(tempNode); //위에서 정의해준 임시노드를 FirstWin벡터의 한 요소로 추가해준다.
			SecondWIN.push_back(tempNode); //위에서 정의해준 임시노드를 SecondWin벡터의 한 요소로 추가해준다.
		}
	}	//가로로 돌이 이어지는 경우는 위의 경우를 모두 따져주면 총 1행당 4개이고 6행이므로 24가지의 경우가 있다.

	for (int i = 0; i < ROW - 3; i++) {	//이 경우는 세로로 돌이 이어지는 경우이다.
		for (int j = 0; j < COL; j++) {
			int temp[4][2] = { { i, j },{ i + 1, j },{ i + 2, j },{ i + 3, j } }; //처음에 (1행1열, 2행1열, 3행1열, 4행1열)부터 (4행4열, 4행5열,4행6열, 4행7열)까지 가는한 경우를 모두 확인한다.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //위의 가로때와 동일하다.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //이것도 위와 동일하다.
		}
	}	//세로로 돌이 이어지는 경우는 총 1열당 3개이고 7열이므로 21가지의 경우가 있다.

	for (int i = 0; i < ROW - 3; i++) {	//이 경우는 대각선으로 돌이 이어지는 경우인데 왼쪽아래부터 시작하여 오른쪽 위로 나가는 방향으로 대각선인 경우이다.
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i + 1, j + 1 },{ i + 2, j + 2 },{ i + 3, j + 3 } };	//처음에 (1행1열, 2행2열, 3행3열, 4행4열)부터 시작하여 쭉 돌아가면서 가능한 경우를 모두 확인한다.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //위와 동일하다.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //이것도 위와 동일하다.
		}
	}	//왼쪽아래->오른쪽위 대각선으로 돌이 1행당 4개가 나오고 3행까지만 가능하므로 이어지는 경우는 총 12가지가 있다.

	for (int i = ROW - 1; i >= 3; i--) {
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i - 1, j + 1 },{ i - 2, j + 2 },{ i - 3, j + 3 } };
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //위와 동일하다.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //이것도 위와 동일하다.
		}
	}	//오른쪽아래->왼쪽 위로 가능한 경우는 위와 동일한 이유로 총 12가지가 있다.
}

int selectmode() {	//AI를 heuristic mode랑 대결할 것인지, rule-based mode랑 대결할 것인지를 정해주기 위한 함수이다.
	int mode;	//모드를 정해주는 변수
	printf("\n안녕하세요. 인공지능 34조입니다.\n어떤 mode로 경기를 하시겠습니까?\n\n1. Heuristic mode     2. Rule-based mode\n\n ===> ");
	scanf_s("%d", &mode);
	if (mode == 1) printf("Heuristic mode를 선택하셨습니다~~~!!! Depth를 설정해주세요. ===> ");
	scanf_s("%d", &DEPTH);
	
	return mode;	//heuristic mode를 선택하면 1을 반환하고, rule-based mode를 선택하면 2를 반환해준다. 
}

int firstattack(int mode) {	//처음 공격하는 것(?)을 정의해주기 위한 함수이다. (즉, 사람 먼저? AI 먼저?)
	int sel;	//선택을 위한 변수
	if (mode == 1) printf("\n\n Heuristic mode를 선택하셨습니다.");	//heuristic mode를 선택한 경우만 출력
	else printf("\n\n Rule-based mode를 선택하셨습니다.");	//rule-based mode를 선택한 경우만 출력
	printf("\n 누가 먼저 공격하시겠습니까?\n 1. User      2. AI\n ===> ");
	scanf_s("%d", &sel);
	return sel;	//사람이 먼저 공격하면 1을 반환, AI가 먼저 공격하면 2를 반환한다.
}

void boardprint(char(*connectboard)[COL], int mode) {	//커넥트 보드를 프린트해주는 함수이다.
	int row, column;
	system("cls"); //커넥트보드를 프린트하기 전에 한번 지워준다.(기존 것이 남아있지 않도록!)

	if (mode == 1) {
		
		puts("\n    <<<Heuristic Mode>>>\n");	//아까 mode선택에 따라 경기중에 어떤 모드랑 경기하고 있는지를 보여준다.
		printf("      <<<DEPTH - %d>>>\n", DEPTH);
		printf("<<<이전처리시간 - %.3f sec >>>\n", computetime);
	}
	else puts("\n    <<<Rule-based Mode>>> \n");
	printf("     <<<%d번째 turn>>>\n\n", turn);
	for (row = ROW - 1; row >= 0; row--) {
		for (column = 0; column < COL; column++) {
			printf("| %c ", connectboard[row][column]);
		}
		puts("|");
		puts("-----------------------------");

	}
	puts("  1   2   3   4   5   6   7\n");
}	//https://codereview.stackexchange.com/questions/27446/connect-four-game

int whoisfirst(int sel) {	//사람일 경우에 0을 반환, AI일 경우에 1을 반환해주는 함수인데 추후 다른 함수 정의할 때 도움을 주기 위한 함수이다.
	static int num = -1;
	if (num == -1) num = sel - 1;
	return num;
}

int whoisattack(char(*connectboard)[COL], int attacker, const char *checkOX, int mode) {	//전체적으로 이 함수가 게임을 진행시키는(?)함수라고 봐도 된다. 게임진행의 전반적인 부분을 맡는다.
						//https://codereview.stackexchange.com/questions/27446/connect-four-game
	
	int row = 0, column = 0;

	if (attacker == whoisfirst(0)) {	//user가 공격일 때,
		printf("몇번째 열에 두시겠습니까? ==> ");
		scanf_s("%d", &column);	//몇번 째 라인에 둘 지 선택해준다.
		while (connectboard[ROW - 1][COL - 1] != ' ' && column >= 1 && column <= 7) {	//만약에 입력한 라인이 꽉찬 라인일 경우에 대한 예외처리이다. 다른 곳에 입력하도록 한다.
			printf("여기는 꽉찼습니다. 다른 곳에 두세요. ===> ");
			scanf_s("%d", &column);
			if (connectboard[ROW - 1][column - 1] == ' ') break;	//입력한 라인이 꽉찬 라인이 아니면 합격. 둘 수 있게 해준다.
		}
		while (turn == 0 && column == 4) {	//이 경우는 처음에 가운데를 두었을 때에 대한 예외처리이다. 가운데를 두면 다른 곳에 두도록 말해준다.
			printf("처음에는 가운데를 둘 수 없습니다. 다시 입력해주세요 ==> ");
			scanf_s("%d", &column);
		}

		while (column < 1 || column >7) {	//예외처리. 열은 7개이므로, 1~7 이외의 값을 선택하면 error가 나게 해준다.
			if (column != 1000)	printf("잘못 입력했습니다. 다시 입력해주세요. ==> ");	//밑에서 가운데를 뒀을 때 경고문이 중복되는 경우를 방지하긷 위해 1000이 아닐 경우만 호출해준다.
			scanf_s("%d", &column);
			if (column >= 1 && column <= 7 && turn != 0) break;	//첫 번째 턴이 아니고, 1~7 사이에 수를 입력하면 break
			if (column == 4 && turn == 0) {	//이 경우는 처음에 가운데 -> 다음에 1~7이외의 열 -> 다시 가운데를 뒀을 때를 위한 예외처리이다.
				printf("처음에는 가운데를 둘 수 없습니다. 다시 입력해주세요 ==> ");
				column = 1000;	//column을 1000으로 처리해 위해서 경고문이 반복되는 경우를 방지해준다.
			}
		}
		column--;	//숫자에 입력한 값보다 하나를 빼줘야 제대로 된 위치에 두어진다.(배열이니)

		for (; row < ROW; row++) {	//선택한 열의 행을 밑에서부터 하나하나 보면서 마지막으로 돌이 놓아져 있는 위치 바로 위에 돌을 놔준다.
			if (connectboard[row][column] == ' ') {
				connectboard[row][column] = checkOX[attacker];
				return 1;
			}
		}
	}
	else {	//AI가 선택되었을 때(user가 아닐 때),
		if (turn == 0) column = 2;	//첫 번째로 두는 것일 때, AI는 무조건 2번째에 두게 한다(가운데 둘 수 없으므로! 그 다음 확률이 가장 높은 곳).
		else {
			if (mode == 1) column = nextHeuristic();	//이 경우는 heuristic mode일 때 호출되는 경우로, 다음 AI가 둘 column을 heuristic 방식에 따라 결정해준다.
			else column = nextRuleBased();	//여기는 rulebase를 구현해주면 됩니다!
			printf("\n\n%d\\n\n", whoisfirst(0));
		}
		for (; row < ROW; row++) {	//선택한 열의 행을 밑에서부터 하나하나 보면서 마지막으로 돌이 놓아져 있는 위치 바로 위에 돌을 둔다.
			if (connectboard[row][column] == ' ') {
				connectboard[row][column] = checkOX[attacker];
				printf("Wht\n");
				return 1;
			}
		}
	}
	return 0;
}

void remove(vector<node>* targetnode, vector<node>* tempnode, int xpos, int ypos) {
	for (vector<node>::iterator iter = (*targetnode).begin(); iter != (*targetnode).end(); ) {	//전체벡터를 도는 반복문이다(vector.begin부터 vector.end까지. 즉, 벡터의 첫번 째 요소부터 마지막 요소까지 돈다.)
		for (int i = 0; i < 4; i++) {
			if ((*iter).rowcolumn[i][0] == xpos && (*iter).rowcolumn[i][1] == ypos) { //반복문을 돌다가 동일한 좌표가 있다면?
				node temp;
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 2; k++) {
						temp.rowcolumn[j][k] = (*iter).rowcolumn[j][k]; //임시노드를 생성하여 저장해준다.
					}
				}
				(*tempnode).push_back(temp); // 저장한 node는 temp(쓰레기통)에 넣고
				iter = (*targetnode).erase(iter); // win에서 삭제한다.				~~이 부분은 이해가 잘 안가서 좀 더 이해하고 다시 봐야겠습니다!
				break;
			}
			if (i == 3) ++iter; //만약 다 봤으면 다음 node를 봐주기 위함이다. 
		}
	}
}

void recover(vector<node>* targetnode, vector<node>* tempnode) {
	while (!(*tempnode).empty()) { //tempnode가 빌 때까지 반복해준다.
		(*targetnode).push_back((*tempnode).back()); //tempnode위 맨 뒤에 요소를 targetnode로 넣어준다.
		(*tempnode).pop_back(); //tempnode는 그 node를 빼준다.
	}
}

void status() {
	recover(&FirstWIN, &FirstTEMP); //FirstWin 벡터가 다른 작업을 하면서 수정이 생겼을 경우가 있으니, 원래대로 돌려준다.
	recover(&SecondWIN, &SecondTEMP); //SecondWin 벡터가 다른 작업을 하면서 수정이 생겼을 경우가 있으니, 원래대로 돌려준다.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) { //커넥트보드를 전체적으로 돌면서
			if (connectboard[i][j] == 'X') remove(&FirstWIN, &FirstTEMP, i, j); //X가 좌표 i행j열에 있다면, FirstWin벡터에서 제거해준다.
			else if (connectboard[i][j] == 'O') remove(&SecondWIN, &SecondTEMP, i, j); //O가 좌표 i행j열에 있다면, SecondWin벡터에서 제거해준다.
		}
	}
}

int finishcheck(char(*connectboard)[COL]) {	//이 함수는 끝나는걸 체크해주는 함수이다. 게임이 끝나는 경우에 1을 반환해준다.
							//https://codereview.stackexchange.com/questions/27446/connect-four-game

	for (int row = 0; row < ROW; row++) {	//커넥트보드를 처음부터 쭉 돌면서 세로로 4개의 돌이 완성되어 끝나는 경우가 있는지 확인을 한다.
		for (int column = 0; column < COL - 3; column++) {
			char temp = connectboard[row][column];
			if ((temp != ' ') &&
				(connectboard[row][column + 1] == temp) &&
				(connectboard[row][column + 2] == temp) &&
				(connectboard[row][column + 3] == temp))
			{
				return 1;
			}
		}
	}
	for (int row = 0; row < ROW - 3; row++) {	//이 경우는 돌면서 가로로 끝난 경우가 있는지 확인해준다.
		for (int column = 0; column < COL; column++) {
			char temp = connectboard[row][column];
			if ((temp != ' ') &&
				(connectboard[row + 1][column] == temp) &&
				(connectboard[row + 2][column] == temp) &&
				(connectboard[row + 3][column] == temp))
			{
				return 1;
			}
		}
	}

	for (int row = 0; row < ROW - 3; row++) {	//이 경우는 돌면서 왼쪽 아래에서 오른쪽 위로 끝나는 경우가 있는지 확인해준다.
		for (int column = 0; column < COL - 3; column++) {
			char temp = connectboard[row][column];
			if ((temp != ' ') &&
				(connectboard[row + 1][column + 1] == temp) &&
				(connectboard[row + 2][column + 2] == temp) &&
				(connectboard[row + 3][column + 3] == temp))
			{
				return 1;
			}
		}
	}

	for (int row = 0; row < ROW - 3; row++) {	//이 경우는 돌면서 오른쪽 아래에서 왼쪽 위로 끝나는 경우가 있는지 확인해준다.
		for (int column = 3; column < COL; column++) {
			char temp = connectboard[row][column];
			if ((temp != ' ') &&
				(connectboard[row + 1][column - 1] == temp) &&
				(connectboard[row + 2][column - 2] == temp) &&
				(connectboard[row + 3][column - 3] == temp))
			{
				return 1;
			}
		}
	}
	return 0;	//모두 체크하여 없으면 0을 반환해준다.(끝나지 않은 상태)
}