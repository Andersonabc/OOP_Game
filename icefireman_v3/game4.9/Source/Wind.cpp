#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include <cstdlib>
#include <ctime>
#include "Wind.h"
namespace game_framework {
	Wind::Wind()
	{
		Init();
	}
	void Wind::LoadBitmap()
	{
		/////////////////////////Ū���Ϥ�/////////////////////////////////
		image1.LoadBitmap(WIND, RGB(255, 255, 255));
		image2.LoadBitmap(Wind0, RGB(255, 255, 255));
		image3.LoadBitmap(WIND2, RGB(255, 255, 255));
		image1.SetTopLeft(290, 20);
		image2.SetTopLeft(290, 20);
		image3.SetTopLeft(290, 20);
		//////////////////////////////////////////////////////////////////
	}
	void Wind::Init()
	{
		unsigned seed;
		seed = (unsigned)time(NULL); // ���o�üƺؤl
		srand(seed); // �H�ɶ��ǦC��üƺؤl
		times = 0;
	}
	void Wind::Count()
	{
		times++;
	}
	void Wind::onMove(man *player)
	{
		if (times % 900 == 0)
			direction = rand() % 3 - 1;//�T�ح��V��@��
		player->SetXY(player->GetX1() + direction, player->GetY1());
	}

	void Wind::OnShow()
	{
		if (direction == -1) image1.ShowBitmap();
		if (direction == 0) image2.ShowBitmap();
		if (direction == 1) image3.ShowBitmap();
	}

}