#include "exam_politics.h"
#include "utility.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_map>
#include <vector>
using namespace std;

QuestionList CreatePoliticsExam() {
    struct PoliticsData {
        string genre;        // ジャンル
        string text;         // 問題文
        vector<string> answers; // 答え
    };

    unordered_map<string, vector<PoliticsData>> data;

    // 政治問題をデータを読み込む
    {
        constexpr char filename[] = "japanese_politics.txt";
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "エラー: " << filename << " 読み込めません\n";
            return {};
        }

        while (true) {
            string s;
            getline(ifs, s);
            if (!ifs) break; // ファイル終端に達したので終了
            const vector<string> v = Split(s, ',');
            const string& genre = v[0]; // ジャンルを取得
            data[genre].push_back({ genre, v[1], vector<string>(v.begin() + 2, v.end()) });
        }
    }

    constexpr int genreCount = 2; // 出題するジャンル数
    constexpr int quizCount = 5;  // 各ジャンルの出題数
    QuestionList questions;
    questions.reserve(genreCount * quizCount);
    random_device rd;

    const vector<int> genreIndices = CreateRandomIndices((int)data.size());
    for (int i = 0; i < genreCount; i++) {
        // 出題するジャンルを選択
        auto itr = data.begin();
        advance(itr, genreIndices[i]); // 参照位置を指定したところまで進める
        const auto& genre = itr->second;

        // ジャンル内でランダムに5問選ぶ
        const vector<int> questionIndices = CreateRandomIndices((int)genre.size());
        for (int j = 0; j < quizCount; j++) {
            const auto& selectedQuestion = genre[questionIndices[j]]; // 選んだ問題データ

            vector<int> blanks;
            for (int k = 0; k < selectedQuestion.text.size() - 1; k++) {
                if (selectedQuestion.text[k] == '{' && selectedQuestion.text[k + 1] == '}') {
                    blanks.push_back(k);
                }
            }

            const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

            string s = "[" + selectedQuestion.genre + "] 次の文章の[ ? ]に入る単語を答えよ\n";
            int from = 0;
            for (int k = 0; k < blanks.size(); k++) {
                const int end = blanks[k];
                s.append(selectedQuestion.text, from, end - from);
                if (k != index) {
                    s += selectedQuestion.answers[k];
                }
                else {
                    s.append("[ ? ]"); //選ばれた空欄の場合は[表示用の空欄文字列]コピー
                }
                from = end + 2;
            }
            s.append(selectedQuestion.text, from);

            questions.push_back({ s, selectedQuestion.answers[index] }); // 修正済み
        }
    }

    return questions;
}
