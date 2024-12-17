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
        string genre;        // �W������
        string text;         // ��蕶
        vector<string> answers; // ����
    };

    unordered_map<string, vector<PoliticsData>> data;

    // ���������f�[�^��ǂݍ���
    {
        constexpr char filename[] = "japanese_politics.txt";
        ifstream ifs(filename);
        if (!ifs) {
            cerr << "�G���[: " << filename << " �ǂݍ��߂܂���\n";
            return {};
        }

        while (true) {
            string s;
            getline(ifs, s);
            if (!ifs) break; // �t�@�C���I�[�ɒB�����̂ŏI��
            const vector<string> v = Split(s, ',');
            const string& genre = v[0]; // �W���������擾
            data[genre].push_back({ genre, v[1], vector<string>(v.begin() + 2, v.end()) });
        }
    }

    constexpr int genreCount = 2; // �o�肷��W��������
    constexpr int quizCount = 5;  // �e�W�������̏o�萔
    QuestionList questions;
    questions.reserve(genreCount * quizCount);
    random_device rd;

    const vector<int> genreIndices = CreateRandomIndices((int)data.size());
    for (int i = 0; i < genreCount; i++) {
        // �o�肷��W��������I��
        auto itr = data.begin();
        advance(itr, genreIndices[i]); // �Q�ƈʒu���w�肵���Ƃ���܂Ői�߂�
        const auto& genre = itr->second;

        // �W���������Ń����_����5��I��
        const vector<int> questionIndices = CreateRandomIndices((int)genre.size());
        for (int j = 0; j < quizCount; j++) {
            const auto& selectedQuestion = genre[questionIndices[j]]; // �I�񂾖��f�[�^

            vector<int> blanks;
            for (int k = 0; k < selectedQuestion.text.size() - 1; k++) {
                if (selectedQuestion.text[k] == '{' && selectedQuestion.text[k + 1] == '}') {
                    blanks.push_back(k);
                }
            }

            const int index = uniform_int_distribution<>(0, (int)blanks.size() - 1)(rd);

            string s = "[" + selectedQuestion.genre + "] ���̕��͂�[ ? ]�ɓ���P��𓚂���\n";
            int from = 0;
            for (int k = 0; k < blanks.size(); k++) {
                const int end = blanks[k];
                s.append(selectedQuestion.text, from, end - from);
                if (k != index) {
                    s += selectedQuestion.answers[k];
                }
                else {
                    s.append("[ ? ]"); //�I�΂ꂽ�󗓂̏ꍇ��[�\���p�̋󗓕�����]�R�s�[
                }
                from = end + 2;
            }
            s.append(selectedQuestion.text, from);

            questions.push_back({ s, selectedQuestion.answers[index] }); // �C���ς�
        }
    }

    return questions;
}
