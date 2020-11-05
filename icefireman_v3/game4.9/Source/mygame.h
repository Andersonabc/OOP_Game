#include"CgameMap.h"
#include"StartMovie.h"
#include"Wind.h"
#include "Fireballmovie.h"
#include"Iceballmovie.h"
#include"ingamemovie.h"
#include "Sasuke.h"
#include "Shikamaru.h"
#include "bloodcount.h"
#include "Neji.h"
#include "Shoot.h"
#include "Kakashi.h"
#include "Orochimaru.h"

enum AUDIO_ID  					// 定義各種音效的編號
{
	gamemusic=0,				// 0
	Gem,						// 1
	GameOver,					// 2
	Icejump,					// 3
	Firejump,					// 4
	gamewin,					// 5
	hit,						// 6
	fireball,					// 7
	iceball,					// 8
	attack,						// 9
	attackmusic,				// 10
	Round1,						// 1
	MagicFire,					// 2
	MagicIce,					// 3
	ButtonHover,				// 4
	Button2Hover,				// 5
	Button3Hover,				// 6
	Button4Hover,				// 7
	Button5Hover,				// 8
	Book,						// 9
	NarutoBGM,					// 20
	SasukeCombo,				// 1
	SasukeCombo2,				// 2
	SasukeAttack,				// 3
	Sasukeskillsuccess,			// 4
	Sasukefireball,				// 5
	SasukeSkill,				// 6
	SasukeSkill4,				// 7
	SasukeSkill42,				// 8
	NarutoisAttacked,			// 9
	NarutoDie,					// 30
	EnemySkill,					// 31
	NarutoBGM2,					// 32
};
extern bool stage[5];			//關卡是否通關
extern int current_level;		//當前為第幾關
extern int ranklevel[5];		
extern bool current_rank;
extern int winner;
namespace game_framework
{
	class CGameStateInit : public CGameState
	{
	public:
		CGameStateInit(CGame* g);
		~CGameStateInit();
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnKeyUp(UINT, UINT, UINT); 				// 處理鍵盤Up的動作
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);
		void AddRoutePic();
		void AddShinePic();
		void AddRankPic();
		void ChooseStage(int mode);
		void ChangeLevel();
		void ShowRank();
	protected:
		void OnShow();									// 顯示這個狀態的遊戲畫面
		void OnMove();
	private:
		CMovingBitmap logo;								// csie的logo
		CMovingBitmap arror;
		CMovingBitmap teach;
		CMovingBitmap starter;
		CMovingBitmap about_show;
		CAnimation routePic;
		CAnimation shinePic;
		CAnimation rankSelection;
		CAnimation instructor;
		
		vector<CAnimation*> rank;
		bool flag;
		int time;
		int view;
		int current_point;
		int position[5][2] = { {296, 436},{317, 381},{303, 319},{307, 255},{315,177} };
		bool starting;
		bool aboutIsShow;
	};
	class CGameStateRun : public CGameState
	{
	public:
		CGameStateRun(CGame* g);
		~CGameStateRun();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonUp(UINT nFlags, CPoint point);	// 處理滑鼠的動作
		void OnMouseMove(UINT nFlags, CPoint point);	// 處理滑鼠的動作

	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		iceman			player1;		
		fireman         player2;
		CgameMap		gamemap;
		ingamemovie     showmovie;
	};
	class CGameStateOver : public CGameState
	{
	public:
		CGameStateOver(CGame* g);
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnMouseMove(UINT nFlags, CPoint point);  // 處理滑鼠的動作
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnInit();
		void SetRank();
		void AddAllAnimation();
	protected:
		void OnMove();	// 移動遊戲元素
		void OnShow();
	private:
		int counter;	// 倒數之計數器
		int time;
		CAnimation GameOverPic;
		CAnimation GameWinPic;
		CAnimation RankPic;
		CAnimation FireWinnerPic;
		CAnimation IceWinnerPic;
		CMovingBitmap winBackground;
		vector<CAnimation*> ShowTime;
		int position[3][2] = { {300, 192},{345, 192},{390, 192}};
		CInteger timeCount;
	};
	class CGameStateAttack : public CGameState
	{
	public:
		CGameStateAttack(CGame* g);
		~CGameStateAttack();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	background;	// 背景圖
		iceman			player1;		// 拍子
		fireman         player2;
		Movie			Start;
		Wind			wind;
		CInteger		hits_left;	// 剩下的撞擊數
		CgameMap		gamemap;
		CMovingBitmap	player1image;
		CMovingBitmap	player2image;
		FireBallMovie   fireballmovie;
		IceBallMovie	iceballmovie;
	};
	class CGameStateNaruto : public CGameState
	{
	public:
		CGameStateNaruto(CGame* g);
		~CGameStateNaruto();
		void OnBeginState();							// 設定每次重玩所需的變數
		void OnInit();  								// 遊戲的初值及圖形設定
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		bool Hit();
		bool ShootHit(Sasuke _player1, Shoot *shoot);
		bool ShootHit(EnemyAI* _player1, Shoot *shoot);
	protected:
		void OnMove();									// 移動遊戲元素
		void OnShow();									// 顯示這個狀態的遊戲畫面
	private:
		CMovingBitmap	background;	// 背景圖
		CAnimation		Skillbackground;
		Sasuke			player1;	
		EnemyAI*		player2 = new Shikamaru;
		bloodcount      Player1UI,Player2UI, Player3UI,Player4UI;
		bool			stage1, stage2 ,stage3;
		Kakashi			kakainstrctor;
	};

}