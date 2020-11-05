#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Kakashi.h"

namespace game_framework {
	Kakashi::Kakashi()
	{

	}
	void Kakashi::Init()
	{
		AddPic();
		instructions.Reset();
		instructions.SetDelayCount(5);
		instructions.SetTopLeft(0, 55);
		victory.Reset();
		victory.SetDelayCount(5);
		victory.SetTopLeft(0, 55);
		victory2.Reset();
		victory2.SetDelayCount(5);
		victory2.SetTopLeft(0, 55);
		failed.Reset();
		failed.SetDelayCount(5);
		failed.SetTopLeft(0, 55);
		final.Reset();
		final.SetDelayCount(5);
		final.SetTopLeft(0, 55);
		isEnd = false;
		Done = false;
		isFinish = false;
		section = 1;
		nowVicFilm = 0;
		nowVic2Film = 0;
		nowFilm = 0;
	}

	void Kakashi::OnShow(int _section)
	{
		////////////////////////////判斷目前要顯示的對話場景/////////////////////////
		if (_section == 1) {
			if (Done == false)instructions.OnShow();
			if (instructions.GetCurrentBitmapNumber() < film[nowFilm] - 1 && isFinish == false && Done == false && isEnd == false) instructions.Movetonum(instructions.GetCurrentBitmapNumber() + 1);
			if (instructions.GetCurrentBitmapNumber() == film[nowFilm] - 1 && isFinish == false && Done == false && isEnd == false)isEnd = true;
			if (instructions.IsFinalBitmap())isFinish = true;
		}
		else if (_section == 2) {
			if (Done == false)victory.OnShow();
			if (victory.GetCurrentBitmapNumber() < vicfilm[nowVicFilm] - 1 && isFinish == false && Done == false && isEnd == false) victory.Movetonum(victory.GetCurrentBitmapNumber() + 1);
			if (victory.GetCurrentBitmapNumber() == vicfilm[nowVicFilm] - 1 && isFinish == false && Done == false && isEnd == false)isEnd = true;
			if (victory.IsFinalBitmap())isFinish = true;
		}
		else if (_section == 3) {
			if (Done == false)failed.OnShow();
			if (failed.GetCurrentBitmapNumber() < 10 && isFinish == false && Done == false && isEnd == false) failed.Movetonum(failed.GetCurrentBitmapNumber() + 1);
			if (failed.GetCurrentBitmapNumber() == 10 && isFinish == false && Done == false && isEnd == false)isEnd = true;
			if (failed.IsFinalBitmap())isFinish = true;
		}
		else if (_section == 4) {
			if (Done == false)victory2.OnShow();
			if (victory2.GetCurrentBitmapNumber() < vic2film[nowVic2Film] - 1 && isFinish == false && Done == false && isEnd== false) victory2.Movetonum(victory2.GetCurrentBitmapNumber() + 1);
			if (victory2.GetCurrentBitmapNumber() == vic2film[nowVic2Film] - 1 && isFinish == false && Done == false && isEnd == false)isEnd = true;
			if (victory2.IsFinalBitmap())isFinish = true;
		}
		else if (_section == 5) {
			if (Done == false)final.OnShow();
			if (final.GetCurrentBitmapNumber() < 10 && isFinish == false && Done == false && isEnd == false) final.Movetonum(final.GetCurrentBitmapNumber() + 1);
			if (final.GetCurrentBitmapNumber() == 10 && isFinish == false && Done == false && isEnd == false)isEnd = true;
			if (final.IsFinalBitmap())isFinish = true;
		}
		/////////////////////////////////////////////////////////////////////////////
	}


	void Kakashi::ChangeFilm(int _film)				//切換對話框
	{
		if(_film < 7)nowFilm = _film;
		isEnd = false;
	}

	int Kakashi::GetFilm()
	{
		return nowFilm;
	}
	void Kakashi::ChangeVicFilm(int _film)			//切換對話框
	{
		if(_film<2)nowVicFilm = _film;
		isEnd = false;
	}
	void Kakashi::ChangeVic2Film(int _film)			//切換對話框
	{
		if (_film < 2)nowVic2Film = _film;
		isEnd = false;
	}
	int Kakashi::GetVicFilm()
	{
		return nowVicFilm;
	}
	int Kakashi::GetVic2Film()
	{
		return nowVic2Film;
	}
	int Kakashi::GetSection()
	{
		return section;
	}
	void Kakashi::ChangeSection(int _section)		//切換場景
	{
		isEnd = false;
		Done = false;
		isFinish = false;
		victory.Reset();
		victory2.Reset();
		instructions.Reset();
		failed.Reset();
		final.Reset();
		nowVicFilm = 0;
		nowVic2Film = 0;
		nowFilm = 0;
		section = _section;
	}
	void Kakashi::SetDone(bool _flag) 
	{
		Done = _flag;
	}

