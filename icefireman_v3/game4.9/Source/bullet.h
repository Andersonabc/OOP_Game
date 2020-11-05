#ifndef BULLET_H
#define BULLET_H

namespace game_framework {
	class bullet
	{
	public:
		bullet(int _x, int _y,int _direction,string _characteristic);
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int GetX2();
		int GetY2();
		int Getdirection();
		void AddPic();				// ���J�ϧ�
		void OnShow();
		void Move();
		void SetXY(int _x, int _y);
		CAnimation Getbullet();
	protected:
		CAnimation bulletPic;		// �Q�ΰʵe�@�ϧ�
		string characteristic;
		int x, y, direction;
	};

}
#endif