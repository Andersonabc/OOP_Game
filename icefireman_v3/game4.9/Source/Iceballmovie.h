#ifndef ICEBALLMOVIE_H
#define ICEBALLMOVIE_H
namespace game_framework {
	class IceBallMovie {
	public:
		IceBallMovie();
		void Init();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void isEnd();
		bool isStart();
	private:
		bool Stop, Start;
		CMovingBitmap image;
		int delaycount, x, y;
	};
}
#endif
