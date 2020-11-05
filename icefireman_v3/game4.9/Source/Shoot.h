#ifndef SHOOT_H
#define SHOOT_H
//�~�ӥ�//
namespace game_framework {
	class Shoot
	{
	public:
		Shoot();
		virtual void Init(int _x ,int _y ,int _direction)=0;
		virtual int GetX1()=0;					// ���l���W�� x �y��
		virtual int GetY1()=0;					// ���l���W�� y �y��
		virtual int GetX2()=0;
		virtual int GetY2()=0;
		virtual int Getdirection()=0;
		virtual void AddPic()=0;				// ���J�ϧ�
		virtual void OnShow()=0;
		virtual void Move()=0;
		virtual void SetXY(int _x, int _y)=0;
	protected:
		CAnimation Shurikanpic,Fireballpic;		// �Q�ΰʵe�@�ϧ�
		int x, y, direction;
		string characteristic;
	};
}
#endif