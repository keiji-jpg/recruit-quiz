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
    vector<Question> questions(3); // 3つの問題を用意する

   

    cout << "[リクルート試験対策クイズ]\n";

    cout << "教科を選んでください\nn1=数学\nn2=国語\nn3=英語\nn4=理科\nn5=地理\nn=6政治\nn=7経済\n";
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
        cout << e.q << " \n"; // 問題文を表示

        string answer;
        cin >> answer; // ユーザーからの入力を受け取る

        const string ascii = ConvertSjisNumberToAscii(answer);
        //変換が成功した場合は文字列を置き換える
        if (!ascii.empty())
        {
            answer = ascii;
        }
        if (answer == e.a) {
            cout << "正解！" << endl;
        }
        else if(e.b.empty()) {
            cout << "間違い！ 正解は " << e.a << " です。" << endl;
        }
        else {
            //答えが複数ある場合、いずれかち一致すれば正解とする
            bool isMatch = false;
            for (const auto& b : e.b) {
                if (answer == b) {
                    isMatch = true; //一致する答えが見つかった
                    break;
                }
            }
            //比較結果を出力
            if (isMatch) {
                cout << "正解!\n";
            }
            else {
                cout << "間違い! 正解は" << e.a << "(または";
                for (auto& b : e.b) {
                    cout << "," << b;
                }
                cout << ")\n";
            }
        }
    }

    return 0;
}
