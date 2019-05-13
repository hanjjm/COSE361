//�ڵ��ۼ�: ������ ������
#include "node.h"
#include<time.h>
extern char connectboard[ROW][COL];	//Ŀ��Ʈ���� �����ε� function.cpp���� �������ذǵ� ����ϹǷ� extern����� ���
extern vector<node> FirstWIN;	//�̰͵� function.cpp���� �������� �ǵ� ����Ҳ��̹Ƿ� extern ����� ���
extern vector<node> SecondWIN;	//���� ����
extern vector<node> FirstTEMP;	//���� ����
extern vector<node> SecondTEMP;	 //���� ����
extern int first;	//main.cpp���� ������ ��
extern int DEPTH;	//selectmode���� �����ִ� DEPTH(���������ϰ� �ϱ� ����)
float computetime;

int nextHeuristic() {	//�� �Լ��� whoisattack���� ȣ��Ǵ� �Լ���, heuristic mode�� �� ��쿡 ���� ���õǴ� column�� ã���ִ� �Լ��̴�.
	int column;
	char OX = (whoisfirst(0) == 0) ? 'X' : 'O';	//user�� ���� �δ� ���쿡 ���� 'X'�̰�, AI�� ���� �ִ� ���� ���� 'O'�̴�.
	int start = clock();
	status();
	
	
	column = maxScore(DEPTH, OX);	//Depth�� 12�̰� �� column�߿� ���� ���� ������ ��ȯ�޴´�. 
	int end = clock();
	computetime = float(end-start) / CLOCKS_PER_SEC;
	
	
	
	return column;	//���� ���� ������ ��ȯ���� column�� ��ȯ���ش�.
}


int maxScore(int depth, char stone) { //�� column �߿� ���� ���� ������ ���� column�� ��ȯ���ִ� �Լ��̴�.
	int temp[COL];	//�� score�� �������ִ� �ӽ� �迭�̴�.
	printf("������ column���� ����� ������ column�� ������ ����Ͽ�, ������ ���� ���� column�� ���� �������ݴϴ�.\n�̸� ���� heuristic ������� ������ ������ָ�\n");
	for (int i = 0; i < COL; i++) {
		temp[i] = heuristic(depth, true, i, stone, -277, 277); //�� column�� score�� heuristic������� ����ؼ� �������ش�. depth�� minmax�� ��쿡�� �� ó���̹Ƿ� true�̰�,
									//i�� column, stone�� �ξ����� ��('X'���� 'O'����)�̰� alpha-beta pruning�� ���� ���� �־��ش�.
		printf("%d���� �����¸� ����غ��� => %d\n", i + 1, temp[i]);
	}

	int maxcolumn = 0;
	for (int i = 0; i < COL; i++) { //�ְ� ������ ã���ִ� �ݺ���
		if (temp[i] > temp[maxcolumn]) maxcolumn = i; 
		else if (temp[i] == temp[maxcolumn]) {	//���� ������ ������ column�� ��쿡��?
			if (abs(3 - maxcolumn) >= abs(3 - i)) maxcolumn = i;	//�� ����� ����� column�� maxcolumn���� �������ش�.
		}
	}
	printf("������ ������ column���� ��쿡�� ���� ��������� �켱������ �Ӵϴ�.\n");
	printf("�̸� ���� heristic ��꿡 ���� ���� ���� ������ ��ȯ���� column�� %d���Դϴ�. �����ϽŴٸ� 1���� �����ּ���.", maxcolumn + 1);
	int temp2 = 0;
	while (true) {
		scanf_s("%d", &temp2);
		if (temp2 == 1) break;
	}
	return maxcolumn; // ���� ���� ������ ���� column�� ��ȯ���ش�.
}

int height(int column) {	//������ column�� height�� ��ȯ���ִ� �Լ��̴�.
	int row;
	for (row = 0; row < ROW; row++) {
		if (connectboard[row][column] == ' ') {
			return row;	//���� �ؿ������� ���� �ö󰡸� ���ٰ� ���� �ȵξ��� ���� ������ ��ȯ���ش�.
		}
	}
	return row;
}


