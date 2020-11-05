#ifndef SKILLSTART_H
#define SKILLSTART_H
namespace game_framework {
	class skillstart {
	public:
		skillstart();
		void Init();
		void LoadBitmap(int IDB_BITMAP, COLORREF colorkey);
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