#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include "audio.h"
#include <ddraw.h>
#include "gamelib.h"
#include "mygame.h"
#include <fstream>
#include <string>
#include <strstream>
bool stage[5] = { false,false,false,false,false };
int current_level = 1;
int ranklevel[5] = { 0,0,0,0,0 };
bool current_rank = false;
int winner ;
namespace game_framework
{

CGameStateInit::CGameStateInit(CGame* g)
    : CGameState(g) 
{
}
CGameStateInit::~CGameStateInit()
{
	int rank_size = (int)rank.size();
	for (int i = 0; i < rank_size; i++)
	{ 
		delete rank[0];
		rank.erase(rank.begin());
	}
}
void CGameStateInit::AddShinePic()
{
	shinePic.AddBitmap(shining01, RGB(30, 30, 30));
	shinePic.AddBitmap(shining02, RGB(30, 30, 30));
	shinePic.AddBitmap(shining03, RGB(30, 30, 30));
	shinePic.AddBitmap(shining04, RGB(30, 30, 30));
	shinePic.AddBitmap(shining05, RGB(30, 30, 30));
	shinePic.AddBitmap(shining06, RGB(30, 30, 30));
	shinePic.AddBitmap(shining07, RGB(30, 30, 30));
	shinePic.AddBitmap(shining08, RGB(30, 30, 30));
	shinePic.AddBitmap(shining09, RGB(30, 30, 30));
	shinePic.AddBitmap(shining10, RGB(30, 30, 30));
	shinePic.AddBitmap(shining12, RGB(30, 30, 30));
	shinePic.AddBitmap(shining13, RGB(30, 30, 30));
	shinePic.AddBitmap(shining14, RGB(30, 30, 30));
	shinePic.AddBitmap(shining15, RGB(30, 30, 30));
	shinePic.AddBitmap(shining16, RGB(30, 30, 30));
	shinePic.AddBitmap(shining17, RGB(30, 30, 30));
	shinePic.AddBitmap(shining18, RGB(30, 30, 30));
	shinePic.AddBitmap(shining19, RGB(30, 30, 30));
	shinePic.AddBitmap(shining20, RGB(30, 30, 30));

}
void CGameStateInit::AddRankPic()
{
	for (unsigned int i = 0; i < rank.size(); i++) {
		rank[i]->AddBitmap(rank1, RGB(255,255,255));
		rank[i]->AddBitmap(rank2, RGB(255,255,255));
		rank[i]->AddBitmap(rank3, RGB(255,255,255));
		rank[i]->SetTopLeft(position[i][0], position[i][1]);
		rank[i]->SetDelayCount(1);
		rank[i]->Reset();
	}

}
void CGameStateInit::AddRoutePic()
{
	routePic.AddBitmap(route1);
	routePic.AddBitmap(routetomain);
	routePic.AddBitmap(route2);
	routePic.AddBitmap(route2tomain);
	routePic.AddBitmap(map3);
	routePic.AddBitmap(map3mainmenu);
	routePic.AddBitmap(map4);
	routePic.AddBitmap(map4mainmenu);
	routePic.AddBitmap(map5);
	routePic.AddBitmap(map5mainmenu);
	routePic.AddBitmap(map6);
	routePic.AddBitmap(map6mainmenu);
}
void CGameStateInit::OnInit()
{
	view = 0;
	current_point = 0;
	AddShinePic();
	AddRoutePic();
	teach.LoadBitmap(map3);
	teach.SetTopLeft(0, 0);
	logo.LoadBitmap(INIT);
	arror.LoadBitmap(ARROR,RGB(255,255,255));
	arror.SetTopLeft(175, 205);
	instructor.AddBitmap(INSTRUCT01);
	instructor.AddBitmap(INSTRUCT02);
	instructor.AddBitmap(INSTRUCT03);
	instructor.AddBitmap(INSTRUCT04);
	instructor.SetTopLeft(0, 0);
	instructor.SetDelayCount(1);
	instructor.Reset();
	routePic.SetTopLeft(0, 0);
	routePic.SetDelayCount(1);
	routePic.Reset();
	shinePic.SetTopLeft(283, 429);
	shinePic.SetDelayCount(1);
	shinePic.Reset();
	starter.LoadBitmap(starting_view);
	starter.SetTopLeft(100, 100);
	starting = true;
	about_show.LoadBitmap(about);
	about_show.SetTopLeft(0, 27);
	aboutIsShow = false;
	for (int temp = 0; temp < 5; temp++) {
		rank.push_back(new CAnimation);
	}
	AddRankPic();
	ChooseStage(1);
///////////////////////////////初始化音樂/////////////////////////////////////////////////
	CAudio::Instance()->Load(GameOver, "sounds\\LevelFailed.wav");
	CAudio::Instance()->Load(gamemusic, "sounds\\gamemusic.wav");
	CAudio::Instance()->Load(Gem, "sounds\\DiamondCollected.wav");
	CAudio::Instance()->Load(Icejump, "sounds\\watergirl_jump.wav");
	CAudio::Instance()->Load(Firejump, "sounds\\fireboy_jump.wav");
	CAudio::Instance()->Load(hit, "sounds\\hit.wav");
	CAudio::Instance()->Load(gamewin, "sounds\\LevelSuccess.wav");
	CAudio::Instance()->Load(fireball, "sounds\\fireball.mp3");
	CAudio::Instance()->Load(iceball, "sounds\\iceball.mp3");
	CAudio::Instance()->Load(attack, "sounds\\attack.mp3");
	CAudio::Instance()->Load(attackmusic, "sounds\\attackmusic.mp3");
	CAudio::Instance()->Load(Round1, "sounds\\Round1.mp3");
	CAudio::Instance()->Load(MagicFire, "sounds\\Magic.mp3");
	CAudio::Instance()->Load(MagicIce, "sounds\\Magic.mp3");
	CAudio::Instance()->Load(ButtonHover, "sounds\\Hover.mp3");
	CAudio::Instance()->Load(Button2Hover, "sounds\\Hover.mp3");
	CAudio::Instance()->Load(Button3Hover, "sounds\\Hover.mp3");
	CAudio::Instance()->Load(Button4Hover, "sounds\\Hover.mp3");
	CAudio::Instance()->Load(Button5Hover, "sounds\\Hover.mp3");
	CAudio::Instance()->Load(Book, "sounds\\book.wav");
	CAudio::Instance()->Load(NarutoBGM, "sounds\\BGM.wav");
	CAudio::Instance()->Load(SasukeCombo, "sounds\\SasukeCombo1.wav");
	CAudio::Instance()->Load(SasukeCombo2, "sounds\\SasukeCombo2.wav");
	CAudio::Instance()->Load(SasukeAttack, "sounds\\SasukeAttack.wav");
	CAudio::Instance()->Load(Sasukeskillsuccess, "sounds\\isSkillsuccess.wav");
	CAudio::Instance()->Load(Sasukefireball, "sounds\\sasukefireball.wav");
	CAudio::Instance()->Load(SasukeSkill, "sounds\\skill1.wav");
	CAudio::Instance()->Load(SasukeSkill4, "sounds\\sikk4-1.wav");
	CAudio::Instance()->Load(SasukeSkill42, "sounds\\skill4-2.wav");
	CAudio::Instance()->Load(NarutoisAttacked, "sounds\\isAttacked.wav");
	CAudio::Instance()->Load(NarutoDie, "sounds\\NarutoDie.wav");
	CAudio::Instance()->Load(EnemySkill, "sounds\\EnemySkill.wav");
	CAudio::Instance()->Load(NarutoBGM2, "sounds\\Naruto2.wav");
///////////////////////////////初始化音樂/////////////////////////////////////////////////
}

void CGameStateInit::OnBeginState()
{
	current_point = 0;
	flag = false;
	ChangeLevel();
	winner = 0;
	
}

void CGameStateInit::ChooseStage(int mode)
{
	if (stage[4] == true) {
		if (mode == 1)
			routePic.Movetonum(10);
		else
			routePic.Movetonum(11);
	}
	else if (stage[3] == true) {
		if (mode == 1)
			routePic.Movetonum(8);
		else
			routePic.Movetonum(9);
	}
	else if (stage[2] == true) {
		if (mode == 1)
			routePic.Movetonum(6);
		else
			routePic.Movetonum(7);
	}
	else if (stage[1] == true) {
		if (mode == 1)
			routePic.Movetonum(4);
		else
			routePic.Movetonum(5);
	}else if((stage[0] == true)){
		if (mode == 1)
			routePic.Movetonum(2);
		else
			routePic.Movetonum(3);
	}
	else {
		if (mode == 1)
			routePic.Movetonum(0);
		else
			routePic.Movetonum(1);
	}
	
	OnShow();
}
void CGameStateInit::ChangeLevel()
{
	for (unsigned int i = 0; i < rank.size(); i++) {
		rank[i]->Movetonum(2-ranklevel[i]);
	}
	current_rank = false;
}
void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (starting == false && aboutIsShow == false)
	{
	
		if (view == 2)
		{
			if ((point.x > 388 && point.x < 456) && (point.y > 404 && point.y < 434)) {
				CAudio::Instance()->Play(Book, false);
				if (instructor.IsFinalBitmap()) {
					view = 0;
					instructor.Reset();
				}
				else instructor.OnMove();
			}
		}
		else if (view == 0)
		{
			if (point.x >= 207 && point.y >= 201 && point.x <= 421 && point.y <= 241)
			{
				view = 1;
			}
			if (point.x >= 207 && point.y >= 259 && point.x <= 421 && point.y <= 298)
			{
				current_level = 98;
				GotoGameState(GAME_STATE_ATTACK);
			}
			if (point.x >= 207 && point.y >= 315 && point.x <= 421 && point.y <= 357)
			{
				view = 2;
			}
			if (point.x >= 207 && point.y >= 374 && point.x <= 421 && point.y <= 412)
			{
				current_level = 98;
				GotoGameState(GAME_STATE_NARUTO);
			}
			if (point.x >= 207 && point.y >= 429 && point.x <= 421 && point.y <= 464)
			{
				PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
			}
			if (point.x >= 545 && point.y >= 0 && point.x <= 640 && point.y <= 90)
			{
				aboutIsShow = true;
			}
		}
		else
		{
			if ((point.x > 30 && point.x < 190) && (point.y > 425 && point.y < 450)) {
				view = 0;
			}
			else
			{
				if ((view == 1) && ((point.x > 290 && point.x < 330) && (point.y > 430 && point.y < 470) || ((point.x > 310 && point.x < 350) && (point.y > 380 && point.y < 415)) || ((point.x > 300 && point.x < 335) && (point.y > 320 && point.y < 345)) || ((point.x > 302 && point.x < 335) && (point.y > 253 && point.y < 285)) || ((point.x > 314 && point.x < 347) && (point.y > 180 && point.y < 205)))) {
					GotoGameState(GAME_STATE_RUN);
				}
			}
		}
	
	}


}
void CGameStateInit::OnMouseMove(UINT nFlags, CPoint point)
{
	current_point = 0;
	if (starting == false && aboutIsShow == false)
	{

		if (view == 0)
		{
			if (point.x >= 207 && point.y >= 201 && point.x <= 421 && point.y <= 241)
			{
				if (arror.Top() != 205) CAudio::Instance()->Play(ButtonHover, false);
				arror.SetTopLeft(175, 205);
			}
			if (point.x >= 207 && point.y >= 259 && point.x <= 421 && point.y <= 298)
			{
				if (arror.Top() != 260) CAudio::Instance()->Play(Button2Hover, false);
				arror.SetTopLeft(175, 260);
			}
			if (point.x >= 207 && point.y >= 315 && point.x <= 421 && point.y <= 357)
			{
				if (arror.Top() != 320) CAudio::Instance()->Play(Button3Hover, false);
				arror.SetTopLeft(175, 320);
			}
			if (point.x >= 207 && point.y >= 374 && point.x <= 421 && point.y <= 412)
			{
				if (arror.Top() != 382) CAudio::Instance()->Play(Button4Hover, false);
				arror.SetTopLeft(175, 382);
			}
			if (point.x >= 207 && point.y >= 430 && point.x <= 421 && point.y <= 475)
			{
				if (arror.Top() != 434) CAudio::Instance()->Play(Button4Hover, false);
				arror.SetTopLeft(175, 434);
			}
			if (point.x >= 545 && point.y >= 0 && point.x <= 640 && point.y <= 90)
			{
				if (arror.Top() != 37) CAudio::Instance()->Play(Button4Hover, false);
				arror.SetTopLeft(528, 37);

			}
		}
		else if (view == 1)
		{
			if ((point.x > 30 && point.x < 190) && (point.y > 425 && point.y < 450))
			{
				ChooseStage(0);
			}
			else
			{
				if (((point.x > 290 && point.x < 330) && (point.y > 430 && point.y < 470)))
				{
					current_point = 1;
					shinePic.SetTopLeft(283, 429);
					current_level = 1;
				}
				else if ((stage[0] == true) && ((point.x > 310 && point.x < 350) && (point.y > 380 && point.y < 415)))
				{
					current_point = 1;
					current_level = 2;
					shinePic.SetTopLeft(305, 372);
				}
				else if ((stage[1] == true) && ((point.x > 300 && point.x < 335) && (point.y > 320 && point.y < 345)))
				{
					current_point = 1;
					shinePic.SetTopLeft(293, 310);
					current_level = 3;
				}
				else if ((stage[2] == true) && ((point.x > 302 && point.x < 335) && (point.y > 253 && point.y < 285)))
				{
					current_point = 1;
					shinePic.SetTopLeft(294, 244);
					current_level = 4;
				}
				else if ((stage[3] == true) && ((point.x > 314 && point.x < 347) && (point.y > 180 && point.y < 205)))
				{
					current_point = 1;
					shinePic.SetTopLeft(305, 168);
					current_level = 5;
				}
				ChooseStage(1);
			}
		}
		else if (view == 2)
		{
			if ((point.x > 388 && point.x < 456) && (point.y > 404 && point.y < 434))
			{
				if (!flag) CAudio::Instance()->Play(ButtonHover + instructor.GetCurrentBitmapNumber(), false);
				flag = true;
			}
			else flag = false;
		}
	}
	
}
void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_Q = 0x51;
	const char KEY_Z = 0x5a;
	const char KEY_ENTER = 0x0D;
	if (nChar == KEY_Q)	for (int i = 0; i < 5; i++)  stage[i] = true;
	else if (nChar == KEY_Z)
	{
		current_level = 99;
		GotoGameState(GAME_STATE_RUN);
	}
	else if (nChar == KEY_ENTER)
	{
		starting = false;
		aboutIsShow = false;
	}
}

