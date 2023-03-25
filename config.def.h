/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 1;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
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

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenumgd } },
	{ MODKEY|ControlMask|ShiftMask, XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          SHCMD("passmenu") },
	{ MODKEY,                       XK_b,      spawn,          {.v = web } },
	{ MODKEY|ShiftMask,             XK_t,      spawn,          TRMCMD("top") },
	{ MODKEY,                       XK_r,      spawn,          TRMCMD("calc") },
	{ MODKEY,                       XK_f,      spawn,          TRMCMD("launch_nnn.sh") },
	{ MODKEY|ControlMask,           XK_c,      spawn,          SHCMD("launch_cmus.sh") },
	{ MODKEY|ControlMask,           XK_b,      spawn,          SHCMD("cmus-remote -n") },
	{ MODKEY|ControlMask,           XK_z,      spawn,          SHCMD("cmus-remote -r") },
	{ MODKEY|ControlMask,           XK_m,      spawn,          SHCMD("cmus-remote -C 'toggle aaa_mode'") },
	{ MODKEY,                       XK_n,      spawn,          {.v = guimail } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          TRMCMD("neomutt") },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      inplacerotate,  {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      inplacerotate,  {.i = -1} },
	{ MODKEY|ControlMask|ShiftMask, XK_j,      inplacerotate,  {.i = +2} },
	{ MODKEY|ControlMask|ShiftMask, XK_k,      inplacerotate,  {.i = -2} },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.03} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.03} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.15} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.15} },
	{ MODKEY|ControlMask|ShiftMask, XK_i,      setcfact,       {.f =  0.00} },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ControlMask|ShiftMask,	XK_l,	   spawn,          {.v = slock } },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },/*Tiled*/
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },/*Floating*/
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },/*Monocle*/
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	{ MODKEY,                       XK_q,      moveplace,      {.ui = WIN_NW }},
	{ MODKEY,                       XK_w,      moveplace,      {.ui = WIN_N  }},
	{ MODKEY,                       XK_e,      moveplace,      {.ui = WIN_NE }},
	{ MODKEY,                       XK_a,      moveplace,      {.ui = WIN_W  }},
	{ MODKEY,                       XK_s,      moveplace,      {.ui = WIN_C  }},
	{ MODKEY,                       XK_d,      moveplace,      {.ui = WIN_E  }},
	{ MODKEY,                       XK_z,      moveplace,      {.ui = WIN_SW }},
	{ MODKEY,                       XK_x,      moveplace,      {.ui = WIN_S  }},
	{ MODKEY,                       XK_c,      moveplace,      {.ui = WIN_SE }},
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
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
