#include"question.h"
#include"exam_japanese.h"
#include"exam_mathematics.h"
#include"exam_enlish.h"
#include"exam_science.h"
#include"exam_gegraphy.h"
#include"exam_politics.h"
#include"exam_economics.h"
#include"utility.h"
#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;






int main() {

    //���ȃf�[�^�z��
    static const struct {
        const char* name;  //���Ȗ�
        QuestionList(*create)(); //���쐬�֐��̃A�h���X
    }subjectData[] = {
        {"���w",CreateMathematicsExam},
        {"����",CreateJapaneseExam},
        {"�p��",CreateEnglishExam},
        {"����",CreatePhysicsExam},
        {"�n��",CreatePrefecturesExam},
        {"����",CreatePoliticsExam},
        {"�o��",CreateEconomicsExam},

    };

    vector<Question> questions(3); // 3�̖���p�ӂ���

   
    int subject;
    cout << "[���N���[�g�����΍�N�C�Y]\n";

    cout << "���Ȃ�I��ł�������\n";

    for (int i = 0; i < size(subjectData); i++) {
        cout << i + 1 << "=" << subjectData[i].name << "\n";
    }
    cin >> subject;

    if (subject > 0 && subject <= size(subjectData)) {
        questions = subjectData[subject - 1].create();
   }


    for (const auto& e : questions) {
        cout << e.q << " \n"; // ��蕶��\��

        string answer;
        cin >> answer; // ���[�U�[����̓��͂��󂯎��

        const string ascii = ConvertSjisNumberToAscii(answer);
        //�ϊ������������ꍇ�͕������u��������
        if (!ascii.empty())
        {
            answer = ascii;
        }
        if (answer == e.a) {
            cout << "�����I" << endl;
        }
        else if(e.b.empty()) {
            cout << "�ԈႢ�I ������ " << e.a << " �ł��B" << endl;
        }
        else {
            //��������������ꍇ�A�����ꂩ����v����ΐ����Ƃ���
            bool isMatch = false;
            for (const auto& b : e.b) {
                if (answer == b) {
                    isMatch = true; //��v���铚������������
                    break;
                }
            }
            //��r���ʂ��o��
            if (isMatch) {
                cout << "����!\n";
            }
            else {
                cout << "�ԈႢ! ������" << e.a << "(�܂���";
                for (auto& b : e.b) {
                    cout << "," << b;
                }
                cout << ")\n";
            }
        }
    }

    return 0;
}
