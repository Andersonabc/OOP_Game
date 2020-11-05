#ifndef FIREBALLMOVIE_H
#define FIREBALLMOVIE_H
namespace game_framework {
	class FireBallMovie {
	public:
		FireBallMovie();
		void Init();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void isEnd();
		bool isStart();
	private:
		bool Stop,Start;
		CMovingBitmap image;
		int delaycount,x,y;
	};
}
#endif