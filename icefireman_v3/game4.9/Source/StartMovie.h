#ifndef STARTMOVIE
#define STARTMOVIE
namespace game_framework {
	class Movie {
	public:
		Movie();
		void LoadBitmap();
		void SetIceXY(int _x,int _y);
		void SetFireXY(int _x, int _y);
		void Restart();
		void OnMove();
		void OnShow();
		bool Getend();
	private:
		CAnimation iceman;
		CAnimation fireman;
		int delaycount;
	};
}
#endif