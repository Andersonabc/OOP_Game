#ifndef INGAMEMOVIE_H
#define INGAMEMOVIE_H

namespace game_framework {
	class ingamemovie {
	public:
		ingamemovie();
		void Init();
		void LoadBitmap();
		void OnShow();
		void OnMove();
		void SetUp();
		void SetDown();
		void GoMenu();
		void GoRetry();
		void GoInit();
		void ResetPos();
		bool isOK();
	private:
		bool up, down;
		CAnimation image;
		int  x, y;
	};
}
#endif