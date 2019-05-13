//�ڵ��ۼ�: ������ ������
#include "node.h"

char connectboard[ROW][COL];	//Ŀ��Ʈ���带 �������ش�.
const char *checkOX = "OX";	//���� ����(��, ������ �������� O, X)�������� �����̴�.(const�� �������𸣰ڴµ� �Ⱦ��ϱ� ����� ������ ���� ��)
int turn = 0;
extern int first;	//main�Լ����� �������� ������ ����ϹǷ� extern �����
int DEPTH;	//Depth������ ���� ����
extern float computetime;

vector<node> FirstWIN;	//ù ��° �δ� ����� �̱�� ��� ����� node���� ����
vector<node> SecondWIN;	//�� ��° �δ� ����� �̱�� ��� ����� node���� ����
vector<node> FirstTEMP;	//ù ��° �δ� ������� node���� ���Ϳ��� ������ �̷���� ���(�߰�/����) �̸� �ӽ÷� �����س��� ���� ���� 
vector<node> SecondTEMP; //�� ��° �δ� ������� node���� ���Ϳ��� ������ �̷���� ���(�߰� / ����) �̸� �ӽ÷� �����س��� ���� ����

void init() {	//main�Լ��� ������ �� �ѹ� ����Ǵ� �ʱ�ȭ�Լ�. Ŀ��Ʈ���忡�� ������ ����� ���� 4�� �̾����� ��츦 �������ش�.

	for (int i = 0; i < ROW; i++) {	//�� ���� ���η� ���� �̾����� ����̴�.
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i, j + 1 },{ i, j + 2 },{ i, j + 3 } }; //ó���� (1��1��, 1��2��, 1��3��, 1��4��)���� (6��4��, 6��5��, 6��6��, 6��7��)���� ������ ��츦 ��� Ȯ���Ѵ�.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //�ӽ� node�� ������༭ ������ ������ ��� �� �ϳ��� �������ش�.
				}
			}
			FirstWIN.push_back(tempNode); //������ �������� �ӽó�带 FirstWin������ �� ��ҷ� �߰����ش�.
			SecondWIN.push_back(tempNode); //������ �������� �ӽó�带 SecondWin������ �� ��ҷ� �߰����ش�.
		}
	}	//���η� ���� �̾����� ���� ���� ��츦 ��� �����ָ� �� 1��� 4���̰� 6���̹Ƿ� 24������ ��찡 �ִ�.

	for (int i = 0; i < ROW - 3; i++) {	//�� ���� ���η� ���� �̾����� ����̴�.
		for (int j = 0; j < COL; j++) {
			int temp[4][2] = { { i, j },{ i + 1, j },{ i + 2, j },{ i + 3, j } }; //ó���� (1��1��, 2��1��, 3��1��, 4��1��)���� (4��4��, 4��5��,4��6��, 4��7��)���� ������ ��츦 ��� Ȯ���Ѵ�.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //���� ���ζ��� �����ϴ�.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //�̰͵� ���� �����ϴ�.
		}
	}	//���η� ���� �̾����� ���� �� 1���� 3���̰� 7���̹Ƿ� 21������ ��찡 �ִ�.

	for (int i = 0; i < ROW - 3; i++) {	//�� ���� �밢������ ���� �̾����� ����ε� ���ʾƷ����� �����Ͽ� ������ ���� ������ �������� �밢���� ����̴�.
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i + 1, j + 1 },{ i + 2, j + 2 },{ i + 3, j + 3 } };	//ó���� (1��1��, 2��2��, 3��3��, 4��4��)���� �����Ͽ� �� ���ư��鼭 ������ ��츦 ��� Ȯ���Ѵ�.
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //���� �����ϴ�.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //�̰͵� ���� �����ϴ�.
		}
	}	//���ʾƷ�->�������� �밢������ ���� 1��� 4���� ������ 3������� �����ϹǷ� �̾����� ���� �� 12������ �ִ�.

	for (int i = ROW - 1; i >= 3; i--) {
		for (int j = 0; j < COL - 3; j++) {
			int temp[4][2] = { { i, j },{ i - 1, j + 1 },{ i - 2, j + 2 },{ i - 3, j + 3 } };
			node tempNode;
			for (int k = 0; k < 4; k++) {
				for (int l = 0; l < 2; l++) {
					tempNode.rowcolumn[k][l] = temp[k][l]; //���� �����ϴ�.
				}
			}
			FirstWIN.push_back(tempNode);
			SecondWIN.push_back(tempNode); //�̰͵� ���� �����ϴ�.
		}
	}	//�����ʾƷ�->���� ���� ������ ���� ���� ������ ������ �� 12������ �ִ�.
}

