#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "CgameMap.h"
#include <fstream>
#include <string>
#include <strstream>
#include <iostream>
namespace game_framework {
	CgameMap::CgameMap()
	:MW(20), MH(20), buttonnum(0), elevatornum(0), icegemnum(0), firegemnum(0), stonenum(0), fallwallnum(0), risingnum(0),delaycount(5)
	{
		Initialize(1);
	}

	CgameMap::~CgameMap()
	{
		/////////////////////解構地圖物件////////////////////////////
		for (int i = 0; i < buttonnum; i++) delete button[i];
		for (int i = 0; i < buttonnum; i++) button.erase(button.begin());
		for (int i = 0; i < elevatornum; i++) delete _elevator[i];
		for (int i = 0; i < elevatornum; i++) _elevator.erase(_elevator.begin());
		for (int i = 0; i < stonenum; i++) delete stone[i];
		for (int i = 0; i < stonenum; i++) stone.erase(stone.begin());
		for (int i = 0; i < fallwallnum; i++) delete fallwall[i];
		for (int i = 0; i < fallwallnum; i++) fallwall.erase(fallwall.begin());
		for (int i = 0; i < redbuttonnum; i++) delete Redbutton[i];
		for (int i = 0; i < redbuttonnum; i++) Redbutton.erase(Redbutton.begin());
		for (int i = 0; i < risingnum; i++) delete rising[i];
		for (int i = 0; i < risingnum; i++) rising.erase(rising.begin());
		for (int i = 0; i < chainelevatornum; i++) delete chainelevator[i];
		for (int i = 0; i < chainelevatornum; i++) chainelevator.erase(chainelevator.begin());
		for (int i = 0; i < Levernum; i++) delete Lever[i];
		for (int i = 0; i < Levernum; i++) Lever.erase(Lever.begin());
		///////////////////////////////////////////////////////////////
	}

