#include "man.h"
namespace game_framework
{
	class rockStone {
		public:
			rockStone();
			int  GetX();					// ���Y���W�� x �y��
			int  GetY();					// ���Y���W�� y �y��
			int  GetX2();					// ���Y�k�U�� x �y��
			int  GetY2();					// ���Y�k�U�� y �y��
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