void CGameStateInit::ShowRank() 
{
	for (unsigned int i = 0; i < rank.size(); i++) if(stage[i] == true) rank[i]->OnShow();
}

void CGameStateInit::OnShow()
{
	if (view == 0) 
	{
		logo.SetTopLeft(0, 0);
		logo.ShowBitmap();
		arror.ShowBitmap();
	}
	else if (view == 1) 
	{
		routePic.OnShow();
		ShowRank();
		if (current_point == 1) shinePic.OnShow(); 
	}
	else if (view == 2) instructor.OnShow();

	if (starting) {
		starter.ShowBitmap();
	}
	if (aboutIsShow) 
	{
		about_show.ShowBitmap();
	}
}

void CGameStateInit::OnMove()
{
	if (current_point == 1) 
	{
		shinePic.OnMove();
		OnShow();
	}
}

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的結束狀態(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g)
    : CGameState(g)
{
}

void CGameStateOver::OnMove()
{	
	if (winner == 2)
	{	
		IceWinnerPic.OnMove();
		if (IceWinnerPic.IsFinalBitmap())GotoGameState(GAME_STATE_INIT);
	}
	else if (winner == 1)
	{
		FireWinnerPic.OnMove();
		if (FireWinnerPic.IsFinalBitmap())GotoGameState(GAME_STATE_INIT);
	}
	OnShow();
}
void CGameStateOver::SetRank() 
{
	if (time < 60) 
	{
		RankPic.Movetonum(0);
		ranklevel[current_level - 1] = 0;
	}
	else if (time >= 60 && time < 80) 
	{
		RankPic.Movetonum(1);
		ranklevel[current_level - 1] = 1;
	}
	else 
	{
		RankPic.Movetonum(2);
		ranklevel[current_level - 1] = 2;
	}
}
void CGameStateOver::OnBeginState()
{
	time = CSpecialEffect::GetCurrentTimeCount() / 30;
    counter = 30000 * 5;
	timeCount.SetInteger(time);
	IceWinnerPic.Reset();
	FireWinnerPic.Reset();
	SetRank();
}

