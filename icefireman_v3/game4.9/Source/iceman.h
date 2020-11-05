#ifndef ICEMAN_H
#define ICEMAN_H

#include "man.h"
namespace game_framework {
	class iceman : public man
	{
	public:
		iceman();
		virtual void LoadBitmap();
		virtual void LoadBitmap(int);
		virtual void Initialize();
		virtual void jumpsound();
	};

}
#endif