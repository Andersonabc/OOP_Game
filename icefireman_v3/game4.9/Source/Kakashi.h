#ifndef KAKASHI_H
#define KAKASHI_H

namespace game_framework {
	class Kakashi
	{
	public:
		Kakashi();
		void Init();
		void OnShow(int _section);
		void ChangeFilm(int _film);
		int GetFilm();
		void ChangeVicFilm(int _film);
		void ChangeVic2Film(int _film);
		int GetVicFilm();
		int GetVic2Film();
		int GetSection();
		void ChangeSection(int _section);
		void AddPic();
		bool GetEnd();
		bool IsFinish();
		bool IsDone();
		void SetDone(bool _flag);
	protected:
		CAnimation instructions;
		CAnimation victory;
		CAnimation failed;
		CAnimation victory2;
		CAnimation final;
		bool isEnd, Done, isFinish;
		int nowFilm, nowVicFilm, section, nowVic2Film;
		int film[7] = {18,29,43,60,75,85,102};                 //�����C�@�ӹ�ܮبϥδX�i��
		int vicfilm[2] = {13,24};							   //�����C�@�ӹ�ܮبϥδX�i��	
		int vic2film[2] = { 13,30 };						   //�����C�@�ӹ�ܮبϥδX�i��
	};
}
#endif