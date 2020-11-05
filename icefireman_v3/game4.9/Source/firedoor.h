#ifndef FIREDOOR_H
#define FIREDOOR_H

#include "door.h"
namespace game_framework {
	class firedoor : public door
	{
	public:
		firedoor();
		virtual void LoadBitmap();
		virtual bool Clearance(man player, int firegemnum);
	};

}
#endif