int selectmode() {	//AI�� heuristic mode�� ����� ������, rule-based mode�� ����� �������� �����ֱ� ���� �Լ��̴�.
	int mode;	//��带 �����ִ� ����
	printf("\n�ȳ��ϼ���. �ΰ����� 34���Դϴ�.\n� mode�� ��⸦ �Ͻðڽ��ϱ�?\n\n1. Heuristic mode     2. Rule-based mode\n\n ===> ");
	scanf_s("%d", &mode);
	if (mode == 1) printf("Heuristic mode�� �����ϼ̽��ϴ�~~~!!! Depth�� �������ּ���. ===> ");
	scanf_s("%d", &DEPTH);
	
	return mode;	//heuristic mode�� �����ϸ� 1�� ��ȯ�ϰ�, rule-based mode�� �����ϸ� 2�� ��ȯ���ش�. 
}

int firstattack(int mode) {	//ó�� �����ϴ� ��(?)�� �������ֱ� ���� �Լ��̴�. (��, ��� ����? AI ����?)
	int sel;	//������ ���� ����
	if (mode == 1) printf("\n\n Heuristic mode�� �����ϼ̽��ϴ�.");	//heuristic mode�� ������ ��츸 ���
	else printf("\n\n Rule-based mode�� �����ϼ̽��ϴ�.");	//rule-based mode�� ������ ��츸 ���
	printf("\n ���� ���� �����Ͻðڽ��ϱ�?\n 1. User      2. AI\n ===> ");
	scanf_s("%d", &sel);
	return sel;	//����� ���� �����ϸ� 1�� ��ȯ, AI�� ���� �����ϸ� 2�� ��ȯ�Ѵ�.
}

void boardprint(char(*connectboard)[COL], int mode) {	//Ŀ��Ʈ ���带 ����Ʈ���ִ� �Լ��̴�.
	int row, column;
	system("cls"); //Ŀ��Ʈ���带 ����Ʈ�ϱ� ���� �ѹ� �����ش�.(���� ���� �������� �ʵ���!)

	if (mode == 1) {
		
		puts("\n    <<<Heuristic Mode>>>\n");	//�Ʊ� mode���ÿ� ���� ����߿� � ���� ����ϰ� �ִ����� �����ش�.
		printf("      <<<DEPTH - %d>>>\n", DEPTH);
		printf("<<<����ó���ð� - %.3f sec >>>\n", computetime);
	}
	else puts("\n    <<<Rule-based Mode>>> \n");
	printf("     <<<%d��° turn>>>\n\n", turn);
	for (row = ROW - 1; row >= 0; row--) {
		for (column = 0; column < COL; column++) {
			printf("| %c ", connectboard[row][column]);
		}
		puts("|");
		puts("-----------------------------");

	}
	puts("  1   2   3   4   5   6   7\n");
}	//https://codereview.stackexchange.com/questions/27446/connect-four-game

int whoisfirst(int sel) {	//����� ��쿡 0�� ��ȯ, AI�� ��쿡 1�� ��ȯ���ִ� �Լ��ε� ���� �ٸ� �Լ� ������ �� ������ �ֱ� ���� �Լ��̴�.
	static int num = -1;
	if (num == -1) num = sel - 1;
	return num;
}

