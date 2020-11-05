#include "yellowbutton.h"
#include "elevator.h"
#include "man.h"
#include "iceman.h"
#include "fireman.h"
#include "Stone.h"
#include "firedoor.h"
#include "icedoor.h"
#include "fire.h"
#include "water.h"
#include "poison.h"
#include "FallWall.h"
#include "RedButton.h"
#include "Rising.h"
#include "Chainelevator.h"
#include "lever.h"
namespace game_framework {
	class CgameMap {
	public:
		CgameMap();
		~CgameMap();
		void Initialize(int i);
		void Initialize(int i,man *player1,man *player2);
		int GetButtonnum();
		vector<yellowbutton*> GetButton();
		vector<RedButton*> GetRedButton();
		vector<FallWall*> GetFallWall();
		vector<Rising*> GetRising();
		vector<ChainElevator*> GetChainElevator();
		void LoadBitmap();
		void LoadObject();
		void OnShow();
		int floor(man *player,int move);
		int floor(man *player);
		bool wall(man player);
		int leftwall(man player);
		int rightwall(man *player);
		int elevatormove(bool flag);
		void FallWallMove(int j);
		void ChainElevatorMove(int j);
		void PushStone(int direction);
		void StoneDown();
		bool gameover(man player);
		bool isgem(man player);
		bool Clearance(man player);
		int OnSlade(man *player, int i, int j);
		int OnRSlade(man *player, int i, int j);
		void makewall(bool flag);
		void LeverOn(bool flag);
		void deleteObject();
		//bool CheckPosition(int i, int j, man player);
	protected:
		CMovingBitmap down, slade,Rslade, icegem, firegem, rock, lr, dul, dur, durl,background;
		water _water;
		fire _fire;
		poison _poison;
		vector<RedButton*> Redbutton;
		vector<buttonelevator*> _elevator;
		vector<yellowbutton*> button;
		vector<rockStone*> stone;
		vector<FallWall*> fallwall;
		vector<Rising*> rising;
		vector<ChainElevator*> chainelevator;
		vector<lever*> Lever;
		int buttonnum,elevatornum,icegemnum,firegemnum,stonenum,fallwallnum, redbuttonnum,risingnum,chainelevatornum,Levernum;
		firedoor fdoor;
		icedoor idoor;
		int map[24][32];
		int delaycount;
		const int MW, MH;
	};
}