void CGameStateOver::OnMouseMove(UINT nFlags, CPoint point)
{
	if (current_rank == false) 
	{
		if ((point.x > 184 && point.x < 481) && (point.y > 219 && point.y < 251))		GameOverPic.Movetonum(1);
		else if ((point.x > 239 && point.x < 411) && (point.y > 300 && point.y < 375))	GameOverPic.Movetonum(2);
		else GameOverPic.Movetonum(0);
	}
	else 
	{
		if ((point.x > 261 && point.x < 390) && (point.y > 325 && point.y < 349))		GameWinPic.Movetonum(1);
		else GameWinPic.Movetonum(0);
	}
	OnShow();
}

void CGameStateOver::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (current_rank == false && winner == 0) 
	{
		if ((point.x > 184 && point.x < 481) && (point.y > 219 && point.y < 251)) 
		{
			if(current_level != 98) GotoGameState(GAME_STATE_RUN);
			else GotoGameState(GAME_STATE_ATTACK);
		}
		else if ((point.x > 239 && point.x < 411) && (point.y > 300 && point.y < 375)) GotoGameState(GAME_STATE_INIT);
		else GameOverPic.Movetonum(0);
	}
	else if (current_rank == true && winner == 0) 
	{
		if ((point.x > 261 && point.x < 390) && (point.y > 325 && point.y < 349)) GotoGameState(GAME_STATE_INIT);
	}

}

void CGameStateOver::AddAllAnimation()
{
	IceWinnerPic.AddBitmap(ICEATTACKED1, RGB(0, 0, 0));				//16
	IceWinnerPic.AddBitmap(ICEATTACKED2, RGB(0, 0, 0));				//17
	IceWinnerPic.AddBitmap(ICEATTACKED3, RGB(0, 0, 0));				//18
	IceWinnerPic.AddBitmap(ICEATTACKED4, RGB(0, 0, 0));				//19
	IceWinnerPic.AddBitmap(ICEATTACKED5, RGB(0, 0, 0));				//20
	IceWinnerPic.AddBitmap(ICEATTACKED6, RGB(0, 0, 0));				//21
	IceWinnerPic.AddBitmap(ICEATTACKED1, RGB(0, 0, 0));				//16
	IceWinnerPic.AddBitmap(ICEATTACKED2, RGB(0, 0, 0));				//17
	IceWinnerPic.AddBitmap(ICEATTACKED3, RGB(0, 0, 0));				//18
	IceWinnerPic.AddBitmap(ICEATTACKED4, RGB(0, 0, 0));				//19
	IceWinnerPic.AddBitmap(ICEATTACKED5, RGB(0, 0, 0));				//20
	IceWinnerPic.AddBitmap(ICEATTACKED6, RGB(0, 0, 0));				//21
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED1, RGB(0, 0, 0));			//16
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED2, RGB(0, 0, 0));			//17
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED3, RGB(0, 0, 0));			//18
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED4, RGB(0, 0, 0));			//19
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED5, RGB(0, 0, 0));			//20
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED6, RGB(0, 0, 0));			//21
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED1, RGB(0, 0, 0));			//16
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED2, RGB(0, 0, 0));			//17
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED3, RGB(0, 0, 0));			//18
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED4, RGB(0, 0, 0));			//19
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED5, RGB(0, 0, 0));			//20
	FireWinnerPic.AddBitmap(FIRE_ATTTACKED6, RGB(0, 0, 0));			//21
	FireWinnerPic.SetTopLeft(307, 210);
	FireWinnerPic.SetDelayCount(8);
	IceWinnerPic.SetTopLeft(307, 210);
	IceWinnerPic.SetDelayCount(8);
}

void CGameStateOver::OnInit()
{
    ShowInitProgress(66);	// 接個前一個狀態的進度，此處進度視為66%
	AddAllAnimation();
	winBackground.LoadBitmap(winnerBack);
	winBackground.SetTopLeft(0, 0);
	GameOverPic.AddBitmap(GameOver01);
	GameOverPic.AddBitmap(GameOver02);
	GameOverPic.AddBitmap(GameOver03);
	GameOverPic.SetDelayCount(1);
	GameOverPic.Reset();
	GameOverPic.SetTopLeft(0, 0);
	GameWinPic.AddBitmap(score);
	GameWinPic.AddBitmap(score2);
	GameWinPic.SetDelayCount(1);
	GameWinPic.Reset();
	GameWinPic.SetTopLeft(0, 0);
	RankPic.AddBitmap(CH_A, RGB(255, 255, 255));
	RankPic.AddBitmap(CH_B, RGB(255, 255, 255));
	RankPic.AddBitmap(CH_C, RGB(255, 255, 255));
	RankPic.SetDelayCount(1);
	RankPic.Reset();
	RankPic.SetTopLeft(347,252);
	timeCount.LoadBitmap();
	timeCount.SetTopLeft(280, 172);
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	if (winner == 0) 
	{
		if (!current_rank) 
		{
			GameOverPic.SetTopLeft(0, 0);
			GameOverPic.OnShow();
		}
		else if (current_rank) 
		{
			GameWinPic.SetTopLeft(0, 0);
			GameWinPic.OnShow();
			timeCount.ShowBitmap();
			RankPic.OnShow();
		}
	}
	else if (winner == 2) 
	{
		winBackground.ShowBitmap();
		IceWinnerPic.OnShow(2);
	}
	else if (winner == 1)
	{
		winBackground.ShowBitmap();
		FireWinnerPic.OnShow(2);
	}
}
CGameStateRun::CGameStateRun(CGame* g)
    : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
    player1.Initialize();
	player2.Initialize();
	CSpecialEffect::GetCurrentTimeCount();                                                                                              
	gamemap.deleteObject();
	gamemap.Initialize(current_level,&player1,&player2);
	gamemap.LoadObject();
	CAudio::Instance()->Play(gamemusic);
}

