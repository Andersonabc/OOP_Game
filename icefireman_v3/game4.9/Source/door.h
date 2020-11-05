#ifndef DOOR_H
#define DOOR_H
#include "man.h"
namespace game_framework {
	class door
	{
	public:
		door();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		CAnimation* GetDoor();
		virtual void LoadBitmap();				// 載入圖形
		void OnShow(int _x,int _y);
		virtual bool Clearance(man player,int gemnum);
	protected:
		CAnimation animation;		// 利用動畫作圖形
		int x, y;
	};

}
#endif