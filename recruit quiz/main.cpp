#include"question.h"
#include"exam_japanese.h"
#include"exam_enlish.h"
#include"exam_science.h"
#include"exam_gegraphy.h"
#include"exam_politics.h"
#include<iostream>
#include<string>
#include<vector>
#include<random>
using namespace std;



//最大公約数を求める
int gcd(int a, int b) {
    //余りが0になった時の除数を返す
    while (b) {
        int r = a % b;
        a = b; //除数を次の被除数にする
        b = r; //余りを次の除数にする
    }
    return a;
}




int main() {
    vector<Question> questions(3); // 3つの問題を用意する

    random_device rd;
    mt19937 rand(rd());

    // 掛け算
    int x = uniform_int_distribution<>(1, 30)(rand);
    int y = uniform_int_distribution<>(1, 20)(rand);
    questions[0].q = to_string(x) + " × " + to_string(y) + "の答えは?"; // 問題文を作成
    questions[0].a = to_string(x * y); // 答えを計算

    // 割り算
    x = uniform_int_distribution<>(1, 100)(rand);
    y = uniform_int_distribution<>(1, 10)(rand);
    questions[1].q = to_string(x * y) + " ÷ " + to_string(y) + "の答えは?"; // 問題文を作成
    questions[1].a = to_string(x); // 答えを計算

    // 複雑な式
    x = uniform_int_distribution<>(1, 100)(rand);
    y = uniform_int_distribution<>(1, 10)(rand);
    int z = uniform_int_distribution<>(1, 10)(rand);
    int w = uniform_int_distribution<>(1, 10)(rand);
    questions[2].q =
        to_string(x) + " - (" + to_string(y * w) + " + " + to_string(z * w) + ") ÷ " + to_string(w) + "の答えは?"; // 問題文を作成
    questions[2].a = to_string(x - (y + z)); // 答えを計算

    // 三角形の面積
    x = uniform_int_distribution<>(1, 10)(rand);
    y = uniform_int_distribution<>(1, 5)(rand) * 2;
    questions.push_back({
        "面積" + to_string(x * y / 2) + "cm^2、底辺" + to_string(y) + "cmの三角形の高さを求めよ。",
        to_string(x) });

    // 円錐の体積
    x = uniform_int_distribution<>(1, 10)(rand);
    y = uniform_int_distribution<>(1, 5)(rand) * 3;
    questions.push_back({
        "底面の半径" + to_string(x) + "cm、高さ" + to_string(y) + "cmの円錐がある。\n" +
        "この円錐の体積をXπcm^3とする。Xの値を求めよ。", to_string(x * x * y / 3) });

    // 球の体積
    x = uniform_int_distribution<>(1, 10)(rand);
    questions.push_back({
        "半径" + to_string(x) + "cmの球がある。\n" +
        "この球の体積をXπcm^3とする。Xの値を求めよ。", to_string(4 * x * x * x / 3) });


    //サイコロの確率
    x = uniform_int_distribution<>(1, 5)(rand);
    y = uniform_int_distribution<>(1, 6 - x)(rand);
    z = gcd(y + 1, 6);
    questions.push_back({
        "サイコロふって、" + to_string(x) + "から" + to_string(x + y) +
        "が出る確率を求めよ。",
        to_string((y + 1) / z) + "/" + to_string(6 / z) });
    

    //順列
    x = uniform_int_distribution<>(3, 7)(rand);
    y = uniform_int_distribution<>(1, x)(rand);
    z = 1;
    for (int i = 0; i < y; i++) {
        z *= x - 1;
    }
    questions.push_back({
        to_string(x) + "人のうち" + to_string(y) + "人を選んで選べる方法は何通りあるか?",
        to_string(z) });


    //組み合わせ
    x = uniform_int_distribution<>(3, 6)(rand);
    y = uniform_int_distribution<>(1, x)(rand);
    z = 1;
    for (int i = 0; i < y; i++) {
        z *= x - i;
    }
    for (int i = 0; i < y; i++) {

        z /= y - i;
    }
    questions.push_back({
        to_string(x) + "人のうち" + to_string(y) + "人を選ぶ組み合わせは何通りあるか?",
        to_string(z) });

    cout << "[リクルート試験対策クイズ]\n";

    cout << "教科を選んでください\nn1=数学\nn2=国語\nn3=英語\nn4=理科\nn5=地理\nn=6政治\n";
    int subject;

    cin >> subject;
    if (subject == 2) {
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


    for (const auto& e : questions) {
        cout << e.q << " \n"; // 問題文を表示

        string answer;
        cin >> answer; // ユーザーからの入力を受け取る
        if (answer == e.a) {
            cout << "正解！" << endl;
        }
        else {
            cout << "間違い！ 正解は " << e.a << " です。" << endl;
        }
    }

    return 0;
}
