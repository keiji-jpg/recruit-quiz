#include"exam_science.h"
#include"utility.h"
#include<random>
using namespace std;

//���������쐬����

QuestionList CreatePhysicsExam()
{
	QuestionList questions;
	questions.reserve(10);
	random_device rd;
	{	//���������^��
		constexpr int divisors[] = { 1,2,3,4,5,6,10,12,15,20,30,60 };
		int i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		int v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i]; //����
		int t = uniform_int_distribution<>(1, 10)(rd) * divisors[i]; //����
		questions.push_back({
			"����" + to_string(v) + "Km�ňړ�����Ԃ�����B\n���̎Ԃ�" + to_string(v * t / 60) +
			"Km�ړ�����̂ɂ����鎞�Ԃ𕪒P�ʂŋ��߂�",
			to_string(t) });

		 i = uniform_int_distribution<>(0, size(divisors) - 1)(rd);
		 v = uniform_int_distribution<>(1, 10)(rd) * 60 / divisors[i]; //����
		 t = uniform_int_distribution<>(1, 10)(rd) * divisors[i]; //����
		 questions.push_back({
			"����Ԃ�" + to_string(v*t/60) + "Km���ꂽ�n�_�܂ňړ�����̂�" + to_string(t) +
			"���������B\n���̎Ԃ̕��ϑ��x�����߂�",
			to_string(v) });
	}//���������^��
	{ //	�����������^��
		//����: v = v0 +at ���g���ĉ������
		int v0 = uniform_int_distribution<>(1, 10)(rd); //����
		int a = uniform_int_distribution<>(1, 5)(rd); //�����x
		int t = uniform_int_distribution<>(1, 20)(rd); //�ړ�����
		questions.push_back({
		   "�b��" + to_string(v0) + "Km�ňړ����Ă����Ԃ��A�i�s�����ɑ傫��" + to_string(a) +
		   "m/s�œ������x�����^�����͂��߂��B\n"+ to_string(t) + "�b��̑��x��m/s�P�ʂŋ��߂�B",
		   to_string(v0+a*t) });

		//����: x = v0t +1/2*at^2 ���g���ĉ������
		 v0 = uniform_int_distribution<>(5, 20)(rd); //����
		 a = uniform_int_distribution<>(1, 5)(rd); //�����x
		 t = uniform_int_distribution<>(1, 10)(rd); //�ړ�����
		questions.push_back({
		   "�b��" + to_string(v0) + "Km�ňړ����Ă����Ԃ��A�i�s�����ɑ傫��" + to_string(a) +
		   "m/s�œ������x�����^�����͂��߂��B\n�������n�߂Ă���" + to_string(t) +
		   "�b��܂łɈړ�����������m�P�ʂŋ��߂�B",
		   to_string(v0*t+a*t*t/2) });

		//����: v^2 - v0^2 = 2ax���g���ĉ������
		a = uniform_int_distribution<>(1, 5)(rd)*2; //�����x
		t = uniform_int_distribution<>(1, 10)(rd); //�ړ�����
		v0 = -a * t; //����
		questions.push_back({
		   "�b��" + to_string(v0) + "m�ňړ����Ă����Ԃ��u���[�L���������Ƃ���" +
		   to_string(v0*t+a*t*t/2) +"m�i��Œ�~�����B\n"+
			"�u���[�L�̉����x��m/s^2�P�ʂŋ��߂�B" 
			+ to_string(a)  });


	}//�������x�����^��

	{//�d�͉����x
		int t = uniform_int_distribution<>(1, 10)(rd);	//�ړ�����
		int x = 98 * t * t / 2; //�P�O�{���邱�ƂŁA�����_�ȉ����܂ł𐮐��Ƃ��ĕ\��
		string answer = to_string(x / 10); //�������𕶎���
		if (x % 10) {
			answer += '.';
			answer += '0' + x % 10;

		}
		questions.push_back({
			"�d�͉����x��9.8m/s^2�Ƃ���B\n�\���ɍ����ʒu���畨�̂�Â��ɗ��Ƃ��ƁA���̂�" +
			to_string(t) + "�b�Ԃ�Xm��������B\n" +
			"X�̒l�͏����_�ȉ����܂ŋ��߂�(��C��R�͂Ȃ����̂Ƃ���)�B",
			answer });

		int v0 = uniform_int_distribution<>(5, 10)(rd); //����
		 t = uniform_int_distribution<>(1, 10)(rd);	//�ړ�����
		int v = v0 * 10 - 98 * t; //���x
		answer.clear();
		if (v < 0) {
			v = -v;
			answer = '-';
		}
		answer += to_string(v / 10);
		if (v % 10) {
			answer += '.';
			answer += '0' + v % 10;
		}
		questions.push_back({
			"�d�͉����x��9.8m/s^2�Ƃ���B\n����" + to_string(v0) +
			"m/s�ŕ��̂������ɓ������Ƃ��A" + to_string(t) +
			"�b��̕��̂̑��x��Xm/s�ł���B\n" +
			"X�̒l�͏����_�ȉ����ʂ܂ŋ��߂�(��C��R�͂Ȃ����̂Ƃ���)�B",
			answer });


	} 

	{//����
		int s = uniform_int_distribution<>(5, 20)(rd); //��ʐ�
		int h = uniform_int_distribution <>(2, 10)(rd); //����
		int v = s * h + 5; //�̐ς����߁A�l�̌ܓ��̂��߂ɂT��������
		string answer = to_string(v / 100); //�������𕶎���ɕϊ�
		v /= 10;	//�����_�ȉ���Q�ɓ����镔�����̂Ă�
		if (v % 10) {	//�����_�ȉ���ꂪ�[���ȊO�Ȃ�A�������𕶎���ɉ�����
			answer += '.';
			answer += '0' + v % 10;

		}

		questions.push_back({
			"����100g�̕��̂ɓ����d�͂�1N�Ƃ���B\n��ʐ�" + to_string(s) + "cm^2�A����" +
			to_string(h) + "cm�̉~�������S�ɐ����ɒ��߂��B\n" +
			"���̂Ƃ��A���̉~���ɓ������͂�X�j���[�g���ł���B\n" +
			"X�̒l�͏����_�ȉ���Q�ʂ��l�̌ܓ����ċ��߂�B",
			answer });

		int x = uniform_int_distribution<>(20, 50)(rd)*10; //�d��(����)
		int y = uniform_int_distribution <>(x/2,x-1)(rd); //�d��(����)
		int z = x - y + 5; //�̐ς����߁A�l�̌ܓ��̂��߂ɂT��������
		answer = to_string(z / 100);
		z /= 10;	

		if (z % 10) {	//�����_�ȉ���ꂪ�[���ȊO�Ȃ�A�������𕶎���ɉ�����
			answer += '.';
			answer += '0' + z % 10;

		}
		questions.push_back({
			"����100g�̕��̂ɓ����d�͂�1N�Ƃ���B\n���镨�̂̏d���΂˂͂���ł͂���ƁA" +
			to_string(x) + "g���������B\n" + "���̕��̂����S�ɐ��ɓ��ꂽ�Ƃ���A�΂˂͂����"
			+ to_string(y) + "g���������B\n���̂Ƃ��A���̂ɂ͂��炭���͂�X�j���[�g���ł���B\n" +
			"X�̒l�������_�ȉ���Q�ʂ��l�̌ܓ����ċ��߂�B",
			answer });

		int p0 = uniform_int_distribution<>(1, 9)(rd)*10; //���x
			 s = uniform_int_distribution <>(5, 10)(rd);   //��ʐ�
			 h = uniform_int_distribution<>(5, 10)(rd);    //����
			 answer = to_string(h * p0 / 100);
			 if (h * p0 % 100) {
				 answer += '.';
				 answer += '0' + h * p0 / 10 % 10;
			 }

			 questions.push_back({
				 "���x" + to_string(p0) + "g/cm3�A��ʐ�" + to_string(s) + "cm^2�A����" +
				 to_string(h) + "cm�̕��̂𐅂ɒ��߂悤�Ƃ����Ƃ���AXcm����ŐÎ~�����B\n" +
				 "X�̒l�������_�ȉ����܂ŋ��߂�B",
				 answer });
			}//����
	//�d�͉����x
	return questions;
}