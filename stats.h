//---------------------------------------------------------------------------

#ifndef statsH
#define statsH
#include <vcl.h>
#include <Controls.hpp>
#include <StdCtrls.hpp> 
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>



class UserStats
{
public:
        static UserStats* getInstance();
        void print(TLabel *livesCountLabel,  TLabel * scoresLabel, TLabel * lvlNameLabel, TLabel * gameOverLabel, TProgressBar * pb, TLabel* currenthp);

        int livesCount, scores;
        int enemyTotalCount;
        int maxhp, hp;
        bool gameOver;
        String levelName;

private:
        UserStats();
        ~UserStats();
};


struct UserStatsStatic
{
        friend UserStats;
private:
        UserStats * instance;
        bool init;
}usStatic;

//---------------------------------------------------------------------------
#endif
