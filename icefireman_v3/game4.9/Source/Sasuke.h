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
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  Gety();
		int  Getx();
		void Initialize();				// 設定擦子為初始值
		void LoadBitmap();				// 載入圖形
		void OnMove();
		void setfloor(int _floor);
		void jump();					// 跳躍
		void OnShow();					// 將擦子圖形貼到畫面
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
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
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
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
		int velocity;			// 目前的速度(點/次)
		int initial_velocity;	// 初始速度
		bool rising;				// true表上升、false表下降
		int x, y;					// 擦子左上角座標
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
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
		CAnimation animation;		// 利用動畫作圖形
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