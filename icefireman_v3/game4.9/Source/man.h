#ifndef MAN_H
#define MAN_H
#include "bullet.h"
namespace game_framework {
	class man
	{
	public:
		man();
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		int  GetX2();					// 擦子右下角 x 座標
		int  GetY2();					// 擦子右下角 y 座標
		int  Getvelocity();
		int  Getfloor();
		bool Onfloor();
		string Getcharacteristic();
		bool GetRising();
		bool Getfly();
		void Addgem();
		int getgem();
		int Getstep();
		virtual void Initialize();				// 設定擦子為初始值
		virtual void LoadBitmap();				// 載入圖形
		virtual void LoadBitmap(int);
		void OnMove();					// 移動擦子
		void OnMove(man *player);
		void setfloor(int _floor);
		void sethead(bool flag);
		void setleft(int flag);
		void setright(int flag);
		void jump();					// 跳躍
		void jump(int);
		void OnShow();					// 將擦子圖形貼到畫面
		void OnShow(int);
		void SetMovingDown(bool flag);	// 設定是否正在往下移動
		void SetMovingLeft(bool flag);	// 設定是否正在往左移動
		void SetMovingRight(bool flag); // 設定是否正在往右移動
		void SetMovingUp(bool flag);	// 設定是否正在往上移動
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
		void SetXY(int nx, int ny);		// 設定擦子左上角座標
		void Setfly(bool flag);
		int GetBullet();
		int GetDamage();
		void AddDamage();
		void SetCombodelay();
		virtual void jumpsound();
		void DeleteBullet();
	protected:
		int floor;
		int velocity;			// 目前的速度(點/次)
		int initial_velocity;	// 初始速度
		bool rising;				// true表上升、false表下降
		bool fly;
		int x, y;					// 擦子左上角座標
		bool isMovingDown;			// 是否正在往下移動
		bool isMovingLeft;			// 是否正在往左移動
		bool isMovingRight;			// 是否正在往右移動
		bool isMovingUp;			// 是否正在往上移動
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
		CAnimation animation;		// 利用動畫作圖形
		CMovingBitmap MagicBar;
		CMovingBitmap Black;
		int MagicX, MagicY;
		vector <bullet*> shoot;
		vector <char> combo;
	};
}
#endif