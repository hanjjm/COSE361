//�ڵ��ۼ�: ������ ������
#include "node.h"

extern char connectboard[ROW][COL];



const int oderarray[7] = { 3, 2, 4, 1, 5, 0, 6 };//�� ���� �켱���� �迭


int CentralCheck(int col, char OX) {
	//�� ���� �ڸ����� ���� �������� �ִ��� �˻����ִ� �Լ�(2��->3 �ش� �ڸ��� ������ �� 2�� �̻�->2 ��ȯ




	int checknearby = 0;//������ ���� ���� ����


	if (col < 6 && col>0) {//1���� 7�� ����ó��(�迭 ũ�⸦ �Ѿ�Ƿ�)
		if (connectboard[height(col)][col - 1] == OX && connectboard[height(col)][col + 1] == OX) { //���� �� �˻�

			if (col < 5) {
				if (connectboard[height(col)][col + 2] == ' ') {//�ش� ������ ������ �ڸ��� ����ִ��� �˻�->������ 3��ȯ

					return 3;
				}
			}
			if (col > 1) {
				if (connectboard[height(col)][col - 2] == ' ') {//�ش� ������ ���� �ڸ��� ����ִ��� �˻�->������ 3��ȯ

					return 3;
				}
			}
		}
	}

	if (height(col) > 0 && col > 0 && height(col) < 6 && col < 6) {//1��,7��,1��,7�� ����ó��(�迭 ũ�⸦ �Ѿ�Ƿ�)
		if (connectboard[height(col) - 1][col - 1] == OX && connectboard[height(col) + 1][col + 1] == OX) {//�������� �밢�� 
			if (col > 1 && height(col) > 1) {//2��,2�� ����ó��(�迭 ũ�⸦ �Ѿ�Ƿ�)
				if (connectboard[height(col) - 2][col - 2] == ' ') {//�ش� ������ ���� �Ʒ��� ������� �˻�->������ 3��ȯ			

					return 3;
				}
			}
			if (col < 5 && height(col) < 5) {//6��,6�� ����ó��(�迭 ũ�⸦ �Ѿ�Ƿ�)
				if (connectboard[height(col) + 2][col + 2] == ' ') {//�ش� ������ ������ ���� ������� �˻�->������ 3��ȯ
					return 3;
				}
			}
		}
		if (connectboard[height(col) - 1][col + 1] == OX && connectboard[height(col) + 1][col - 1] == OX) {//���� �� �밢�� �˻�

			if (height(col) > 1 && col < 5) {
				if (connectboard[height(col) - 2][col + 2] == ' ') {//�ش� �����ǿ����� �Ʒ��� ������� �˻�
					return 3;
				}
			}
			if (height(col) < 5 && col > 1) {
				if (connectboard[height(col) + 2][col - 2] == ' ') {//�ش� ������ ���� ���� ������� �˻�	
			
					

					return 3;
				}
			}

		}


		


		if (height(col) > 0 && col > 0) {//1��,1�� ����ó��(�迭 ũ�⸦ �Ѿ�Ƿ�)
			if (connectboard[height(col) + 1][col - 1] == OX)checknearby++;//�»����� �̿��� ���� �ִ���?
			if (connectboard[height(col)][col - 1] == OX)checknearby++;//������ �̿��� ���� �ִ���?
			if (connectboard[height(col) - 1][col - 1] == OX)checknearby++;//�������� �̿��� ���� �ִ���?
			if (connectboard[height(col) - 1][col] == OX)checknearby++;//�Ʒ����� �̿��� ���� �ִ���?
			if (connectboard[height(col) - 1][col + 1] == OX)checknearby++;//�������� �̿��� ���� �ִ���?
			if (connectboard[height(col)][col + 1] == OX)checknearby++;//������ �̿��� ���� �ִ���?
			if (connectboard[height(col) + 1][col + 1] == OX)checknearby++;//������� �̿��� ���� �ִ���?
		}

		if (checknearby >= 2) {//�̿��� ���� 2�� �̻��� ��� 2�� ��ȯ

			return 2;
		}

	}

	return 1;//��� ���� ��� 1��ȯ

}

