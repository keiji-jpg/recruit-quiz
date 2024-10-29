#include"exam_japanese.h"
#include<random>
#include"utility.h"
using namespace std;

//漢字の読み取り問題を作成する

QuestionList CreateKanjiExam() {
	static const struct {
		const char* kanji; //漢字
		const char* reading; //読み
		const char* meaning; //意味
	}data[]{
		{"市井","しせい","人が多く集まって暮らすところ、町"},
		{"捺印","なついん","(署名と共に)印鑑を押すところ"},
		{"相殺","そうさい","足し引きの結果、差が無くなるころ"},
		{"凡例","はんれい","本や図表のはじめに、使い方や約束事を箇条書きにしたもの"},
		{"必定","ひつじょう","必ずそうなると決まっていること"},
		{"知己","ちき","自分をよく理解してくれる人、親しい友人"},
		{"境内","けいだい","神社、寺院の敷地内"},
		{"破綻","はたん","物事がうまくいかなくなること"},
		{"拘泥","こうでい","ひとりの考え方や行動にこだわること"},
		{"吟味","ぎんみ","物事を念入りに調べること"},
		{"承る","うけたまわる","敬意を持って受ける、[受ける]、[聞く]の嫌譲語"},
		{"寸暇","すんか","ほんの少しの空き時間"},
		{"弄ぶ","もてあそぶ","手であれこれいじる、好き勝ってに扱う"},
		{"灰汁","あく","食べ物を煮たときに出る渋みやえぐみの成分、独特の個性"},
		{"潔い","いさぎよい","思い切りがよい、道を反することがない"},
		{"借款","しゃっかん","金銭を借りること、国同士の長期的の金銭の貸し借り"},
		{"培う","つちかう","時間をかけて育てること"},
		{"赴く","おもむく","ある場所、方向へ向かって行く"},
		{"疾病","しっぺい","健康でない状態、病気"},
		{"老舗","しにせ","先祖代々同じ商売をしている信用のある店"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;
	
	//問題の種類を選ぶ
	int type = uniform_int_distribution<>(0, 1)(rd);
	if (type == 0) {
		//漢字の読み方を答える問題
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"「" + string(e.kanji) + "」の読みをひらがなで答えよ",
				e.reading });
		}
	}
	else
	{
		//正しい熟語を答える問題
		for (int i = 0; i < quizCount; i++) {
			//間違った番号をランダムに選ぶ
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);

			//ランダムな位置を正しい番号を上書き
			const int correctNo = uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//問題文を作成
			string s = "「" + string(data[correctIndex].meaning) +
				"」を意味する熟語の番号を選べ";
			for (int j = 0; j < 3; j++) {
				s += "\n " + to_string(j + 1) + ":"+data[answers[j]].kanji;
			}

			questions.push_back({ s,to_string(correctNo) });
		}
	}//if type
	return questions;

}