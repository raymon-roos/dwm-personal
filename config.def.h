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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "(M)",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define CMDTAGKEYS(KEY,TAG) \
	{ {0,0,0,0},                     {KEY,0,0,0},      view,           {.ui = 1 << TAG} }, \
	{ {ControlMask,0,0,0},           {KEY,0,0,0},      toggleview,     {.ui = 1 << TAG} }, \
	{ {ShiftMask,0,0,0},             {KEY,0,0,0},      tag,            {.ui = 1 << TAG} }, \
	{ {ControlMask|ShiftMask,0,0,0}, {KEY,0,0,0},      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }
#define TRMCMD(cmd) { .v = (const char*[]){ "/usr/local/bin/st", "-e", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {
    "dmenu_run", "-m", dmenumon,
    "-fn", dmenufont, "-nb", col_gray1,
    "-nf", col_gray3, "-sb", col_orange,
    "-sf", col_gray4, NULL
};
static const char *dmenumgd[] = {
    "dmenu_run", "-m", dmenumon,
    "-fn", dmenufont, "-nb", col_gray1,
    "-nf", col_gray3, "-sb", col_orange,
    "-sf", col_gray4, "-c", "-wm",
    NULL
};
static const char *termcmd[] = { "st", NULL };
static const char *slock[]   = { "slock", NULL };
static const char *web[]     = { "librewolf", NULL };
static const char *guimail[] = { "thunderbird", NULL };

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function           argument */
	{ MODKEY,                       XK_Escape, setkeymode,        {.ui = ModeCommand} },
	{ MODKEY,                       XK_semicolon, setkeymode,     {.ui = ModeCommand} },
	{ MODKEY,                       XK_p,      spawn,             {.v = dmenumgd } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      spawn,             {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,             SHCMD("passmenu") },
	{ MODKEY,                       XK_b,      spawn,             {.v = web } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,             TRMCMD("top") },
	{ MODKEY,                       XK_r,      spawn,             TRMCMD("calc") },
	{ MODKEY,                       XK_f,      spawn,             TRMCMD("launch_nnn.sh") },
	{ MODKEY|ControlMask,           XK_c,      spawn,             SHCMD("launch_cmus.sh") },
	{ MODKEY|ControlMask,           XK_b,      spawn,             SHCMD("cmus-remote -n") },
	{ MODKEY|ControlMask,           XK_z,      spawn,             SHCMD("cmus-remote -r") },
	{ MODKEY|ControlMask,           XK_m,      spawn,             SHCMD("cmus-remote -C 'toggle aaa_mode'") },
	{ MODKEY,                       XK_n,      spawn,             {.v = guimail } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,             TRMCMD("neomutt") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,             {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,         {0} },
	{ MODKEY,                       XK_j,      focusstack,        {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,         {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,          {.f = -0.02} },
	{ MODKEY,                       XK_l,      setmfact,          {.f = +0.02} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,          {.f = +0.12} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,          {.f = -0.12} },
	{ MODKEY|ControlMask|ShiftMask, XK_i,      setcfact,          {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,              {0} },
	{ MODKEY,                       XK_Tab,    view,              {0} },
	{ MODKEY|ControlMask|ShiftMask,	XK_l,	   spawn,             {.v = slock } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,        {0} },
	{ MODKEY,                       XK_t,      setlayout,         {.v = &layouts[0]} }, /*Tiled*/
//  { MODKEY|ShiftMask,             XK_f,      setlayout,         {.v = &layouts[1]} }, /*Floating*/
	{ MODKEY,                       XK_m,      setlayout,         {.v = &layouts[2]} }, /*Monocle*/
	{ MODKEY,                       XK_space,  setlayout,         {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating,    {0} },
	{ MODKEY,                       XK_0,      view,              {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,               {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,          {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,          {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,            {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,            {.i = +1 } },
	{ MODKEY,                       XK_q,      moveplace,         {.ui = WIN_NW }},
	{ MODKEY,                       XK_w,      moveplace,         {.ui = WIN_N  }},
	{ MODKEY,                       XK_e,      moveplace,         {.ui = WIN_NE }},
	{ MODKEY,                       XK_a,      moveplace,         {.ui = WIN_W  }},
	{ MODKEY,                       XK_s,      moveplace,         {.ui = WIN_C  }},
	{ MODKEY,                       XK_d,      moveplace,         {.ui = WIN_E  }},
	{ MODKEY,                       XK_z,      moveplace,         {.ui = WIN_SW }},
	{ MODKEY,                       XK_x,      moveplace,         {.ui = WIN_S  }},
	{ MODKEY,                       XK_c,      moveplace,         {.ui = WIN_SE }},
	TAGKEYS(                        XK_1,                         0)
	TAGKEYS(                        XK_2,                         1)
	TAGKEYS(                        XK_3,                         2)
	TAGKEYS(                        XK_4,                         3)
	TAGKEYS(                        XK_5,                         4)
	TAGKEYS(                        XK_6,                         5)
	TAGKEYS(                        XK_7,                         6)
	TAGKEYS(                        XK_8,                         7)
	TAGKEYS(                        XK_9,                         8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,              {0} },
	{ MODKEY,                       XK_minus,  scratchpad_show,   {0} },
	{ MODKEY|ShiftMask,             XK_minus,  scratchpad_hide,   {0} },
	{ MODKEY,                       XK_equal,  scratchpad_remove, {0} },
};

static Key cmdkeys[] = {
	/* modifier                          keys                   function           argument */
	{ 0,                                 XK_Escape,             clearcmd,          {0} },
	{ ControlMask,                       XK_g,                  clearcmd,          {0} },
	{ 0,                                 XK_i,                  setkeymode,        {.ui = ModeInsert} },
};

static Command commands[] = {
	/* modifier (4 keys)                 keysyms (4 keys)       function           argument */
	{ {0, 0, 0, 0},                      {XK_p,      0, 0, 0},  spawn,             {.v = dmenucmd } },
	{ {ShiftMask, 0, 0, 0},              {XK_Return, 0, 0, 0},  spawn,             {.v = termcmd } },
	{ {0, 0, 0, 0},                      {XK_b,      0, 0, 0},  togglebar,         {0} },
	{ {0, 0, 0, 0},                      {XK_j,      0, 0, 0},  focusstack,        {.i = +1 } },
	{ {0, 0, 0, 0},                      {XK_k,      0, 0, 0},  focusstack,        {.i = -1 } },
	{ {ShiftMask, 0, 0, 0},              {XK_j,      0, 0, 0},  movestack,         {.i = +1 } },
	{ {ShiftMask, 0, 0, 0},              {XK_k,      0, 0, 0},  movestack,         {.i = -1 } },
	{ {0, 0, 0, 0},                      {XK_h,      0, 0, 0},  setmfact,          {.f = -0.02} },
	{ {0, 0, 0, 0},                      {XK_l,      0, 0, 0},  setmfact,          {.f = +0.02} },
	{ {ShiftMask, 0, 0, 0},              {XK_h,      0, 0, 0},  setcfact,          {.f = +0.12} },
	{ {ShiftMask, 0, 0, 0},              {XK_l,      0, 0, 0},  setcfact,          {.f = -0.12} },
	{ {ControlMask|ShiftMask, 0, 0, 0},  {XK_i,      0, 0, 0},  setcfact,          {.f =  0.00} },
	{ {0, 0, 0, 0},                      {XK_Return, 0, 0, 0},  zoom,              {0} },
	{ {ControlMask,0, 0, 0},             {XK_i,      0, 0, 0},  view,              {0} },
	{ {ShiftMask, 0, 0, 0},              {XK_c,      0, 0, 0},  killclient,        {0} },
	{ {0, 0, 0, 0},                      {XK_t,      0, 0, 0},  setlayout,         {.v = &layouts[0]} },
//  { {0, 0, 0, 0},                      {XK_f,      0, 0, 0},  setlayout,         {.v = &layouts[1]} },
	{ {0, 0, 0, 0},                      {XK_m,      0, 0, 0},  setlayout,         {.v = &layouts[2]} },
	{ {0, 0, 0, 0},                      {XK_space,  0, 0, 0},  setlayout,         {0} },
	{ {ShiftMask, 0, 0, 0},              {XK_space,  0, 0, 0},  togglefloating,    {0} },
	{ {0, 0, 0, 0},                      {XK_0,      0, 0, 0},  view,              {.ui = ~0 } },
	{ {ShiftMask, 0, 0, 0},              {XK_0,      0, 0, 0},  tag,               {.ui = ~0 } },
	{ {0, 0, 0, 0},                      {XK_comma,  0, 0, 0},  focusmon,          {.i = -1 } },
	{ {0, 0, 0, 0},                      {XK_period, 0, 0, 0},  focusmon,          {.i = +1 } },
	{ {ShiftMask, 0, 0, 0},              {XK_comma,  0, 0, 0},  tagmon,            {.i = -1 } },
	{ {ShiftMask, 0, 0, 0},              {XK_period, 0, 0, 0},  tagmon,            {.i = +1 } },
	{ {0, 0, 0, 0},                      {XK_q,      0, 0, 0},  moveplace,         {.ui = WIN_NW }},
	{ {0, 0, 0, 0},                      {XK_w,      0, 0, 0},  moveplace,         {.ui = WIN_N  }},
	{ {0, 0, 0, 0},                      {XK_e,      0, 0, 0},  moveplace,         {.ui = WIN_NE }},
	{ {0, 0, 0, 0},                      {XK_a,      0, 0, 0},  moveplace,         {.ui = WIN_W  }},
	{ {0, 0, 0, 0},                      {XK_s,      0, 0, 0},  moveplace,         {.ui = WIN_C  }},
	{ {0, 0, 0, 0},                      {XK_d,      0, 0, 0},  moveplace,         {.ui = WIN_E  }},
	{ {0, 0, 0, 0},                      {XK_z,      0, 0, 0},  moveplace,         {.ui = WIN_SW }},
	{ {0, 0, 0, 0},                      {XK_x,      0, 0, 0},  moveplace,         {.ui = WIN_S  }},
	{ {0, 0, 0, 0},                      {XK_c,      0, 0, 0},  moveplace,         {.ui = WIN_SE }},
	CMDTAGKEYS(                                                 XK_1,              0)
	CMDTAGKEYS(                                                 XK_2,              1)
	CMDTAGKEYS(                                                 XK_3,              2)
	CMDTAGKEYS(                                                 XK_4,              3)
	CMDTAGKEYS(                                                 XK_5,              4)
	CMDTAGKEYS(                                                 XK_6,              5)
	CMDTAGKEYS(                                                 XK_7,              6)
	CMDTAGKEYS(                                                 XK_8,              7)
	CMDTAGKEYS(                                                 XK_9,              8)
	{ {ShiftMask|ControlMask, 0, 0, 0},  {XK_q,      0, 0, 0},  quit,              {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
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
