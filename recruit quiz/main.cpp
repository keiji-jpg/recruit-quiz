#include<iostream>
#include<string>
using namespace std;

//��蕶�Ɠ������܂Ƃ߂�\����
struct Question
{
	string s; //��蕶
	int a;    //����
};

int main() {
	Question questions[] = {
		{"13*(-5)",13*-5},
		{"(-21)/(-3)", -21 / 3},
		{"7-(4+2)/2", 7 - (4 + 2) / 2},
	};

	cout << "[���N���[�g�����΍�N�C�Y]\n";
	
	for (const auto& e : questions) {
		cout << e.s << "�̓�����?\n";


		int answer;
		cin >> answer;
		if (answer == e.a)
		{
			cout << "����" << endl;
		}
		else {
			cout << "�ԈႢ�I������" <<e.s << endl;
		}
	} //for questions
}