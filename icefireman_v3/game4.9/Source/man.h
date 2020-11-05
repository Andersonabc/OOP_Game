#ifndef MAN_H
#define MAN_H
#include "bullet.h"
namespace game_framework {
	class man
	{
	public:
		man();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  Getvelocity();
		int  Getfloor();
		bool Onfloor();
		string Getcharacteristic();
		bool GetRising();
		bool Getfly();
		void Addgem();
		int getgem();
		int Getstep();
		virtual void Initialize();				// �]�w���l����l��
		virtual void LoadBitmap();				// ���J�ϧ�
		virtual void LoadBitmap(int);
		void OnMove();					// �������l
		void OnMove(man *player);
		void setfloor(int _floor);
		void sethead(bool flag);
		void setleft(int flag);
		void setright(int flag);
		void jump();					// ���D
		void jump(int);
		void OnShow();					// �N���l�ϧζK��e��
		void OnShow(int);
		void SetMovingDown(bool flag);	// �]�w�O�_���b���U����
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetTwojump(bool flag);
		void SetAttack(bool flag);
		void SetAttacked(int flag);
		bool SetShooting();
		void SetRush();
		void SetisMagic(bool flag);
		CAnimation GetAnimation();
		bool GetMovingLeft();
		bool GetMovingRight();
		bool Getleft();
		bool Getright();
		bool Getshooting();
		bool GetRush();
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void Setfly(bool flag);
		int GetBullet();
		int GetDamage();
		void AddDamage();
		void SetCombodelay();
		virtual void jumpsound();
		void DeleteBullet();
	protected:
		int floor;
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��
		bool fly;
		int x, y;					// ���l���W���y��
		bool isMovingDown;			// �O�_���b���U����
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isTwojump;
		bool isAttack;
		bool isRush;
		bool isMagic;
		int isAttacked;
		int RushTime;
		bool isShooting;
		bool head;
		int direction;
		int combodelay;
		int times;
		int left;
		int step_size;
		int magic;
		string characteristic;
		int right;
		int gem;
		int damage;
		CAnimation animation;		// �Q�ΰʵe�@�ϧ�
		CMovingBitmap MagicBar;
		CMovingBitmap Black;
		int MagicX, MagicY;
		vector <bullet*> shoot;
		vector <char> combo;
	};
}
#endif