#ifndef CHAINELEVATOR_H
#define CHAINELEVATOR_H
#include "FallWall.h"
namespace game_framework
{
	class ChainElevator :public FallWall
	{
	public:
		ChainElevator();
		void SetX2Y2(int X2,int Y2);
		void Setaimy1(int y);
		void Setaimy2(int y);
		bool Onstand2(man player);
		bool OnStand(int x,int y);
		bool OnStand2(int x,int y);
		int GetFall2();
		void SetFall2(int flag);
		void SetFall2(man player);
		double Getcount();
		int GetaimY1();
		int GetX2();
		int GetY2();
		void LoadBitmap();
		void onShow();
	private:
		int x2,y2;
		int rangey1, rangey2;
		int aimy1, aimy2;
		int Fall2;
		double count;
		CMovingBitmap Elevator2;
	};
}
#endif
