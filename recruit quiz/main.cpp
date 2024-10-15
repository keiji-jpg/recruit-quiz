#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;

// ��蕶�Ɠ������܂Ƃ߂�\����
struct Question
{
    string q; // ��蕶
    string a; // ����
};

//�ő���񐔂����߂�
int gcd(int a, int b) {
    //�]�肪0�ɂȂ������̏�����Ԃ�
    while (b) {
        int r = a % b;
        a = b; //���������̔폜���ɂ���
        b = r; //�]������̏����ɂ���
    }
    return a;
}




int main() {
    vector<Question> questions(3); // 3�̖���p�ӂ���

    random_device rd;
    mt19937 rand(rd());

    // �|���Z
    int x = uniform_int_distribution<>(1, 30)(rand);
    int y = uniform_int_distribution<>(1, 20)(rand);
    questions[0].q = to_string(x) + " �~ " + to_string(y) + "�̓�����?"; // ��蕶���쐬
    questions[0].a = to_string(x * y); // �������v�Z

    // ����Z
    x = uniform_int_distribution<>(1, 100)(rand);
    y = uniform_int_distribution<>(1, 10)(rand);
    questions[1].q = to_string(x * y) + " �� " + to_string(y) + "�̓�����?"; // ��蕶���쐬
    questions[1].a = to_string(x); // �������v�Z

    // ���G�Ȏ�
    x = uniform_int_distribution<>(1, 100)(rand);
    y = uniform_int_distribution<>(1, 10)(rand);
    int z = uniform_int_distribution<>(1, 10)(rand);
    int w = uniform_int_distribution<>(1, 10)(rand);
    questions[2].q =
        to_string(x) + " - (" + to_string(y * w) + " + " + to_string(z * w) + ") �� " + to_string(w) + "�̓�����?"; // ��蕶���쐬
    questions[2].a = to_string(x - (y + z)); // �������v�Z

    // �O�p�`�̖ʐ�
    x = uniform_int_distribution<>(1, 10)(rand);
    y = uniform_int_distribution<>(1, 5)(rand) * 2;
    questions.push_back({
        "�ʐ�" + to_string(x * y / 2) + "cm^2�A���" + to_string(y) + "cm�̎O�p�`�̍��������߂�B",
        to_string(x) });

    // �~���̑̐�
    x = uniform_int_distribution<>(1, 10)(rand);
    y = uniform_int_distribution<>(1, 5)(rand) * 3;
    questions.push_back({
        "��ʂ̔��a" + to_string(x) + "cm�A����" + to_string(y) + "cm�̉~��������B\n" +
        "���̉~���̑̐ς�X��cm^3�Ƃ���BX�̒l�����߂�B", to_string(x * x * y / 3) });

    // ���̑̐�
    x = uniform_int_distribution<>(1, 10)(rand);
    questions.push_back({
        "���a" + to_string(x) + "cm�̋�������B\n" +
        "���̋��̑̐ς�X��cm^3�Ƃ���BX�̒l�����߂�B", to_string(4 * x * x * x / 3) });


    //�T�C�R���̊m��
    x = uniform_int_distribution<>(1, 5)(rand);
    y = uniform_int_distribution<>(1, 6 - x)(rand);
    z = gcd(y + 1, 6);
    questions.push_back({
        "�T�C�R���ӂ��āA" + to_string(x) + "����" + to_string(x + y) +
        "���o��m�������߂�B",
        to_string((y + 1) / z) + "/" + to_string(6 / z) });
    cout << "[���N���[�g�����΍�N�C�Y]\n";

    for (const auto& e : questions) {
        cout << e.q << " \n"; // ��蕶��\��

        string answer;
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
