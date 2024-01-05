/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int gappx     = 5;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font Mono:style:medium:size=11", "SymbolsNerdFont:size=14:antialias=true:autohint=true", "NotoColorEmoji:size=11:antialias=true:autohint=true" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font Mono:style:medium:size=11";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
static const char col_cyan[]        = "#005577";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

/* tagging */
/*                         Arch Discord Firefox Remote Steam VSC*/
static const char *tags[] = { "󰣇", "󰙯", "", "󰢹", "󰓓", "󰨞" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class               instance    title       tags mask     isfloating   monitor */
	{ "discord",  		   NULL,	   NULL,	   1 << 1,       0,           -1 },
	{ "firefox",  		   NULL,       NULL,       1 << 2,       0,           -1 },
	{ "Nxplayer.bin",      NULL,       NULL,       1 << 3,       0,           -1 },
	{ "steam",  		   NULL,       NULL,       1 << 4,       0,           -1 },
	{ "Code",  			   NULL,       NULL,       1 << 5,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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

/* commands */
static const char *dmenucmd[]   = { "dmenu_run", "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]    = { "st", NULL };

/* apps */
static const char *discord[]    = { "discord", NULL };
static const char *firefox[]    = { "firefox", NULL };
static const char *nomachine[]  = { "nomachine-client", NULL };
static const char *steam[]      = { "steam", NULL };
static const char *code[]       = { "code", NULL };

/* tagfun */
static struct {
	void (*func)(const Arg *arg);
	const Arg arg;
} tagfun_cmds[LENGTH(tags)] = {
	[1] = { spawn, { .v = discord } },
	[2] = { spawn, { .v = firefox } },
	[3] = { spawn, { .v = nomachine } },
	[4] = { spawn, { .v = steam } },
	[5] = { spawn, { .v = code } },
};

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_l,         setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_k,         focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_j,         focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_h,         setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_g,         togglebar,      {0} },
	{ MODKEY,                       XK_f,	      zoom,           {0} },
	{ MODKEY,                       XK_d,         incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_s,         incnmaster,     {.i = +1 } },
	{ MODKEY,		                XK_q,         killclient,     {0} },
	{ MODKEY,                       XK_w,         setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_e,         setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,         setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_r,  	      togglefloating, {0} },
	{ MODKEY,                       XK_t,  	      setlayout,      {0} },
	{ MODKEY,                       XK_space,     spawn,          {.v = dmenucmd } },
	{ MODKEY,			            XK_Return,    spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_Tab,       view,           {0} },
	{ MODKEY,                       XK_agrave,    view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_agrave,    tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,     focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_semicolon, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,     tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_semicolon, tagmon,         {.i = +1 } },
	{ MODKEY,			            XK_minus,     setgaps,	      {.i = -1 } },
	{ MODKEY,			            XK_equal,     setgaps,	      {.i = +1 } },
	{ MODKEY|ShiftMask,		        XK_equal,     setgaps,	      {.i =  0 } },
	TAGKEYS(                        XK_ampersand,                 0)
	TAGKEYS(                        XK_eacute,                    1)
	TAGKEYS(                        XK_quotedbl,                  2)
	TAGKEYS(                        XK_apostrophe,                3)
	TAGKEYS(                        XK_parenleft,                 4)
	TAGKEYS(                        XK_minus,                     5)
	TAGKEYS(                        XK_egrave,                    6)
	TAGKEYS(                        XK_underscore,                7)
	TAGKEYS(                        XK_ccedilla,                  8)
	{ MODKEY|ShiftMask,		        XK_q,         quit,          {0} },
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
	{ ClkTagBar,            0,              Button2,        tagfun,         {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