	void CgameMap::Initialize(int mapID)
	{
		////////////////////////////////////////////////////////初始化/////////////////////////////////////////
		buttonnum = 0, elevatornum = 0, icegemnum = 0, firegemnum = 0, stonenum = 0, fallwallnum = 0, redbuttonnum = 0, risingnum = 0,chainelevatornum=0,Levernum=0;
		int count = 0, flag = 0;
		string MapId = "Map" + to_string(mapID), str;
		int map_init[24][32];
		ifstream inFile("maps.txt");
		////////////////////////////////////////////////////////讀檔///////////////////////////////////////////
		while (!inFile.eof())
		{
			getline(inFile, str);
			if (str == MapId)
			{
				for (int i = 0; i < 24; i++)
					for (int j = 0; j < 32; j++)
						inFile >> map_init[i][j];
				break;
			}
		}

		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				map[i][j] = map_init[i][j];
				switch (map[i][j])
				{
				case 2:
					buttonnum++;
					button.push_back(new yellowbutton);
					break;
				case 3:
					count++;
					if (count == 3)
					{
						elevatornum++;
						_elevator.push_back(new buttonelevator);
					}
					break;
				case 7:
					firegemnum++;
					break;
				case 8:
					icegemnum++;
					break;
				case 11:
					stonenum++;
					stone.push_back(new rockStone);
					break;
				case 14:
					count++;
					if (count == 3)
					{
						fallwallnum++;
						fallwall.push_back(new FallWall);
					}
					break;
				case 15:
					redbuttonnum++;
					Redbutton.push_back(new RedButton);
					break;
				case 17:
					count++;
					if (count == 3)
					{
						risingnum++;
						rising.push_back(new Rising);
					}
					break;
				case 18:
					count++;
					if (count == 3)
					{
						flag++;
						count = 0;
					}
					if (flag == 2)
					{
						chainelevatornum++;
						chainelevator.push_back(new ChainElevator);
					}
					break;
				case 20:
					Levernum++;
					Lever.push_back(new lever);
				default:
					count = 0;
					break;
				}
			}
		}
		inFile.close();
		//////////////////////////////////////////////////////////////////////////////
	}

	void CgameMap::Initialize(int i, man* player1, man* player2)
	{
		/////////////////////////////////////角色位置讀檔/////////////////////////////
		Initialize(i);
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				if (map[i][j] == 99) { player1->SetXY((MW*j), (MH*i)); map[i][j] = 0; }
				if (map[i][j] == 98) { player2->SetXY((MW*j), (MH*i)); map[i][j] = 0; }
			}
		}
		/////////////////////////////////////////////////////////////////////////////
	}

	int CgameMap::GetButtonnum()
	{
		return buttonnum;
	}

	vector<yellowbutton*> CgameMap::GetButton()
	{
		return button;
	}

	vector<RedButton*> CgameMap::GetRedButton()
	{
		return Redbutton;
	}

	vector<FallWall*> CgameMap::GetFallWall()
	{
		return fallwall;
	}

	vector<Rising*> CgameMap::GetRising()
	{
		return rising;
	}

	vector<ChainElevator*> CgameMap::GetChainElevator()
	{
		return chainelevator;
	}

	void CgameMap::LoadBitmap()
	{
		///////////////////////////////////////////////讀取圖片////////////////////////////////////////
		down.LoadBitmap(pic_d);
		slade.LoadBitmap(pic_slade, RGB(255, 255, 255));
		background.LoadBitmap(ground);
		Rslade.LoadBitmap(rslade, RGB(255, 255, 255));
		icegem.LoadBitmap(bluegem, RGB(255, 255, 255));
		firegem.LoadBitmap(redgem, RGB(255, 255, 255));
		idoor.LoadBitmap();
		fdoor.LoadBitmap();
		_water.LoadBitmap();
		_fire.LoadBitmap();
		_poison.LoadBitmap();
		/////////////////////////////////////////////////////////////////////////////////////////////
	}

	void CgameMap::LoadObject()
	{
		/////////////////////////////////物件讀取圖片///////////////////////////////////////////////
		int elevatorcount = 0, stonecount = 0, fallwallcount = 0,risingcount=0,chainelevatorcount=0,flag=0;
		for (int i = 0; i < buttonnum; i++)	button[i]->LoadBitmap();
		for (int i = 0; i < stonenum; i++)	stone[i]->LoadBitmap();
		for (int i = 0; i < elevatornum; i++)	_elevator[i]->LoadBitmap();
		for (int i = 0; i < fallwallnum; i++)	fallwall[i]->LoadBitmap();
		for (int i = 0; i < risingnum; i++)	rising[i]->LoadBitmap();
		for (int i = 0; i < chainelevatornum; i++)	chainelevator[i]->LoadBitmap();
		for (int i = 0; i < Levernum; i++)	Lever[i]->LoadBitmap();
		///////////////////////////////物件設定位置/////////////////////////////////////
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				switch (map[i][j])
				{
				case 3:
					_elevator[elevatorcount]->setoxy((MW*j), (MH*i));
					_elevator[elevatorcount++]->SetTopLeft((MW*j), (MH*i));
					j = j + 2;
					break;
				case 11:
					stone[stonecount++]->SetXY((MW*j), (MH*i));
					break;
				case 14:
					fallwall[fallwallcount]->Setoxy((MW*j), (MH*i));
					fallwall[fallwallcount++]->SetTopLeft((MW*j), (MH*i));
					j = j + 2;
					break;
				case 17:
					rising[risingcount++]->SetXY((MW*j), (MH*i));
					j = j + 2;
					break;
				case 18:
					if (flag == 0)
					{
						chainelevator[chainelevatorcount]->SetTopLeft((MW*j), (MH*i));
						flag = 1;
						j = j + 2;
					}
					else if (flag == 1)
					{
						chainelevator[chainelevatorcount++]->SetX2Y2((MW*j),(MH*i));
						flag = 0;
						j = j + 2;
					}
					break;
				default:
					break;
				}
			}
			/////////////////////////////////////設定電梯範圍///////////////////////////
		}
		for (int i = 0; i < 24; i++)
		{
			for (int j = 0; j < 32; j++)
			{
				switch (map[i][j])
				{
				case 19:
					for (int k = 0; k < chainelevatorcount; k++)
					{
						if ((MW*j) == chainelevator[k]->GetX())
							chainelevator[k]->Setaimy1((MH*i));
						else if (((MW*j) == chainelevator[k]->GetX2()))
							chainelevator[k]->Setaimy2((MH*i));
					}
					map[i][j] = 0;
					break;
				default:
					break;
				}
			}
		}
		////////////////////////////////讀取按鈕圖片//////////////////////
		for (int i = 0; i < redbuttonnum; i++) Redbutton[i]->LoadBitmap();
		////////////////////////////////設定陷阱流速//////////////////////
		_fire.SetDelayTime();
		_water.SetDelayTime();
		_poison.SetDelayTime();
		//////////////////////////////////////////////////////////////////
	}

	void CgameMap::OnShow()
	{
		//////////////////////////////根據地圖資訊建立地圖///////////////
		int snum = 0;
		int bnum = 0;
		int Rbnum = 0;
		int Lnum = 0;
		for (int i = 0; i < 24; i++)
			for (int j = 0; j < 32; j++)
			{
				switch (map[i][j]) {
				case 0:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 1:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					break;
				case 2:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					button[bnum]->SetTopLeft((MW*j), (MH*i));
					button[bnum++]->ShowBitmap();
					break;
				case 3:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 4:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					_fire.OnShow((MW*j), (MH*i));
					break;
				case 5:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					_water.OnShow((MW*j), (MH*i));
					break;
				case 6:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					_poison.OnShow((MW*j), (MH*i));
					break;
				case 7:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					firegem.SetTopLeft((MW*j), (MH*i)+5);
					firegem.ShowBitmap();
					break;
				case 8:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					icegem.SetTopLeft((MW*j), (MH*i)+5);
					icegem.ShowBitmap();
					break;
				case 9:
					j++;
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					fdoor.OnShow((MW*j) - 40, (MH*i) - 40);
					break;
				case 10:
					j++;
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					idoor.OnShow((MW*j) - 40, (MH*i) - 40);
					break;
				case 11:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 12:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					slade.SetTopLeft((MW*j), (MH*i));
					slade.ShowBitmap();
					break;
				case 13:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					Rslade.SetTopLeft((MW*j), (MH*i));
					Rslade.ShowBitmap();
					break;
				case 14:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 15:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					Redbutton[Rbnum]->SetTopLeft((MW*j), (MH*i));
					Redbutton[Rbnum++]->ShowBitmap();
					break;
				case 16:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					break;
				case 17:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 18:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					break;
				case 20:
					background.SetTopLeft((MW*j), (MH*i));
					background.ShowBitmap();
					Lever[Lnum++]->SetXY((MW*j), (MH*i));
					break;
				case 21:
					down.SetTopLeft((MW*j), (MH*i));
					down.ShowBitmap();
					break;
				default:
					ASSERT(0);
				}
			}
			//////////////////將物件建立在地圖上///////////////////
		for (int i = 0; i < stonenum;i++) stone[i]->ShowBitmap();
		for (int i = 0; i < elevatornum; i++) _elevator[i]->ShowBitmap();
		for (int i = 0; i < fallwallnum; i++) fallwall[i]->ShowBitmap();
		for (int i = 0; i < risingnum; i++) rising[i]->OnShow();
		for (int i = 0; i < chainelevatornum; i++) chainelevator[i]->onShow();
		for (int i = 0; i < Levernum; i++)
		{
			Lever[i]->OnShow();
			LeverOn(Lever[i]->Getimage().IsFinalBitmap());
		}
		///////////////////////陷阱流動///////////////////////////
		_fire.OnMove();
		_water.OnMove();
		_poison.OnMove();
		/////////////////////////////////////////////////////////
	}
	int CgameMap::floor(man *player,int move)
	{
		//////////////////////抓取角色位置///////////////////////////////
		int i = ((player->GetX2() + player->GetX1()) / 2) / 20;
		int j = (player->GetY2()) / 20;
		////////////////////////判斷是否在石頭上//////////////////////////
		if (stone.size() != 0) if (!stone[0]->CheckStone(player->GetX1() + 5,player->GetX2()-5,player->GetY1()+5,player->GetY2()+5))  return  stone[0]->GetY()-1;
		/////////////////////////判斷腳下位置/////////////////////////////
		switch (map[j][i]){
		case 0:
			switch (map[j-1][i]) { 
			case 3:
				player->SetXY(player->GetX1(), player->GetY1()+move);
				return (_elevator[0]->GetY());
			case 4:
				return (MH*j + 12);
			case 5:
				return (MH*j + 12);
			case 6:
				return (MH*j + 12);
			case 12:
				return (OnSlade(player, i, j - 1));
			case 13:
				return (OnRSlade(player, i, j - 1));
			case 14:
			for (i = 0; i < (int)fallwall.size(); i++)
			{
				if (fallwall[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), fallwall[i]->GetY()-39);
					return (fallwall[i]->GetY());
				}
			}
			return (MH*j);
			case 18:
			for (i = 0; i < (int)chainelevator.size(); i++)
			{
				if (chainelevator[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY() - 39);
					return (chainelevator[i]->GetY());
				}
				else if (chainelevator[i]->Onstand2(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY2()+ (int)chainelevator[i]->Getcount() - 39 +4);
					return (player->GetY2());
				}
			}
			case 20:
				if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j-1));
				else
				{
					player->setleft(1);
					return (OnRSlade(player, i, j-1));
				}
			default:
				return 480;
			}
		case 1:
			switch (map[j - 1][i])
			{
			case 12:
				return (OnSlade(player,i,j-1));
			case 13:
				return (OnRSlade(player, i, j - 1));
			case 20:
				if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j-1));
				else
				{
					player->setleft(1);
					return (OnRSlade(player, i, j-1));
				}
			default:
				break;
			}
			return (MH*j);
			break;
		case 2:
			return (MH*(j+1));
		case 3:
			player->SetXY(player->GetX1(), player->GetY1() + move);
			return (_elevator[0]->GetY());
		case 4:
			return (MH*j + 12);
		case 5:
			return (MH*j + 12);
		case 6:
			return (MH*j + 12);
		case 11:
			return (MH*j+3);
		case 12:
			return (OnSlade(player,i,j));
		case 13:
			player->setleft(1);
			return (OnRSlade(player, i, j));
		case 14:
			for (i = 0; i < (int)fallwall.size(); i++)
			{
				if (fallwall[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), fallwall[i]->GetY()-39);
					return (fallwall[i]->GetY());
				}
			}
			return (MH*j);
		case 15:
			return (MH*(j + 1));
		case 16:
			return (MH*j);
		case 17:
			return (MH*j);
		case 18:
			for (i = 0; i < (int)chainelevator.size(); i++)
			{
				if (chainelevator[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY() - 39);
					return (chainelevator[i]->GetY());
				}
				else if (chainelevator[i]->Onstand2(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY2() + (int)chainelevator[i]->Getcount() - 39);
					return (player->GetY2());
				}
				return 480;
			}
		case 20:
			if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j));
			else
			{
				player->setleft(1);
				return (OnRSlade(player, i, j));
			}
		case 21:
			return (MH*j);
		default:
			return 480;
		}
	}
	int CgameMap::floor(man * player)
	{
		//////////////////////////////////////////角色位置//////////////////////////////////
		int i = ((player->GetX2() + player->GetX1()) / 2) / 20;
		int j = (player->GetY2()) / 20;
		//////////////////////////////////////////判斷是否在石頭上//////////////////////////
		if (stone.size() != 0) if (!stone[0]->CheckStone(player->GetX1() + 5, player->GetX2() - 5, player->GetY1() + 5, player->GetY2() + 5))  return  stone[0]->GetY() - 1;
		/////////////////////////////////////////判斷四周位置///////////////////////////////////
		switch (map[j][i]) {
		case 0:
			switch (map[j - 1][i]) {
			case 3:
				player->SetXY(player->GetX1(), (_elevator[0]->GetY()-39));
				return (_elevator[0]->GetY());
			case 4:
				return (MH*j + 12);
			case 5:
				return (MH*j + 12);
			case 6:
				return (MH*j + 12);
			case 12:
				return (OnSlade(player, i, j - 1));
			case 13:
				return (OnRSlade(player, i, j - 1));
			case 14:
				for (i = 0; i < (int)fallwall.size(); i++)
				{
					if (fallwall[i]->Onstand(*player))
					{
						player->SetXY(player->GetX1(), fallwall[i]->GetY() - 39);
						return (fallwall[i]->GetY());
					}
				}
				return (MH*j);
			case 18:
				for (i = 0; i < (int)chainelevator.size(); i++)
				{
					if (chainelevator[i]->Onstand(*player))
					{
						player->SetXY(player->GetX1(), chainelevator[i]->GetY() - 39);
						return (chainelevator[i]->GetY());
					}
					else if (chainelevator[i]->Onstand2(*player))
					{
						player->SetXY(player->GetX1(), chainelevator[i]->GetY2() + (int)chainelevator[i]->Getcount() - 39 + 4);
						return (player->GetY2());
					}
				}
			case 20:
				if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j - 1));
				else
				{
					player->setleft(1);
					return (OnRSlade(player, i, j - 1));
				}
			default:
				return 480;
			}
		case 1:
			switch (map[j - 1][i])
			{
			case 12:
				return (OnSlade(player, i, j - 1));
			case 13:
				return (OnRSlade(player, i, j - 1));
			case 20:
				if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j - 1));
				else
				{
					player->setleft(1);
					return (OnRSlade(player, i, j - 1));
				}
			default:
				break;
			}
			return (MH*j);
			break;
		case 2:
			return (MH*(j + 1));
		case 3:
			player->SetXY(player->GetX1(), (_elevator[0]->GetY()-39));
			return (_elevator[0]->GetY());
		case 4:
			return (MH*j + 12);
		case 5:
			return (MH*j + 12);
		case 6:
			return (MH*j + 12);
		case 11:
			return (MH*j + 3);
		case 12:
			return (OnSlade(player, i, j));
		case 13:
			player->setleft(1);
			return (OnRSlade(player, i, j));
		case 14:
			for (i = 0; i < (int)fallwall.size(); i++)
			{
				if (fallwall[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), fallwall[i]->GetY() - 39);
					return (fallwall[i]->GetY());
				}
			}
			return (MH*j);
		case 15:
			return (MH*(j + 1));
		case 16:
			return (MH*j);
		case 17:
			return (MH*j);
		case 18:
			for (i = 0; i < (int)chainelevator.size(); i++)
			{
				if (chainelevator[i]->Onstand(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY() - 39);
					return (chainelevator[i]->GetY());
				}
				else if (chainelevator[i]->Onstand2(*player))
				{
					player->SetXY(player->GetX1(), chainelevator[i]->GetY2() + (int)chainelevator[i]->Getcount() - 39);
					return (player->GetY2());
				}
				return 480;
			}
		case 20:
			if (!Lever[0]->Getimage().IsFinalBitmap()) return (OnSlade(player, i, j));
			else
			{
				player->setleft(1);
				return (OnRSlade(player, i, j));
			}
		case 21:
			return (MH*j);
		default:
			return 480;
		}
		///////////////////////////////////////////////////////////////////////////////////
	}
	bool CgameMap::wall(man player)
	{
		///////////////////////////////////抓取角色左上右上座標////////////////////////////
		int i1 = (player.GetX1() + 5) / 20;
		int j1 = (player.GetY1() + 5 - player.Getvelocity()) / 20;
		int i2 = (player.GetX2() - 5) / 20;
		int j2 = (player.GetY1() + 5 - player.Getvelocity()) / 20;
		///////////////////////////////////判斷頭上方塊////////////////////////////////////
		switch (map[j1][i1])
		{
		case 0:
			switch (map[j2][i2])
			{
			case 0:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1() + 5, player.GetX2() - 5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			case 1:
				return false;
			case 2:
				return false;
				break;
			case 7:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1() + 5, player.GetX2() - 5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			case 8:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1() + 5, player.GetX2() - 5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			default:
				return false;
			}
		case 1:
			return false;
		case 2:
			return false;
		case 7:
			switch (map[j2][i2])
			{
			case 0:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1() + 5, player.GetX2() - 5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			case 1:
				return false;
			case 2:
				return false;
			case 7:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1()+5, player.GetX2()-5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			case 8:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1()+5, player.GetX2()-5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			default:
				return false;
			}
		case 8:
			switch (map[j2][i2])
			{
			case 0:
				return true;
			case 1:
				return false;
			case 2:
				return false;
			case 7:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1()+5, player.GetX2()-5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			case 8:
				if (stone.size() != 0) return stone[0]->CheckStone(player.GetX1()+5, player.GetX2()-5, player.GetY1() + 5, player.GetY2()-3);
				else return true;
			default:
				return false;
			}
		case 15:
			return false;
		case 17:
			return false;
		case 18:
			return false;
		default:
			return false;
		}
		///////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int CgameMap::leftwall(man player)
	{
		////////////////////////////////////抓取角色左上左下位置///////////////////////////////////////////
		int i1 = (player.GetX1() + 5 - player.Getstep()) / 20;
		int j1 = (player.GetY1() + 5) / 20;
		int j2 = (player.GetY2() - 6) / 20;
		/////////////////////////////////////判斷是否為石頭///////////////////////////////////////////////
		if(stone.size() != 0){
			if (!stone[0]->CheckStone(player.GetX1()-player.Getstep()+5, player.GetX1()  - player.Getstep()+5, player.GetY1()+5, player.GetY2()-3)) 
			{ 
				if (player.Onfloor())
					PushStone(1);//////////推動石頭
				return 0; 
			}
		}
		//////////////////////////////////////判斷左邊方塊////////////////////////////////////////////////
		switch (map[j1][i1])
		{
		case 0:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
			case 1:
				return 0;
			case 2:
				return 1;
			case 12:
				return 0;
			case 13:
				return 1;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 20:
				if (!Lever[0]->Getimage().IsFinalBitmap() && player.GetMovingLeft()) Lever[0]->OnMove();
				else return 1;
				return 0;
			case 21:
				return 0;
			default:
				return 1;
			}
			break;
		case 1:
			return 0;
			break;
		case 2:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
			case 1:
				return 0;
				break;
			case 2:
				return 1;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 21:
				return 0;
			default:
				return 1;
			}
		case 12:
			return 0;
		case 13:
			return 1;
		case 15:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
				break;
			case 1:
				return 0;
				break;
			case 2:
				return 1;
				break;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 21:
				return 0;
			default:
				return 1;
				break;
			}
		case 16:
			return 0;
		case 17:
			return 0;
		case 18:
			return 0;
		case 20:
			if (!Lever[0]->Getimage().IsFinalBitmap()&& player.GetMovingLeft()) Lever[0]->OnMove();
			else return 1;
			return 0;
		case 21:
			return 0;
		default:
			return 1;
			break;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int CgameMap::rightwall(man *player)
	{
		////////////////////////////////////////抓取角色右上右下座標////////////////////////////////////
		int i1 = (player->GetX2() - 5 + player->Getstep()) / 20;
		int j1 = (player->GetY1() + 5) / 20;
		int j2 = (player->GetY2() - 6) / 20;
		/////////////////////////////////////////判斷是否為石頭/////////////////////////////////////////
		if (stone.size() != 0){
			if (!stone[0]->CheckStone(player->GetX2() + player->Getstep(), player->GetX2() +player->Getstep(), player->GetY1() + 5, player->GetY2() - 3))
			{ 
				if(player->Onfloor())
					PushStone(2); /////////////推動石頭
				return 0; 
			}
		}
		//////////////////////////////////////判斷右邊方塊//////////////////////////////////////////////
		switch (map[j1][i1])
		{
		case 0:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
				break;
			case 1:
				return 0;
				break;
			case 2:
				return 1;
			case 12:
				return 1;
				break;
			case 13:
				return 0;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 20:
				if (Lever[0]->Getimage().IsFinalBitmap() && player->GetMovingRight()) Lever[0]->OnMove();
				else return 1;
				return 0;
			case 21:
				return 0;
			default:
				return 1;
				break;
			}
			break;
		case 1:
			return 0;
		case 2:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
			case 1:
				return 0;
			case 2:
				return 1;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 21:
				return 0;
			default:
				return 1;
			}
			break;
		case 12:
			return 1;
			break;
		case 13:
			return 0;
		case 15:
			switch (map[j2][i1])
			{
			case 0:
				return 1;
			case 1:
				return 0;
			case 2:
				return 1;
			case 15:
				return 1;
			case 16:
				return 0;
			case 17:
				return 0;
			case 21:
				return 0;
			default:
				return 1;
			}
			break;
		case 16:
			return 0;
		case 17:
			return 0;
		case 18:
			return 0;
		case 20:
			if (Lever[0]->Getimage().IsFinalBitmap() && player->GetMovingRight()) Lever[0]->OnMove();
			else return 1;
			return 0;
		case 21:
			return 0;
		default:
			return 1;
			break;
		}
		/////////////////////////////////////////////////////////////////////////////////
	}
	void CgameMap::PushStone(int direction)
	{
		////////////////////若有石頭/////////////////////////////////////////////////
		if (stonenum != 0)
		{
			//////////////////////////////石頭往左推//////////////////////////////
			if (direction == 1)
			{
				if (map[stone[0]->GetY() / 20][((stone[0]->GetX() - 7) / 20)] != 1 || map[stone[0]->GetY() / 20 + 1][((stone[0]->GetX() - 7) / 20)] != 1)
				{
					/////////////////////////更新地圖///////////////////////////////
					map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 0;
					map[stone[0]->GetY() / 20][(stone[0]->GetX() - 7) / 20] = 11;
					stone[0]->SetXY(stone[0]->GetX() - 7, stone[0]->GetY());
					stone[0]->ShowBitmap();
					/////////////////////////////////////////////////////////////////
				}

			}
			/////////////////////////////石頭往右推///////////////////////////////////
			else if (direction == 2)
			{
				if (map[stone[0]->GetY() / 20][((stone[0]->GetX() + 7) / 20) + 2] != 1 && map[stone[0]->GetY() / 20 + 1][((stone[0]->GetX() + 7) / 20) + 2] != 1)
				{
					//////////////////////////////更新地圖/////////////////////////////////
					map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 0;
					map[stone[0]->GetY() / 20][(stone[0]->GetX() + 7) / 20] = 11;
					stone[0]->SetXY(stone[0]->GetX() + 7, stone[0]->GetY());
					stone[0]->ShowBitmap();
					/////////////////////////////////////////////////////////////////////
				}
			}
		}
	}
	void CgameMap::StoneDown()
	{
		////////////////////////////////////判斷是否有石頭////////////////////////////////
		if (stonenum != 0)
		{
			///////////////////////////////判斷石頭底下方塊////////////////////////////////
			if ((map[(stone[0]->GetY() / 20) + 2][stone[0]->GetX() / 20] == 18 || map[(stone[0]->GetY() / 20) + 2][(stone[0]->GetX() / 20) + 1] == 18) || (map[(stone[0]->GetY() / 20) + 1][stone[0]->GetX() / 20] == 18 || map[(stone[0]->GetY() / 20) + 1][(stone[0]->GetX() / 20) + 1] == 18))
			{
				for (int i = 0; i < (int)chainelevator.size(); i++)
				{
					///////////////////////若石頭壓在電梯一上//////////////////////////////
					if (chainelevator[i]->OnStand(stone[0]->GetX(), stone[0]->GetY()+40))
					{
						////////////////////////電梯下降地圖更新///////////////////////////////
						map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 0;
						stone[0]->SetXY(stone[0]->GetX(), chainelevator[i]->GetY() - 40);
						map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 11;
						chainelevator[i]->SetFall(chainelevator[i]->GetFall()+1);
						////////////////////////////////////////////////////////////////////////
					}
					///////////////////////若石頭壓在電梯二上//////////////////////////////
					else if (chainelevator[i]->OnStand2(stone[0]->GetX(), stone[0]->GetY() + 40))
					{
						///////////////////////電梯下降地圖更新////////////////////////////////
						map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 0;
						stone[0]->SetXY(stone[0]->GetX(), chainelevator[i]->GetY2() + (int)chainelevator[i]->Getcount() - 40 );
						map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 11;
						chainelevator[i]->SetFall2(chainelevator[i]->GetFall2()+1);
						//////////////////////////////////////////////////////////////////////
					}
					////////////////////////////////////////////////////////////////////////////
				}
			}
			//////////////////////////////////////////若底下為空氣//////////////////////////////
			else if (map[(stone[0]->GetY() / 20) + 2][stone[0]->GetX() / 20] == 0 && map[(stone[0]->GetY() / 20) + 2][(stone[0]->GetX() / 20) + 1] == 0)
			{
				/////////////////////////下降並更新地圖///////////////////////////////////
				map[stone[0]->GetY() / 20][stone[0]->GetX() / 20] = 0;
				map[stone[0]->GetY() / 20 + 1][stone[0]->GetX() / 20] = 11;
				stone[0]->SetXY(stone[0]->GetX(), stone[0]->GetY() + 5);
				stone[0]->ShowBitmap();
				////////////////////////////////////////////////////////////////////////
			}
		}
	}
	int CgameMap::elevatormove(bool flag)
	{
		/////////////////////////////////電梯數大於1/////////////////////////////////
		if (elevatornum != 0)
		{
			if (flag)
			{
				///////////////////////////////電梯下降////////////////////////////////////
				if (map[((_elevator[0]->GetY()-1) / 20)+1][_elevator[0]->GetX() / 20] != 1)
				{
					int nowy = _elevator[0]->down();
					for (int i = 0; i < 3; i++)
					{
						map[(_elevator[0]->GetY()- _elevator[0]->Getvelocity()) / 20-1][_elevator[0]->GetX() / 20 + i] = 0;
						map[((_elevator[0]->GetY()-1) / 20)][_elevator[0]->GetX() / 20 + i] = 3;
					}
					_elevator[0]->SetTopLeft(_elevator[0]->GetX(), nowy);
					_elevator[0]->ShowBitmap();
					return _elevator[0]->Getvelocity();
				}
				///////////////////////////////////////////////////////////////////////////////
			}
			else
			{
				//////////////////////////電梯上升////////////////////////////////////////
				if (_elevator[0]->getoy() < _elevator[0]->GetY())
				{
					int nowy = _elevator[0]->up();
					for (int i = 0; i < 3; i++)
					{
						map[_elevator[0]->GetY() / 20][_elevator[0]->GetX() / 20 + i] = 3;
						if(map[(_elevator[0]->GetY() / 20) + 1][_elevator[0]->GetX() / 20 + i]==3) map[(_elevator[0]->GetY() / 20) + 1][_elevator[0]->GetX() / 20 + i] = 0;
					}
					_elevator[0]->SetTopLeft(_elevator[0]->GetX(), nowy);
					_elevator[0]->ShowBitmap();
					return _elevator[0]->Getvelocity()*-1;
				}
				///////////////////////////////////////////////////////////////////////////
			}
		}
		return 0;
	}

	void CgameMap::FallWallMove(int j)
	{
		/////////////////////////////若是角色站在上方//////////////////////////////////
		if (fallwall[j]->GetFall()>0)
		{
			///////////////////////////////地板下陷//////////////////////////////////////
			if (map[((fallwall[j]->GetY()) / 20) + 1][fallwall[j]->GetX() / 20] != 1)
			{
				fallwall[j]->Down();
				for (int i = 0; i < 3; i++)
				{
					map[(fallwall[j]->GetY() - 4) / 20 - 1][fallwall[j]->GetX() / 20 + i] = 0;
					map[((fallwall[j]->GetY()-4) / 20)][fallwall[j]->GetX() / 20 + i] = 14;
				}
				fallwall[j]->ShowBitmap();
			}
			////////////////////////////////////////////////////////////////////////////////
		}
		else 
		{
			/////////////////////////////////地板上升回地面////////////////////////////////
			if (fallwall[j]->Getoy() < fallwall[j]->GetY())
			{
			fallwall[j]->Up();
			for (int i = 0; i < 3; i++)
			{
				map[fallwall[j]->GetY() / 20][fallwall[j]->GetX() / 20 + i] = 14;
				if (map[(fallwall[j]->GetY() / 20) + 1][fallwall[j]->GetX() / 20 + i] == 14) map[(fallwall[j]->GetY() / 20) + 1][fallwall[j]->GetX() / 20 + i] = 0;
			}
			fallwall[j]->ShowBitmap();
			}
			////////////////////////////////////////////////////////////////////////////////
		}
	}

	void CgameMap::ChainElevatorMove(int j)
	{
		//////////////////////若電梯一重量大於電梯二////////////////////////////////////////
		if (chainelevator[j]->GetFall() >chainelevator[j]->GetFall2())
		{
			///////////////////電梯1下降、電梯2上升////////////////////////////////
			if (chainelevator[j]->GetY()<chainelevator[j]->GetaimY1())
			{
				chainelevator[j]->Down();
				for (int i = 0; i < 3; i++)
				{
					map[(chainelevator[j]->GetY() - 4) / 20 - 1][chainelevator[j]->GetX() / 20 + i] = 0;
					map[((chainelevator[j]->GetY() - 4) / 20)][chainelevator[j]->GetX() / 20 + i] = 18;
					map[(chainelevator[j]->GetY2()+ (int)chainelevator[j]->Getcount()) / 20][chainelevator[j]->GetX2() / 20 + i] = 18;
					if (map[((chainelevator[j]->GetY2() + (int)chainelevator[j]->Getcount()) / 20) + 1][chainelevator[j]->GetX2() / 20 + i] == 18) map[((chainelevator[j]->GetY2() + (int)chainelevator[j]->Getcount()) / 20) + 1][chainelevator[j]->GetX2() / 20 + i] = 0;
				}
				chainelevator[j]->ShowBitmap();
			}
			////////////////////////////////////////////////////////////
		}
			///////////////////電梯2重量大於電梯1////////////////////////////////
		else if(chainelevator[j]->GetFall2() > chainelevator[j]->GetFall())
		{
			//////////////////電梯1上升、電梯2下降/////////////////////////////////////////
			if ((int)chainelevator[j]->Getcount()<=0)
			{
				chainelevator[j]->Up(4);
				for (int i = 0; i < 3; i++)
				{
					map[chainelevator[j]->GetY() / 20][chainelevator[j]->GetX() / 20 + i] = 18;
					if (map[(chainelevator[j]->GetY() / 20) + 1][chainelevator[j]->GetX() / 20 + i] == 18) map[(chainelevator[j]->GetY() / 20) + 1][chainelevator[j]->GetX() / 20 + i] = 0;
					map[(chainelevator[j]->GetY2() + (int)chainelevator[j]->Getcount()) / 20 - 1][chainelevator[j]->GetX2() / 20 + i] = 0;
					map[((chainelevator[j]->GetY2() + (int)chainelevator[j]->Getcount()) / 20)][chainelevator[j]->GetX2() / 20 + i] = 18;
				}
				chainelevator[j]->ShowBitmap();
			}
			////////////////////////////////////////////////////////////////////////////////
		}
	}

	bool CgameMap::gameover(man player)
	{
		////////////////////////抓取角色位置/////////////////////////////////////
		int i = ((player.GetX2() + player.GetX1()) / 2) / 20;
		int j = (player.GetY2()) / 20;
		///////////////若是進到與自身角色不同的陷阱或是毒素死亡/////////////////
		switch (map[j][i]) {
		case 4:
			if (player.Getcharacteristic() == "ice") return true;
			else return false;
			break;
		case 5:
			if (player.Getcharacteristic() == "fire") return true;
			else return false;
			break;
		case 6:
			return true;
			break;
		default:
			break;
			ASSERT(0);
		}
		switch (map[j-1][i]){
		case 4:
			if (player.Getcharacteristic() == "ice") return true;
			else return false;
			break;
		case 5:
			if (player.Getcharacteristic() == "fire") return true;
			else return false;
			break;
		case 6:
			return true;
			break;
		default:
			return false;
			ASSERT(0);
		
		}
		///////////////////////////////////////////////////////
	}
	bool CgameMap::isgem(man player)
	{
		/////////////////抓取角色四個點///////////////////////
		int manY1 = player.GetY1();
		int manY2 = player.GetY2();
		int manX1 = player.GetX1();
		int manX2 = player.GetX2();
		int image[4][2] = { 0 };
		image[0][0] = manX1 + 5;
		image[0][1] = manY1 + 5;
		image[1][0] = manX2 - 5;
		image[1][1] = manY1 + 5;
		image[2][0] = manX1;
		image[2][1] = manY2 - 1;
		image[3][0] = manX2;
		image[3][1] = manY2 - 1;
		////////////判斷是否碰撞到適合的寶石//////////////////
		switch (map[image[0][1] / 20][image[0][0] / 20]) {
		case 7:
			if (player.Getcharacteristic() == "fire")
			{
				map[image[0][1] / 20][image[0][0] / 20] = 0;
				return true;
			}
			else break;
		case 8:
			if (player.Getcharacteristic() == "ice")
			{
				map[image[0][1] / 20][image[0][0] / 20] = 0;
				return true;
			}
			else break;
		default:
			break;
		}
		switch (map[image[1][1] / 20][image[1][0] / 20]) {
		case 7:
			if (player.Getcharacteristic() == "fire")
			{
				map[image[1][1] / 20][image[1][0] / 20] = 0;
				return true;
			}
			else break;
		case 8:
			if (player.Getcharacteristic() == "ice")
			{
				map[image[1][1] / 20][image[1][0] / 20] = 0;
				return true;
			}
			else break;
		default:
			break;
		}
		switch (map[image[2][1] / 20][image[2][0] / 20]) {
		case 7:
			if (player.Getcharacteristic() == "fire")
			{
				map[image[2][1] / 20][image[2][0] / 20] = 0;
				return true;
			}
			else break;
		case 8:
			if (player.Getcharacteristic() == "ice")
			{
				map[image[2][1] / 20][image[2][0] / 20] = 0;
				return true;
			}
			else break;
		default:
			break;
		}
		switch (map[image[3][1] / 20][image[3][0] / 20]) {
		case 7:
			if (player.Getcharacteristic() == "fire")
			{
				map[image[3][1] / 20][image[3][0] / 20] = 0;
				return true;
			}
			else return false;
		case 8:
			if (player.Getcharacteristic() == "ice")
			{
				map[image[3][1] / 20][image[3][0] / 20] = 0;
				return true;
			}
			else return false;
		default:
			return false;
			ASSERT(0);
		}
		/////////////////////////////////////////////////////
	}

	bool CgameMap::Clearance(man player)
	{
		////////////////////角色位置////////////////////////
		int i = ((player.GetX2() + player.GetX1()) / 2) / 20;
		int j = (player.GetY2() - 20) / 20;
		//////////////////判斷關卡是否完成//////////////////
		switch (map[j][i]) {
		case 9:
			return fdoor.Clearance(player, firegemnum);
			break;
		case 10:
			return idoor.Clearance(player, icegemnum);
		default:
			if (fdoor.GetDoor()->GetCurrentBitmapNumber()!= 0 && player.Getcharacteristic() == "fire")
			{
				fdoor.GetDoor()->Movetonum(fdoor.GetDoor()->GetCurrentBitmapNumber() - 1);
			}
			if (idoor.GetDoor()->GetCurrentBitmapNumber() != 0 && player.Getcharacteristic() == "ice")
			{
				idoor.GetDoor()->Movetonum(idoor.GetDoor()->GetCurrentBitmapNumber() - 1);
			}
			return false;
			ASSERT(0);
		}
		///////////////////////////////////////////////////
	}

	int CgameMap::OnSlade(man* player, int i, int j)
	{ 
		int temp = 0;
		/////////////////將角色位置根據移動的X座標上升Y座標增加///////////////////////////
		player->SetXY(player->GetX1() - 1, player->GetY1());
		temp = (player->GetX2()-(i+1)*20);
		if (player->GetX2() >= i * 20&& player->GetMovingRight()) player->SetXY(player->GetX1() + player->Getstep(), ((j - 1) * 20) - temp);
		player->SetXY(player->GetX1(), ((j-1) *20) - temp);
		return player->GetY2();
		/////////////////////////////////////////////////////////////////////////////
	}

	int CgameMap::OnRSlade(man * player, int i, int j)
	{
		int temp = 0;
		//////////////將X座標上升Y下降//////////////////////////////////////////////
		player->SetXY(player->GetX1() + 1, player->GetY1());
		temp = 20-(player->GetX1()-((i-1)*20));
		if (player->GetX1()<= (i) * 20 && player->GetMovingLeft())
		{
			player->SetXY(player->GetX1()-player->Getstep(), ((j - 1) * 20) -temp);
		}
		else player->SetXY(player->GetX1(), ((j - 1) * 20) - temp);
		return player->GetY2();
		////////////////////////////////////////////////////////////////////////////
	}

	void CgameMap::makewall(bool flag)
	{
		int wallx=0, wally=0,count=0;
		////////////////////////////////找到牆的位子////////////////////////////////
		for (int i = 0; i < 24; i++) for (int j = 0; j < 32; j++) if (map[i][j] == 16) { wallx = j, wally = i; count++; }
		////////////////////////////////若是按鈕被觸發長出一個牆////////////////////
		if (!flag) 
		{ 
			if (map[wally + 1][wallx] == 0 && delaycount-- <= 0)
			{
				delaycount = 5;
				map[wally + 1][wallx] = 16;
			}
		}
		///////////////////////////若是沒被觸發牆縮回去/////////////////////////////
		else
		{
			if (count > 1 && delaycount-- <= 0)
			{
				delaycount = 5;
				map[wally][wallx] = 0;
			}
		}
		///////////////////////////////////////////////////////////////////////////
	}
	void CgameMap::LeverOn(bool flag)
	{
		int wallx = 0, wally = 0, count = 0;
		//////////////////////////////////找到牆下降的位置/////////////////////////
		for (int i = 0; i < 24; i++) for (int j = 0; j < 32; j++) if (map[i][j] == 21) { if (count == 0) { wallx = j, wally = i; } count++;}
		//////////////////////////////////若是拉桿被觸發///////////////////////////
		if (!flag)
		{
		///////////////////////////////////將牆壁下降//////////////////////////////
			if (map[wally - 1][wallx] == 0 && delaycount-- <= 0)
			{
				delaycount = 5;
				map[wally - 1][wallx] = 21;
			}
		}
		else
		{
		///////////////////////////////////牆壁上升///////////////////////////////
			if (count > 1 && delaycount-- <= 0)
			{
				delaycount = 5;
				map[wally][wallx] = 0;
			}
		}
	}
	void CgameMap::deleteObject()
	{
		/////////////////////////////////刪除物件/////////////////////////////////
		for (int i = 0; i < buttonnum; i++) delete button[i];
		for (int i = 0; i < buttonnum; i++) button.erase(button.begin());
		for (int i = 0; i < elevatornum; i++) delete _elevator[i];
		for (int i = 0; i < elevatornum; i++) _elevator.erase(_elevator.begin());
		for (int i = 0; i < stonenum; i++) delete stone[i];
		for (int i = 0; i < stonenum; i++) stone.erase(stone.begin());
		for (int i = 0; i < fallwallnum; i++) delete fallwall[i];
		for (int i = 0; i < fallwallnum; i++) fallwall.erase(fallwall.begin());
		for (int i = 0; i < redbuttonnum; i++) delete Redbutton[i];
		for (int i = 0; i < redbuttonnum; i++) Redbutton.erase(Redbutton.begin());
		for (int i = 0; i < risingnum; i++) delete rising[i];
		for (int i = 0; i < risingnum; i++) rising.erase(rising.begin());
		for (int i = 0; i < chainelevatornum; i++) delete chainelevator[i];
		for (int i = 0; i < chainelevatornum; i++) chainelevator.erase(chainelevator.begin());
		for (int i = 0; i < Levernum; i++) delete Lever[i];
		for (int i = 0; i < Levernum; i++) Lever.erase(Lever.begin());
		////////////////////////////////////////////////////////////////////////////
	}
	
}