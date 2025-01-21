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
    vector<Question> questions(3); // 3�̖���p�ӂ���

   

    cout << "[���N���[�g�����΍�N�C�Y]\n";

    cout << "���Ȃ�I��ł�������\nn1=���w\nn2=����\nn3=�p��\nn4=����\nn5=�n��\nn=6����\nn=7�o��\n";
    int subject;

    cin >> subject;

    if (subject == 1) {
        questions = CreateMathematicsExam();
    }
    else if (subject == 2)
    {
        questions = CreateKanjiExam();
        const QuestionList idiomExam = CreateIdiomExam();
        questions.insert(questions.end(), idiomExam.begin(), idiomExam.end());
        QuestionList HomophoneExam = CreateHomophoneExam();
        questions.insert(questions.end(), HomophoneExam.begin(), HomophoneExam.end());
        QuestionList antonymExam = CreateAntonymExam();
        questions.insert(questions.end(), antonymExam.begin(), antonymExam.end());
        QuestionList synoymExam = CreateSynonymExam();
        questions.insert(questions.end(), synoymExam.begin(), synoymExam.end());
    }
    else if (subject == 3) {
        questions = CreateEnglishWordExam();
        QuestionList phraseExam = CreateEnglishPhraseExam();
        questions.insert(questions.end(), phraseExam.begin(), phraseExam.end());
    }
    else if (subject == 4) {
        questions = CreatePhysicsExam();
    }
    else if (subject == 5) {
        questions = CreatePrefecturesExam();
    }
    else if (subject == 6) {
        questions = CreatePoliticsExam();
    }
    else if (subject == 7) {
        questions = CreateEconomicsExam();
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
