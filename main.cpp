//�ڵ��ۼ�: ������
#include "node.h"

extern char connectboard[ROW][COL];	//Ŀ��Ʈ���� ����
extern int turn;
extern const char *checkOX;
int first = 0, finish = 0;
int main() {
	init();	//��� �¸��� ����� ���� �����ش�.
	memset(connectboard, ' ', ROW*COL);	//������ size(6x7)��ŭ �迭 �ʱ�ȭ
	int AImode = selectmode();	//AImode���� - selectmode�Լ��� ���� �Է¹��� ������ heuristic mode�� �����ϸ� 1�� ���Ϲް�, rule-based mode�� �����ϸ� 2�� ���Ϲ޴´�.
	while (first != 1 && first != 2) {	//������ �����ϴ� ���, 1(user����)�� 2(AI����) �̿ܿ� ���� �Է��ϸ�, ����� �Է��� ������ �ݺ���
		first = firstattack(AImode);
		if (first == 1 || first == 2) break;
		printf("\n�߸��� ���ڸ� �Է��ϼ̽��ϴ�. �ٽ� �Է����ּ���.");
	}
	whoisfirst(first);	//ù��° �����ϴ� ����� ���� user���� => 0 return, AI���� => 1�� return���ش�.
	int time = 5;	//���º��� �� �������ֱ� ���� �ӽú���
	while (true) {	//main�Լ��� �ָ� �̷�� �κ�. ������ ���������� �ݺ���
		boardprint(connectboard, AImode);	//connectboad�� ����Ʈ���ִ� �Լ�(AImode�� ���� �ٸ��� ���)
		if (finishcheck(connectboard) == 1) {	//finishcheck�Լ��� ���� ������ ������ 1�� return, �������̸� 0�� return���ش�.
			printf("�������ϴ�. �����ϼ̽��ϴ�!!!!\n");
			Sleep(3000);
			break;
		}
		whoisattack(connectboard, turn % 2, checkOX, AImode);	//�������ִ� �Լ�. turn���� ���� �����ְ�(%2), AImode�� ���� �ٸ� ����(heuristic, rule-based)�� ���Ѵ�.

		turn++;

		if (turn == 42 && finish == 0) {	//�� ���� ���� �� �� ������ �ºΰ� �ȳ� ����̴�. ���º�ó���ϰ� 5�� �� ���α׷� �������ش�.
			while (true) {
				boardprint(connectboard, AImode);
				printf("���º��Դϴ�~~~~~~~~�����ϼ̽��ϴ�!!!\n5�� �ڿ� ���α׷��� ����˴ϴ�.\n������� ���� �ð� : ");
				printf("%d", time);
				Sleep(1000);
				time--;
				if (time == 0) return 0;
			}
		}
	}

	system("pause");	//�̰� �����ִϱ� ��� �����淡 �ϴ� �س��Ҵ�.
	return 0;
}