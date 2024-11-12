#include"exam_enlish.h"
#include"utility.h"
using namespace std;

QuestionList CreateEnglishWordExam()
{
	const struct {
		const char* word; // �p�P��
		const char* reading;//�ǂ�
		const char* meanig; //�Ӗ�

	}data[] = {
		{"state","�X�e�[�g","���"},
		{"business","�r�W�l�X","���ƁA�d��"},
		{"abstract","�A�u�X�g���N�g","���ۓI��"},
		{"concreate","�R���N���[�g","��̓I��"},
		{"digital","�f�W�^��","���w�ŏ���`����"},
		{"analogue","�A�i���O","�ގ����Ă���A�ގ���"},
		{"exchange","�G�N�X�`�F���W���[","�����A���ցA�ב�"},
		{"infrastructure","�C���X�g���N�`��","�����\���A��b�ƂȂ�{�݂�ݔ�"},
		{"knowledge","�i���b�W","�m��"},
		{"creedit","�N���W�b�g","�M�p"}

	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));

	for (int i = 0; i < quizCount; i++) {
		const auto& e = data[indices[i]];
		questions.push_back({
			"�u" + string(e.meanig) + "�v���Ӗ�����p�P��𓚂���",
			e.word });
	}
	return questions;
}