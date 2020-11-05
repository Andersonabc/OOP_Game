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

enum AUDIO_ID  					// �w�q�U�ح��Ī��s��
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
extern bool stage[5];			//���d�O�_�q��
extern int current_level;		//��e���ĴX��
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
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnKeyUp(UINT, UINT, UINT); 				// �B�z��LUp���ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);
		void AddRoutePic();
		void AddShinePic();
		void AddRankPic();
		void ChooseStage(int mode);
		void ChangeLevel();
		void ShowRank();
	protected:
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
		void OnMove();
	private:
		CMovingBitmap logo;								// csie��logo
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		void OnLButtonDown(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonUp(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@
		void OnMouseMove(UINT nFlags, CPoint point);	// �B�z�ƹ����ʧ@

	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnMouseMove(UINT nFlags, CPoint point);  // �B�z�ƹ����ʧ@
		void OnLButtonDown(UINT nFlags, CPoint point);
		void OnInit();
		void SetRank();
		void AddAllAnimation();
	protected:
		void OnMove();	// ���ʹC������
		void OnShow();
	private:
		int counter;	// �˼Ƥ��p�ƾ�
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	background;	// �I����
		iceman			player1;		// ��l
		fireman         player2;
		Movie			Start;
		Wind			wind;
		CInteger		hits_left;	// �ѤU��������
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
		void OnBeginState();							// �]�w�C�������һݪ��ܼ�
		void OnInit();  								// �C������Ȥιϧγ]�w
		void OnKeyDown(UINT, UINT, UINT);
		void OnKeyUp(UINT, UINT, UINT);
		bool Hit();
		bool ShootHit(Sasuke _player1, Shoot *shoot);
		bool ShootHit(EnemyAI* _player1, Shoot *shoot);
	protected:
		void OnMove();									// ���ʹC������
		void OnShow();									// ��ܳo�Ӫ��A���C���e��
	private:
		CMovingBitmap	background;	// �I����
		CAnimation		Skillbackground;
		Sasuke			player1;	
		EnemyAI*		player2 = new Shikamaru;
		bloodcount      Player1UI,Player2UI, Player3UI,Player4UI;
		bool			stage1, stage2 ,stage3;
		Kakashi			kakainstrctor;
	};

}