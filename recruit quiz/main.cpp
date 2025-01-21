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

    //教科データ配列
    static const struct {
        const char* name;  //教科名
        QuestionList(*create)(); //問題作成関数のアドレス
    }subjectData[] = {
        {"数学",CreateMathematicsExam},
        {"国語",CreateJapaneseExam},
        {"英語",CreateEnglishExam},
        {"物理",CreatePhysicsExam},
        {"地理",CreatePrefecturesExam},
        {"政治",CreatePoliticsExam},
        {"経済",CreateEconomicsExam},

    };

    vector<Question> questions(3); // 3つの問題を用意する

   
    int subject;
    cout << "[リクルート試験対策クイズ]\n";

    cout << "教科を選んでください\n";

    for (int i = 0; i < size(subjectData); i++) {
        cout << i + 1 << "=" << subjectData[i].name << "\n";
    }
    cin >> subject;

    if (subject > 0 && subject <= size(subjectData)) {
        questions = subjectData[subject - 1].create();
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
