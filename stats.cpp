//---------------------------------------------------------------------------


#pragma hdrstop

#include "stats.h"

UserStats::UserStats()
{
        livesCount=scores=enemyTotalCount=gameOver=maxhp=hp=0;
        levelName = "";
        usStatic.init = true;
        usStatic.instance = this;
        lasttimedmg=0;
}
UserStats::~UserStats()
{
;
}
UserStats* UserStats::getInstance()
{
        return usStatic.init?usStatic.instance:new UserStats();
}
void UserStats::print(TLabel *livesCountLabel,  TLabel * scoresLabel, TLabel * lvlNameLabel, TLabel * gameOverLabel, TProgressBar * pb, TLabel* currenthp)
{
        livesCountLabel->Caption = "Lives Left: "+IntToStr(livesCount);
        scoresLabel->Caption = "Scores: "+IntToStr(scores);
        lvlNameLabel->Caption = "Level: "+levelName;
        if (gameOver)
                gameOverLabel->Visible=true;
        else
                gameOverLabel->Visible=false;
        pb->Max = maxhp;
        pb->Position=hp;
        currenthp->Caption = "HP: "+IntToStr(hp);

}
void UserStats::damage(int i)
{
        if (::GetTickCount()-lasttimedmg>250)
        {
                hp-=i;
                if (hp<0)
                        hp=0;
                if (hp>maxhp)
                        hp=maxhp;
                lasttimedmg=::GetTickCount();
        }
}

//---------------------------------------------------------------------------

#pragma package(smart_init)
