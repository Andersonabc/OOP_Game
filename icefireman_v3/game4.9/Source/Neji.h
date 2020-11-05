#ifndef NEJI_H
#define NEJI_H
#include "EnemyAI.h"
namespace game_framework {
	class Neji : public EnemyAI
	{
	public:
		Neji();
		~Neji();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void AttackMovie();
		void RunSkillsuccessMovie();	
		void Initialize();				
		void LoadBitmap();				
		void UI(bool Hit);
		void SetpicXY();
		void OnShow();
	private:
		int picx, picy;
		int Skilldelay;
		int SasukeDistance;
		int _direction, _distance;
	};
}
#endif