	void Kakashi::AddPic()
	{
		instructions.AddBitmap(KAKASHI001, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI002, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI003, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI004, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI005, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI006, RGB(255, 242, 0)); 
		instructions.AddBitmap(KAKASHI007, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI008, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI009, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI010, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI011, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI012, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI013, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI014, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI015, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI016, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI017, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI018, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI101, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI102, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI103, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI104, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI105, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI106, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI107, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI108, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI109, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI110, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI111, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI201, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI202, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI203, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI204, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI205, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI206, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI207, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI208, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI209, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI210, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI211, RGB(255, 242, 0)); 
		instructions.AddBitmap(KAKASHI212, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI213, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI214, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI301, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI302, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI303, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI304, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI305, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI306, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI307, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI308, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI309, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI310, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI311, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI312, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI313, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI314, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI315, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI316, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI317, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI401, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI402, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI403, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI404, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI405, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI406, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI407, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI408, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI409, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI410, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI411, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI412, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI413, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI414, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI415, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI501, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI502, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI503, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI504, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI505, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI506, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI507, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI508, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI509, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI510, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI601, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI602, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI603, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI604, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI605, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI606, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI607, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI608, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI609, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI610, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI611, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI612, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI613, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI614, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI615, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI616, RGB(255, 242, 0));
		instructions.AddBitmap(KAKASHI617, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI701, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI702, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI703, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI704, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI705, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI706, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI707, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI708, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI709, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI710, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI711, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI712, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI713, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI801, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI802, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI803, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI804, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI805, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI806, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI807, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI808, RGB(255, 242, 0));
		victory.AddBitmap(KAKASHI809, RGB(255, 242, 0));
		victory2.AddBitmap(vic_01, RGB(255, 242, 0));
		victory2.AddBitmap(vic_02, RGB(255, 242, 0));
		victory2.AddBitmap(vic_03, RGB(255, 242, 0));
		victory2.AddBitmap(vic_04, RGB(255, 242, 0));
		victory2.AddBitmap(vic_05, RGB(255, 242, 0));
		victory2.AddBitmap(vic_06, RGB(255, 242, 0));
		victory2.AddBitmap(vic_07, RGB(255, 242, 0));
		victory2.AddBitmap(vic_08, RGB(255, 242, 0));
		victory2.AddBitmap(vic_09, RGB(255, 242, 0));
		victory2.AddBitmap(vic_10, RGB(255, 242, 0));
		victory2.AddBitmap(vic_11, RGB(255, 242, 0));
		victory2.AddBitmap(vic_12, RGB(255, 242, 0));
		victory2.AddBitmap(vic_13, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_01, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_02, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_03, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_04, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_05, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_06, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_07, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_08, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_09, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_10, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_11, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_12, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_13, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_14, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_15, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_16, RGB(255, 242, 0));
		victory2.AddBitmap(vic2_17, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI901, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI902, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI903, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI904, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI905, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI906, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI907, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI908, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI909, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI910, RGB(255, 242, 0));
		failed.AddBitmap(KAKASHI911, RGB(255, 242, 0));
		final.AddBitmap(final01, RGB(255, 242, 0));
		final.AddBitmap(final02, RGB(255, 242, 0));
		final.AddBitmap(final03, RGB(255, 242, 0));
		final.AddBitmap(final04, RGB(255, 242, 0));
		final.AddBitmap(final05, RGB(255, 242, 0));
		final.AddBitmap(final06, RGB(255, 242, 0));
		final.AddBitmap(final07, RGB(255, 242, 0)); 
		final.AddBitmap(final08, RGB(255, 242, 0));
		final.AddBitmap(final09, RGB(255, 242, 0));
		final.AddBitmap(final10, RGB(255, 242, 0));
	}

	bool Kakashi::GetEnd()
	{
		return isEnd;
	}

	bool Kakashi::IsFinish()
	{
		return isFinish;
	}

	bool Kakashi::IsDone()
	{
		return Done;
	}
}