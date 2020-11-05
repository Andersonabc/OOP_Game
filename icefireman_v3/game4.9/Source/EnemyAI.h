#ifndef ENEMYAI_H
#define ENEMYAI_H
#include "Shurikan.h"
#include "Sasuke.h"
#include "SkillStart.h"
namespace game_framework {
	class EnemyAI
	{
	public:
		EnemyAI();
		virtual ~EnemyAI();
		virtual int  GetX1();					// ���l���W�� x �y��
		virtual int  GetY1();					// ���l���W�� y �y��
		virtual int  GetX2();					// ���l�k�U�� x �y��
		virtual int  GetY2();					// ���l�k�U�� y �y��
		virtual void Initialize()=0;				// �]�w���l����l��
		virtual void LoadBitmap()=0;				// ���J�ϧ�
		virtual void UI(bool Hit) = 0;
		void SetonFloor();
		void OnMove();
		void jump();					// ���D
		virtual void OnShow()=0;					// �N���l�ϧζK��e��
		void SetMovingLeft(bool flag);	// �]�w�O�_���b��������
		void SetMovingRight(bool flag); // �]�w�O�_���b���k����
		void SetMovingUp(bool flag);	// �]�w�O�_���b���W����
		void SetDirection(int flag);
		void SetAttacked(int flag);
		void SetDie(int direction);
		void SetSkillsuccess();
		bool GetSkillsuccess();
		int GetDirection();
		bool GetMovingLeft();
		bool GetMovingRight();
		void SetXY(int nx, int ny);		// �]�w���l���W���y��
		void SetisShow(bool flag);
		bool GetMove();
		void Addattacknum();
		bool GetAttack();
		bool GetDie();
		bool GetAttacked();
		int Getblood();
		int Setblood(int _blood);
		int GetAttacknum();
		int GetCurrentBitmapNumber();
		void SetSasukeX(int x);
		void SetMove(bool flag);
		vector <Shurikan*> GetShurikan();
		CAnimation GetSkillMovie();
		CAnimation* GetSkillsuccessMovie();
		void SetShurikanDelete(int flag);
		virtual bool GetisSkill();
		void SetPlayer(Sasuke *_player);
		skillstart* Getskillstart();
		void Attack();
		void Attacked();
		void Throw();
		void MovePlayer();
		void Die();
		void Stand();
		void SetSkill();
		void SetSkill2();
	protected:
		int floor;
		int velocity;			// �ثe���t��(�I/��)
		int initial_velocity;	// ��l�t��
		bool rising;				// true��W�ɡBfalse��U��
		int x, y;					// ���l���W���y��
		int SasukeX;
		bool isMovingLeft;			// �O�_���b��������
		bool isMovingRight;			// �O�_���b���k����
		bool isMovingUp;			// �O�_���b���W����
		bool isDie;
		bool isSkill,Skillsuccess;
		int isAttacked;
		bool isAttack;
		bool isShooting;
		bool isThrow;
		int Playerdirection;
		int direction;
		int times;
		int Skill;
		int step_size;
		int Moldingdelay;
		bool Move;
		bool isShow;
		int StandHeight, StandWidth;
		int StandStart,StandNum,RunStart,RunNum,JumpStart,JumpNum,AttackStart,AttackNum, Attack2Start, Attack2Num, Attack3Start,Attack3Num,ThrowStart,ThrowNum,HurtStart,HurtNum,DieStart,DieNum,SkillStart,Skillnum,Total;
		CAnimation animation;		// �Q�ΰʵe�@�ϧ�
		CAnimation SkillMovie;
		CAnimation SkillsuccessMovie;
		skillstart Movie;
		CMovingBitmap MagicBar;
		CMovingBitmap Black;
		int MagicX, MagicY;
		vector <Shurikan*> shoot;
		int attacknum;
		int distance;
		bool Wall;
		int Diedelay;
		int Blood;
		int delay;
		Sasuke* Player;
		bool Movieflag;
	};

}
#endif