int whoisattack(char(*connectboard)[COL], int attacker, const char *checkOX, int mode) {	//��ü������ �� �Լ��� ������ �����Ű��(?)�Լ���� ���� �ȴ�. ���������� �������� �κ��� �ô´�.
						//https://codereview.stackexchange.com/questions/27446/connect-four-game
	
	int row = 0, column = 0;

	if (attacker == whoisfirst(0)) {	//user�� ������ ��,
		printf("���° ���� �νðڽ��ϱ�? ==> ");
		scanf_s("%d", &column);	//��� ° ���ο� �� �� �������ش�.
		while (connectboard[ROW - 1][COL - 1] != ' ' && column >= 1 && column <= 7) {	//���࿡ �Է��� ������ ���� ������ ��쿡 ���� ����ó���̴�. �ٸ� ���� �Է��ϵ��� �Ѵ�.
			printf("����� ��á���ϴ�. �ٸ� ���� �μ���. ===> ");
			scanf_s("%d", &column);
			if (connectboard[ROW - 1][column - 1] == ' ') break;	//�Է��� ������ ���� ������ �ƴϸ� �հ�. �� �� �ְ� ���ش�.
		}
		while (turn == 0 && column == 4) {	//�� ���� ó���� ����� �ξ��� ���� ���� ����ó���̴�. ����� �θ� �ٸ� ���� �ε��� �����ش�.
			printf("ó������ ����� �� �� �����ϴ�. �ٽ� �Է����ּ��� ==> ");
			scanf_s("%d", &column);
		}

		while (column < 1 || column >7) {	//����ó��. ���� 7���̹Ƿ�, 1~7 �̿��� ���� �����ϸ� error�� ���� ���ش�.
			if (column != 1000)	printf("�߸� �Է��߽��ϴ�. �ٽ� �Է����ּ���. ==> ");	//�ؿ��� ����� ���� �� ����� �ߺ��Ǵ� ��츦 �����ϱ� ���� 1000�� �ƴ� ��츸 ȣ�����ش�.
			scanf_s("%d", &column);
			if (column >= 1 && column <= 7 && turn != 0) break;	//ù ��° ���� �ƴϰ�, 1~7 ���̿� ���� �Է��ϸ� break
			if (column == 4 && turn == 0) {	//�� ���� ó���� ��� -> ������ 1~7�̿��� �� -> �ٽ� ����� ���� ���� ���� ����ó���̴�.
				printf("ó������ ����� �� �� �����ϴ�. �ٽ� �Է����ּ��� ==> ");
				column = 1000;	//column�� 1000���� ó���� ���ؼ� ����� �ݺ��Ǵ� ��츦 �������ش�.
			}
		}
		column--;	//���ڿ� �Է��� ������ �ϳ��� ����� ����� �� ��ġ�� �ξ�����.(�迭�̴�)

		for (; row < ROW; row++) {	//������ ���� ���� �ؿ������� �ϳ��ϳ� ���鼭 ���������� ���� ������ �ִ� ��ġ �ٷ� ���� ���� ���ش�.
			if (connectboard[row][column] == ' ') {
				connectboard[row][column] = checkOX[attacker];
				return 1;
			}
		}
	}
	else {	//AI�� ���õǾ��� ��(user�� �ƴ� ��),
		if (turn == 0) column = 2;	//ù ��°�� �δ� ���� ��, AI�� ������ 2��°�� �ΰ� �Ѵ�(��� �� �� �����Ƿ�! �� ���� Ȯ���� ���� ���� ��).
		else {
			if (mode == 1) column = nextHeuristic();	//�� ���� heuristic mode�� �� ȣ��Ǵ� ����, ���� AI�� �� column�� heuristic ��Ŀ� ���� �������ش�.
			else column = nextRuleBased();	//����� rulebase�� �������ָ� �˴ϴ�!
			printf("\n\n%d\\n\n", whoisfirst(0));
		}
		for (; row < ROW; row++) {	//������ ���� ���� �ؿ������� �ϳ��ϳ� ���鼭 ���������� ���� ������ �ִ� ��ġ �ٷ� ���� ���� �д�.
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
	for (vector<node>::iterator iter = (*targetnode).begin(); iter != (*targetnode).end(); ) {	//��ü���͸� ���� �ݺ����̴�(vector.begin���� vector.end����. ��, ������ ù�� ° ��Һ��� ������ ��ұ��� ����.)
		for (int i = 0; i < 4; i++) {
			if ((*iter).rowcolumn[i][0] == xpos && (*iter).rowcolumn[i][1] == ypos) { //�ݺ����� ���ٰ� ������ ��ǥ�� �ִٸ�?
				node temp;
				for (int j = 0; j < 4; j++) {
					for (int k = 0; k < 2; k++) {
						temp.rowcolumn[j][k] = (*iter).rowcolumn[j][k]; //�ӽó�带 �����Ͽ� �������ش�.
					}
				}
				(*tempnode).push_back(temp); // ������ node�� temp(��������)�� �ְ�
				iter = (*targetnode).erase(iter); // win���� �����Ѵ�.				~~�� �κ��� ���ذ� �� �Ȱ��� �� �� �����ϰ� �ٽ� ���߰ڽ��ϴ�!
				break;
			}
			if (i == 3) ++iter; //���� �� ������ ���� node�� ���ֱ� �����̴�. 
		}
	}
}

void recover(vector<node>* targetnode, vector<node>* tempnode) {
	while (!(*tempnode).empty()) { //tempnode�� �� ������ �ݺ����ش�.
		(*targetnode).push_back((*tempnode).back()); //tempnode�� �� �ڿ� ��Ҹ� targetnode�� �־��ش�.
		(*tempnode).pop_back(); //tempnode�� �� node�� ���ش�.
	}
}

void status() {
	recover(&FirstWIN, &FirstTEMP); //FirstWin ���Ͱ� �ٸ� �۾��� �ϸ鼭 ������ ������ ��찡 ������, ������� �����ش�.
	recover(&SecondWIN, &SecondTEMP); //SecondWin ���Ͱ� �ٸ� �۾��� �ϸ鼭 ������ ������ ��찡 ������, ������� �����ش�.
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) { //Ŀ��Ʈ���带 ��ü������ ���鼭
			if (connectboard[i][j] == 'X') remove(&FirstWIN, &FirstTEMP, i, j); //X�� ��ǥ i��j���� �ִٸ�, FirstWin���Ϳ��� �������ش�.
			else if (connectboard[i][j] == 'O') remove(&SecondWIN, &SecondTEMP, i, j); //O�� ��ǥ i��j���� �ִٸ�, SecondWin���Ϳ��� �������ش�.
		}
	}
}

int finishcheck(char(*connectboard)[COL]) {	//�� �Լ��� �����°� üũ���ִ� �Լ��̴�. ������ ������ ��쿡 1�� ��ȯ���ش�.
							//https://codereview.stackexchange.com/questions/27446/connect-four-game

	for (int row = 0; row < ROW; row++) {	//Ŀ��Ʈ���带 ó������ �� ���鼭 ���η� 4���� ���� �ϼ��Ǿ� ������ ��찡 �ִ��� Ȯ���� �Ѵ�.
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
	for (int row = 0; row < ROW - 3; row++) {	//�� ���� ���鼭 ���η� ���� ��찡 �ִ��� Ȯ�����ش�.
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

	for (int row = 0; row < ROW - 3; row++) {	//�� ���� ���鼭 ���� �Ʒ����� ������ ���� ������ ��찡 �ִ��� Ȯ�����ش�.
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

	for (int row = 0; row < ROW - 3; row++) {	//�� ���� ���鼭 ������ �Ʒ����� ���� ���� ������ ��찡 �ִ��� Ȯ�����ش�.
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
	return 0;	//��� üũ�Ͽ� ������ 0�� ��ȯ���ش�.(������ ���� ����)
}