#include<iostream>
#include<string>
#include<random>
using namespace std;

// ��蕶�Ɠ������܂Ƃ߂�\����
struct Question
{
	string q; // ��蕶
	int a;    // ����
};

int main() {
	Question questions[3]; // 3�̖���p�ӂ���

	random_device rd;
	mt19937 rand(rd());

	// �|���Z
	int x = uniform_int_distribution<>(1, 30)(rand);
	int y = uniform_int_distribution<>(1, 20)(rand);
	questions[0].q = to_string(x) + " �~ " + to_string(y); // ��蕶���쐬
	questions[0].a = x * y; // �������v�Z

	// ����Z
	x = uniform_int_distribution<>(1, 100)(rand);
	y = uniform_int_distribution<>(1, 10)(rand);
	questions[1].q = to_string(x * y) + " �� " + to_string(y); // ��蕶���쐬
	questions[1].a = x; // �������v�Z

	// ���G�Ȏ�
	x = uniform_int_distribution<>(1, 100)(rand);
	y = uniform_int_distribution<>(1, 10)(rand);
	int z = uniform_int_distribution<>(1, 10)(rand);
	int w = uniform_int_distribution<>(1, 10)(rand);
	questions[2].q = 
		to_string(x) + " - (" + to_string(y * w) + " + " + to_string(z * w) + ") �� " + to_string(w); // ��蕶���쐬
	questions[2].a = x - (y + z); // �������v�Z

	cout << "[���N���[�g�����΍�N�C�Y]\n";

	for (const auto& e : questions) {
		cout << e.q << " �̓�����?\n"; // ��蕶��\��

		int answer;
		cin >> answer; // ���[�U�[����̓��͂��󂯎��
		if (answer == e.a) {
			cout << "�����I" << endl;
		}
		else {
			cout << "�ԈႢ�I ������ " << e.a << " �ł��B" << endl;
		}
	}

	return 0;
}
