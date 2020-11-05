#pragma once
#ifndef POISON_H
#define POISON_H
#include "trap.h"
namespace game_framework {
	class poison : public trap
	{
	public:
		poison();
		virtual void LoadBitmap();
		virtual void SetDelayTime();
	};

}
#endif