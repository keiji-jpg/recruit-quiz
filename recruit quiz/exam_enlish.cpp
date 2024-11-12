#include"exam_enlish.h"
#include"utility.h"
#include<random>
using namespace std;

QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word; // 英単語
		const char* reading;//読み
		const char* meanig; //意味

	}data[] = {
		{"state","ステート","状態"},
		{"business","ビジネス","事業、仕事"},
		{"abstract","アブストラクト","抽象的な"},
		{"concreate","コンクリート","具体的な"},
		{"digital","デジタル","数学で情報を伝える"},
		{"analogue","アナログ","類似している、類似物"},
		{"exchange","エクスチェンジャー","交換、両替、為替"},
		{"infrastructure","インストラクチャ","下部構造、基礎となる施設や設備"},
		{"knowledge","ナレッジ","知識"},
		{"creedit","クレジット","信用"},
		{"routine", "ルーティン", "決まった手順、日課" },
		{"management", "マネジメント", "管理、経営" },
		{"account", "アカウント", "会計、口座" },
		{"unique", "ユニーク", "他に類を見ない、個性的な" },
		{"variety", "バラエティー", "変化に富む、多様な" },
		{"schedule", "スケジュール", "予定、計画" },
		{"agenda", "アジェンダ", "課題、議題" },
		{"technology", "テクノロジー", "科学技術" },
		{"collaboration", "コラボレーション", "協力、共同事業、共同作業" },
		{"tax", "タックス", "税金" },
		{"stock", "ストック", "在庫、株券" },
		{"product", "プロダクト", "製品" },
		{"booking", "ブッキング", "予約、帳簿への記入" },
		{"weight", "ウェイト", "重さ" },
		{"compliance","コンプライアンス","法令.社会的模範を守る"},
		{"receipt","レシート","領収書"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//問題の種類をランダムに選ぶ
	const int type = uniform_int_distribution<>(0, 3)(rd);
	switch (type) {
	case 0: //意味から英単語を答える
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"「" + string(e.meanig) + "」を意味する英単語を答えよ",
				e.word });
		}
		break;

	case 1: //読みから英単語を答える
		for (int i = 0; i < quizCount; i++) 
		{
			const auto& e = data[indices[i]];
			questions.push_back({
				"カタカナの読み「" + string(e.reading) + "」に対応する英単語を答えよ",
				e.word });
		}
		break;

	case 2: //読みから英単語を答える
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({
				string(e.word) + "の読みをカタカナで答えよ",
				e.reading });
		}
		break;
	case 3:
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号で上書き
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].word) +
				"」の意味として正しい番号を選べ\n";
			s += std::string("	1:") + data[answers[0]].meanig + "\n";
			s += std::string("	2:") + data[answers[2]].meanig + "\n";
			s += std::string("	3:") + data[answers[3]].meanig;

			questions.push_back({ s,to_string(correctNo) });

		}
		break;
	}	//switch(type)
	return questions;
}