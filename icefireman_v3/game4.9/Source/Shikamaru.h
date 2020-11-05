#ifndef SHIKAMARU_H
#define SHIKAMARU_H
#include "EnemyAI.h"
namespace game_framework {
	class Shikamaru : public EnemyAI
	{
	public:
		Shikamaru();
		~Shikamaru();
		int  GetX1();
		int  GetY1();
		int  GetX2();
		int  GetY2();
		void AttackMovie();
		void RunSkillsuccessMovie();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void UI(bool Hit);
		void SetpicXY();
		void SetSasukeDistance();
		void OnShow();
	private:
		int picx, picy;
		int Skilldelay;
		int SasukeDistance;
		int _direction, _distance;
	};
}
#endif