void CGameStateRun::OnMove()
{
	showmovie.OnMove();
	if (showmovie.isOK()) 
	{
		///////////////初始化變數////////////////
		bool winfire, winice;		
		bool press = false;			
		bool Redpress = false;		
		player1.Setfly(false);		
		player2.Setfly(false);
		/////////////////////////////////////////////////////////判斷是否在物件上////////////////////////////////////////////////////////////////
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++) gamemap.GetFallWall()[i]->SetFall(0);
		for (int i = 0; i < (int)gamemap.GetChainElevator().size(); i++)
		{
			gamemap.GetChainElevator()[i]->SetFall(0);
			gamemap.GetChainElevator()[i]->SetFall2(0);
		}
		for (int i = 0; i < gamemap.GetButtonnum(); i++)
		{
			if (!press) press = gamemap.GetButton()[i]->Onpress(((player1.GetX2() + player1.GetX1()) / 2), player1.GetY2() - 1);
			if (!press)	press = gamemap.GetButton()[i]->Onpress(((player2.GetX2() + player2.GetX1()) / 2), player2.GetY2() - 1);
		}
		for (int i = 0; i < (int)gamemap.GetRedButton().size(); i++)
		{
			if (!Redpress)  Redpress = gamemap.GetRedButton()[i]->Onpress(((player1.GetX2() + player1.GetX1()) / 2), player1.GetY2() - 1);
			if (!Redpress)	Redpress = gamemap.GetRedButton()[i]->Onpress(((player2.GetX2() + player2.GetX1()) / 2), player2.GetY2() - 1);
		}
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++)
		{
			if (gamemap.GetFallWall()[i]->GetFall() == 0)	gamemap.GetFallWall()[i]->SetFall(player1);
			if (gamemap.GetFallWall()[i]->GetFall() == 0)	gamemap.GetFallWall()[i]->SetFall(player2);
		}
		for (int i = 0; i < (int)gamemap.GetChainElevator().size(); i++)
		{
			gamemap.GetChainElevator()[i]->SetFall(player1);
			gamemap.GetChainElevator()[i]->SetFall(player2);
			gamemap.GetChainElevator()[i]->SetFall2(player1);
			gamemap.GetChainElevator()[i]->SetFall2(player2);
		}
		for (int i = 0; i < (int)gamemap.GetRising().size(); i++)
		{
			if (!player1.Getfly())player1.Setfly(gamemap.GetRising()[i]->SetRising(&player1));
			if (!player2.Getfly())player2.Setfly(gamemap.GetRising()[i]->SetRising(&player2));
		}
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++) gamemap.FallWallMove(i);
		gamemap.StoneDown();
		for (int i = 0; i < (int)gamemap.GetChainElevator().size(); i++) gamemap.ChainElevatorMove(i);
		int move = gamemap.elevatormove(press);
		if ((int)gamemap.GetRedButton().size() != 0) gamemap.makewall(Redpress);
		/////////////////////////////////////////////////////////判斷四周是否為牆壁////////////////////////////////////////////////////////////////
		player1.sethead(gamemap.wall(player1));
		player1.setleft(gamemap.leftwall(player1));
		player1.setright(gamemap.rightwall(&player1));
		player2.sethead(gamemap.wall(player2));
		player2.setleft(gamemap.leftwall(player2));
		player2.setright(gamemap.rightwall(&player2));
		player1.setfloor(gamemap.floor(&player1, move));
		player2.setfloor(gamemap.floor(&player2, move));
		player1.OnMove();
		player2.OnMove();
		/////////////////////////////////////////////////////////////人物死亡///////////////////////////////////////////////////////////////////////
		if (gamemap.gameover(player1)) { CAudio::Instance()->Play(hit, false); CAudio::Instance()->Stop(gamemusic); GotoGameState(GAME_STATE_OVER); }
		if (gamemap.gameover(player2)) { CAudio::Instance()->Play(hit, false); CAudio::Instance()->Stop(gamemusic); GotoGameState(GAME_STATE_OVER); }
		/////////////////////////////////////////////////////////////獲得寶石音效///////////////////////////////////////////////////////////////////
		if (gamemap.isgem(player1)) { player1.Addgem(); CAudio::Instance()->Play(Gem, false); }
		if (gamemap.isgem(player2)) { player2.Addgem(); CAudio::Instance()->Play(Gem, false); }
		/////////////////////////////////////////////////////////////判斷各人物是否通關/////////////////////////////////////////////////////////////
		winfire = gamemap.Clearance(player2);
		winice = gamemap.Clearance(player1);
		///////////////////////////////////////////////////////////////////通關/////////////////////////////////////////////////////////////////////
		if (winfire&&winice)
		{
			stage[current_level - 1] = true;
			current_rank = true;
			CAudio::Instance()->Stop(gamemusic);
			CAudio::Instance()->Play(gamewin);
			GotoGameState(GAME_STATE_OVER);
		}
		else CSpecialEffect::SetCurrentTime();		//計時
	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
    ShowInitProgress(33);	// 接個前一個狀態的進度，此處進度視為33%
	/////////////讀取圖片/////////////
    player1.LoadBitmap();	
	player2.LoadBitmap();
	gamemap.LoadBitmap();
	showmovie.LoadBitmap();
	showmovie.Init();
	/////////////////////////////////
	ShowInitProgress(50);	// 此處進度視為50%
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_SPACE = ' ';
    const char KEY_LEFT  = 0x25; // keyboard左箭頭
    const char KEY_UP    = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_LEFT2 = 0x41; // keyboard A
	const char KEY_UP2 = 0x57; // keyboard W
	const char KEY_RIGHT2 = 0x44; // keyboard D
	const char KEY_DOWN2= 0x53; // keyboard S
	if (nChar == KEY_LEFT)
		player1.SetMovingLeft(true);
    if (nChar == KEY_RIGHT)
        player1.SetMovingRight(true);
    if (nChar == KEY_UP)
        player1.SetMovingUp(true);
    if (nChar == KEY_DOWN)
        player1.SetMovingDown(true);
	if (nChar == KEY_LEFT2)
		player2.SetMovingLeft(true);
	if (nChar == KEY_RIGHT2)
		player2.SetMovingRight(true);
	if (nChar == KEY_UP2)
		player2.SetMovingUp(true);
	if (nChar == KEY_DOWN2)
		player2.SetMovingDown(true);
	if (nChar == KEY_SPACE)
		GotoGameState(GAME_STATE_RUN);
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard左箭頭
    const char KEY_UP    = 0x26; // keyboard上箭頭
    const char KEY_RIGHT = 0x27; // keyboard右箭頭
    const char KEY_DOWN  = 0x28; // keyboard下箭頭
	const char KEY_LEFT2 = 0x41; // keyboard A
	const char KEY_UP2 = 0x57; // keyboard W
	const char KEY_RIGHT2 = 0x44; // keyboard D
	const char KEY_DOWN2 = 0x53; // keyboard S
	if (nChar == KEY_LEFT)
		player1.SetMovingLeft(false);
    if (nChar == KEY_RIGHT)
        player1.SetMovingRight(false);
    if (nChar == KEY_UP)
        player1.SetMovingUp(false);
    if (nChar == KEY_DOWN)
        player1.SetMovingDown(false);
	if (nChar == KEY_LEFT2)
		player2.SetMovingLeft(false);
	if (nChar == KEY_RIGHT2)
		player2.SetMovingRight(false);
	if (nChar == KEY_UP2)
		player2.SetMovingUp(false);
	if (nChar == KEY_DOWN2)
		player2.SetMovingDown(false);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
	if (!showmovie.isOK()) 
	{
		if (((point.x > 235 && point.x < 423) && (point.y > 174 && point.y < 200)))
		{
			showmovie.ResetPos();
			showmovie.Init();
			GotoGameState(GAME_STATE_RUN);
		}
		else if (((point.x > 244 && point.x < 422) && (point.y > 285 && point.y < 310))) 
		{
			showmovie.ResetPos();
			showmovie.Init();
			CAudio::Instance()->Stop(gamemusic);
			GotoGameState(GAME_STATE_INIT);
		}
	}
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
	if (((point.x > 310 && point.x < 380) && (point.y > 450 && point.y < 480))) showmovie.SetUp();
	if (point.x < 160 || point.x > 528) showmovie.SetDown();
	if (!showmovie.isOK()) 
	{
		if (((point.x > 235 && point.x < 423) && (point.y > 174 && point.y < 200)))		 showmovie.GoRetry();
		else if (((point.x > 244 && point.x < 422) && (point.y > 285 && point.y < 310))) showmovie.GoMenu();
		else showmovie.GoInit();
	}
}

