#ifndef FIREMAN_H
#define FIREMAN_H

#include "man.h"

namespace game_framework {

	class fireman : public man
	{
	public:
		fireman();
		virtual void LoadBitmap();				// ���J�ϧ�
		virtual void LoadBitmap(int i);
		virtual void Initialize();
		virtual void jumpsound();
	};
}
#endif // !FIREMAN_H