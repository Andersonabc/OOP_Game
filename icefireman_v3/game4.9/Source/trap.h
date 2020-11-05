#ifndef TRAP_H
#define TRAP_H
//繼承用//
namespace game_framework {
	class trap
	{
	public:
		trap();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		virtual void LoadBitmap();				// 載入圖形
		virtual void SetDelayTime()=0;
		void OnMove();
		void OnShow(int _x, int _y);
	protected:
		CAnimation animation;
		int x, y;
	};
}
#endif