void CGameStateRun::OnShow()
{
	///////////顯示地圖、角色、暫停畫面///////////////
	gamemap.OnShow();
	player2.OnShow();
	player1.OnShow();
	showmovie.OnShow();
	//////////////////////////////////////////////////
}

CGameStateAttack::CGameStateAttack(CGame * g)
	: CGameState(g)
{
}

CGameStateAttack::~CGameStateAttack()
{
	//////////////////////////////刪除剩餘子彈////////////////////////////
	player1.DeleteBullet();
	player2.DeleteBullet();
	//////////////////////////////////////////////////////////////////////
}

void CGameStateAttack::OnBeginState()
{
	////////////////////////////人物初始化////////////////////////////////
	player1.Initialize();
	player2.Initialize();
	////////////////////////////地圖初始化////////////////////////////////
	gamemap.deleteObject();
	gamemap.Initialize(current_level, &player1, &player2);
	gamemap.LoadObject();
	////////////////////////////風向初始化////////////////////////////////
	wind.Init();
	////////////////////////////播放開頭音效及BGM/////////////////////////
	CAudio::Instance()->Play(Round1);
	CAudio::Instance()->Play(attackmusic);
	////////////////////////////開場動畫位置//////////////////////////////
	Start.SetIceXY(player1.GetX1(), player1.GetY1());
	Start.SetFireXY(player2.GetX1(), player2.GetY1());
	Start.Restart();
	/////////////////////////刪除上場剩餘子彈/////////////////////////////
	player1.DeleteBullet();
	player2.DeleteBullet();
}

void CGameStateAttack::OnInit()
{
	///////////////////////////////////////讀取圖片及設定圖片初始位置////////////////////////////////
	player1.LoadBitmap(1);
	player2.LoadBitmap(1);
	Start.LoadBitmap();
	background.LoadBitmap(pic_background);					
	gamemap.LoadBitmap();
	background.SetTopLeft(0, 0);
	player1image.LoadBitmap(ICEATTACK2, RGB(0, 0, 0));
	player2image.LoadBitmap(FIRE_ATTTACK, RGB(0, 0, 0));
	player1image.SetTopLeft(574, 10);
	player2image.SetTopLeft(20, 10);
	fireballmovie.LoadBitmap();
	iceballmovie.LoadBitmap();
	wind.LoadBitmap();
	//////////////////////////////////////////////////////////////////////////////////////////////////
}

void CGameStateAttack::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_SPACE = ' ';
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_LEFT2 = 0x41; // keyboard A
	const char KEY_UP2 = 0x57; // keyboard W
	const char KEY_RIGHT2 = 0x44; // keyboard D
	const char KEY_DOWN2 = 0x53; // keyboard S
	const char KEY_Z = 0x5a;
	const char KEY_J = 0x4a;
	const char KEY_1 = 0x61;
	const char KEY_2 = 0x62;
	const char KEY_K = 'K';
	if (nChar == KEY_LEFT)
	{
		player1.SetMovingLeft(true);
		player1.SetCombodelay();		//將combo歸零倒數計時設為5
	}
	if (nChar == KEY_RIGHT)
	{
		player1.SetMovingRight(true);
		player1.SetCombodelay();
	}

	if (nChar == KEY_UP)
	{
		player1.SetMovingUp(true);
		player1.SetCombodelay();
	}

	if (nChar == KEY_DOWN)
	{
		player1.SetMovingDown(true);
		player1.SetCombodelay();
	}

	if (nChar == KEY_1)
	{
		player1.SetAttack(true);
		player1.SetCombodelay();
	}
	if (nChar == KEY_2)
	{
		player1.SetisMagic(true);
		player1.SetCombodelay();
		CAudio::Instance()->Play(13, true);	//播放集氣音效
	}
	if (nChar == KEY_LEFT2)
	{
		player2.SetMovingLeft(true);
		player2.SetCombodelay();
	}

	if (nChar == KEY_RIGHT2)
	{
		player2.SetMovingRight(true);
		player2.SetCombodelay();
	}

	if (nChar == KEY_UP2)
	{
		player2.SetMovingUp(true);
		player2.SetCombodelay();
	}

	if (nChar == KEY_DOWN2)
	{
		player2.SetMovingDown(true);
		player2.SetCombodelay();
	}

	if (nChar == KEY_J)
	{
		player2.SetAttack(true);
		player2.SetCombodelay();
	}

	if (nChar == KEY_K)
	{
		player2.SetisMagic(true);
		CAudio::Instance()->Play(12, true);  //播放集氣音效
	}
}

