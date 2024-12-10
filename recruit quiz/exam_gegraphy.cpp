#include"exam_gegraphy.h"
#include"utility.h"
#include<iostream>
#include<fstream>
#include<random>
using namespace std;

//�s���{�������쐬����

QuestionList CreatePrefecturesExam()
{
	//�s���{���f�[�^
	struct  PrefectureData
	{
		string name;	//�s���{����
		string cppital;	//�������ݒn
		vector<string>features; //����
	};
	vector< PrefectureData> data;

	{	//�s���{���f�[�^��ǂݍ���
		constexpr char filename[] = "japanese_prefectures.txt";
		ifstream ifs(filename);
		if (!ifs) {
			cerr << "�G���[:" << filename << "�ǂݍ��߂܂���\n";
			return {};
		}

		string s;
		while (true)
		{
			getline(ifs, s); //	��s�ǂݎ��
			if (!ifs) {
				break; //�t�@�C���I�[�ɒB�����̂ŏI��
			}
			const vector<string>v = Split(s, ',');
			data.push_back({ v[0],v[1],vector<string>(v.begin() + 2,v.end()) });
		}

	}//�s���{���f�[�^��ǂݍ���

	constexpr int quizCount = 5;
	QuestionList questions;
	questions.reserve(quizCount);
	vector<int>indices = CreateRandomIndices((int)data.size());
	random_device rd;

	/*const int type = uniform_int_distribution<>(0, 2)(rd);*/
	const int type = 1;
	switch (type)
	{
	case 0: //��������s���{���𓚂���
		for (int i = 0; i < quizCount; i++)
		{
			//�����ȊO�̓����������_���ɑI��
			const int correctIndex = indices[i];
			vector<int> answer = CreateWrongIndices((int)data.size(), correctIndex);

			//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answer[correctNo - 1] = correctIndex;

			//�����쐬
			string s = "�ȉ��̓��������s���{���̔ԍ���I��\n";

			//�s���{���̓����������_���ȏ��ԂŌ������A����ǉ�
			const auto& features = data[correctIndex].features;
			vector<int>featureIndices = CreateRandomIndices((int)features.size());
			s += features[featureIndices[0]];
			for (int j = 1; j < features.size(); j++)
			{
				s += ",";
				s += features[featureIndices[j]];
			}

			//�����ƂȂ�s���{�����蕶�ɒǉ�
			for (int j = 0; j < 3; j++)
			{
				s += "\n" + to_string(j + 1) + ":" + data[answer[j]].name;
			}
			//��蕶�Ɠ����̃y�A����z��ɒǉ�
			questions.push_back({ s,to_string(correctNo) });

		}
		break;
	case 1: //�s���{��������킷�����𓚂���
		for (int i = 0; i < quizCount; i++)
		{
			//�����ȊO�̓����������_���ɑI��
			const int correctIndex = indices[i];
			vector<int> answer = CreateWrongIndices((int)data.size(), correctIndex);



			//�����_���Ȉʒu�𐳂����ԍ��ŏ㏑��
			const int correctNo = std::uniform_int_distribution<>(1, 3)(rd);
			answer[correctNo - 1] = correctIndex;

			//�����쐬
			string s = "�u" + data[correctIndex].name + "�v�̓���������킷�ԍ���I��";
			//�����ƂȂ�s���{�����蕶�ɒǉ�
			for (int j = 0; j < 3; j++)
			{
				const auto& features = data[answer[j]].features;
				const int n = uniform_int_distribution<>(0, (int)features.size() - 1)(rd);
				s += "\n" + to_string(j + 1) + ":" + features[n];
			}
			//��蕶�Ɠ����̃y�A����z��ɒǉ�
			questions.push_back({ s,to_string(correctNo) });
		}

		break;
	case 2: //�s���{�����猧�����ݒn�𓚂���
		break;
	}//swith(type)

	return questions;
}


	