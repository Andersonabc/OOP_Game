#ifndef SHOOT_H
#define SHOOT_H
//繼承用//
namespace game_framework {
	class Shoot
	{
	public:
		Shoot();
		virtual void Init(int _x ,int _y ,int _direction)=0;
		virtual int GetX1()=0;					// 擦子左上角 x 座標
		virtual int GetY1()=0;					// 擦子左上角 y 座標
		virtual int GetX2()=0;
		virtual int GetY2()=0;
		virtual int Getdirection()=0;
		virtual void AddPic()=0;				// 載入圖形
		virtual void OnShow()=0;
		virtual void Move()=0;
		virtual void SetXY(int _x, int _y)=0;
	protected:
		CAnimation Shurikanpic,Fireballpic;		// 利用動畫作圖形
		int x, y, direction;
		string characteristic;
	};
}
#endif