void CGameStateAttack::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x26; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_LEFT2 = 0x41; // keyboard A
	const char KEY_UP2 = 0x57; // keyboard W
	const char KEY_RIGHT2 = 0x44; // keyboard D
	const char KEY_DOWN2 = 0x53; // keyboard S
	const char KEY_Z = 0x5a;
	const char KEY_J = 0x4a;
	const char KEY_SPACE = ' ';
	const char KEY_2 = 0x62;
	const char KEY_K = 'K';
	if (nChar == KEY_LEFT)
		player1.SetMovingLeft(false);

	if (nChar == KEY_RIGHT)
		player1.SetMovingRight(false);

	if (nChar == KEY_UP)
		player1.SetMovingUp(false);

	if (nChar == KEY_DOWN)
		player1.SetMovingDown(false);

	if (nChar == KEY_2)
	{
		player1.SetisMagic(false);
		CAudio::Instance()->Stop(13);	//暫停集氣音效
	}
	
	if (nChar == KEY_LEFT2)
		player2.SetMovingLeft(false);

	if (nChar == KEY_RIGHT2)
		player2.SetMovingRight(false);

	if (nChar == KEY_UP2)
		player2.SetMovingUp(false);

	if (nChar == KEY_DOWN2)
		player2.SetMovingDown(false);

	if (nChar == KEY_K)
	{
		player2.SetisMagic(false);
		CAudio::Instance()->Stop(12);	//暫停集氣音效
	}
}

void CGameStateAttack::OnMove()
{
	//////////////////開場動畫/////////////////
	if (!Start.Getend())
	{
		Start.OnMove();
	}
	//////////////////技能動畫/////////////////
	else if (fireballmovie.isStart())
	{
		fireballmovie.OnMove();
	}
	else if (iceballmovie.isStart())
	{
		iceballmovie.OnMove();
	}
	////////////////////遊戲運行/////////////////
	else
	{
		//////////////////////////////////下落電梯判斷///////////////////////////////////////////////
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++) gamemap.GetFallWall()[i]->SetFall(0);
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++)
		{
			if (gamemap.GetFallWall()[i]->GetFall() == 0)	gamemap.GetFallWall()[i]->SetFall(player1);
			if (gamemap.GetFallWall()[i]->GetFall() == 0)	gamemap.GetFallWall()[i]->SetFall(player2);
		}
		for (int i = 0; i < (int)gamemap.GetFallWall().size(); i++) gamemap.FallWallMove(i);
		///////////////////////////////////二段跳刷新/////////////////////////////////////////////////
		if (player1.GetY1() == player1.Getfloor() - 39)
			player1.SetTwojump(true);
		if (player2.GetY1() == player2.Getfloor() - 39)
			player2.SetTwojump(true);
		////////////////////////////////判斷角色四周////////////////////////////////////////////////
		player1.sethead(gamemap.wall(player1));
		player1.setleft(gamemap.leftwall(player1));
		player1.setright(gamemap.rightwall(&player1));
		player2.sethead(gamemap.wall(player2));
		player2.setleft(gamemap.leftwall(player2));
		player2.setright(gamemap.rightwall(&player2));
		player1.setfloor(gamemap.floor(&player1));
		player2.setfloor(gamemap.floor(&player2));
		player1.OnMove(&player2);
		player2.OnMove(&player1);
		/////////////////////////////////風向移動角色及計時//////////////////////////////////////////////////
		wind.onMove(&player1);
		wind.onMove(&player2);
		wind.Count();
		/////////////////////////////////技能動畫////////////////////////////////////////////////////////////
		if (player1.SetShooting())  
			iceballmovie.Init();
		if (player2.SetShooting())  
			fireballmovie.Init();
		/////////////////////////////////衝刺技能判斷/////////////////////////////////////////////////////////
		player1.SetRush();
		player2.SetRush();
		/////////////////////////////////遊戲結束////////////////////////////////////////////////////////////
		if (gamemap.gameover(player1)) { CAudio::Instance()->Play(hit, false); CAudio::Instance()->Stop(attackmusic); winner = 1; GotoGameState(GAME_STATE_OVER); }
		if (gamemap.gameover(player2)) { CAudio::Instance()->Play(hit, false); CAudio::Instance()->Stop(attackmusic); winner = 2; GotoGameState(GAME_STATE_OVER); }
	}
}

void CGameStateAttack::OnShow()
{
	////////////////////////////////////顯示地圖/////////////////////////////
	gamemap.OnShow();
	//////////////////////////////判斷是否顯示開場動畫///////////////////////
	if (!Start.Getend()) {Start.OnShow();}
	else
	{
		///////////////////////////顯示角色//////////////////////////////////
		player1image.ShowBitmap(1.5);
		player2image.ShowBitmap(1.5);
		player2.OnShow(1);
		player1.OnShow(1);
		///////////////////////////顯示技能動畫//////////////////////////////////
		if (fireballmovie.isStart())
			fireballmovie.OnShow();
		else if (iceballmovie.isStart())
			iceballmovie.OnShow();
		///////////////////////////顯示風向///////////////////////////////////////
		wind.OnShow();
	}
}

CGameStateNaruto::CGameStateNaruto(CGame * g): CGameState(g)
{
}

CGameStateNaruto::~CGameStateNaruto()
{
	/////////////////////////////刪除人物物件//////////////////////////////////////////
	player1.Deleteobject();
	delete player2;
}

void CGameStateNaruto::OnBeginState()
{
	/////////////////////////////////////初始地圖//////////////////////////////////////
	background.SetTopLeft(0, 0);
	Skillbackground.SetTopLeft(0, 0);
	////////////////////////////////////判斷第幾關敵人////////////////////////////////
	if (stage1) { delete player2; player2 = new Shikamaru; }
	if (stage2) { delete player2; player2 = new Neji;}
	if (stage3) { delete player2; player2 = new Orochimaru; }
	////////////////////////////////////人物初始化///////////////////////////////////////
	player1.Initialize();
	player2->LoadBitmap();
	player2->SetPlayer(&player1);
	if(!stage3)CAudio::Instance()->Play(NarutoBGM,true);
	else CAudio::Instance()->Play(NarutoBGM2, true);
	if(stage1)kakainstrctor.ChangeSection(1);
}

void CGameStateNaruto::OnInit()
{
	/////////////////////////////////////////UI圖初始化///////////////////////////////////
	Player1UI.Init(20, 20, "player", 128, SASUKE, RGB(73, 176, 255));
	Player2UI.Init(426, 20, "AI", 128, ShikamaruUI, RGB(255, 100, 100));
	Player3UI.Init(426, 20, "AI", 128, NejiUI, RGB(0, 128, 128));
	Player4UI.Init(426, 20, "AI", 128, OrochimaruUI, RGB(0, 128, 128));
	//////////////////////////////////////////各圖片讀取///////////////////////////////////
	player1.LoadBitmap();
	background.LoadBitmap(NarutoBackground);
	Skillbackground.AddBitmap(SkillBackground1);
	for(int i=0;i<4;i++) Skillbackground.AddBitmap(SkillBackground2+i);
	Skillbackground.SetDelayCount(3);
	Skillbackground.Reset();
	kakainstrctor.Init();
	/////////////////////////////////////////關卡初始化////////////////////////////////////
	stage1 = true;
	stage2 = stage3=false;
}

void CGameStateNaruto::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x5a; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_X = 0x58;
	const char KEY_A = 0x41;
	const char KEY_B = 0x42;
	if (kakainstrctor.IsDone()) {
		if (nChar == KEY_LEFT)
			player1.SetMovingLeft(true);
		if (nChar == KEY_RIGHT)
			player1.SetMovingRight(true);
		if (nChar == KEY_UP)
			player1.SetMovingUp(true);
		if (nChar == KEY_X && player1.GetMove())
		{
			player1.Addattacknum();
			player1.SetisMolding(true);
		}
		if (nChar == ' ')
			player1.ChangeChakura(128);
		if (nChar == KEY_A)
			player2->SetSkill();
		if (nChar == KEY_B)
			player2->SetSkill2();
	}
}

