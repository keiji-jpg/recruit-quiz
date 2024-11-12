#include"exam_enlish.h"
#include"utility.h"
#include<random>
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
		{"creedit","�N���W�b�g","�M�p"},
		{"routine", "���[�e�B��", "���܂����菇�A����" },
		{"management", "�}�l�W�����g", "�Ǘ��A�o�c" },
		{"account", "�A�J�E���g", "��v�A����" },
		{"unique", "���j�[�N", "���ɗނ����Ȃ��A���I��" },
		{"variety", "�o���G�e�B�[", "�ω��ɕx�ށA���l��" },
		{"schedule", "�X�P�W���[��", "�\��A�v��" },
		{"agenda", "�A�W�F���_", "�ۑ�A�c��" },
		{"technology", "�e�N�m���W�[", "�Ȋw�Z�p" },
		{"collaboration", "�R���{���[�V����", "���́A�������ƁA�������" },
		{"tax", "�^�b�N�X", "�ŋ�" },
		{"stock", "�X�g�b�N", "�݌ɁA����" },
		{"product", "�v���_�N�g", "���i" },
		{"booking", "�u�b�L���O", "�\��A����ւ̋L��" },
		{"weight", "�E�F�C�g", "�d��" },
		{"compliance","�R���v���C�A���X","�@��.�Љ�I�͔͂����"},
		{"receipt","���V�[�g","�̎���"},
	};

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	const vector<int> indices = CreateRandomIndices(size(data));
	random_device rd;

	//���̎�ނ������_���ɑI��
	const int type = uniform_int_distribution<>(0, 3)(rd);
	switch (type) {
	case 0: //�Ӗ�����p�P��𓚂���
		for (int i = 0; i < quizCount; i++) {
			const auto& e = data[indices[i]];
			questions.push_back({
				"�u" + string(e.meanig) + "�v���Ӗ�����p�P��𓚂���",
				e.word });
		}
		break;

	case 1: //�ǂ݂���p�P��𓚂���
		for (int i = 0; i < quizCount; i++) 
		{
			const auto& e = data[indices[i]];
			questions.push_back({
				"�J�^�J�i�̓ǂ݁u" + string(e.reading) + "�v�ɑΉ�����p�P��𓚂���",
				e.word });
		}
		break;

	case 2: //�ǂ݂���p�P��𓚂���
		for (int i = 0; i < quizCount; i++)
		{
			const auto& e = data[indices[i]];
			questions.push_back({
				string(e.word) + "�̓ǂ݂��J�^�J�i�œ�����",
				e.reading });
		}
		break;
	case 3:
		for (int i = 0; i < quizCount; i++) {
			//�Ԉ�����ԍ��������_���ɑI��
			const int correctIndex = indices[i];
			vector<int>answers = CreateWrongIndices(size(data), correctIndex);

			//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answers[correctNo - 1] = correctIndex;

			//��蕶���쐬
			string s = "�u" + string(data[correctIndex].word) +
				"�v�̈Ӗ��Ƃ��Đ������ԍ���I��\n";
			s += std::string("	1:") + data[answers[0]].meanig + "\n";
			s += std::string("	2:") + data[answers[2]].meanig + "\n";
			s += std::string("	3:") + data[answers[3]].meanig;

			questions.push_back({ s,to_string(correctNo) });

		}
		break;
	}	//switch(type)
	return questions;
}