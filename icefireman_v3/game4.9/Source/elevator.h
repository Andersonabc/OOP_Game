namespace game_framework 
{
	class buttonelevator
	{
	public:
		buttonelevator();
		int GetX();
		int GetY();
		int getox();
		int getoy();
		void setoxy(int x, int y);
		void LoadBitmap();
		void SetTopLeft(int _x, int _y);
		void ShowBitmap();
		int Getvelocity();
		int down();
		int up();
	private:
		int x, y;
		int ox, oy, velocity;
		CMovingBitmap image;
	};
}
