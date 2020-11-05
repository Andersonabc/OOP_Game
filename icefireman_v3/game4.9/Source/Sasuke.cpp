#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Sasuke.h"


namespace game_framework {
	Sasuke::Sasuke()
	{
		unsigned seed;
		seed = (unsigned)time(NULL); // 取得時
		srand(seed); // 以時間序列當亂數種子
	}
	Sasuke::~Sasuke()
	{

	}
	int Sasuke::GetX1()
	{
		///////////////////////////////////////////////////////圖片x座標修正///////////////////////////////////////////////
		if (direction == 0) return x;
		if (Skillsuccess) return x + (24 - SkillsuccessMovie.Width()) * 2;
		if (isSkill && direction == 1) return x + (24 - SkillMovie.Width()) * 2;
		return x + (24 - animation.Width())*2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Sasuke::GetY1()
	{
		///////////////////////////////////////////////////////圖片y座標修正///////////////////////////////////////////////
		if (Skillsuccess) return y + (36 - SkillsuccessMovie.Height()) * 2;
		if(isSkill) return y + (36 - SkillMovie.Height()) * 2;
		return y + (36 - animation.Height()) * 2;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	int Sasuke::GetX2()
	{
		if(Skillsuccess) return GetX1() + SkillsuccessMovie.Width() * 2;
		if(isSkill) return GetX1() + SkillMovie.Width() * 2;
		return GetX1() + animation.Width()*2;
	}
	int Sasuke::GetY2()
	{
		if(Skillsuccess) return GetY1() + SkillsuccessMovie.Height() * 2;
		if (isSkill) return GetY1() + SkillMovie.Height() * 2;
		return GetY1() + animation.Height()*2;
	}
	int Sasuke::Gety()
	{
		return y;
	}
	int Sasuke::Getx()
	{
		return x;
	}
	void Sasuke::Initialize()
	{
		////////////////////////////////////////////////////////初始化///////////////////////////////////////////////////////////////////////
		floor = 460;
		const int X_POS = 100;
		const int Y_POS = 460 - 39;
		const int INITIAL_VELOCITY = 18;
		initial_velocity = INITIAL_VELOCITY;
		velocity = initial_velocity;
		x = X_POS;
		y = Y_POS;
		Skillsuccess = Movieflag= isSkill = isSkillFail = isMolding = isDie = isShooting = isAttacked = rising = isMovingLeft = isMovingRight = isMovingUp = false;
		step_size = 10;
		Move = true;
		skill3direction=attacknum = direction = magic = 0;
		Blood = 128;
		Diedelay = 30;
		delay = 2;
		chakura = 64;
		chakuradelay= skill1delay =8;
		skill3delay = 4;
		animation.Reset();
		SkillsuccessMovie.Reset();
		SkillMovie.Reset();
		damage = 1;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::LoadBitmap()
	{
		////////////////////////////////////////////////////////////讀取圖片//////////////////////////////////////////
		animation.AddBitmap(SASUKESTAND1, RGB(73, 176, 255));	//0
		animation.AddBitmap(SASUKESTAND1, RGB(73, 176, 255));	//1
		animation.AddBitmap(SASUKESTAND1, RGB(73, 176, 255));	//2
		animation.AddBitmap(SASUKESTAND2, RGB(73, 176, 255));	//3
		animation.AddBitmap(SASUKESTAND2, RGB(73, 176, 255));	//4
		animation.AddBitmap(SASUKESTAND2, RGB(73, 176, 255));	//5
		animation.AddBitmap(SASUKESTAND3, RGB(73, 176, 255));	//6
		animation.AddBitmap(SASUKESTAND3, RGB(73, 176, 255));	//7
		animation.AddBitmap(SASUKESTAND3, RGB(73, 176, 255));	//8
		animation.AddBitmap(SASUKESTAND4, RGB(73, 176, 255));	//9
		animation.AddBitmap(SASUKESTAND4, RGB(73, 176, 255));	//10
		animation.AddBitmap(SASUKESTAND4, RGB(73, 176, 255));	//11
		animation.AddBitmap(SASUKERUN1, RGB(73, 176, 255));		//12
		animation.AddBitmap(SASUKERUN1, RGB(73, 176, 255));		//13
		animation.AddBitmap(SASUKERUN1, RGB(73, 176, 255));		//14
		animation.AddBitmap(SASUKERUN2, RGB(73, 176, 255));		//15
		animation.AddBitmap(SASUKERUN2, RGB(73, 176, 255));		//16
		animation.AddBitmap(SASUKERUN2, RGB(73, 176, 255));		//17
		animation.AddBitmap(SASUKEJUMP1, RGB(73, 176, 255));	//18
		animation.AddBitmap(SASUKEJUMP2, RGB(73, 176, 255));	//19
		animation.AddBitmap(SASUKEJUMPKICK1, RGB(73, 176, 255));//20
		animation.AddBitmap(SASUKEJUMPKICK1, RGB(73, 176, 255));//21
		animation.AddBitmap(SASUKEJUMPKICK1, RGB(73, 176, 255));//22
		animation.AddBitmap(SASUKEJUMPKICK2, RGB(73, 176, 255));//23
		animation.AddBitmap(SASUKEJUMPKICK2, RGB(73, 176, 255));//24
		animation.AddBitmap(SASUKEJUMPKICK2, RGB(73, 176, 255));//25
		animation.AddBitmap(SASUKEJUMPKICK3, RGB(73, 176, 255));//26
		animation.AddBitmap(SASUKEJUMPKICK3, RGB(73, 176, 255));//27
		animation.AddBitmap(SASUKEJUMPKICK3, RGB(73, 176, 255));//28
		animation.AddBitmap(SASUKEDOWN1, RGB(73, 176, 255));	//29
		animation.AddBitmap(SASUKEDOWN1, RGB(73, 176, 255));	//30
		animation.AddBitmap(SASUKEDOWN1, RGB(73, 176, 255));	//31
		animation.AddBitmap(SASUKECOMBO1, RGB(73, 176, 255));	//32
		animation.AddBitmap(SASUKECOMBO1, RGB(73, 176, 255));	//33
		animation.AddBitmap(SASUKECOMBO1, RGB(73, 176, 255));	//34
		animation.AddBitmap(SASUKECOMBO2, RGB(73, 176, 255));	//35
		animation.AddBitmap(SASUKECOMBO2, RGB(73, 176, 255));	//36
		animation.AddBitmap(SASUKECOMBO2, RGB(73, 176, 255));	//37
		animation.AddBitmap(SASUKECOMBO3, RGB(73, 176, 255));	//38
		animation.AddBitmap(SASUKECOMBO3, RGB(73, 176, 255));	//39
		animation.AddBitmap(SASUKECOMBO3, RGB(73, 176, 255));	//40
		animation.AddBitmap(SASUKECOMBO4, RGB(73, 176, 255));	//41
		animation.AddBitmap(SASUKECOMBO4, RGB(73, 176, 255));	//42
		animation.AddBitmap(SASUKECOMBO4, RGB(73, 176, 255));	//43
		animation.AddBitmap(SASUKECOMBO5, RGB(73, 176, 255));	//44
		animation.AddBitmap(SASUKECOMBO5, RGB(73, 176, 255));	//45
		animation.AddBitmap(SASUKECOMBO5, RGB(73, 176, 255));	//46
		animation.AddBitmap(SASUKECOMBO6, RGB(73, 176, 255));	//47
		animation.AddBitmap(SASUKECOMBO6, RGB(73, 176, 255));	//48
		animation.AddBitmap(SASUKECOMBO6, RGB(73, 176, 255));	//49
		animation.AddBitmap(SASUKECOMBO7, RGB(73, 176, 255));	//50
		animation.AddBitmap(SASUKECOMBO7, RGB(73, 176, 255));	//51
		animation.AddBitmap(SASUKECOMBO7, RGB(73, 176, 255));	//52
		animation.AddBitmap(SASUKECOMBO8, RGB(73, 176, 255));	//53
		animation.AddBitmap(SASUKECOMBO8, RGB(73, 176, 255));	//54
		animation.AddBitmap(SASUKECOMBO8, RGB(73, 176, 255));	//55
		animation.AddBitmap(SASUKECOMBO9, RGB(73, 176, 255));	//56
		animation.AddBitmap(SASUKECOMBO9, RGB(73, 176, 255));	//57
		animation.AddBitmap(SASUKECOMBO9, RGB(73, 176, 255));	//58
		animation.AddBitmap(SASUKECOMBO10, RGB(73, 176, 255));	//59
		animation.AddBitmap(SASUKECOMBO10, RGB(73, 176, 255));	//60
		animation.AddBitmap(SASUKECOMBO10, RGB(73, 176, 255));	//61
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//62
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//63
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//64
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//65
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//66
		animation.AddBitmap(SASUKEDIE1, RGB(73, 176, 255));		//67
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//68
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//69
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//70
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//71
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//72
		animation.AddBitmap(SASUKEDIE2, RGB(73, 176, 255));		//73
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//74
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//75
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//76
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//77
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//78
		animation.AddBitmap(SASUKEDIE3, RGB(73, 176, 255));		//79
		animation.AddBitmap(SASUKEDIE4, RGB(73, 176, 255));		//80
		animation.AddBitmap(SASUKEDIE4, RGB(73, 176, 255));		//81
		animation.AddBitmap(SASUKEDIE5, RGB(73, 176, 255));		//82
		animation.AddBitmap(SASUKEDIE5, RGB(73, 176, 255));		//83
		animation.AddBitmap(SASUKEDIE6, RGB(73, 176, 255));		//84
		animation.AddBitmap(SASUKEDIE6, RGB(73, 176, 255));		//85
		animation.AddBitmap(SASUKEDIE7, RGB(73, 176, 255));		//86
		animation.AddBitmap(SASUKEDIE7, RGB(73, 176, 255));		//87
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//88
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//89
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//90
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//91
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//92
		animation.AddBitmap(SASUKEDIE8, RGB(73, 176, 255));		//93
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//94
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//95
		animation.AddBitmap(transe, RGB(255, 255, 255));		//96
		animation.AddBitmap(transe, RGB(255, 255, 255));		//97
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//98
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//99
		animation.AddBitmap(transe, RGB(255, 255, 255));		//100
		animation.AddBitmap(transe, RGB(255, 255, 255));		//101
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//102
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//103
		animation.AddBitmap(transe, RGB(255, 255, 255));		//104
		animation.AddBitmap(transe, RGB(255, 255, 255));		//105
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//106
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//107
		animation.AddBitmap(transe, RGB(255, 255, 255));		//108
		animation.AddBitmap(transe, RGB(255, 255, 255));		//109
		animation.AddBitmap(SASUKEDIE9, RGB(73, 176, 255));		//110
		animation.AddBitmap(SASUKEHURT1, RGB(73, 176, 255));	//111
		animation.AddBitmap(SASUKEHURT1, RGB(73, 176, 255));	//112
		animation.AddBitmap(SASUKEHURT1, RGB(73, 176, 255));	//113
		animation.AddBitmap(SASUKEMOLDING1, RGB(73, 176, 255));	//114
		animation.AddBitmap(SASUKEMOLDING1, RGB(73, 176, 255));	//115
		animation.AddBitmap(SASUKEMOLDING1, RGB(73, 176, 255));	//116
		animation.AddBitmap(SASUKEMOLDING2, RGB(73, 176, 255));	//117
		animation.AddBitmap(SASUKEMOLDING2, RGB(73, 176, 255));	//118
		animation.AddBitmap(SASUKEMOLDING2, RGB(73, 176, 255));	//119
		animation.AddBitmap(SASUKEMOLDING3, RGB(73, 176, 255));	//120
		animation.AddBitmap(SASUKEMOLDING3, RGB(73, 176, 255));	//121
		animation.AddBitmap(SASUKEMOLDING3, RGB(73, 176, 255));	//122
		animation.AddBitmap(SASUKEMOLDING4, RGB(73, 176, 255));	//123
		animation.AddBitmap(SASUKEMOLDING4, RGB(73, 176, 255));	//124
		animation.AddBitmap(SASUKEMOLDING4, RGB(73, 176, 255));	//125
		animation.AddBitmap(SASUKEMOLDING4, RGB(73, 176, 255));	//126
		animation.AddBitmap(SASUKEMOLDING5, RGB(73, 176, 255));	//127
		animation.AddBitmap(SASUKEMOLDING5, RGB(73, 176, 255));	//128
		animation.AddBitmap(SASUKEMOLDING5, RGB(73, 176, 255));	//129
		animation.AddBitmap(SASUKEMOLDING5, RGB(73, 176, 255));	//130
		animation.AddBitmap(SASUKESKILLFAIL1, RGB(73, 176, 255));//131
		animation.AddBitmap(SASUKESKILLFAIL1, RGB(73, 176, 255));//132
		animation.AddBitmap(SASUKESKILLFAIL1, RGB(73, 176, 255));//133
		animation.AddBitmap(SASUKESKILLFAIL2, RGB(73, 176, 255));//134
		animation.AddBitmap(SASUKESKILLFAIL2, RGB(73, 176, 255));//135
		animation.AddBitmap(SASUKESKILLFAIL2, RGB(73, 176, 255));//136
		animation.AddBitmap(SASUKESKILLFAIL3, RGB(73, 176, 255));//137
		animation.AddBitmap(SASUKESKILLFAIL3, RGB(73, 176, 255));//138
		animation.AddBitmap(SASUKESKILLFAIL3, RGB(73, 176, 255));//139
		animation.AddBitmap(SASUKESTAND5, RGB(73, 176, 255));	//140
		animation.AddBitmap(SASUKESTAND5, RGB(73, 176, 255));	//141
		animation.AddBitmap(SASUKESTAND5, RGB(73, 176, 255));	//142
		animation.AddBitmap(SASUKESTAND6, RGB(73, 176, 255));	//143
		animation.AddBitmap(SASUKESTAND6, RGB(73, 176, 255));	//144
		animation.AddBitmap(SASUKESTAND6, RGB(73, 176, 255));	//145
		animation.AddBitmap(SASUKESTAND7, RGB(73, 176, 255));	//146
		animation.AddBitmap(SASUKESTAND7, RGB(73, 176, 255));	//147
		animation.AddBitmap(SASUKESTAND7, RGB(73, 176, 255));	//148
		animation.AddBitmap(SASUKESTAND8, RGB(73, 176, 255));	//149
		animation.AddBitmap(SASUKESTAND8, RGB(73, 176, 255));	//150
		animation.AddBitmap(SASUKESTAND8, RGB(73, 176, 255));	//151
		animation.AddBitmap(SASUKERUN3, RGB(73, 176, 255));		//152
		animation.AddBitmap(SASUKERUN3, RGB(73, 176, 255));		//153
		animation.AddBitmap(SASUKERUN3, RGB(73, 176, 255));		//154
		animation.AddBitmap(SASUKERUN4, RGB(73, 176, 255));		//155
		animation.AddBitmap(SASUKERUN4, RGB(73, 176, 255));		//156
		animation.AddBitmap(SASUKERUN4, RGB(73, 176, 255));		//157
		animation.AddBitmap(SASUKEJUMP3, RGB(73, 176, 255));	//158
		animation.AddBitmap(SASUKEJUMP4, RGB(73, 176, 255));	//159
		animation.AddBitmap(SASUKEJUMPKICK4, RGB(73, 176, 255));//160
		animation.AddBitmap(SASUKEJUMPKICK4, RGB(73, 176, 255));//161
		animation.AddBitmap(SASUKEJUMPKICK4, RGB(73, 176, 255));//162
		animation.AddBitmap(SASUKEJUMPKICK5, RGB(73, 176, 255));//163
		animation.AddBitmap(SASUKEJUMPKICK5, RGB(73, 176, 255));//164
		animation.AddBitmap(SASUKEJUMPKICK5, RGB(73, 176, 255));//165
		animation.AddBitmap(SASUKEJUMPKICK6, RGB(73, 176, 255));//166
		animation.AddBitmap(SASUKEJUMPKICK6, RGB(73, 176, 255));//167
		animation.AddBitmap(SASUKEJUMPKICK6, RGB(73, 176, 255));//168
		animation.AddBitmap(SASUKEDOWN2, RGB(73, 176, 255));	//169
		animation.AddBitmap(SASUKEDOWN2, RGB(73, 176, 255));	//170
		animation.AddBitmap(SASUKEDOWN2, RGB(73, 176, 255));	//171
		animation.AddBitmap(SASUKECOMBO11, RGB(73, 176, 255));	//172
		animation.AddBitmap(SASUKECOMBO11, RGB(73, 176, 255));	//173
		animation.AddBitmap(SASUKECOMBO11, RGB(73, 176, 255));	//174
		animation.AddBitmap(SASUKECOMBO12, RGB(73, 176, 255));	//175
		animation.AddBitmap(SASUKECOMBO12, RGB(73, 176, 255));	//176
		animation.AddBitmap(SASUKECOMBO12, RGB(73, 176, 255));	//177
		animation.AddBitmap(SASUKECOMBO13, RGB(73, 176, 255));	//178
		animation.AddBitmap(SASUKECOMBO13, RGB(73, 176, 255));	//179
		animation.AddBitmap(SASUKECOMBO13, RGB(73, 176, 255));	//180
		animation.AddBitmap(SASUKECOMBO14, RGB(73, 176, 255));	//181
		animation.AddBitmap(SASUKECOMBO14, RGB(73, 176, 255));	//182
		animation.AddBitmap(SASUKECOMBO14, RGB(73, 176, 255));	//183
		animation.AddBitmap(SASUKECOMBO15, RGB(73, 176, 255));	//184
		animation.AddBitmap(SASUKECOMBO15, RGB(73, 176, 255));	//185
		animation.AddBitmap(SASUKECOMBO15, RGB(73, 176, 255));	//186
		animation.AddBitmap(SASUKECOMBO16, RGB(73, 176, 255));	//187
		animation.AddBitmap(SASUKECOMBO16, RGB(73, 176, 255));	//188
		animation.AddBitmap(SASUKECOMBO16, RGB(73, 176, 255));	//189
		animation.AddBitmap(SASUKECOMBO17, RGB(73, 176, 255));	//190
		animation.AddBitmap(SASUKECOMBO17, RGB(73, 176, 255));	//191
		animation.AddBitmap(SASUKECOMBO17, RGB(73, 176, 255));	//192
		animation.AddBitmap(SASUKECOMBO18, RGB(73, 176, 255));	//193
		animation.AddBitmap(SASUKECOMBO18, RGB(73, 176, 255));	//194
		animation.AddBitmap(SASUKECOMBO18, RGB(73, 176, 255));	//195
		animation.AddBitmap(SASUKECOMBO19, RGB(73, 176, 255));	//196
		animation.AddBitmap(SASUKECOMBO19, RGB(73, 176, 255));	//197
		animation.AddBitmap(SASUKECOMBO19, RGB(73, 176, 255));	//198
		animation.AddBitmap(SASUKECOMBO20, RGB(73, 176, 255));	//199
		animation.AddBitmap(SASUKECOMBO20, RGB(73, 176, 255));	//200
		animation.AddBitmap(SASUKECOMBO20, RGB(73, 176, 255));	//201
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//202
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//203
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//204
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//205
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//206
		animation.AddBitmap(SASUKEDIE10, RGB(73, 176, 255));	//207
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//208
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//209
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//210
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//211
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//212
		animation.AddBitmap(SASUKEDIE11, RGB(73, 176, 255));	//213
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//214
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//215
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//216
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//217
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//218
		animation.AddBitmap(SASUKEDIE12, RGB(73, 176, 255));	//219
		animation.AddBitmap(SASUKEDIE13, RGB(73, 176, 255));	//220
		animation.AddBitmap(SASUKEDIE13, RGB(73, 176, 255));	//221
		animation.AddBitmap(SASUKEDIE14, RGB(73, 176, 255));	//222
		animation.AddBitmap(SASUKEDIE14, RGB(73, 176, 255));	//223
		animation.AddBitmap(SASUKEDIE15, RGB(73, 176, 255));	//224
		animation.AddBitmap(SASUKEDIE15, RGB(73, 176, 255));	//225
		animation.AddBitmap(SASUKEDIE16, RGB(73, 176, 255));	//226
		animation.AddBitmap(SASUKEDIE16, RGB(73, 176, 255));	//227
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//228
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//229
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//230
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//231
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//232
		animation.AddBitmap(SASUKEDIE17, RGB(73, 176, 255));	//233
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//234
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//235
		animation.AddBitmap(transe, RGB(255, 255, 255));		//236
		animation.AddBitmap(transe, RGB(255, 255, 255));		//237
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//238
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//239
		animation.AddBitmap(transe, RGB(255, 255, 255));		//240
		animation.AddBitmap(transe, RGB(255, 255, 255));		//241
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//242
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//243
		animation.AddBitmap(transe, RGB(255, 255, 255));		//244
		animation.AddBitmap(transe, RGB(255, 255, 255));		//245
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//246
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//247
		animation.AddBitmap(transe, RGB(255, 255, 255));		//248
		animation.AddBitmap(transe, RGB(255, 255, 255));		//249
		animation.AddBitmap(SASUKEDIE18, RGB(73, 176, 255));	//250
		animation.AddBitmap(SASUKEHURT2, RGB(73, 176, 255));	//251
		animation.AddBitmap(SASUKEHURT2, RGB(73, 176, 255));	//252
		animation.AddBitmap(SASUKEHURT2, RGB(73, 176, 255));	//253
		animation.AddBitmap(SASUKEMOLDING7, RGB(73, 176, 255));	//254
		animation.AddBitmap(SASUKEMOLDING7, RGB(73, 176, 255));	//255
		animation.AddBitmap(SASUKEMOLDING8, RGB(73, 176, 255));	//256
		animation.AddBitmap(SASUKEMOLDING8, RGB(73, 176, 255));	//257
		animation.AddBitmap(SASUKEMOLDING8, RGB(73, 176, 255));	//258
		animation.AddBitmap(SASUKEMOLDING8, RGB(73, 176, 255));	//259
		animation.AddBitmap(SASUKEMOLDING9, RGB(73, 176, 255));	//260
		animation.AddBitmap(SASUKEMOLDING9, RGB(73, 176, 255));	//261
		animation.AddBitmap(SASUKEMOLDING9, RGB(73, 176, 255));	//262
		animation.AddBitmap(SASUKEMOLDING10, RGB(73, 176, 255));//263
		animation.AddBitmap(SASUKEMOLDING10, RGB(73, 176, 255));//264
		animation.AddBitmap(SASUKEMOLDING10, RGB(73, 176, 255));//265
		animation.AddBitmap(SASUKEMOLDING10, RGB(73, 176, 255));//266
		animation.AddBitmap(SASUKEMOLDING11, RGB(73, 176, 255));//267
		animation.AddBitmap(SASUKEMOLDING11, RGB(73, 176, 255));//268
		animation.AddBitmap(SASUKEMOLDING11, RGB(73, 176, 255));//269
		animation.AddBitmap(SASUKEMOLDING11, RGB(73, 176, 255));//270
		animation.AddBitmap(SASUKESKILLFAIL4, RGB(73, 176, 255));//271
		animation.AddBitmap(SASUKESKILLFAIL4, RGB(73, 176, 255));//272
		animation.AddBitmap(SASUKESKILLFAIL4, RGB(73, 176, 255));//273
		animation.AddBitmap(SASUKESKILLFAIL5, RGB(73, 176, 255));//274
		animation.AddBitmap(SASUKESKILLFAIL5, RGB(73, 176, 255));//275
		animation.AddBitmap(SASUKESKILLFAIL5, RGB(73, 176, 255));//276
		animation.AddBitmap(SASUKESKILLFAIL6, RGB(73, 176, 255));//277
		animation.AddBitmap(SASUKESKILLFAIL6, RGB(73, 176, 255));//278
		animation.AddBitmap(SASUKESKILLFAIL6, RGB(73, 176, 255));//279
		SkillMovie.AddBitmap(SASUKEHOUSENKA1, RGB(73, 176, 255));//0
		SkillMovie.AddBitmap(SASUKEHOUSENKA1, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA1, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA2, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA2, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA2, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA3, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA3, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA3, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA4, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA4, RGB(73, 176, 255));//10
		SkillMovie.AddBitmap(SASUKEHOUSENKA4, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA5, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA5, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA5, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA6, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA6, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA6, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA7, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA7, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA7, RGB(73, 176, 255));//20
		SkillMovie.AddBitmap(SASUKEHOUSENKA8, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA8, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA8, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA9, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA9, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA9, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA10, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA10, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA10, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA11, RGB(73, 176, 255));//30
		SkillMovie.AddBitmap(SASUKEHOUSENKA11, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA11, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA12, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA12, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA12, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA13, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA13, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA13, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA14, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA14, RGB(73, 176, 255));//40
		SkillMovie.AddBitmap(SASUKEHOUSENKA14, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA15, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA15, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA15, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA16, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA16, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA16, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA17, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA17, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA17, RGB(73, 176, 255));//50
		SkillMovie.AddBitmap(SASUKEHOUSENKA18, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA18, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA18, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA19, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA19, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA19, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA20, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA20, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA20, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA21, RGB(73, 176, 255));//60
		SkillMovie.AddBitmap(SASUKEHOUSENKA21, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA21, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA22, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA22, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA22, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA23, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA23, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA23, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA24, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA24, RGB(73, 176, 255));//70
		SkillMovie.AddBitmap(SASUKEHOUSENKA24, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA25, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA25, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA25, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA26, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA26, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA26, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA27, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA27, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKEHOUSENKA27, RGB(73, 176, 255));//80
		SkillMovie.AddBitmap(SASUKEHOUSENKA28, RGB(73, 176, 255));//1
		SkillMovie.AddBitmap(SASUKEHOUSENKA28, RGB(73, 176, 255));//2
		SkillMovie.AddBitmap(SASUKEHOUSENKA28, RGB(73, 176, 255));//3
		SkillMovie.AddBitmap(SASUKEHOUSENKA29, RGB(73, 176, 255));//4
		SkillMovie.AddBitmap(SASUKEHOUSENKA29, RGB(73, 176, 255));//5
		SkillMovie.AddBitmap(SASUKEHOUSENKA29, RGB(73, 176, 255));//6
		SkillMovie.AddBitmap(SASUKEHOUSENKA30, RGB(73, 176, 255));//7
		SkillMovie.AddBitmap(SASUKEHOUSENKA30, RGB(73, 176, 255));//8
		SkillMovie.AddBitmap(SASUKEHOUSENKA30, RGB(73, 176, 255));//9
		SkillMovie.AddBitmap(SASUKESKILL1, RGB(73, 176, 255));	  //90
		SkillMovie.AddBitmap(SASUKESKILL1, RGB(73, 176, 255));	  //1
		SkillMovie.AddBitmap(SASUKESKILL1, RGB(73, 176, 255));	  //2
		SkillMovie.AddBitmap(SASUKESKILL2, RGB(73, 176, 255));	  //3
		SkillMovie.AddBitmap(SASUKESKILL2, RGB(73, 176, 255));	  //4
		SkillMovie.AddBitmap(SASUKESKILL2, RGB(73, 176, 255));	  //5
		SkillMovie.AddBitmap(SASUKESKILL3, RGB(73, 176, 255));	  //6
		SkillMovie.AddBitmap(SASUKESKILL3, RGB(73, 176, 255));	  //7
		SkillMovie.AddBitmap(SASUKESKILL3, RGB(73, 176, 255));	  //8
		SkillMovie.AddBitmap(SASUKESKILL4, RGB(73, 176, 255));	  //9
		SkillMovie.AddBitmap(SASUKESKILL4, RGB(73, 176, 255));	  //100
		SkillMovie.AddBitmap(SASUKESKILL4, RGB(73, 176, 255));	  //1
		SkillMovie.AddBitmap(SASUKESKILL5, RGB(73, 176, 255));	  //2
		SkillMovie.AddBitmap(SASUKESKILL5, RGB(73, 176, 255));	  //3
		SkillMovie.AddBitmap(SASUKESKILL5, RGB(73, 176, 255));	  //4
		SkillMovie.AddBitmap(SASUKESKILL6, RGB(73, 176, 255));	  //5
		SkillMovie.AddBitmap(SASUKESKILL6, RGB(73, 176, 255));	  //6
		SkillMovie.AddBitmap(SASUKESKILL6, RGB(73, 176, 255));	  //7
		SkillMovie.AddBitmap(SASUKESKILL7, RGB(73, 176, 255));	  //8
		SkillMovie.AddBitmap(SASUKESKILL7, RGB(73, 176, 255));	  //9
		SkillMovie.AddBitmap(SASUKESKILL7, RGB(73, 176, 255));	  //110
		SkillMovie.AddBitmap(SASUKESKILL8, RGB(73, 176, 255));	  //1
		SkillMovie.AddBitmap(SASUKESKILL8, RGB(73, 176, 255));	  //2
		SkillMovie.AddBitmap(SASUKESKILL8, RGB(73, 176, 255));	  //3
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //4
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //5
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //6
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //7
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //8
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //9
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //120
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //1
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //2
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //3
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //4
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //5
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //6
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //7
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //8
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //9
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //130
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //1
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //2
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //3
		SkillMovie.AddBitmap(SASUKERENDAN1, RGB(73, 176, 255));	  //4
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //5
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //6
		SkillMovie.AddBitmap(SASUKERENDAN2, RGB(73, 176, 255));	  //7
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //8
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //9
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //140
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //1
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //2
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //3
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //4
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //5
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //6
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //7
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //8
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //9
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //150
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //1
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //2
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //3
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //4
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //5
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //6
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //7
		SkillMovie.AddBitmap(SASUKERENDAN22, RGB(73, 176, 255));  //8
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //9
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //160
		SkillMovie.AddBitmap(SASUKERENDAN23, RGB(73, 176, 255));  //1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN3, RGB(73, 176, 255));	//0
		SkillsuccessMovie.AddBitmap(SASUKERENDAN4, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN5, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN5, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN5, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN6, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN6, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN6, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN7, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN7, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN7, RGB(73, 176, 255));	//10
		SkillsuccessMovie.AddBitmap(SASUKERENDAN8, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN8, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN8, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN9, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN9, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN9, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN10, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN10, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN10, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN11, RGB(73, 176, 255));	//20
		SkillsuccessMovie.AddBitmap(SASUKERENDAN11, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN11, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN12, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN12, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN12, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN13, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN13, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN13, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN14, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN14, RGB(73, 176, 255));	//30
		SkillsuccessMovie.AddBitmap(SASUKERENDAN14, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN15, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN15, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN15, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN16, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN16, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN16, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN17, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN17, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN17, RGB(73, 176, 255));	//40
		SkillsuccessMovie.AddBitmap(SASUKERENDAN18, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN18, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN18, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN19, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN19, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN19, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN20, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN20, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN20, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN21, RGB(73, 176, 255));	//50
		SkillsuccessMovie.AddBitmap(SASUKERENDAN21, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN21, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN24, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN25, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN26, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN26, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN26, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN27, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN27, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN27, RGB(73, 176, 255));	//60
		SkillsuccessMovie.AddBitmap(SASUKERENDAN28, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN28, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN28, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN29, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN29, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN29, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN30, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN30, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN30, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN31, RGB(73, 176, 255));	//70
		SkillsuccessMovie.AddBitmap(SASUKERENDAN31, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN31, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN32, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN32, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN32, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN33, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN33, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN33, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN34, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN34, RGB(73, 176, 255));	//80
		SkillsuccessMovie.AddBitmap(SASUKERENDAN34, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN35, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN35, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN35, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN36, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN36, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN36, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN37, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN37, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN37, RGB(73, 176, 255));	//90
		SkillsuccessMovie.AddBitmap(SASUKERENDAN38, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN38, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN38, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN39, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN39, RGB(73, 176, 255));	//5
		SkillsuccessMovie.AddBitmap(SASUKERENDAN39, RGB(73, 176, 255));	//6
		SkillsuccessMovie.AddBitmap(SASUKERENDAN40, RGB(73, 176, 255));	//7
		SkillsuccessMovie.AddBitmap(SASUKERENDAN40, RGB(73, 176, 255));	//8
		SkillsuccessMovie.AddBitmap(SASUKERENDAN40, RGB(73, 176, 255));	//9
		SkillsuccessMovie.AddBitmap(SASUKERENDAN41, RGB(73, 176, 255));	//100
		SkillsuccessMovie.AddBitmap(SASUKERENDAN41, RGB(73, 176, 255));	//1
		SkillsuccessMovie.AddBitmap(SASUKERENDAN41, RGB(73, 176, 255));	//2
		SkillsuccessMovie.AddBitmap(SASUKERENDAN42, RGB(73, 176, 255));	//3
		SkillsuccessMovie.AddBitmap(SASUKERENDAN42, RGB(73, 176, 255));	//4
		SkillsuccessMovie.AddBitmap(SASUKERENDAN42, RGB(73, 176, 255));	//5
		Movie.LoadBitmap(SasukeSkillUI, RGB(73, 176, 255));		 
		Movie2.LoadBitmap(SasukeSkill2UI, RGB(73, 176, 255));	  
		SkillMovie.SetDelayCount(1);						
		SkillMovie.Reset();		
		SkillsuccessMovie.SetDelayCount(2);
		SkillsuccessMovie.Reset();
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::OnMove()
	{
		animation.SetDelayCount(1);
		//////////////被攻擊/////////////////////////
		if (isAttacked && !isDie && !(animation.GetCurrentBitmapNumber() >= 123 + direction * 140 && animation.GetCurrentBitmapNumber() <= 130 + direction * 140) && !isSkill) Attacked();
		else if (Move && !isDie)
		{
			////////////////////////////////////////使用技能、攻擊、集氣、移動、跳躍、恢復查克拉/////////////////////////////////////////////////////////
			if (animation.GetCurrentBitmapNumber() >= 29 + direction * 140 && animation.GetCurrentBitmapNumber() <= 31 + direction * 140) { jump(); attacknum = 0;  }
			else if (isSkillFail) SetSkill();
			else if (attacknum > 0) Attack();
			else if (isMolding && ((animation.GetCurrentBitmapNumber() >= 0 + direction * 140 && animation.GetCurrentBitmapNumber() < 11 + direction * 140) || (animation.GetCurrentBitmapNumber() >= 114 + direction * 140 && animation.GetCurrentBitmapNumber() <= 130 + direction * 140)))Molding();
			else if (isMovingLeft || isMovingRight || isMovingUp) MovePlayer();
			else Stand();
			if(!isSkill)jump();
			if (chakura <= 64 && chakuradelay-- <= 0 && !isSkillFail) { chakura++; chakuradelay = 16; }
			///////////////////////////////////////////////////////////////////////////////////////////////
		}
		///////////////////////////////倒地///////////////////////////////////////////
		if (isDie) Die();
		//////////////////////////////投擲物移動/////////////////////////////////////
		ThrowMove();
	}

	void Sasuke::setfloor(int _floor)
	{
		floor = _floor;	//////////////////////////設定地板
	}
	void Sasuke::jump()
	{
		////////////////////////////////////////////跳躍///////////////////////////////////////////
			if (rising)  			// 上升狀態
			{
				if (velocity > 0)
				{
					y -= velocity;	// 當速度 > 0時，y軸上升(移動velocity個點，velocity的單位為 點/次)
					velocity -= 2;
				}
				else
				{
					rising = false; // 當速度 <= 0，上升終止，下次改為下降
					velocity = 1;	// 下降的初速(velocity)為1
				}
			}
			else  				// 下降狀態
			{
				if (GetY2() < floor)  // 當y座標還沒碰到地板
				{
					y += velocity;	// y軸下降(移動velocity個點，velocity的單位為 點/次)
					velocity += 2;
					if (attacknum == 0) animation.Movetonum(18 + direction * 140);
				}
				else
				{
					y = floor - 72;  // 當y座標低於地板，更正為地板上
					velocity = initial_velocity; // 重設上升初始速度
					if (isMovingUp && attacknum == 0)
					{
						////////////////////////跳躍結束動作/////////////////////////////
						if (!(animation.GetCurrentBitmapNumber() >= 29 + direction * 140 && animation.GetCurrentBitmapNumber() <= 31 + direction * 140))animation.Movetonum(29 + direction * 140);
						else animation.OnMove();
						if (animation.GetCurrentBitmapNumber() == 32 + direction * 140)
						{
							isMovingUp = false;
						}
						//////////////////////////////////////////////////////
					}
				}
			}
	}

	void Sasuke::OnShow()
	{
		/////////////////////////////顯示/////////////////////////////////////
		if (!isSkill)
		{
			animation.SetTopLeft(GetX1(), GetY1());
			animation.OnShow(2);
		}
		else if(!Skillsuccess)
		{
			SkillMovie.SetTopLeft(GetX1(), GetY1());
			if(SkillMovie.GetCurrentBitmapNumber()>=15+direction * 45 && SkillMovie.GetCurrentBitmapNumber() <= 44+direction * 45) SkillMovie.SetTopLeft(GetX1(), GetY1()+14);
			SkillMovie.OnShow(2);
		}
		if (Skillsuccess) SkillsuccessMovie.OnShow(2);
		for (int count = 0; count < (int)Fireball.size(); count++) Fireball[count]->OnShow();
		for (int count = 0; count < (int)shurikan.size(); count++) shurikan[count]->OnShow();
		////////////////////////////////////////////////////////////////////////
	}


	void Sasuke::SetMovingLeft(bool flag)
	{
		isMovingLeft = flag;
	}

	void Sasuke::SetMovingRight(bool flag)
	{
		isMovingRight = flag;
	}

	void Sasuke::SetMovingUp(bool flag)
	{
		isMovingUp = flag;
	}

	void Sasuke::SetAttacked(int flag)
	{
		isAttacked = flag;
	}

	void Sasuke::SetDie()
	{
		isDie = true;
		CAudio::Instance()->Play(29);
		velocity = 18;
		damage = 1;
	}

	void Sasuke::SetDie(int Sub)
	{
		isDie = true;
		CAudio::Instance()->Play(29);
		velocity = 18;
		damage = Sub;
	}

	void Sasuke::SetMove(bool flag)
	{
		Move = flag;
	}

	int Sasuke::GetChakura() 
	{
		return chakura;
	}
	void Sasuke::ChangeChakura(int _chakura)
	{
		chakura = _chakura;
		if (chakura <= 0) chakura = 0;
	}
	void Sasuke::SetDirection(int _direction)
	{
		direction = _direction;
	}
	void Sasuke::SetFireballDelete(int flag)
	{
		delete Fireball[flag];
		Fireball.erase(Fireball.begin() + flag);
	}
	void Sasuke::SetShurikanDelete(int flag)
	{
		delete shurikan[flag];
		shurikan.erase(shurikan.begin() + flag);
	}
	bool Sasuke::GetSkillsuccess()
	{
		return Skillsuccess;
	}
	void Sasuke::SetSkillsuccess()
	{
		Skillsuccess = true;
	}
	CAnimation * Sasuke::GetSkillsuccessMovie()
	{
		return &SkillsuccessMovie;
	}
	void Sasuke::RunSkillsuccessMovie()
	{
		///////////////////////////////////////////////////技能成功動畫//////////////////////////////////////////////////////
		if (SkillsuccessMovie.GetCurrentBitmapNumber() == 52 + direction * 53)
		{
			isSkill = false;
			Skillsuccess = false;
			SkillsuccessMovie.Reset();
			Movieflag = false;
			isSkillFail = false;
			isAttacked = false;
			magic = 0;
		}
		else SkillsuccessMovie.OnMove();
		if(SkillsuccessMovie.GetCurrentBitmapNumber() == 17 + direction * 53) CAudio::Instance()->Play(27);
		SkillsuccessMovie.SetTopLeft(GetX1(), GetY1());
		if(SkillsuccessMovie.GetCurrentBitmapNumber() >= 14 + direction * 53 && SkillsuccessMovie.GetCurrentBitmapNumber() < 32 + direction * 53) y -= 5;
		if(SkillsuccessMovie.GetCurrentBitmapNumber() > 32 + direction * 53) y += 5;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Deleteobject()
	{
		///////////////////////////////////////////刪除子彈///////////////////////////////////////////////////////////////////
		int num = (int)Fireball.size();
		for (int i = 0; i < num; i++)
		{
			delete Fireball[0];
			Fireball.erase(Fireball.begin());
		}
		num = (int)shurikan.size();
		for (int i = 0; i < num; i++)
		{
			delete shurikan[0];
			shurikan.erase(shurikan.begin());
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Attack()
	{
		/////////////////////////////////////////////////攻擊動畫//////////////////////////////////////////////////////////////
		if (GetY2() >= floor && !(animation.GetCurrentBitmapNumber() >= 20 + direction * 140 && animation.GetCurrentBitmapNumber() < 28 + direction * 140))
		{
			if (!(animation.GetCurrentBitmapNumber() >= 32 + direction * 140 && animation.GetCurrentBitmapNumber() < 61 + direction * 140))
			{
				if (rand() % 2 == 0) CAudio::Instance()->Play(21);
				else CAudio::Instance()->Play(22);
				CAudio::Instance()->Play(23);
				animation.Movetonum(32 + direction * 140);
			}
			else
				animation.OnMove();
			if (animation.GetCurrentBitmapNumber() == 40 + direction * 140 || animation.GetCurrentBitmapNumber() == 49 + direction * 140)
			{
				if (direction == 1 && GetX1() - 25 >= 0) x -= 12;
				else if (direction == 0 && GetX2() + 25 <= 640)x += 12;
				attacknum--;
			}
			else if (animation.GetCurrentBitmapNumber() == 61 + direction * 140)
			{
				attacknum = 0;
				if (direction == 1 && GetX1() - 25 >= 0) x -= 25;
				else if (direction == 0 && GetX2() + 25 <= 640)x += 25;
			}
			if (animation.GetCurrentBitmapNumber() == 41 + direction * 140 || animation.GetCurrentBitmapNumber() == 50 + direction * 140) CAudio::Instance()->Play(23);
		}
		//////////////////////////////////////////////////////////跳躍攻擊/////////////////////////////////////////////////////////////
		else										
		{
			if (!(animation.GetCurrentBitmapNumber() >= 20 + direction * 140 && animation.GetCurrentBitmapNumber() < 28 + direction * 140))
			{
				if (rand() % 2 == 0) CAudio::Instance()->Play(21);
				else CAudio::Instance()->Play(22);
				CAudio::Instance()->Play(23);
				animation.Movetonum(20 + direction * 140);
			}
			else
				animation.OnMove();
			if (animation.GetCurrentBitmapNumber() == 28 + direction * 140)
				attacknum = 0;
			if (isMovingLeft && GetX1() - step_size >= 0) x -= step_size;
			if (isMovingRight&& GetX2() + step_size <= 640) x += step_size;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Attacked()
	{
		/////////////////////////////////////////////////////////////被攻擊////////////////////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= 111 + direction * 140 && animation.GetCurrentBitmapNumber() < 113 + direction * 140))
		{
			animation.Movetonum(111 + direction * 140);
			CAudio::Instance()->Play(29);
		}
		else
			animation.OnMove();
		/////////////////////////////////////////////////////////////角色擊退////////////////////////////////////////////////////////////
		if (direction == 1 && GetX2() + 4 <= 640) x += 4;	
		else if (direction == 0 && GetX1() - 4 >= 0)x -= 4;
		/////////////////////////////////////////////////////////////減少血量////////////////////////////////////////////////////////////
		if (animation.GetCurrentBitmapNumber() == 113 + direction * 140) isAttacked = false;
		if (Blood > 0)Blood -= 2;		//減少血量
		attacknum = 0;
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Molding()
	{
		//////////////////////////////////////////////////////////////集氣動畫////////////////////////////////////////////////////////////////
		if (Moldingdelay-- <= 0)
		{
			if (!(animation.GetCurrentBitmapNumber() >= 114 + direction * 140 && animation.GetCurrentBitmapNumber() <= 130 + direction * 140))
			{
				animation.Movetonum(114 + direction * 140);
				CAudio::Instance()->Play(12, true);
			}
			else if (animation.GetCurrentBitmapNumber() == 130 + direction * 140)
			{
				animation.Movetonum(123 + direction * 140);
				isAttacked = false;
			}
			else
				animation.OnMove();
			if ((animation.GetCurrentBitmapNumber() >= 123 + direction * 140 && animation.GetCurrentBitmapNumber() <= 130 + direction * 140))
			{
				magic += 8;
				chakura -= 1;
				isAttacked = false;
				/////////////////////////////////////////////////集氣失敗////////////////////////////////////////////////////////////////
				if (magic >= 512 || chakura < 0)
				{
					isSkillFail = true;
					isMolding = false;
				}
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::ThrowMove()
	{
		for (int count = 0; count < (int)Fireball.size(); count++) Fireball[count]->Move();
		for (int count = 0; count < (int)shurikan.size(); count++) shurikan[count]->Move();
		////////////////////////////////////////////////////////刪除超過邊界之投擲物////////////////////////
		for (int count = 0; count < (int)Fireball.size(); count++)
		{
			Fireball[count]->Move();
			if ((Fireball[count]->GetX1() > 640 && Fireball[count]->Getdirection() == 0) || ((Fireball[count]->GetX1() > 640 || Fireball[count]->GetY1() > 480) && Fireball[count]->Getdirection() == 1) || (Fireball[count]->GetY1() > 480 && Fireball[count]->Getdirection() == 2) || ((Fireball[count]->GetX2() < 0 || Fireball[count]->GetY1() > 480) && Fireball[count]->Getdirection() == 3) || (Fireball[count]->GetX2() < 0 && Fireball[count]->Getdirection() == 4) || ((Fireball[count]->GetX2() < 0 || Fireball[count]->GetY2() < 0) && Fireball[count]->Getdirection() == 5) || (Fireball[count]->GetY2() < 0 && Fireball[count]->Getdirection() == 6) || ((Fireball[count]->GetX1() > 640 || Fireball[count]->GetY2() < 0) && Fireball[count]->Getdirection() == 7))
			{
				delete Fireball[count];
				Fireball.erase(Fireball.begin() + count);
			}
		}
		for (int count = 0; count < (int)shurikan.size(); count++)
		{
			shurikan[count]->Move();
			if ((shurikan[count]->GetX2() < 0 && direction == 0) || (shurikan[count]->GetX1() > 640 && direction == 1))
			{
				delete shurikan[count];
				shurikan.erase(shurikan.begin() + count);
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::MovePlayer()
	{
		////////////////////////////////////////////////////左移////////////////////////////////////////////////
		if (isMovingLeft)
		{
			if (GetX1() > 0)
				x -= step_size;
			if (GetY2() >= floor)
			{
				if (!(animation.GetCurrentBitmapNumber() >= 12 + direction * 140 && animation.GetCurrentBitmapNumber() < 17 + direction * 140))
				{
					animation.Movetonum(12 + direction * 140);
				}
				else
				{
					animation.OnMove();
				}
			}
			direction = 1;
		}
		////////////////////////////////////////////////////右移////////////////////////////////////////////////
		else if (isMovingRight)
		{
			if (GetX2() < 640)
				x += step_size;
			if (GetY2() >= floor)
			{
				if (!(animation.GetCurrentBitmapNumber() >= 12 && animation.GetCurrentBitmapNumber() < 17))
				{
					animation.Movetonum(12);
				}
				else
				{
					animation.OnMove();
				}
			}
			direction = 0;
		}
		////////////////////////////////////////////////////跳躍////////////////////////////////////////////////
		if ((isMovingUp && rising == false && velocity == initial_velocity && GetY2() >= floor) && !(animation.GetCurrentBitmapNumber() >= 29 + direction * 140 && animation.GetCurrentBitmapNumber() <= 31 + direction * 140))
		{
			CAudio::Instance()->Play(23);
			rising = true;
			velocity = initial_velocity;
			if (isMovingRight || isMovingLeft)
				animation.Movetonum(19 + direction * 140);
			else
				animation.Movetonum(18 + direction * 140);

		}
		//////////////////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Die()
	{
		////////////////////////////////////人物倒地/////////////////////////////////////////////////////////////
		Move = false;
		if (animation.GetCurrentBitmapNumber() < 62 + direction * 140 || animation.GetCurrentBitmapNumber() > 110 + direction * 140) animation.Movetonum(62 + direction * 140);
		if (animation.GetCurrentBitmapNumber() >= 74 + direction * 140 && animation.GetCurrentBitmapNumber() <= 79 + direction * 140)
		{
			velocity -= 3;
			if (GetY2() < floor) y -= velocity;	// 當後半段動畫角色從空中落下
		}
		if (animation.GetCurrentBitmapNumber() >= 62 + direction * 140 && animation.GetCurrentBitmapNumber() <= 67 + direction * 140)
		{
			y -= velocity;	// 當前半段動畫角色被擊飛至空中
			velocity -= 3;
		}
		if (animation.GetCurrentBitmapNumber() >= 62 + direction * 140 && animation.GetCurrentBitmapNumber() <= 79 + direction * 140)
		{
			////////////////////////////////////////角色往後飛////////////////////////////////
			if (direction == 1 && GetX2() + 7 <= 640) x += 7;
			else if (direction == 0 && GetX1() - 7 >= 0) x -= 7;
			////////////////////////////////////////////////////////////////////////////////////
		}
		if (GetY2() < floor) y -= velocity;//////////////////確保不超過地面且到達地面
		if (animation.GetCurrentBitmapNumber() == 80 + direction * 140) CAudio::Instance()->Play(30);
		if (animation.GetCurrentBitmapNumber() == 110 + direction * 140)
		{
			//////////////////////////////倒地延遲////////////////////////////////
			if (Diedelay-- <= 0)
			{
				isDie = false;
				Move = true;
				isAttacked = false;
				Diedelay = 30;
				velocity = initial_velocity;
				y = floor - 72;
			}
			//////////////////////////////////////////////////////////////////////
		}
		else 	animation.OnMove();
		/////////////////////////////////減少血量/////////////////////////////////////
		if (Blood > 0 && delay-- <= 0 && animation.GetCurrentBitmapNumber() != 110 + direction * 140)
		{
			Blood -= damage;
			delay = 2;
		}
		///////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::Stand()
	{
		/////////////////////////////////站在原地////////////////////////////////////////////
		if (!(animation.GetCurrentBitmapNumber() >= 0 + direction * 140 && animation.GetCurrentBitmapNumber() < 11 + direction * 140))
			animation.Movetonum(0 + direction * 140);
		else
			animation.OnMove();
		if (chakura <= 64 && chakuradelay-- <= 8) { chakura++; chakuradelay = 16; }
		//////////////////////////////////////////////////////////////////////////////////////
	}
	void Sasuke::SetSkill()
	{
		/////////////////////////////////////////技能判定失敗//////////////////////////////////////////////
		CAudio::Instance()->Stop(12);
		if (magic >= 512 || chakura <= 0)
		{
			if (!(animation.GetCurrentBitmapNumber() >= 131 + direction * 140 && animation.GetCurrentBitmapNumber() < 139 + direction * 140))
				animation.Movetonum(131 + direction * 140);
			else
				animation.OnMove();
			if (animation.GetCurrentBitmapNumber() == 139 + direction * 140)
			{
				magic = 0;
				isSkillFail = false;
			}
		}
		//////////////////////////////////////////////技能成功/////////////////////////////////////////////
		else
		{
			if (!Movieflag)
			{
				if (magic >= 0 && magic < 128)		SkillMovie.Movetonum(90 + direction * 12);	//技能一成功
				if (magic >= 128 && magic < 256)	SkillMovie.Movetonum(0 + direction * 45);	//技能二成功
				if (magic >= 256 && magic < 384)	SkillMovie.Movetonum(90 + direction * 12);	//技能三成功
				if (magic >= 384 && magic < 512)	SkillMovie.Movetonum(114 + direction * 24);	//技能四成功
				animation.Movetonum(0 + direction * 140);
				Movieflag = true;
				////////////////////////////技能成功////////////////////////
				if (magic % 128 < 38) Movie.Init();
				else
				{
					/////////////////技能大成功//////////////////////
					Movie2.Init();
					CAudio::Instance()->Play(24);
					///////////////////////////////////////////////////
				}
				SkillsuccessMovie.SetTopLeft(GetX1(), GetY1());
			}
			isMovingRight = false;
			isMovingLeft = false;
			isAttacked = false;
			isDie = false;
			isSkill = true;
			//////////////////////////////技能動畫////////////////////////////////
			if (magic >= 0 && magic < 128)		AttackMovie1();
			if (magic >= 128 && magic < 256)	AttackMovie2();
			if (magic >= 256 && magic < 384)	AttackMovie3();
			if (magic >= 384 && magic < 512)	AttackMovie4();
			/////////////////////////////////////////////////////////////////////
		}
	}
	void Sasuke::SetisMolding(bool flag)
	{
		isMolding = flag;
		Moldingdelay = 3;
		if (!flag &&(animation.GetCurrentBitmapNumber() >= 114 + direction * 140 && animation.GetCurrentBitmapNumber() <=130 + direction * 140))
		{
			isSkillFail = true;
		}
	}

	bool Sasuke::GetMovingLeft()
	{
		return isMovingLeft;
	}

	bool Sasuke::GetMovingRight()
	{
		return isMovingRight;
	}

	bool Sasuke::GetisDie()
	{
		return isDie;
	}

	void Sasuke::SubBlood(int Sub)
	{
		Blood -= Sub;
	}

	int Sasuke::GetDirection()
	{
		return direction;
	}

	int Sasuke::GetAttack()
	{
		return attacknum;
	}

	bool Sasuke::GetisSkill()
	{
		return isSkill;
	}

	bool Sasuke::GetisMolding()
	{
		return isMolding;
	}

	void Sasuke::SetXY(int nx, int ny)
	{
		x = nx; y = ny;
	}
	void Sasuke::Addattacknum()
	{
		attacknum++;
	}
	bool Sasuke::GetMove()
	{
		return Move;
	}
	int Sasuke::Getblood()
	{
		return Blood;
	}
	int Sasuke::GetMagic()
	{
		return magic;
	}
	int Sasuke::GetCurrentBitmapNumber()
	{
		return animation.GetCurrentBitmapNumber();
	}
	int Sasuke::GetSkillCurrentBitmapNumber()
	{
		return SkillMovie.GetCurrentBitmapNumber();
	}
	skillstart *Sasuke::Getskillstart()
	{
		if (Movie.isStart()) return &Movie;
		else return &Movie2;
	}
	vector<SasukeFireball*> Sasuke::GetFireball()
	{
		return Fireball;
	}
	vector<Shurikan*> Sasuke::GetShurikan()
	{
		return shurikan;
	}
	void Sasuke::AttackMovie1()
	{
		////////////////////////播放技能前置動畫////////////////////////////////
		if (Movie.isStart())	Movie.OnMove();
		else if (Movie2.isStart())	Movie2.OnMove();
		else
		{
			//////////////////////////////////////技能內容///////////////////////////////////////////////////
			if (SkillMovie.GetCurrentBitmapNumber() == 101 + direction * 12)
			{
				////////////////////////////////技能小成功往前射出手里劍//////////////////////////////////////////////
				if (direction == 0)
				{
					shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 1));
					shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 2 + this->GetY1(), 1));
				}
				if (direction == 1)
				{
					shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 0));
					shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 2 + this->GetY1(), 0));
				}
				///////////////////////////////技能大成功往前射出一堆手里劍////////////////////////////////////////////
				if (magic % 128 > 38 && skill1delay-- <= 0)
				{
					if (direction == 0)
					{
						shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 1));
						shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 2 + this->GetY1(), 1));
					}
					if (direction == 1)
					{
						shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 0));
						shurikan.push_back(new Shurikan((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 2 + this->GetY1(), 0));
					}
				}
				////////////////////////////////////////////////////////////////////////////////////
				if (magic % 128 <= 38 || (magic % 128 > 38 && skill1delay <= 0))
				{
					CAudio::Instance()->Play(26);
					isSkill = false;
					Movieflag = false;
					isSkillFail = false;
					isAttacked = false;
					magic = 0;
					skill1delay = 8;
				}
			}
			/////////////////////////////////////////////////////////////////////////////////////////
			else 	SkillMovie.OnMove();
		}
	}
	void Sasuke::AttackMovie2()
	{
		////////////////////////播放技能前置動畫////////////////////////////////
		if (Movie.isStart())	Movie.OnMove();
		else if (Movie2.isStart())	Movie2.OnMove();
		else
		{
			////////////////////////////////////////////技能成功////////////////////////////////////////////
			if(SkillMovie.GetCurrentBitmapNumber() == 20 + direction * 45) CAudio::Instance()->Play(26);
			SkillMovie.OnMove();
			////////////////////////////////////////////技能大成功////////////////////////////////////////////
			if (magic%128 > 38)
			{
				////////////////////////////////////////////射出火球/////////////////////////////////////////
				if (SkillMovie.GetCurrentBitmapNumber() == 20 + direction * 45 || SkillMovie.GetCurrentBitmapNumber() == 26 + direction * 45 || SkillMovie.GetCurrentBitmapNumber() == 32 + direction * 45 || SkillMovie.GetCurrentBitmapNumber() == 38 + direction * 45)
				{
					if(direction == 0) Fireball.push_back(new SasukeFireball(this->GetX2()-20, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 0));
					if(direction == 1) Fireball.push_back(new SasukeFireball(this->GetX1()+20, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), 4));
				}
				///////////////////////////////////////////////////////////////////////////////////////////////
			}
			if (SkillMovie.GetCurrentBitmapNumber() == 44 + direction * 45)
			{
				isSkill = false;
				Movieflag = false;
				isSkillFail = false;
				isAttacked = false;
				magic = 0;
			}
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
	}
	void Sasuke::AttackMovie3()
	{
		////////////////////////播放技能前置動畫////////////////////////////////
		if (Movie.isStart())	Movie.OnMove();
		else if (Movie2.isStart())	Movie2.OnMove();
		else
		{
			if (SkillMovie.GetCurrentBitmapNumber() == 101 + direction * 12)
			{
				if (skill3delay-- <= 0)
				{
					//////////////////////////////順時針射出火球///////////////////////////////////////
					if (direction == 0) Fireball.push_back(new SasukeFireball((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), skill3direction % 8));
					if (direction == 1) Fireball.push_back(new SasukeFireball((this->GetX2() + GetX1()) / 2, (this->GetY2() - this->GetY1()) / 3 + this->GetY1(), (4 + skill3direction) % 8));
					/////////////////////////////////////////////////////////////////////////////////
					if (skill3direction > 24)
					{
						isSkill = false;
						Movieflag = false;
						isSkillFail = false;
						isAttacked = false;
						magic = 0;
					}
					if ((skill3direction >= 23 && magic % 128 > 38) || (skill3direction >= 15 && magic % 128 <= 38))
					{
						isSkill = false;
						Movieflag = false;
						isSkillFail = false;
						isAttacked = false;
						magic = 0;
						skill3direction = 0;
					}
					skill3direction++;
					skill3delay = 4;
				}
			}
			else 	SkillMovie.OnMove();
			y = 200;
			x = 290;
		}
	}
	void Sasuke::AttackMovie4()
	{
		////////////////////////播放技能前置動畫////////////////////////////////
		if (Movie.isStart())	Movie.OnMove();
		else if (Movie2.isStart())	Movie2.OnMove();
		else
		{
			////////////////////////////////////技能動畫///////////////////////////////
			if (!Skillsuccess)
			{
				SkillMovie.OnMove();
				if (GetX2() < 640 && direction == 0) x += step_size;
				if (GetX1() > 0 && direction == 1) x -= step_size;
			}
			else RunSkillsuccessMovie();///////技能命中////////////////////////////////
			if (SkillMovie.GetCurrentBitmapNumber() == 137 + direction * 24)
			{
				isSkill = false;
				Movieflag = false;
				isSkillFail = false;
				isAttacked = false;
				magic = 0;
			}
		}
	}
}
