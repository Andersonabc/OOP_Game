#ifndef ICEDOOR_H
#define ICEDOOR_H

#include "door.h"
namespace game_framework {
	class icedoor : public door
	{
	public:
		icedoor();
		virtual void LoadBitmap();
		virtual bool Clearance(man player, int icegemnum);
	};

}
#endif