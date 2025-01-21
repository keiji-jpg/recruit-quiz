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

   
 
    cout << "[���N���[�g�����΍�N�C�Y]\n";

    cout << "���Ȃ�I��ł�������\n";
    cout << "0=�����e�X�g\n";

    for (int i = 0; i < size(subjectData); i++) {
        cout << i + 1 << "=" << subjectData[i].name << "\n";
    }

    vector<int> questionCounts(size(subjectData));//�e���Ȃ̖�萔
    int subject;
    cin >> subject;
    if (subject > 0 && subject <= size(subjectData)) {
        questions = subjectData[subject - 1].create();
    }
    else if (subject == 0) {
        //�����e�X�g
        questions.clear();
        for (int i = 0; i<size(subjectData);i++) {
            QuestionList tmp = subjectData[i].create();
            questions.insert(questions.end(), tmp.begin(), tmp.end());
            questionCounts[i] = (int)tmp.size();
        }
    }

    vector<int> correctCounts(size(subjectData)); //�e���Ȃ̐�����
    int currentSubjectNo = 0;   //�o�蒆�̋��Ȕԍ�
    int currentAnsweredCount = 0;//�񓚍ς݂̖�萔
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
            correctCounts[currentSubjectNo]++; //�������𑝂₷
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
                correctCounts[currentSubjectNo]++; //�������𑝂₷
            }
            else {
                cout << "�ԈႢ! ������" << e.a << "(�܂���";
                for (auto& b : e.b) {
                    cout << "," << b;
                }
                cout << ")\n";
            }
            //�u�񓚍ςݖ�萔�v���u���Ȃ̖�萔�v�ȊO�ɂȂ�����A���̋��Ȃɐi��
            if (subject == 0) {
                currentAnsweredCount++; //�񓚍ςݖ�萔�𑝂₷
                if (currentAnsweredCount >= questionCounts[currentSubjectNo]) {
                    currentSubjectNo++; //���̋��Ȃɐi��
                    currentAnsweredCount = 0; //�񓚍ςݖ�萔�����Z�b�g
                }
            }// if subject ==0
        } //for questions

        //���т�\��
        cout << "\n--- ���� ---\n";
        if (subject > 0 && subject <= size(subjectData)) {
            cout << subjectData[subject - 1].name << ":"
                << correctCounts[0] << '/' << questions.size() << '\n';
        }
        else if (subject == 0) {
            //���Ȃ��Ƃɐ��т�\�����A�������̍��v���v�Z
            size_t totalCorrectCount = 0; //�������̍��v
            for (int i = 0; i < size(subjectData); i++) {
                cout << subjectData[i].name << ":"
                    << correctCounts[i] << '/' << questionCounts[i] << '\n';
                totalCorrectCount += correctCounts[i];
            }
            cout << "���v:" << totalCorrectCount << '/' << questions.size() << '\n';
        }
    }

    return 0;
}
