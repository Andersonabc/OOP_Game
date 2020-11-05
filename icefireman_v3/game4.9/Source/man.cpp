#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "man.h"

namespace game_framework {
	man::man()
	{
		Initialize();
	}
	int man::GetX1()
	{
		return x;
	}

	int man::GetY1()
	{
		return y;
	}

	int man::GetX2()
	{
		return x + 31 ;
	}

	int man::GetY2()
	{
		return y + 39;
	}

	int man::Getvelocity()
	{
		return velocity;
	}
	int man::Getfloor()
	{
		return floor;
	}
	bool man::Onfloor()
	{
		if (animation.GetCurrentBitmapNumber() < 14 ||animation.GetCurrentBitmapNumber()>22) return true;
		else return false;
	}
	string man::Getcharacteristic()
	{
		return characteristic;
	}
	bool man::GetRising()
	{
		return rising;
	}
	bool man::Getfly()
	{
		return fly;
	}
	void man::Addgem()
	{
		gem++;
	}
	int man::getgem()
	{
		return gem;
	}
	int man::Getstep()
	{
		return step_size;
	}

	void man::Initialize()
	{
	}
	void man::LoadBitmap()
	{
	}
	void man::LoadBitmap(int i)
	{
	}
	void man::OnMove()
	{
		animation.SetDelayCount(1);
		////////////////////////////////////////////////////�P�_�O�_����////////////////////////////////////////////////
		if (isMovingLeft || isMovingRight || isMovingUp)
		{
			////////////////////////////////////////////////////����////////////////////////////////////////////////
			if (isMovingLeft)
			{
				if (left == 1)
					x -= step_size;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 14))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
			}
			////////////////////////////////////////////////////�k��////////////////////////////////////////////////
			else if (isMovingRight)
			{
				if (right == 1)
					x += step_size;
				if (!(animation.GetCurrentBitmapNumber() > 0 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(1);
				}
				else
				{
					animation.OnMove();
				}
			}
			////////////////////////////////////////////////////���D////////////////////////////////////////////////
			if ((isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39))
			{
				rising = true;
				velocity = initial_velocity;
				if (!(animation.GetCurrentBitmapNumber() > 14 && animation.GetCurrentBitmapNumber() < 18))
				{
					animation.Movetonum(15);
				}
			}
		}
		///////////////////////////////////////////////////////���b��a//////////////////////////////////////
		else
			animation.Reset();
		jump();
	}

	void man::OnMove(man *player)
	{
		//--------�l�u---------
		if (isShooting && isAttacked == 2)
		{
			shoot.push_back(new bullet(this->GetX1(), this->GetY1(),direction,characteristic));
			isShooting = false;
		}
		if (shoot.size() != 0) {
			for (int count = 0; count < this->GetBullet(); count++) {
				shoot[count]->Move();
				if (shoot[count]->Getbullet().GetCurrentBitmapNumber()==12 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 23 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 35 || shoot[count]->Getbullet().GetCurrentBitmapNumber() == 47) {
					delete shoot[count];
					shoot.erase(shoot.begin()+count);
				}
				else if (((shoot[count]->GetX2()>player->GetX1()&&shoot[count]->Getdirection()==1 && shoot[count]->GetX1() < player->GetX2()) ||  (shoot[count]->GetX1() < player->GetX2()&&shoot[count]->Getdirection() == 0&& shoot[count]->GetX2() > player->GetX1()))&&((player->GetY1()<shoot[count]->GetY2() && player->GetY1()>shoot[count]->GetY1())||(player->GetY2()>shoot[count]->GetY1()&&player->GetY2()<shoot[count]->GetY2()))) {
					player->SetAttacked(shoot[count]->Getdirection());
					delete shoot[count];
					shoot.erase(shoot.begin() + count);
				}
			}
		}
		///////////////////////////////////////
		animation.SetDelayCount(1);
		///////////////////�P�_�ϥνľW�ޯ�////////////////////////
		if (isRush)
		{
			////////////////////////////�Y�O�ľW�٦��ɶ�///////////////////////
			if (direction == 0 && RushTime>0)
			{
				///////////////////////////////�V���Ĩ�///////////////////////
				if (left == 1)
					x -= step_size*2;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 13))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
				direction = 0;
				////////////////////////////////////////////////////////////////
			}
			else if (direction == 1 && RushTime > 0)
			{
				///////////////////////////////�V�k�Ĩ�///////////////////////
				if (right == 1)
					x += step_size * 2;
				if (!(animation.GetCurrentBitmapNumber() > 1 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(2);
				}
				else
				{
					animation.OnMove();
				}
				direction = 1;
				////////////////////////////////////////////////////////////////
			}
			if (RushTime-- <= 0)
				isRush = false;//�����Ĩ�
		}
		///////////////////����////////////////////////
		else if (isMagic && isAttacked == 2)
		{
			animation.SetDelayCount(5);
			if(magic<100) magic++;//�W�[�]�O
			//////////////////////////�����Ϥ�/////////////////////////////////////////////
			if (direction == 0)
			{
				if(animation.GetCurrentBitmapNumber()!=40) animation.Movetonum(40);
				else animation.Movetonum(41);
			}
			else if (direction == 1)
			{
				if (animation.GetCurrentBitmapNumber() != 38) animation.Movetonum(38);
				else animation.Movetonum(39);
			}
			//////////////////////////////////////////////////////////////////////////
		}
		///////////////////���m////////////////////////
		else if (isMovingDown && isAttacked == 2)
		{
			if (direction == 0) animation.Movetonum(37);
			else if (direction == 1) animation.Movetonum(36);
		}
		///////////////////����//////////////////////
		else if ((isMovingLeft || isMovingRight || isMovingUp) && isAttacked ==2)
		{
			/////////////////////////////////����//////////////////////////////////
			if (isMovingLeft)
			{
				if (left == 1)
					x -= step_size;
				if (!(animation.GetCurrentBitmapNumber() > 7 && animation.GetCurrentBitmapNumber() < 13))
				{
					animation.Movetonum(8);
				}
				else
				{
					animation.OnMove();
				}
				direction = 0;
			}
			////////////////////////////////////////////////////�k��////////////////////////////////////////////////
			else if (isMovingRight)
			{
				if (right == 1)
					x += step_size;
				if (!(animation.GetCurrentBitmapNumber() > 1 && animation.GetCurrentBitmapNumber() < 7))
				{
					animation.Movetonum(2);
				}
				else
				{
					animation.OnMove();
				}
				direction = 1;
			}
			////////////////////////////////////////////////////���D////////////////////////////////////////////////
			if ((isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39) || (isMovingUp && isTwojump))
			{
				if (!(isMovingUp && rising == false && velocity == initial_velocity && y >= floor - 39))
					isTwojump = false;
				rising = true;
				isMovingUp = false;
				velocity = initial_velocity;

			}
			//////////////////////////////////////////////////////////////////////////////////////////////////
		}
		else if (isAttack && isAttacked==2)
		{
		//////////////////////////////////////////////////////�����R���B��⥼���m�ί}��///////////////////////////////////////////////
			if (x + 59 > player->GetX1() && player->GetX1() > x && direction ==1 && player->GetY1() < y + 10 && player->GetY1() > y - 10 &&(player->GetAnimation().GetCurrentBitmapNumber()!=37 || player->GetDamage() > 5))
			{
				if (!(animation.GetCurrentBitmapNumber() > 27 && animation.GetCurrentBitmapNumber() <= 31)) animation.Movetonum(28);
				else if (animation.GetCurrentBitmapNumber() == 31)
				{
					player->SetAttacked(1);//�N���]�w���Q����
					isAttack = false;
					CAudio::Instance()->Play(9, false);
				}
				else animation.OnMove();
				
			}
			else if (x-20 < player->GetX2() && player->GetX2() < GetX2() && direction == 0 && player->GetY1() < y + 10 && player->GetY1() > y - 10 && direction == 0 && (player->GetAnimation().GetCurrentBitmapNumber() != 36 || player->GetDamage()>5))
			{
				if (!(animation.GetCurrentBitmapNumber() > 31 && animation.GetCurrentBitmapNumber() <= 35)) animation.Movetonum(32);
				else if (animation.GetCurrentBitmapNumber() == 35)
				{
					player->SetAttacked(0);
					isAttack = false;
					CAudio::Instance()->Play(9, false);
				}
				else animation.OnMove();
			}
			///////////////////////////////////////////////�������R��//////////////////////////////////////////////////
			else if (direction == 1)
			{
				if (animation.GetCurrentBitmapNumber() < 28)animation.Movetonum(28);
				else if (animation.GetCurrentBitmapNumber() == 31) isAttack = false;
				else animation.OnMove();
			}
			else if (direction == 0)
			{
				if (animation.GetCurrentBitmapNumber() < 32)animation.Movetonum(32);
				else if (animation.GetCurrentBitmapNumber() == 35) isAttack = false;
				else animation.OnMove();
			}
			/////////////////////////////////////////////////�������m���A�W�[�}����/////////////////////////////////////////
			if (((x + 59 > player->GetX1() && player->GetX1() > x && direction == 1 && player->GetY1() < y + 10 && player->GetY1() > y - 10 )||(x - 20 < player->GetX2() && player->GetX2() < GetX2() && player->GetY1() < y + 10 && player->GetY1() > y - 10)) && player->GetAnimation().GetCurrentBitmapNumber() - 36 == direction &&(animation.GetCurrentBitmapNumber() == 31|| animation.GetCurrentBitmapNumber() == 35))
				player->AddDamage();
		}
		/////////////////////////////////////////�Q����////////////////////////////////////////////////////////
		else if (isAttacked!=2)
		{
		/////////////////////////////�V�Ჾ��////////////////////////////////
			if (isAttacked == 0 && left == 1)
				x -= step_size/2;
			else if (isAttacked == 1 && right == 1)
				x += step_size/2;
			if (times == 24)
			{
				times = 0;
				isAttacked = 2;
			}
			else
			{
				if (times % 4 == 0 && player->GetX1() >= x && left == 1)
				{
					if (animation.GetCurrentBitmapNumber() >= 16 && animation.GetCurrentBitmapNumber() < 21)
						animation.OnMove();
					else
						animation.Movetonum(16);
				}
				else if (times % 4 == 0 && player->GetX1() < x && left == 1)
				{
					if (animation.GetCurrentBitmapNumber() >= 21 && animation.GetCurrentBitmapNumber() < 27)
						animation.OnMove();
					else
						animation.Movetonum(21);
				}
				times++;
			}
			//////////////////////////////////////////////////////////////////
		}
		else
		/////////////////////////////////���b��a////////////////////////////////////////////
			if(direction ==1 ) animation.Reset();
			else if(direction == 0) animation.Movetonum(1);
		//////////////////////////////////////////////////////////////////
		jump(1);
	}

	void man::setfloor(int _floor)
	{
		floor = _floor;
	}

	void man::sethead(bool flag)
	{
		head = flag;
	}

	void man::setleft(int flag)
	{
		left = flag;
	}

	void man::setright(int flag)
	{
		right = flag;
	}

	void man::jump()
	{
		if (rising)  			// �W�ɪ��A
		{
			if(velocity == initial_velocity) 	jumpsound();
			if (velocity > 0)
			{
				if (head)
					y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				if (fly && velocity < initial_velocity) velocity++;
				else velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else
			{
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
			if (animation.GetCurrentBitmapNumber() > 14 && animation.GetCurrentBitmapNumber() < 18)
				animation.OnMove();
			else
			{
				animation.Movetonum(15);
			}
		}
		else  				// �U�����A
		{
			if (y < floor - 39)  // ��y�y���٨S�I��a�O
			{
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				if (fly) velocity-=2;
				else velocity++;		// �����O�v�T�A�U�����U���t�׼W�[

				if (animation.GetCurrentBitmapNumber() > 18 && animation.GetCurrentBitmapNumber() < 22)
					animation.OnMove();
				else
					animation.Movetonum(19);
			}
			else
			{
				y = floor - 39;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}
		}
	}
	void man::jump(int i)
	{
		if (rising)  			// �W�ɪ��A
		{
			if (velocity == initial_velocity) 	jumpsound();
			if (velocity > 0)
			{
				if (head)
					y -= velocity;	// ��t�� > 0�ɡAy�b�W��(����velocity���I�Avelocity����쬰 �I/��)
				if (fly && velocity < initial_velocity) velocity++;
				else velocity--;		// �����O�v�T�A�U�����W�ɳt�׭��C
			}
			else
			{
				rising = false; // ��t�� <= 0�A�W�ɲפ�A�U���אּ�U��
				velocity = 1;	// �U������t(velocity)��1
			}
			if (direction == 1)
				animation.Movetonum(14);
			if (direction == 0)
				animation.Movetonum(15);
		}
		else  				// �U�����A
		{
			if (y < floor - 39)  // ��y�y���٨S�I��a�O
			{
				y += velocity;	// y�b�U��(����velocity���I�Avelocity����쬰 �I/��)
				if (fly) velocity -= 2;
				else velocity++;		// �����O�v�T�A�U�����U���t�׼W�[0
				if (direction == 1)
					animation.Movetonum(14);
				if (direction == 0)
					animation.Movetonum(15);
			}
			else
			{
				y = floor - 39;  // ��y�y�ЧC��a�O�A�󥿬��a�O�W
				velocity = initial_velocity; // ���]�W�ɪ�l�t��
			}

		}
	}
	void man::SetMovingDown(bool flag)
	{
		isMovingDown = flag;
		if (flag) combo.push_back('D');//�NCOMBO���O��iCOMBO��
		if (flag) damage = 0;
	}

	void man::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
		if (flag) combo.push_back('L');//�NCOMBO���O��iCOMBO��
	}

	void man::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
		if (flag) combo.push_back('R');//�NCOMBO���O��iCOMBO��
	}

	void man::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
		if(flag) combo.push_back('U');//�NCOMBO���O��iCOMBO��
	}
	bool man::SetShooting()
	{
		if((int)combo.size() ==3 && combo[2]=='A' && (combo[1] == 'R' || combo[1] == 'L') && combo[0] == 'D' &&magic>=20)//�Y�O���U���e�𪺫��O
		{
			isShooting = true;//�g�X�l�u
			magic -= 20;
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//�M��COMBO��
			return true;
		}
		return false;
	}

	void man::SetRush()
	{
		if ((int)combo.size() > 3) combo.erase(combo.begin());//�M��COMBO��
		if ((int)combo.size() == 3 && combo[2] == 'A' && ((combo[1] == 'R' && combo[0] == 'R') || (combo[1] == 'L'&& combo[0] == 'L'))&&magic>=20)//�Y�O���U�e�e�𪺫��O
		{
			isRush = true;//�V�e�Ĩ�
			RushTime = 10;
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//�M��COMBO��
			magic -= 20;
		}
		if (combodelay-- <= 0)
		{
			for (int i = 0; i < (int)combo.size(); i++) combo.erase(combo.begin());//�M��COMBO��
		}
		
	}

	void man::SetisMagic(bool flag)
	{
		isMagic = flag;
	}

	CAnimation man::GetAnimation()
	{
		return animation;
	}

	void man::SetTwojump(bool flag)
	{
		isTwojump = flag;
	}

	void man::SetAttack(bool flag)
	{
		isAttack = flag;
		if (flag) combo.push_back('A');//�NCOMBO���O��iCOMBO��
	}

	void man::SetAttacked(int flag)
	{
		isAttacked = flag;
	}
	bool man::Getshooting()
	{
		return isShooting;
	}
	bool man::GetRush()
	{
		return isRush;
	}
	bool man::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool man::GetMovingRight()
	{
		return isMovingRight;
	}

	bool man::Getleft()
	{
		return left;
	}

	bool man::Getright()
	{
		return right;
	}

	void man::SetXY(int nx, int ny)
	{
		x = nx;
		y = ny;
	}

	void man::Setfly(bool flag)
	{
		fly = flag;
		if (fly && velocity <= 1) rising = true;
	}

	void man::jumpsound()
	{
		CAudio::Instance()->Play(3,false);
	}

	void man::DeleteBullet()
	{
		///////////////////////////////////////�R���l�u//////////////////////////////
		int shootnum = (int)shoot.size();
		for (int i=0; i < shootnum; i++)
		{
			delete shoot[0];
			shoot.erase(shoot.begin());
		}
		////////////////////////////////////////////////////////////////////////////
	}

	int man::GetBullet()
	{
		return shoot.size();
	}

	int man::GetDamage()
	{
		return damage;
	}

	void man::AddDamage()
	{
		damage +=1;
	}

	void man::SetCombodelay()
	{
		combodelay = 5;
	}

	void man::OnShow()
	{
		///////////////////////////////////////////////////////////////////��ܨ���/////////////////////////////////////////////////
		if   (animation.GetCurrentBitmapNumber() > 0 && animation.GetCurrentBitmapNumber() < 8) animation.SetTopLeft(x-19, y);//�ץ��y��
		else if (animation.GetCurrentBitmapNumber() > 18 && animation.GetCurrentBitmapNumber() < 23) animation.SetTopLeft(x, y-12);//�ץ��y��
		else 	animation.SetTopLeft(x, y);
		animation.OnShow();
	}
	void man::OnShow(int i)
	{
		///////////////////////////////////////////////////////////////////��ܨ���/////////////////////////////////////////////////
		animation.SetTopLeft(x, y);
		animation.OnShow();
		///////////////////////////////////////////////////////////////////��ܤl�u/////////////////////////////////////////////////
		if (shoot.size() != 0) {
			for (int count = 0; count < this->GetBullet(); count++) {
				shoot[count]->OnShow();
			}
		}
		///////////////////////////////////////////////////////////////////��ܯ�q��/////////////////////////////////////////////////
		MagicBar.SetTopLeft(MagicX, MagicY);
		MagicBar.ShowBitmap();
		for (int i = 0; i < 100 - magic; i++)
		{
			if (characteristic == "ice")
			{
				Black.SetTopLeft(MagicX + (2 * i), MagicY + 1);
				Black.ShowBitmap();
			}
			if (characteristic == "fire")
			{
				Black.SetTopLeft(MagicX +200 - (2 * i), MagicY + 1);
				Black.ShowBitmap();
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
}