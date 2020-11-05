#include "man.h"
namespace game_framework
{
	class rockStone {
		public:
			rockStone();
			int  GetX();					// 石頭左上角 x 座標
			int  GetY();					// 石頭左上角 y 座標
			int  GetX2();					// 石頭右下角 x 座標
			int  GetY2();					// 石頭右下角 y 座標
			void LoadBitmap();
			void Down();
			bool CheckStone(int ,int,int,int);
			void OnMove();
			void SetTopLeft(int _x, int _y);
			void ShowBitmap();
			void SetXY(int _x, int _y);		
	private:
			int x, y, x2 ,y2;
			CMovingBitmap image;
	};
}