int RuleBased(char OX) {

	if (OX == 'O') {//�ڽ��� ���� O�� ���
		for (int i = 0; i < COL; i++) {//�ڽ��� ���� 3�� ���� ������ �ִ°�� 4���� �ϼ��Ͽ� �¸��ϴ� �ڵ�
			if (height(i) != 6) {//�ش� ���� ������ �ʾ�����
				connectboard[height(i)][i] = 'O';//�ش� ���� ���� ����			

				if (checkScore('O') == 276) { //�ڽ��� ���� 4�� �ϼ�(276��)�� �Ǵ� ���
					connectboard[height(i) - 1][i] = ' ';//���� �ٽ� �����					
					status();
					return i; //�ش� ���� ��ȯ
				}
				connectboard[height(i) - 1][i] = ' ';
				status();
			}

		}
	}
	else {//�ڽ��� ���� X�� ��� OX�� X�� ���� ���� ó��
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

	if (OX == 'O') {//����� ���� 3�� ���� ������ �ִ°�� �̸� ���� �ڵ�
		for (int i = 0; i < COL; i++) {//���ƺ��� ���� �ݴ��(X)�ϰ� ����ó��
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
	else {//���ƺ��� ���� �ݴ��(O)�ϰ� ����ó��
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
			if (height(oderarray[i]) != 6) {//�켱����(�켱���� �迭)�� ���� �˻�
				if (CentralCheck(oderarray[i], 'X') == 3) {
					//CentralCheck ��ȯ ���� 3->�Լ������� �� ��¥�� ����(3�� �����)�� ���
					return oderarray[i];
				}
			}
		}


		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 3) {
					//CentralCheck ��ȯ ���� 3->�ڽ��� �� ��¥�� ����(3�� �����)
					return oderarray[i];
				}
			}
		}
	}
	else {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 3) {
					//CentralCheck ��ȯ ���� 3->�Լ������� �� ��¥�� ����(3�� �����) ���
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 3) {
					//CentralCheck ��ȯ ���� 3->�ڽ��� �� ��¥�� ����(3�� �����)						
					return oderarray[i];
				}
			}
		}
	}



	if (OX == 'O') {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 2) {
					//CentralCheck ��ȯ ���� 2->����� �̿����� 2���̻��� �ڸ��� ���
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 2) {
					//CentralCheck ��ȯ ���� 2->�ڽ��� �̿����� 2���̻��� �ڸ��� ����

					return oderarray[i];
				}
			}
		}
	}
	else {
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'O') == 2) {
					//CentralCheck ��ȯ ���� 2->����� �̿����� 2���̻��� �ڸ��� ���
					return oderarray[i];
				}
			}
		}
		for (int i = 0; i < COL; i++) {
			if (height(oderarray[i]) != 6) {
				if (CentralCheck(oderarray[i], 'X') == 2) {
					//CentralCheck ��ȯ ���� 2->�ڽ��� �̿����� 2���̻��� �ڸ��� ����
					return oderarray[i];
				}
			}
		}
	}



	for (int i = 0; i < COL; i++) {//������ ��� �켱������ ���� �� ��ȯ
		if (height(oderarray[i]) != 6) {
			return oderarray[i];
		}
	}



}


int nextRuleBased() {	//�� �Լ��� whoisattack���� ȣ��Ǵ� �Լ���, rule-based mode�� �� ��쿡 ���� ���õǴ� column�� ã���ִ� �Լ��̴�.
	int column;
	char OX = (whoisfirst(0) == 0) ? 'X' : 'O';	//user�� ���� �δ� ���쿡 ���� 'X'�̰�, AI�� ���� �ִ� ���� ���� 'O'�̴�.
	status();


	column = RuleBased(OX);
	return column;
}