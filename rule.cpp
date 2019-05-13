//코드작성: 김한주 이종희
#include "node.h"

extern char connectboard[ROW][COL];



const int oderarray[7] = { 3, 2, 4, 1, 5, 0, 6 };//각 열의 우선순위 배열


int CentralCheck(int col, char OX) {
	//각 열의 자리에서 돌이 연속으로 있는지 검사해주는 함수(2개->3 해당 자리에 인접한 돌 2개 이상->2 반환




	int checknearby = 0;//인접한 돌을 세는 변수


	if (col < 6 && col>0) {//1열과 7열 예외처리(배열 크기를 넘어가므로)
		if (connectboard[height(col)][col - 1] == OX && connectboard[height(col)][col + 1] == OX) { //가로 줄 검사

			if (col < 5) {
				if (connectboard[height(col)][col + 2] == ' ') {//해당 라인의 오른쪽 자리가 비어있는지 검사->있으면 3반환

					return 3;
				}
			}
			if (col > 1) {
				if (connectboard[height(col)][col - 2] == ' ') {//해당 라인의 왼쪽 자리가 비어있는지 검사->있으면 3반환

					return 3;
				}
			}
		}
	}

	if (height(col) > 0 && col > 0 && height(col) < 6 && col < 6) {//1열,7열,1행,7행 예외처리(배열 크기를 넘어가므로)
		if (connectboard[height(col) - 1][col - 1] == OX && connectboard[height(col) + 1][col + 1] == OX) {//오른쪽위 대각선 
			if (col > 1 && height(col) > 1) {//2열,2행 예외처리(배열 크기를 넘어가므로)
				if (connectboard[height(col) - 2][col - 2] == ' ') {//해당 라인의 왼쪽 아래가 비었는지 검사->있으면 3반환			

					return 3;
				}
			}
			if (col < 5 && height(col) < 5) {//6열,6행 예외처리(배열 크기를 넘어가므로)
				if (connectboard[height(col) + 2][col + 2] == ' ') {//해당 라인의 오른쪽 위가 비었는지 검사->있으면 3반환
					return 3;
				}
			}
		}
		if (connectboard[height(col) - 1][col + 1] == OX && connectboard[height(col) + 1][col - 1] == OX) {//왼쪽 위 대각선 검사

			if (height(col) > 1 && col < 5) {
				if (connectboard[height(col) - 2][col + 2] == ' ') {//해당 라인의오른쪽 아래가 비었는지 검사
					return 3;
				}
			}
			if (height(col) < 5 && col > 1) {
				if (connectboard[height(col) + 2][col - 2] == ' ') {//해당 라인의 왼쪽 위가 비었는지 검사	
			
					

					return 3;
				}
			}

		}


		


		if (height(col) > 0 && col > 0) {//1행,1열 예외처리(배열 크기를 넘어가므로)
			if (connectboard[height(col) + 1][col - 1] == OX)checknearby++;//좌상측에 이웃한 돌이 있는지?
			if (connectboard[height(col)][col - 1] == OX)checknearby++;//좌측에 이웃한 돌이 있는지?
			if (connectboard[height(col) - 1][col - 1] == OX)checknearby++;//좌하측에 이웃한 돌이 있는지?
			if (connectboard[height(col) - 1][col] == OX)checknearby++;//아래측에 이웃한 돌이 있는지?
			if (connectboard[height(col) - 1][col + 1] == OX)checknearby++;//우하측에 이웃한 돌이 있는지?
			if (connectboard[height(col)][col + 1] == OX)checknearby++;//우측에 이웃한 돌이 있는지?
			if (connectboard[height(col) + 1][col + 1] == OX)checknearby++;//우상측에 이웃한 돌이 있는지?
		}

		if (checknearby >= 2) {//이웃한 돌이 2개 이상인 경우 2를 반환

			return 2;
		}

	}

	return 1;//모두 없을 경우 1반환

}

