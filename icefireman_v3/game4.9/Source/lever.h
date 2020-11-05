#ifndef LEVER_H
#define LEVER_H
namespace game_framework
{
	class lever
	{
	public:
		lever();
		void SetXY(int _x,int _y);
		int GetX();
		int GetY();
		CAnimation Getimage();
		void LoadBitmap();
		void OnMove();
		void OnShow();
	private:
		int x, y;
		CAnimation image;
	};
}
#endif