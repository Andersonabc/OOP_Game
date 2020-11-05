#ifndef DOOR_H
#define DOOR_H
#include "man.h"
namespace game_framework {
	class door
	{
	public:
		door();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		CAnimation* GetDoor();
		virtual void LoadBitmap();				// ���J�ϧ�
		void OnShow(int _x,int _y);
		virtual bool Clearance(man player,int gemnum);
	protected:
		CAnimation animation;		// �Q�ΰʵe�@�ϧ�
		int x, y;
	};

}
#endif