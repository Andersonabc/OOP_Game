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
		virtual int  GetX1();					// 擦子左上角 x 座標
		virtual int  GetY1();					// 擦子左上角 y 座標
		virtual int  GetX2();					// 擦子右下角 x 座標
		virtual int  GetY2();					// 擦子右下角 y 座標
		virtual void Initialize()=0;				// 設定擦子為初始值
		virtual void LoadBitmap()=0;				// 載入圖形
		virtual void UI(bool Hit) = 0;
		void SetonFloor();
		void OnMove();
		void jump();					// 跳躍
		virtual void OnShow()=0;					// 將擦子圖形貼到畫面
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
		void SetDirection(int flag);
		void SetAttacked(int flag);
		void SetDie(int direction);
		void SetSkillsuccess();
		bool GetSkillsuccess();
		int GetDirection();
		bool GetMovingLeft();
		bool GetMovingRight();
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
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
		int velocity;			// 目前的速度(點/次)
		int initial_velocity;	// 初始速度
		bool rising;				// true表上升、false表下降
		int x, y;					// 擦子左上角座標
		int SasukeX;
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
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
		CAnimation animation;		// 利用動畫作圖形
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