int RuleBased(char OX) {

	if (OX == 'O') {//자신의 돌이 O인 경우
		for (int i = 0; i < COL; i++) {//자신의 돌이 3개 연속 놓여져 있는경우 4개를 완성하여 승리하는 코드
			if (height(i) != 6) {//해당 열이 꽉차지 않았을때
				connectboard[height(i)][i] = 'O';//해당 열에 돌을 놔봄			

				if (checkScore('O') == 276) { //자신의 돌이 4개 완성(276점)이 되는 경우
					connectboard[height(i) - 1][i] = ' ';//돌을 다시 지우고					
					status();
					return i; //해당 열을 반환
				}
				connectboard[height(i) - 1][i] = ' ';
				status();
			}

		}
	}
	else {//자신의 돌이 X일 경우 OX를 X로 놓고 같은 처리
		for (int i = 0; i < COL; i++) {
			if (height(i) != 6) {
				connectboard[height(i)][i] = 'X';
				if (checkScore('X') == 276) {
					connectboard[height(i) - 1][i] = ' ';
					status();
					return i;
				}
				connectboard[height(i) - 1][i] = ' ';
				status();
			}
		}
	}

	if (OX == 'O') {//상대의 돌이 3개 연속 놓여져 있는경우 이를 막는 코드
		for (int i = 0; i < COL; i++) {//놓아보는 돌을 반대로(X)하고 같은처리
			if (height(i) != 6) {
				connectboard[height(i)][i] = 'X';
				status();
				if (checkScore('X') == 276) {
					connectboard[height(i) - 1][i] = ' ';
					status();
					return i;
				}
				connectboard[height(i) - 1][i] = ' ';
				status();
			}
		}
	}
	else {//놓아보는 돌을 반대로(O)하고 같은처리
		for (int i = 0; i < COL; i++) {
			if (height(i) != 6) {
				connectboard[height(i)][i] = 'O';
				status();
				if (checkScore('O') == 276) {
					connectboard[height(i) - 1][i] = ' ';
					status();
					return i;
				}
				connectboard[height(i) - 1][i] = ' ';
				status();
			}

		}
	}




	if (OX == 'O') {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {//우선순위(우선순위 배열)에 따라 검사
				if (CentralCheck(oderarray[i], 'X') == 3) {
					//CentralCheck 반환 값이 3->함수상대방의 두 개짜리 공격(3개 만들기)를 방어
					return oderarray[i];
				}
			}
		}


		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 3) {
					//CentralCheck 반환 값이 3->자신의 두 개짜리 공격(3개 만들기)
					return oderarray[i];
				}
			}
		}
	}
	else {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 3) {
					//CentralCheck 반환 값이 3->함수상대방의 두 개짜리 공격(3개 만들기) 방어
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 3) {
					//CentralCheck 반환 값이 3->자신의 두 개짜리 공격(3개 만들기)						
					return oderarray[i];
				}
			}
		}
	}



	if (OX == 'O') {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 2) {
					//CentralCheck 반환 값이 2->상대의 이웃돌이 2개이상인 자리를 방어
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 2) {
					//CentralCheck 반환 값이 2->자신의 이웃돌이 2개이상인 자리를 공격

					return oderarray[i];
				}
			}
		}
	}
	else {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 2) {
					//CentralCheck 반환 값이 2->상대의 이웃돌이 2개이상인 자리를 방어
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 2) {
					//CentralCheck 반환 값이 2->자신의 이웃돌이 2개이상인 자리를 공격
					return oderarray[i];
				}
			}
		}
	}



	for (int i = 0; i < COL; i++) {//나머지 경우 우선순위에 따라 열 반환
		if (height(oderarray[i]) != 6) {
			return oderarray[i];
		}
	}



}


int nextRuleBased() {	//이 함수는 whoisattack에서 호출되는 함수로, rule-based mode를 할 경우에 다음 선택되는 column을 찾아주는 함수이다.
	int column;
	char OX = (whoisfirst(0) == 0) ? 'X' : 'O';	//user가 먼저 두는 걍우에 돌은 'X'이고, AI가 먼저 주는 경우면 돌은 'O'이다.
	status();


	column = RuleBased(OX);
	return column;
}