#ifndef BLOODCOUNT_H
#define BLOODCOUNT_H

namespace game_framework {
	class bloodcount
	{
	public:
		bloodcount();
		void Init(int _x, int _y, string _characteristic, int _numOfBlood, int IDB_BITMAP, COLORREF colorkey);
		int  GetX1();					// 擦子左上角 x 座標
		int  GetY1();					// 擦子左上角 y 座標
		void OnShow();
		void SetXY(int _x, int _y);
		void ChangeBlood(int _numOfBlood);
		void SetisMolding(bool flag, int _numOfMagic);
		void ChangeChakura(int _chakura);
		int GetChakura();
		int GetBlood();
	protected:
		CMovingBitmap Blood,Blood2,Magic,Chakura;
		CMovingBitmap characterUI;
		CMovingBitmap MagicBar;
		CMovingBitmap bloodbackground;
		CAnimation SkillText;
		bool isMolding;
		int x, y, numOfBlood,numOfMagic, numOfChakura;
		string characteristic;
	};

}
#endif