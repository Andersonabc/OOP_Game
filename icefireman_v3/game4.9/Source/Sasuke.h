#ifndef SASUKE_H
#define SASUKE_H
#include "SkillStart.h"
#include "SasukeFireball.h"
#include "Shurikan.h"
namespace game_framework {
	class Sasuke
	{
	public:
		Sasuke();
		~Sasuke();
		int  GetX1();					// ���l���W�� x �y��
		int  GetY1();					// ���l���W�� y �y��
		int  GetX2();					// ���l�k�U�� x �y��
		int  GetY2();					// ���l�k�U�� y �y��
		int  Gety();
		int  Getx();
		void Initialize();				// �]�w���l����l��
		void LoadBitmap();				// ���J�ϧ�
		void OnMove();
		void setfloor(int _floor);
		void jump();					// ���D
		void OnShow();					// �N���l�ϧζK��e��
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetAttacked(int flag);
		void SetDie();
		void SetDie(int Sub);
		void SetMove(bool flag);
		void SetisMolding(bool flag);
		bool GetMovingLeft();
		bool GetMovingRight();
		bool GetisDie();
		void SubBlood(int Sub);
		int GetDirection();
		int GetAttack();
		bool GetisSkill();
		bool GetisMolding();
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void Addattacknum();
		bool GetMove();
		int Getblood();
		int GetMagic();
		int GetCurrentBitmapNumber();
		int GetSkillCurrentBitmapNumber();
		skillstart* Getskillstart();
		vector<SasukeFireball*> GetFireball();
		vector<Shurikan*> GetShurikan();
		void AttackMovie1();
		void AttackMovie2();
		void AttackMovie3();
		void AttackMovie4();
		int GetChakura();	
		void ChangeChakura(int _chakura);
		void SetDirection(int _direction);
		void SetFireballDelete(int flag);
		void SetShurikanDelete(int flag);
		bool GetSkillsuccess();
		void SetSkillsuccess();
		CAnimation* GetSkillsuccessMovie();
		void RunSkillsuccessMovie();
		void Deleteobject();
		void Attack();
		void Attacked();
		void Molding();
		void ThrowMove();
		void MovePlayer();
		void Die();
		void Stand();
		void SetSkill();
	protected:
		int floor;
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��
		int x, y;					// ���l���W���y��
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isMolding;
		bool isSkillFail;
		bool isDie;
		int isAttacked;
		bool isShooting;
		bool Skillsuccess;
		int direction;
		int step_size;
		int magic;
		int Moldingdelay;
		bool Move;
		int Diedelay, chakuradelay, delay;
		CAnimation animation;		// �Q�ΰʵe�@�ϧ�
		CAnimation SkillMovie;
		CAnimation SkillsuccessMovie;
		skillstart Movie, Movie2;
		CMovingBitmap MagicBar;
		CMovingBitmap Black;
		vector<SasukeFireball*> Fireball;
		vector<Shurikan*> shurikan;
		int MagicX, MagicY;
		int Blood;
		vector <char> combo;
		bool Movieflag;
		int attacknum;
		bool isSkill;
		int chakura;
		int skill3direction,skill3delay, skill1delay;
		int damage;
	};

}
#endif