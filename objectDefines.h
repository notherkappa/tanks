#ifndef objectsDefinesH
#define objectsDefinesH


#define SFM_CURRENT     SFM_CACHED
#define SFM_NEW         newSprite
#define SFM_CACHED      newCachedSprite
#define SFM_COPY        copySprite
#define SFM_INSTANCE    newInstanceOf

#define TYPE_WALL                       0x100
#define TYPE_BRICK_WALL                 0x101
#define TYPE_CONCRETE_WALL_LVL1         0x102
#define TYPE_BOUND_WALL                 0x1FF

#define TYPE_BULLETS                    0x200
#define TYPE_BULLET                     0x201
#define TYPE_ANTICONCRETE_BULLET        0x202


#define TYPE_TANK                       0x400
#define TYPE_PLAYER_TANK                0x401
#define TYPE_AI_TANK                    0x402


#define AITANK_RANDOM_MOVE              0x010401




#define TEAM_PLAYER_TANK                TEAM_PLAYER
#define TEAM_BRICK_WALL                 TEAM_PEACEFUL

#define PLAYERTANK_STATE_STILL          0x00
#define PLAYERTANK_STATE_GO_UP          0x01
#define PLAYERTANK_STATE_GO_LEFT        0x02
#define PLAYERTANK_STATE_GO_RIGHT       0x03
#define PLAYERTANK_STATE_GO_DOWN        0x04
#define PLAYERTANK_STATE_DEAD           0x05
#define PLAYERTANK_STATE_ON_ICE         0x100
#define PLAYERTANK_STATE_IN_CAVE        0x200


#define AIRM_STATE_GO_UP                0x01
#define AIRM_STATE_GO_LEFT              0x02
#define AIRM_STATE_GO_RIGHT             0x03
#define AIRM_STATE_GO_DOWN              0x04
#define AIRM_STATE_DEAD                 0x05
#define AIRM_FREEWAY                    0x000
#define AIRM_WALL                       0x100
#define AIRM_SWALL                      0x200

#define BULLET_STATE_DEFAULT            0x00
#define BULLET_STATE_MOVE_UP            0x01
#define BULLET_STATE_MOVE_LEFT          0x02
#define BULLET_STATE_MOVE_RIGHT         0x03
#define BULLET_STATE_MOVE_DOWN          0x04
#define BULLET_STATE_DEAD               0x05


#define RESIST_TYPE_NORMAL              0x01




//---------------------------------------------------------------------------
#endif


