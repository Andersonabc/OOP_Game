#ifndef BULLET_H
#define BULLET_H

namespace game_framework {
	class bullet
	{
	public:
		bullet(int _x, int _y,int _direction,string _characteristic);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int GetX2();
		int GetY2();
		int Getdirection();
		void AddPic();				// 載入圖形
		void OnShow();
		void Move();
		void SetXY(int _x, int _y);
		CAnimation Getbullet();
	protected:
		CAnimation bulletPic;		// 利用動畫作圖形
		string characteristic;
		int x, y, direction;
	};

}
#endif