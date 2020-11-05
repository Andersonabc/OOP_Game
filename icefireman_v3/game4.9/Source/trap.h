#ifndef TRAP_H
#define TRAP_H
//�~�ӥ�//
namespace game_framework {
	class trap
	{
	public:
		trap();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		virtual void LoadBitmap();				// ���J�ϧ�
		virtual void SetDelayTime()=0;
		void OnMove();
		void OnShow(int _x, int _y);
	protected:
		CAnimation animation;
		int x, y;
	};
}
#endif