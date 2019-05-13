//코드작성: 김한주
#include "node.h"

extern char connectboard[ROW][COL];	//커넥트보드 정의
extern int turn;
extern const char *checkOX;
int first = 0, finish = 0;
int main() {
	init();	//모든 승리의 경우의 돌을 정해준다.
	memset(connectboard, ' ', ROW*COL);	//보드의 size(6x7)만큼 배열 초기화
	int AImode = selectmode();	//AImode변수 - selectmode함수를 통해 입력받은 값으로 heuristic mode를 선택하면 1를 리턴받고, rule-based mode를 선택하면 2를 리턴받는다.
	while (first != 1 && first != 2) {	//선공을 결정하는 경우, 1(user먼저)과 2(AI먼저) 이외에 값을 입력하면, 제대로 입력할 때까지 반복문
		first = firstattack(AImode);
		if (first == 1 || first == 2) break;
		printf("\n잘못된 숫자를 입력하셨습니다. 다시 입력해주세요.");
	}
	whoisfirst(first);	//첫번째 공격하는 사람에 따라 user먼저 => 0 return, AI먼저 => 1을 return해준다.
	int time = 5;	//무승부일 때 종료해주기 위한 임시변수
	while (true) {	//main함수의 주를 이루는 부분. 게임이 끝날때까지 반복문
		boardprint(connectboard, AImode);	//connectboad를 프린트해주는 함수(AImode에 따라 다르게 출력)
		if (finishcheck(connectboard) == 1) {	//finishcheck함수를 통해 게임이 끝나면 1을 return, 진행중이면 0을 return해준다.
			printf("끝났습니다. 수고하셨습니다!!!!\n");
			Sleep(3000);
			break;
		}
		whoisattack(connectboard, turn % 2, checkOX, AImode);	//공격해주는 함수. turn수로 돌을 정해주고(%2), AImode에 따라 다른 공격(heuristic, rule-based)을 취한다.

		turn++;

		if (turn == 42 && finish == 0) {	//이 경우는 판이 꽉 찰 때까지 승부가 안난 경우이다. 무승부처리하고 5초 뒤 프로그램 종료해준다.
			while (true) {
				boardprint(connectboard, AImode);
				printf("무승부입니다~~~~~~~~수고하셨습니다!!!\n5초 뒤에 프로그램이 종료됩니다.\n종료까지 남은 시간 : ");
				printf("%d", time);
				Sleep(1000);
				time--;
				if (time == 0) return 0;
			}
		}
	}

	system("pause");	//이거 안해주니까 계속 꺼지길래 일단 해놓았다.
	return 0;
}