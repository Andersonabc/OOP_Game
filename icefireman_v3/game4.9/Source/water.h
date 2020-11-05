#ifndef WATER_H
#define WATER_H
#include "trap.h"
namespace game_framework {
	class water : public trap
	{
	public:
		water();
		virtual void LoadBitmap();
		virtual void SetDelayTime();
	};

}
#endif