void CGameStateNaruto::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_LEFT = 0x25; // keyboard左箭頭
	const char KEY_UP = 0x5a; // keyboard上箭頭
	const char KEY_RIGHT = 0x27; // keyboard右箭頭
	const char KEY_DOWN = 0x28; // keyboard下箭頭
	const char KEY_X = 0x58;
	const char KEY_S = 0x53;
	const char KEY_Z = 0x5a;

	if (kakainstrctor.IsDone()) {
		if (nChar == KEY_LEFT)
			player1.SetMovingLeft(false);
		if (nChar == KEY_RIGHT)
			player1.SetMovingRight(false);

		if (nChar == KEY_X)
			player1.SetisMolding(false);
	}
	else {
		if (nChar == KEY_S)
		{
			if (kakainstrctor.GetSection() == 5 || (kakainstrctor.GetSection() == 3))
			{
				CAudio::Instance()->Stop(NarutoBGM);
				GotoGameState(GAME_STATE_INIT);
			}
			kakainstrctor.SetDone(true);
		}
		if (nChar == KEY_Z && kakainstrctor.GetEnd())
			if(kakainstrctor.GetSection() == 1)kakainstrctor.ChangeFilm(kakainstrctor.GetFilm() + 1);
			else if (kakainstrctor.GetSection() == 2)kakainstrctor.ChangeVicFilm(kakainstrctor.GetVicFilm() + 1);
			else if (kakainstrctor.GetSection() == 4)kakainstrctor.ChangeVic2Film(kakainstrctor.GetVic2Film() + 1);
			else if (kakainstrctor.GetSection() == 5 || (kakainstrctor.GetSection() == 3))
			{
				CAudio::Instance()->Stop(NarutoBGM);
				GotoGameState(GAME_STATE_INIT);
			}
		if (nChar == KEY_Z && kakainstrctor.IsFinish())
		{
			if (kakainstrctor.GetSection() == 5 || (kakainstrctor.GetSection() == 3))
			{
				CAudio::Instance()->Stop(NarutoBGM);
				GotoGameState(GAME_STATE_INIT);
			}
			kakainstrctor.SetDone(true);
		}

	}

}

///////////////////////////////////////////////////////////////////////判斷碰撞///////////////////////////////////////////////////////////////////////////////
bool CGameStateNaruto::Hit()
{
	if (player1.GetX1() >= player2->GetX1() && player1.GetX1() <= player2->GetX2() && player1.GetY1() >= player2->GetY1() && player1.GetY1() <= player2->GetY2())
		return true;
	if (player1.GetX2() >= player2->GetX1() && player1.GetX2() <= player2->GetX2() && player1.GetY1() >= player2->GetY1() && player1.GetY1() <= player2->GetY2())
		return true;
	if (player1.GetX1() >= player2->GetX1() && player1.GetX1() <= player2->GetX2() && player1.GetY2() >= player2->GetY1() && player1.GetY2() <= player2->GetY2())
		return true;
	if (player1.GetX2() >= player2->GetX1() && player1.GetX2() <= player2->GetX2() && player1.GetY2() >= player2->GetY1() && player1.GetY2() <= player2->GetY2())
		return true;
	if (player2->GetX1() >= player1.GetX1() && player2->GetX1() <= player1.GetX2() && player2->GetY1() >= player1.GetY1() && player2->GetY1() <= player1.GetY2())
		return true;
	if (player2->GetX2() >= player1.GetX1() && player2->GetX2() <= player1.GetX2() && player2->GetY1() >= player1.GetY1() && player2->GetY1() <= player1.GetY2())
		return true;
	if (player2->GetX1() >= player1.GetX1() && player2->GetX1() <= player1.GetX2() && player2->GetY2() >= player1.GetY1() && player2->GetY2() <= player1.GetY2())
		return true;
	if (player2->GetX2() >= player1.GetX1() && player2->GetX2() <= player1.GetX2() && player2->GetY2() >= player1.GetY1() && player2->GetY2() <= player1.GetY2())
		return true;
	return false;
}
bool CGameStateNaruto::ShootHit(Sasuke _player1, Shoot *shoot)
{
	if (_player1.GetX1() >= shoot->GetX1() && _player1.GetX1() <= shoot->GetX2() && _player1.GetY1() >= shoot->GetY1() && _player1.GetY1() <= shoot->GetY2())
		return true;
	if (_player1.GetX2() >= shoot->GetX1() && _player1.GetX2() <= shoot->GetX2() && _player1.GetY1() >= shoot->GetY1() && _player1.GetY1() <= shoot->GetY2())
		return true;
	if (_player1.GetX1() >= shoot->GetX1() && _player1.GetX1() <= shoot->GetX2() && _player1.GetY2() >= shoot->GetY1() && _player1.GetY2() <= shoot->GetY2())
		return true;
	if (_player1.GetX2() >= shoot->GetX1() && _player1.GetX2() <= shoot->GetX2() && _player1.GetY2() >= shoot->GetY1() && _player1.GetY2() <= shoot->GetY2())
		return true;
	if (shoot->GetX1() >= _player1.GetX1() && shoot->GetX1() <= _player1.GetX2() && shoot->GetY1() >= _player1.GetY1() && shoot->GetY1() <= _player1.GetY2())
		return true;
	if (shoot->GetX2() >= _player1.GetX1() && shoot->GetX2() <= _player1.GetX2() && shoot->GetY1() >= _player1.GetY1() && shoot->GetY1() <= _player1.GetY2())
		return true;
	if (shoot->GetX1() >= _player1.GetX1() && shoot->GetX1() <= _player1.GetX2() && shoot->GetY2() >= _player1.GetY1() && shoot->GetY2() <= _player1.GetY2())
		return true;
	if (shoot->GetX2() >= _player1.GetX1() && shoot->GetX2() <= _player1.GetX2() && shoot->GetY2() >= _player1.GetY1() && shoot->GetY2() <= _player1.GetY2())
		return true;
	return false;
}