int checkScore(char OX) { //������ ������ִ� �Լ��̴�.

	if (OX == 'O') {	//���� ���� 'O'���?
		for (node temp : SecondWIN) {	//�ӽ� node�� �����Ͽ� �ι�° �δ� ��(���� 'X'�� ���)���� �ݺ����� ���� 'X'�� �̱�� 'O'�� ����. => �� -276�� ��ȯ�Ѵ�.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'X' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'X' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'X' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'X') {
				return -276;	//276�� ������ connectboard�� �� ��ǥ�� ����ġ�� ���� ���� ���� 276�̹Ƿ� �� ���� ���� �� �����Ƿ� 276���� �����Ͽ���.
			}
		}
		for (node temp : FirstWIN) {	//�ӽ� node�� �����Ͽ� ù��° �δ� ��(���� 'O'�� ���)���� �ݺ����� ���� 'O'�� �̱�ٸ� 276�� ��ȯ�Ѵ�.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'O' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'O' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'O' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'O') {
				return 276;
			}
		}
	}
	else {
		for (node temp : FirstWIN) {	//�ӽ� node�� �����Ͽ� ù��° �δ� ��(���� 'O'�� ���)���� �ݺ����� ���� 'O'�� �̱�� 'X'�� ����. => �� -276�� ��ȯ�Ѵ�.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'O' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'O' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'O' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'O') {
				return -276;
			}
		}

		for (node temp : SecondWIN) {	//�ӽ� node�� �����Ͽ� �ι�° �δ� ��(���� 'X'�� ���)���� �ݺ����� ���� 'X'�� �̱�� 276�� ��ȯ�Ѵ�.
			if (connectboard[temp.rowcolumn[0][0]][temp.rowcolumn[0][1]] == 'X' &&
				connectboard[temp.rowcolumn[1][0]][temp.rowcolumn[1][1]] == 'X' &&
				connectboard[temp.rowcolumn[2][0]][temp.rowcolumn[2][1]] == 'X' &&
				connectboard[temp.rowcolumn[3][0]][temp.rowcolumn[3][1]] == 'X') {
				return 276;
			}
		}
	}

	int plus[ROW][COL] = { {3,4,5,7,5,4,3}, {4,6,8,10,8,6,4}, {5,8,11,13,11,8,5}, {5,8,11,13,11,8,5}, {4,6,8,10,8,6,4}, {3,4,5,7,5,4,3} };
	//Ŀ��Ʈ������� �� ��ǥ���� ����ġ�� �д�. �̴� �� ��ǥ���� �̱� �� �ִ� ����� ���� �ִ� ��찡 ���� ������ 1�� �����Ѵ�. �������? 1��1���� �ű⸦ �ξ��� �� �̱�� ����� ��츦 3������ ���� �� �����Ƿ� 3�̴�.
	//https://softwareengineering.stackexchange.com/questions/263514/why-does-this-evaluation-function-work-in-a-connect-four-game-in-java

	int sum = 0;
	
	for (int i = 0; i < ROW; i++) {	//�ݺ����� �������� ���� �ξ��� ���� �ش��ϴ� ����ġ�� �����ش�.
		for (int j = 0; j < COL; j++) {
			if (connectboard[i][j] == 'O') sum += plus[i][j];	//������ ����ϴ� ���� O�ϰ�� ����ġ�� �����ش�.
			else sum -= plus[i][j];	//������ ����ϴ� ���� X�� ��� ����ġ�� ���ش�.
		}
	}

	return (OX == 'O') ? (int)(sum + 138) : (int)(-sum - 138);	//���� O�� ��쿡 138�� ���ؼ� ���� ��ȯ���ְ�, �ݴ��ϰ�� -���� �������ش�.
						//https://softwareengineering.stackexchange.com/questions/263514/why-does-this-evaluation-function-work-in-a-connect-four-game-in-java
}

int heuristic(int depth, bool minmax, int column, char OX, int alpha, int beta) {	//depth�� �������鼭 ������ִ� �Լ��̴�.
	int score;
	if (height(column) == 6) return -9999;	//���࿡ ���� ����������, �� ���� ���� ���ϰ� �ϱ� ���� -9999�� ��ȯ���ش�.

	connectboard[height(column)][column] = OX;	//���õ� ��ǥ�� ��������� ���� �켱 ���� �д�.

	if (depth == 1) score = minmax ? checkScore(OX) : -checkScore(OX);	//depth�� �������ٰ� 1�� �����ϸ�, minmax���� �Ǵ��Ͽ� max�� �ƴϸ� -�� �ٿ��� ��ȯ���ش�.
	else if (depth >= 2) { // 2�� �̻��� �����ִٸ�?
		int temp = checkScore(OX);	//�ӽ÷� score����� ���ش�.
		if (temp == 276 || temp == -276) { //���� ������ ����? (���� �θ� 4���� ����� �̱� �� �ִ� ���ų� ������ �θ� 4���� �Ǵ� ���)
			connectboard[height(column) - 1][column] = ' ';	//�Ʊ� ����� ���� �ξ�ô� ���� �������ش�.
			return minmax ? temp + 1 : -(temp + 1);	//minmax���� �Ǵ��Ͽ� max�� temp���� 1�� ���Ͽ� �ٷ� ��ȯ���� �� �ְ� ���ش�.(min�̸� �ݴ�� �� �ٷ� ��ȯ���ְ�!)
		}

		if (minmax) { //max�� �����?
			score = 276;	//scroe�� �켱 276�� �־��ش�.(���� ū ��)
			for (int i = 0; i < COL; i++) {	//column�� ���鼭,
				int temp = heuristic(depth - 1, !minmax, i, (OX == 'O') ? 'X' : 'O', alpha, beta);	//���� �ܰ��� depth�� ���� ��츦 ������ش�. ��������� ȣ���� �Ǵµ� �� ���� depth�� ���������� 7�辿 ȣ��ȴ�.

				if (temp != -9999) {	//���� ��찡 �ƴ϶��?
					score = min(score, temp);	//score�� 1000+depth�� ���� �ܰ��� depth������ score�� ���Ͽ� min���� ���Ѵ�.
					if (score <= alpha) {	//alpha���� ������?
						connectboard[height(column) - 1][column] = ' ';
						return score;
					}
					beta = min(beta, score);
				}
			}
		}
		else {
			score = -276;	//score�� �ϴ� -276�� �־��ش�.(���� ���� ��)
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

	connectboard[height(column) - 1][column] = ' '; // �Ʊ� ��������� ���� �ξ��� ���� �������ش�.
	return score; //�������� score�� ��ȯ���ش�.
}