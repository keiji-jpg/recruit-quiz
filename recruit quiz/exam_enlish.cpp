#include"exam_enlish.h"
#include"utility.h"
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
		{"creedit","クレジット","信用"}

	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];
		questions.push_back({
			"「" + string(e.meanig) + "」を意味する英単語を答えよ",
			e.word });
	}
	return questions;
}