bool CGameStateNaruto::ShootHit(EnemyAI * _player1, Shoot * shoot)
{
	if (_player1->GetX1() >= shoot->GetX1() && _player1->GetX1() <= shoot->GetX2() && _player1->GetY1() >= shoot->GetY1() && _player1->GetY1() <= shoot->GetY2())
		return true;
	if (_player1->GetX2() >= shoot->GetX1() && _player1->GetX2() <= shoot->GetX2() && _player1->GetY1() >= shoot->GetY1() && _player1->GetY1() <= shoot->GetY2())
		return true;
	if (_player1->GetX1() >= shoot->GetX1() && _player1->GetX1() <= shoot->GetX2() && _player1->GetY2() >= shoot->GetY1() && _player1->GetY2() <= shoot->GetY2())
		return true;
	if (_player1->GetX2() >= shoot->GetX1() && _player1->GetX2() <= shoot->GetX2() && _player1->GetY2() >= shoot->GetY1() && _player1->GetY2() <= shoot->GetY2())
		return true;
	if (shoot->GetX1() >= _player1->GetX1() && shoot->GetX1() <= _player1->GetX2() && shoot->GetY1() >= _player1->GetY1() && shoot->GetY1() <= _player1->GetY2())
		return true;
	if (shoot->GetX2() >= _player1->GetX1() && shoot->GetX2() <= _player1->GetX2() && shoot->GetY1() >= _player1->GetY1() && shoot->GetY1() <= _player1->GetY2())
		return true;
	if (shoot->GetX1() >= _player1->GetX1() && shoot->GetX1() <= _player1->GetX2() && shoot->GetY2() >= _player1->GetY1() && shoot->GetY2() <= _player1->GetY2())
		return true;
	if (shoot->GetX2() >= _player1->GetX1() && shoot->GetX2() <= _player1->GetX2() && shoot->GetY2() >= _player1->GetY1() && shoot->GetY2() <= _player1->GetY2())
		return true;
	return false;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CGameStateNaruto::OnMove()
{
	if (kakainstrctor.IsDone())
	{
		//////////////////////////////////////////////////////人物移動/////////////////////////////////////////
		player1.OnMove();
		player2->UI(Hit());
		///////////////////////////////////////////攻擊判定////////////////////////////////////////////////
		if ((player1.GetCurrentBitmapNumber() == 40 || player1.GetCurrentBitmapNumber() == 49) && Hit() && !player2->GetDie()) { player2->SetAttacked(true); player2->SetDirection(0); }
		else if ((player1.GetCurrentBitmapNumber() == 180 || player1.GetCurrentBitmapNumber() == 189) && Hit() && !player2->GetDie()) { player2->SetAttacked(true); player2->SetDirection(1); }
		else if ((player1.GetCurrentBitmapNumber() == 61 || player1.GetCurrentBitmapNumber() == 27) && Hit() && !player2->GetDie())  player2->SetDie(0);
		else if ((player1.GetCurrentBitmapNumber() == 201 || player1.GetCurrentBitmapNumber() == 167) && Hit() && !player2->GetDie()) player2->SetDie(1);
		/////////////////////////////////////////////技能判定//////////////////////////////////////////////////////////////
		if (player1.GetisSkill() && Hit() && (player1.GetSkillCurrentBitmapNumber() == 14 + player1.GetDirection() * 44 || player1.GetSkillCurrentBitmapNumber() == 23 + player1.GetDirection() * 44 || player1.GetSkillCurrentBitmapNumber() == 32 + player1.GetDirection() * 44 || player1.GetSkillCurrentBitmapNumber() == 41 + player1.GetDirection() * 44)) player2->SetAttacked(true);
		////////////////////////////////////////////飛行道具判定////////////////////////////////////////////////////////////
		for (int i = 0; i < (int)player2->GetShurikan().size(); i++) if (ShootHit(player1, player2->GetShurikan()[i])) { player1.SetAttacked(true); player2->SetShurikanDelete(i); }
		for (int i = 0; i < (int)player1.GetFireball().size(); i++)if (ShootHit(player2, player1.GetFireball()[i])) { if (player2->GetMove()) { player2->SetAttacked(true); } player1.SetFireballDelete(i); }
		for (int i = 0; i < (int)player1.GetShurikan().size(); i++)if (ShootHit(player2, player1.GetShurikan()[i])) { if (player2->GetMove()) { player2->SetAttacked(true); } player1.SetShurikanDelete(i); }
		/////////////////////////////////////////////敵人移動/////////////////////////////
		player2->OnMove();
		//////////////////////////////////////////////判斷敵人是否死亡/////////////////////////
		if (player2->Getblood() <= 0)
		{
			player1.Deleteobject();
			if (stage1)
			{
				stage1 = false;
				stage2 = true;
				kakainstrctor.ChangeSection(2);
				GotoGameState(GAME_STATE_NARUTO);
			}else if (stage2)
			{
				kakainstrctor.ChangeSection(4);
				stage3 = true;
				stage2 = false;
				GotoGameState(GAME_STATE_NARUTO);
			}
			else if (stage3)
			{
				stage1 = true;
				stage3 = false;
				CAudio::Instance()->Stop(NarutoBGM2);
				kakainstrctor.ChangeSection(5);
			}
			
			
			
		}
		///////////////////////////////////////////////技能動畫/////////////////////////////////////
		if (!player2->GetisSkill() && player2->GetMove() && player1.GetisSkill() && Hit() && player1.GetSkillCurrentBitmapNumber() >= 114 + player1.GetDirection() * 24 && player1.GetSkillCurrentBitmapNumber() <= 137 + player1.GetDirection() * 24 && !player1.GetSkillsuccess())
		{
			player1.SetSkillsuccess();
			CAudio::Instance()->Play(28);
			player1.GetSkillsuccessMovie()->Movetonum(0 + player1.GetDirection() * 53);
		}
		if (player1.GetSkillsuccessMovie()->GetCurrentBitmapNumber() >= 4 + player1.GetDirection() * 53 && player1.GetSkillsuccessMovie()->GetCurrentBitmapNumber() <= 37 + player1.GetDirection() * 53) { player2->SetAttacked(true); player2->Setblood(player2->Getblood()+1); }
		else if (player1.GetSkillsuccessMovie()->GetCurrentBitmapNumber() == 52 + player1.GetDirection() * 53)
		{
			player2->SetDie(true);
			player2->SetonFloor();
		}
		////////////////////////////////////////////////判斷技能是否命中////////////////////////////////////////////
		if (player1.GetSkillsuccess())
		{
			player2->SetMove(false);
			if (player1.GetDirection() == 0)player2->SetXY(player1.GetX2(), player1.GetY1()+20);
			else player2->SetXY(player1.GetX1() - 50, player1.GetY1()+20);
		}
		//////////////////////////////////////////////各人物UI更新////////////////////////////////////
		Player1UI.ChangeChakura(player1.GetChakura());
		Player1UI.ChangeBlood(player1.Getblood());
		Player2UI.ChangeBlood(player2->Getblood());
		Player3UI.ChangeBlood(player2->Getblood());
		Player4UI.ChangeBlood(player2->Getblood());
		Player1UI.SetisMolding(player1.GetisMolding(), player1.GetMagic());
		///////////////////////////////////////////////判斷敵方是否使用技能/////////////////////////////
		if (player1.Getskillstart()->isStart()) player2->SetMove(false);
		else if (player1.GetisSkill()) player2->SetMove(true);
		//////////////////////////////////////////////更換技能背景////////////////////////////
		if (player1.GetSkillsuccess())Skillbackground.OnMove();
		///////////////////////////////////////////////死亡/////////////////////////////
		if (player1.Getblood() <= 0)
		{
			player1.Deleteobject();
			kakainstrctor.ChangeSection(3);
			CAudio::Instance()->Stop(NarutoBGM);
			CAudio::Instance()->Stop(NarutoBGM2);
			stage2 = false;
			stage3 = false;
			stage1 = true;
		}
	}



}

void CGameStateNaruto::OnShow()
{
	////////////////////////////////////////////////顯示圖片////////////////////////////////////////////
	background.ShowBitmap();
	if(player1.GetSkillsuccess()) Skillbackground.OnShow();
	player2->OnShow();
	player1.OnShow();
	Player1UI.OnShow();
	if (stage1)Player2UI.OnShow();
	if (stage2)Player3UI.OnShow();
	if (stage3)Player4UI.OnShow();
	if (player1.Getskillstart()->isStart()) player1.Getskillstart()->OnShow();
	if (player2->Getskillstart()->isStart()) player2->Getskillstart()->OnShow();
	kakainstrctor.OnShow(kakainstrctor.GetSection());
}

}