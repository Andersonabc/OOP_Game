#ifndef YELLOWBUTTON_H
#define YELLOWBUTTON_H
namespace game_framework 
{
	class yellowbutton 
	{
	public:
		yellowbutton();
		int GetX();
		int	GetY();
		bool Onpress(int _x,int _y);
		virtual void LoadBitmap();
		void SetTopLeft(int _x, int _y);
		void ShowBitmap();
	protected:
		int x, y;
		CMovingBitmap image;
	};
	
}
#endif