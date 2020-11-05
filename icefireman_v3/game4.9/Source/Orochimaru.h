#ifndef OROCHIMARU_H
#define OROCHIMARU_H
#include "EnemyAI.h"
namespace game_framework {
	class Orochimaru : public EnemyAI
	{
	public:
		Orochimaru();
		~Orochimaru();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void AttackMovie();
		void AttackMovie2();
		void RunSkillsuccessMovie();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void UI(bool Hit);
		void SetpicXY();
		void OnShow();
		bool GetisSkill();
	private:
		int picx, picy;
		int Skilldelay;
		int SasukeDistance;
		int _direction, _distance;
		int SasukeX, SasukeY;
		bool Return;
		bool isSkill2;
	};

}
#endif
