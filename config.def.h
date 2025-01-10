/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1; /* border pixel of windows */
static const unsigned int snap      = 1; /* snap pixel */
static const int showbar            = 1; /* 0 means no bar */
static const int topbar             = 1; /* 0 means bottom bar */
static const char *fonts[]          = { "CaskaydiaCove Nerd Font:style=Regular:size=4:antialias=true" };
static const char dmenufont[]       = "CaskaydiaCove Nerd Font:style=Regular:size=5:antialias=true";
static const char col_gray0[]       = "#F4F6F6";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char col_orange[]      = "#ab381c";
static const char col_orange2[]     = "#673722";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_orange2 },
	[SchemeSel]  = { col_gray4, col_orange, col_gray4  },
	[SchemeTitle]  = { col_gray0, col_gray1,  col_cyan  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class         instance       title    tags mask  iscentered  isfloating  monitor */
	{ "thunderbird", "Calendar",    NULL,    0,         1,          1,          -1 },
	{ "Dragon",      "dragon",      NULL,    0,         1,          1,          -1 },
	{ "term-float",  "st-256color", NULL,    0,         1,          1,          -1 },
	{ "cmus",        "st-256color", NULL,    0,         0,          0,           2 },
	{ "dmenu",       "dmenu",       NULL,    0,         1,          1,          -1 },
};

/* layout(s) */
static const int dirs[3] = { DirHor, DirVer, DirVer }; /* tiling dirs */
static const float facts[3] = { 1.0, 1.0, 1.0 };       /* tiling facts */
static const int nmaster = 1;        /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol arrange function */
	{ "[]=", tile },   /* first entry is default */
	{ "[M]", monocle },
};

/* key definitions */
#define MODKEY Mod4Mask

#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define TILEKEYS(MOD,G,M,S) \
	{ MOD, XK_t, setdirs,  {.v = (int[])  { INC(G * +1),    INC(M * +1),    INC(S * +1)    } } }, \
	{ MOD, XK_m, setfacts, {.v = (float[]){ INC(G * -0.04), INC(M * -0.06), INC(S * -0.06) } } }, \
	{ MOD, XK_i, setfacts, {.v = (float[]){ INC(G * +0.04), INC(M * +0.06), INC(S * +0.06) } } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

#define TRMCMD(cmd) { .v = (const char*[]){ "kitty", "--hold", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon,
    "-fn", dmenufont, "-nb", col_gray1,
    "-nf", col_gray3, "-sb", col_orange,
    "-sf", col_gray4, "-c", NULL
};
static const char *termcmd[] = { "kitty", NULL };
static const char *slock[]   = { "slock", NULL };
static const char *web[]     = { "librewolf", NULL };
static const char *guimail[] = { "thunderbird", NULL };

