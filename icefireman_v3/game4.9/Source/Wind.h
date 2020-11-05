#ifndef WIND_H
#define WIND_H
#include "man.h"
namespace game_framework {
	class Wind {
	public:
		Wind();
		void LoadBitmap();
		void Init();
		void Count();
		void onMove(man *player);
		void OnShow();
	private:
		int times;
		int direction;
		CMovingBitmap image1,image2,image3;
	};
}
#endif