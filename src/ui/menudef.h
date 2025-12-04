/*
 * Jaymod - menudef.h stub
 * This file was missing from the original repository.
 * Creating a minimal stub to allow compilation.
 */

#ifndef UI_MENUDEF_H
#define UI_MENUDEF_H

// Text alignment constants
#define ITEM_ALIGN_LEFT     0
#define ITEM_ALIGN_CENTER   1
#define ITEM_ALIGN_RIGHT    2

// Text style constants
#define ITEM_TEXTSTYLE_NORMAL           0
#define ITEM_TEXTSTYLE_BLINK            1
#define ITEM_TEXTSTYLE_PULSE            2
#define ITEM_TEXTSTYLE_SHADOWED         3
#define ITEM_TEXTSTYLE_OUTLINED         4
#define ITEM_TEXTSTYLE_OUTLINESHADOWED  5
#define ITEM_TEXTSTYLE_SHADOWEDMORE     6

// HUD orientation constants
#define HUD_VERTICAL		0x00
#define HUD_HORIZONTAL		0x01

// CS_SERVERTOGGLES
#define CV_SVS_MUTESPECS		1
#define CV_SVS_FRIENDLYFIRE		2
// 2 bits for warmup damage setting
#define CV_SVS_WARMUPDMG		12
#define CV_SVS_PAUSE			16
#define CV_SVS_LOCKTEAMS		32
#define CV_SVS_LOCKSPECS		64
#define CV_SVS_ANTILAG			128
#define CV_SVS_BALANCEDTEAMS	256
#define CV_SVS_NEXTMAP			512

// "cg_ui_voteFlags"
#define CV_SVF_COMP				1
#define CV_SVF_GAMETYPE			2
#define CV_SVF_KICK				4
#define CV_SVF_MAP				8
#define CV_SVF_MATCHRESET		16
#define CV_SVF_MUTESPECS		32
#define CV_SVF_NEXTMAP			64
#define CV_SVF_PUB				128
#define CV_SVF_REFEREE			256
#define CV_SVF_SHUFFLETEAMS		512
#define CV_SVF_STARTMATCH		1024
#define CV_SVF_SWAPTEAMS		2048
#define CV_SVF_FRIENDLYFIRE		4096
#define CV_SVF_TIMELIMIT		8192
#define CV_SVF_WARMUPDMG		16384
#define CV_SVF_ANTILAG			32768
#define CV_SVF_BALANCEDTEAMS	65536
#define CV_SVF_MUTING			131072
#define CV_SVF_SURRENDER		262144
#define CV_SVF_RESTARTCAMPAIGN	524288
#define CV_SVF_NEXTCAMPAIGN		1048576
#define CV_SVF_POLL				2097152
#define CV_SVF_MAPRESTART		4194304
#define CV_SVF_COINTOSS			8388608
#define CV_SVF_PAUSE			16777216

#endif // UI_MENUDEF_H