static const Key keys[] = {
	/* modifier                     key           function           argument */
	{ MODKEY,                       XK_semicolon, spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_semicolon, spawn,             SHCMD("passmenu_custom") },
	{ MODKEY,                       XK_z,         spawn,             {.v = web } },
	{ MODKEY|ShiftMask,             XK_b,         spawn,             TRMCMD("btm") },
	{ MODKEY|ShiftMask,             XK_h,         spawn,             TRMCMD("calc") },
	{ MODKEY,                       XK_p,         spawn,             SHCMD("directories_dmenu.sh") },
	{ MODKEY|ControlMask,           XK_d,         spawn,             SHCMD("st_cmus.sh") },
	{ MODKEY|ControlMask,           XK_z,         spawn,             SHCMD("cmus-remote -n") },
	{ MODKEY|ControlMask,           XK_x,         spawn,             SHCMD("cmus-remote -r") },
	{ MODKEY|ControlMask,           XK_h,         spawn,             SHCMD("cmus-remote -C 'toggle aaa_mode'") },
	{ MODKEY,                       XK_k,         spawn,             {.v = guimail } },
	// { MODKEY|ShiftMask,             XK_k,         spawn,             TRMCMD("mailsync.sh") },
	{ MODKEY|ShiftMask,             XK_Return,    spawn,             {.v = termcmd } },
	{ MODKEY,                       XK_n,         focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_e,         focusstack,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_n,         movestack,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_e,         movestack,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_u,         incnmaster,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_s,         incnmaster,        {.i = -1 } },
	{ MODKEY,                       XK_Return,    zoom,              {0} },
	{ MODKEY,                       XK_Tab,       view,              {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_v,         spawn,             {.v = slock } },
	{ MODKEY|ShiftMask,             XK_d,         killclient,        {0} },
	// { MODKEY,                       XK_b,         setlayout,         {.v = &layouts[0]} }, /*Tiled*/
	// { MODKEY,                       XK_h,         setlayout,         {.v = &layouts[1]} }, /*Monocle*/
	TILEKEYS(MODKEY,                                                 1, 0, 0)
	TILEKEYS(MODKEY|ShiftMask,                                       0, 1, 0)
	TILEKEYS(MODKEY|ControlMask,                                     0, 0, 1)
	TILEKEYS(MODKEY|ShiftMask|ControlMask,                           1, 1, 1)
	{ MODKEY|ControlMask,           XK_b,         setdirs,           {.v = (int[]){ DirHor, DirVer, DirVer } } }, /* Right stack */
	{ MODKEY|ShiftMask,             XK_y,         setdirs,           {.v = (int[]){ DirVer, DirHor, DirHor } } }, /* Bottom stack */
	{ MODKEY|ShiftMask|ControlMask, XK_y,         setdirs,           {.v = (int[]){ DirVer, DirVer, DirVer } } }, /* All horizontal */
	{ MODKEY|ShiftMask|ControlMask, XK_b,         setdirs,           {.v = (int[]){ DirHor, DirHor, DirHor } } }, /* All columns */
	{ MODKEY,                       XK_h,     setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,     togglefloating,    {0} },
	{ MODKEY,                       XK_0,         view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,         tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period,    focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period,    tagmon,            {.i = +1 } },
	{ MODKEY,                       XK_q,         moveplace,         {.ui = WIN_NW }},
	{ MODKEY,                       XK_w,         moveplace,         {.ui = WIN_N  }},
	{ MODKEY,                       XK_f,         moveplace,         {.ui = WIN_NE }},
	{ MODKEY,                       XK_a,         moveplace,         {.ui = WIN_W  }},
	{ MODKEY,                       XK_r,         moveplace,         {.ui = WIN_C  }},
	{ MODKEY,                       XK_s,         moveplace,         {.ui = WIN_E  }},
	{ MODKEY,                       XK_x,         moveplace,         {.ui = WIN_SW }},
	{ MODKEY,                       XK_c,         moveplace,         {.ui = WIN_S  }},
	{ MODKEY,                       XK_d,         moveplace,         {.ui = WIN_SE }},
	{ MODKEY|ControlMask|ShiftMask, XK_n,         aspectresize,      {.i = +26} },
	{ MODKEY|ControlMask|ShiftMask, XK_e,         aspectresize,      {.i = -26} },
	{ MODKEY,                       XK_Down,      moveresize,        {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,        moveresize,        {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,     moveresize,        {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,      moveresize,        {.v = "-25x 0y 0w 0h" } },
	{ MODKEY|ShiftMask,             XK_Down,      moveresize,        {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,        moveresize,        {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,     moveresize,        {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,      moveresize,        {.v = "0x 0y -25w 0h" } },
	{ MODKEY|ControlMask,           XK_Up,        moveresizeedge,    {.v = "t"} },
	{ MODKEY|ControlMask,           XK_Down,      moveresizeedge,    {.v = "b"} },
	{ MODKEY|ControlMask,           XK_Left,      moveresizeedge,    {.v = "l"} },
	{ MODKEY|ControlMask,           XK_Right,     moveresizeedge,    {.v = "r"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Up,        moveresizeedge,    {.v = "T"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Down,      moveresizeedge,    {.v = "B"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Left,      moveresizeedge,    {.v = "L"} },
	{ MODKEY|ControlMask|ShiftMask, XK_Right,     moveresizeedge,    {.v = "R"} },
	TAGKEYS(                        XK_1,                            0)
	TAGKEYS(                        XK_2,                            1)
	TAGKEYS(                        XK_3,                            2)
	TAGKEYS(                        XK_4,                            3)
	TAGKEYS(                        XK_5,                            4)
	TAGKEYS(                        XK_6,                            5)
	TAGKEYS(                        XK_7,                            6)
	TAGKEYS(                        XK_8,                            7)
	TAGKEYS(                        XK_9,                            8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,         quit,              {0} },
	{ MODKEY,                       XK_minus,     scratchpad_show,   {0} },
	{ MODKEY|ShiftMask,             XK_minus,     scratchpad_hide,   {0} },
	{ MODKEY,                       XK_equal,     scratchpad_remove, {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[1]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
