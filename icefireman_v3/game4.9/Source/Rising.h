#include "man.h"
namespace game_framework
{
	class Rising {
	public:
		Rising();
		int getX();
		int getY();
		void SetXY(int _x,int _y);
		bool SetRising(man *player);
		void LoadBitmap();
		void OnShow();
	private:
		int x, y;
		CMovingBitmap image;
		CAnimation smoke;
	};

}