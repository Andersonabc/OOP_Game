#ifndef FIRE_H
#define FIRE_H

#include "trap.h"
namespace game_framework {
	class fire : public trap
	{
	public:
		fire();
		virtual void LoadBitmap();
		virtual void SetDelayTime();
	};

}
#endif