/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int refresh_rate    = 144;     /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int borderpx        = 1;        /* border pixel of windows */
static const unsigned int snap            = 26;       /* snap pixel */
static const int swallowfloating          = 1;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;   /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 5;   /* systray spacing */
static const int systraypinningfailfirst  = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;        /* 0 means no systray */
static const int showbar                  = 1;        /* 0 means no bar */
static const int topbar                   = 1;        /* 0 means bottom bar */
#define ICONSIZE 20   /* icon size */
#define ICONSPACING 5 /* space between icon and title */
#define SHOWWINICON 1       /* 0 means no winicon */
static const char *fonts[]          = { "MesloLGS Nerd Font Mono:size=15", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true"  };
static const char dmenufont[]       = "MesloLGS Nerd Font Mono:size=16";
static const char col_gray1[]       = "#222222"; // background color for unfocused windows is dark gray
static const char col_gray2[]       = "#444444"; // border color for unfocused windows is dark gray
static const char col_gray3[]       = "#bbbbbb"; // foreground color for unfocused windows is light gray
static const char col_gray4[]       = "#eeeeee"; // background color for focused windows is light gray
static const char col_cyan[]        = "#005577"; // border color for focused windows is cyan
static const char col_red[]         = "#ff0000"; // border color for focused windows is red
static const char col_black[]       = "#000000"; // background color for focused windows is black
static const char white[]           = "#ffffff"; // background color for focused windows is black

// Define the enumeration for color schemes
enum Scheme {
    // SchemeNorm,
    // SchemeSel,
    SchemeTitle,
    TabSel,
    // TabNorm,
};

static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { white, col_black, col_black }, 
	[SchemeSel]  = { white, col_cyan,  col_black }, 
	[SchemeTitle] = { white, col_black,  col_black  },
	// [TabSel] = { white, col_cyan,  col_black },
	[SchemeStatus]  = { white, col_black,  col_black  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { white, col_cyan,  col_cyan  }, // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsNorm]  = { white, col_black,  col_black  }, // Tagbar left unselected {text,background,not used but cannot be empty}
	// [SchemeInfoSel]  = { col_black, col_black,  col_black  }, // infobar middle  selected {text,background,not used but cannot be empty}
	// [SchemeInfoNorm]  = { col_black, col_gray1,  col_black  }, // infobar middle  unselected {text,background,not used but cannot be empty}
};

static const char *const autostart[] = {
  "xset", "s", "off", NULL,
  "xset", "s", "noblank", NULL,
  "xset", "-dpms", NULL,
  "dbus-update-activation-environment", "--systemd", "--all", NULL,
  "sh", "-c", "./Nextcloud/git_repos/aznh7/dotfiles/desktop/dwm/scripts/status_v2", NULL,
  "flameshot", NULL,
  "dunst", "-config", "/home/$USER/.config/dunst/dunstrc", NULL,
  "picom", NULL,
  "sh", "-c", "feh --randomize --bg-fill /home/$USER/.config/wallpapers/*", NULL,
  "slstatus", NULL,
  "nextcloud", NULL,
  "solaar", "-w", "hide", NULL,
  "nm-applet", "--indicator", NULL,
  "blueman-applet", NULL,
  "unclutter", NULL,
  "conky", "-c", "/home/$USER/.config/conky/qtile/gruvbox-dark-01.conkyrc", NULL,
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "St",      NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "eww",     NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ "firefox", NULL, 	   NULL, 		   2 << 9, 	  0,    	  0,  	       0, 		 -1 },
	{ "kitty",   NULL,     NULL,           1 << 2,    0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile },    /* first entry is default */
	{ "",      NULL },    /* no layout function means floating behavior */
	{ "",      monocle },
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

#define STATUSBAR "dwmblocks"

/* commands */
static const char *launchercmd[] = { "rofi", "-show", "drun", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *browsercmd[] = { "firefox", "-p", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = launchercmd} }, // spawn rofi for launching other programs
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } }, // spawn a terminal
	// { MODKEY|ShiftMask,             XK_b,          spawn,                  SHCMD ("xdg-open https://")}, // open default browser
	{ MODKEY|ShiftMask,             XK_b,          spawn,				   {.v = browsercmd}}, // open firefox profile
	{ MODKEY,                       XK_p,          spawn,                  SHCMD ("flameshot full -p /home/$USER/Screenshots/")}, // capture full screen screenshot
	{ MODKEY|ShiftMask,             XK_p,          spawn,                  SHCMD ("flameshot gui -p /home/$USER/Screenshots/")}, // open flameshot gui for screenshot selection
	{ MODKEY|ControlMask,           XK_p,          spawn,                  SHCMD ("flameshot gui --clipboard")}, // copy screenshot to clipboard
	{ MODKEY|ShiftMask,             XK_f,          spawn,                  SHCMD ("thunar")}, // open thunar file manager
	{ MODKEY,                       XK_w,          spawn,                  SHCMD ("looking-glass-client -F")}, // start Looking glass
	{ 0,                            0x1008ff02,    spawn,                  SHCMD ("xbacklight -inc 10")}, // increase backlight brightness
	{ 0,                            0x1008ff03,    spawn,                  SHCMD ("xbacklight -dec 10")}, // decrease backlight brightness
	{ 0,                            0x1008ff1b,    spawn,                  SHCMD ("xbacklight -inc 10")}, // increase backlight brightness
	{ 0,                            0x1008ff8e,    spawn,                  SHCMD ("xbacklight -dec 10")}, // decrease backlight brightness
	{ 0,                            0x1008ff11,    spawn,                  SHCMD ("amixer sset Master 5%- unmute")}, // unmute volume
	{ 0,                            0x1008ff12,    spawn,                  SHCMD ("amixer sset Master $(amixer get Master | grep -q '\\[on\\]' && echo 'mute' || echo 'unmute')")}, // toggle mute/unmute
	{ 0,                            0x1008ff13,    spawn,                  SHCMD ("amixer sset Master 5%+ unmute")}, // unmute volume
	{ MODKEY,                       XK_m,          togglebar,              {0} }, // toggle bar visibility
	{ MODKEY,                       XK_j,          focusstack,             {.i = +1 } }, // focus on the next client in the stack
	{ MODKEY,                       XK_k,          focusstack,             {.i = -1 } }, // focus on the previous client in the stack
	{ MODKEY|ShiftMask,             XK_j,          movestack,              {.i = +1 } }, // move stack up
	{ MODKEY|ShiftMask,             XK_k,          movestack,              {.i = -1 } }, // move stack down
	{ MODKEY,                       XK_i,          incnmaster,             {.i = +1 } }, // decrease the number of clients in the master area
	{ MODKEY,                       XK_z,          incnmaster,             {.i = -1 } }, // increase the number of clients in the master area
	{ MODKEY,                       XK_h,          setmfact,               {.f = -0.05} }, // decrease the size of the master area compared to the stack area(s)
	{ MODKEY,                       XK_l,          setmfact,               {.f = +0.05} }, // increase the size of the master area compared to the stack area(s)
	// { MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} }, // increase size respective to other windows within the same area
	// { MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} }, // decrease client size respective to other windows within the same area
	// { MODKEY|ShiftMask,             XK_o,          setcfact,               {.f =  0.00} }, // reset client area
	{ MODKEY,                       XK_x,          zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
	{ MODKEY,                       XK_Tab,        view,                   {0} }, // view last focused tag
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} }, // close the currently focused window
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} }, // set tile layout
	{ MODKEY|ShiftMask,             XK_t,          setlayout,              {.v = &layouts[2]} }, // set floating layout
	{ MODKEY,                       XK_f,          fullscreen,             {0} }, // toggles fullscreen for the currently selected client
	{ MODKEY,                       XK_space,      setlayout,              {0} }, // toggles between current and previous layout
	{ MODKEY|ShiftMask,             XK_m,          togglefloating,         {0} }, // toggles between tiled and floating arrangement for the currently focused client
	// { MODKEY|ShiftMask,             `,          togglefakefullscreen,   {0} }, // toggles "fake" fullscreen for the selected window
	{ MODKEY,                       XK_0,          view,                   {.ui = ~0 } }, // view all tags on the current monitor
	{ MODKEY,                       XK_comma,      focusmon,               {.i = -1 } }, // focus on the previous monitor, if any
	{ MODKEY,                       XK_period,     focusmon,               {.i = +1 } }, // focus on the next monitor, if any
	{ MODKEY|ShiftMask,             XK_comma,      tagmon,                 {.i = -1 } }, // tag previous monitor
	{ MODKEY|ShiftMask,             XK_period,     tagmon,                 {.i = +1 } }, // tag next monitor
	{ MODKEY,                       XK_n,          spawn,                  SHCMD("dunstctl history-pop")}, // show last notification
	{ MODKEY|ShiftMask,             XK_n,          spawn,                  SHCMD("dunstctl close-all")}, // close all notifications
	{ MODKEY|ShiftMask,				XK_w,		   spawn, 				   SHCMD("feh --randomize --bg-fill /home/$USER/.config/wallpapers/*") }, // change wallpaper
	{ MODKEY,                       XK_r,          spawn,                  SHCMD("dmenu_run") }, // spawn dmenu
	{ MODKEY,                       XK_a,          spawn,                  SHCMD("pavucontrol") }, // spawn pavucontrol
	{ MODKEY,                       XK_o,          spawn,                  SHCMD("obs") }, // spawn obs
	{ MODKEY,                       XK_q,          spawn,                  SHCMD("qutebrowser") }, // spawn qutebrowser
	{ MODKEY,                       XK_u,          spawn,                  SHCMD("ulauncher") }, // spawn ulauncher
	{ MODKEY,                       XK_i,          spawn,                  SHCMD("flameshot gui") }, // spawn flameshot
	{ MODKEY,                       XK_b,          spawn,                  SHCMD("blueman-manager") }, // spawn blueman-manager
	{ MODKEY,                       XK_F2,         spawn,                  SHCMD("dmenupower") }, // spawn dmenupower
	{ MODKEY,                       XK_F3,         spawn,                  SHCMD("dmenurecent") }, // spawn dmenurecent
	{ MODKEY,                       XK_F4,         spawn,                  SHCMD("dmenuemoji") }, // spawn dmenuemoji					
	TAGKEYS(                        XK_1,                                  0)
	TAGKEYS(                        XK_2,                                  1)
	TAGKEYS(                        XK_3,                                  2)
	TAGKEYS(                        XK_4,                                  3)
	TAGKEYS(                        XK_5,                                  4)
	TAGKEYS(                        XK_6,                                  5)
	TAGKEYS(                        XK_7,                                  6)
	TAGKEYS(                        XK_8,                                  7)
	TAGKEYS(                        XK_9,                                  8)
	{ MODKEY|ShiftMask,             XK_0,          tag,                    {.ui = ~0 } }, // tag all tags on the current monitor
	{ MODKEY|ShiftMask,             XK_q,          quit,                   {0} }, // exit dwm
	{ MODKEY|ControlMask,           XK_q,          spawn,                  SHCMD("$HOME/.config/rofi/powermenu.sh")}, // exit dwm
	{ MODKEY|ShiftMask,			    XK_r,          spawn,                  SHCMD("systemctl reboot")}, // reboot system
	{ MODKEY|ControlMask|ShiftMask, XK_s,          spawn,                  SHCMD("systemctl suspend")}, // suspend system
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button1,        sigstatusbar,   {.i = 1} },
	{ ClkStatusText,        0,              Button2,        sigstatusbar,   {.i = 2} },
	{ ClkStatusText,        0,              Button3,        sigstatusbar,   {.i = 3} },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
