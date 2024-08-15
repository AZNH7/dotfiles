/* See LICENSE file for copyright and license details. */

#include <X11/XF86keysym.h> // Include the necessary header for XF86 keysyms
#include <X11/Xlib.h> // Include the necessary header for Xlib

/* appearance */
static const unsigned int refresh_rate    = 144;     /* matches dwm's mouse event processing to your monitor's refresh rate for smoother window interactions */
static const unsigned int enable_noborder = 0;      /* toggles noborder feature (0=disabled, 1=enabled) */
static const unsigned int borderpx        = 2;      /* border pixel of windows */
static const unsigned int snap            = 26;     /* snap pixel */
static const int swallowfloating          = 1;      /* 1 means swallow floating windows by default */
static const unsigned int systraypinning  = 0;      /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft   = 0;      /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing  = 5;      /* systray spacing */
static const int systraypinningfailfirst  = 1;      /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray              = 1;      /* 0 means no systray */
static const int showbar                  = 1;      /* 0 means no bar */
static const int topbar                   = 1;      /* 0 means bottom bar */
static const int floatbar                 = 1;        /* 1 means the bar will float(don't have padding),0 means the bar have padding */
static const int tag_preview        = 0;        /* 1 means enable, 0 is off */
static const int colorfultag        = 1;        /* 0 means use SchemeSel for selected non vacant tag */
#define ICONSIZE                            17      /* icon size */
#define ICONSPACING                         5       /* space between icon and title */
#define SHOWWINICON                         1       /* 0 means no winicon */
static const char *fonts[]                = { "JetBrainsMono Nerd Font Mono:size=16", "NotoColorEmoji:pixelsize=16:antialias=true:autohint=true"  };

// theme
// static const char normbordercolor[]       = "#3B4252"; // border color for unfocused window
// static const char normbgcolor[]           = "#2E3440"; // background color for unfocused windows
// static const char normfgcolor[]           = "#D8DEE9"; // foreground color for unfocused windows
// static const char selbordercolor[]        = "#434C5E"; // border color for focused windows
// static const char selbgcolor[]            = "#434C5E"; // background color for focused windows
// static const char selfgcolor[]            = "#ECEFF4"; // foreground color for focused windows

// static const char *colors[][3]      = {
// 	/*               fg           bg           border   */
// 	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
// 	[SchemeSel] =  { selfgcolor,  selbgcolor,  selbordercolor },
// };

// Define the enumeration for color schemes
enum Scheme {
    // SchemeNorm,
    // SchemeSel,
    SchemeTitle,
    TabSel,
    TabNorm,
    SchemeTag,
    SchemeTag1,
    SchemeTag2,
    SchemeTag3,
    SchemeTag4,
    SchemeTag5,
    SchemeLayout,
    SchemeBtnPrev,
    SchemeBtnNext,
    SchemeBtnClose,
    SchemeLast
};
#include "themes/onedark.h"
static const char *colors[][3]      = {
    /*                     fg       bg      border */
    [SchemeNorm]       = { gray3,   black,  gray2 },
    [SchemeSel]        = { gray4,   blue,   blue  },
    [SchemeTitle]      = { white,   black,  black }, // active window title
    [TabSel]           = { blue,    gray2,  black },
    [TabNorm]          = { gray3,   black,  black },
    [SchemeTag]        = { gray3,   black,  black },
    [SchemeTag1]       = { blue,    black,  black },
    [SchemeTag2]       = { red,     black,  black },
    [SchemeTag3]       = { orange,  black,  black },
    [SchemeTag4]       = { green,   black,  black },
    [SchemeTag5]       = { pink,    black,  black },
    [SchemeLayout]     = { green,   black,  black },
    [SchemeBtnPrev]    = { green,   black,  black },
    [SchemeBtnNext]    = { yellow,  black,  black },
    [SchemeBtnClose]   = { red,     black,  black },
};
/* Define color schemes */
// enum { SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5, SchemeTag6, SchemeTag7, SchemeTag8, SchemeTag9 }; // Add SchemeTag4 here

// static const char *colors[][3]      = {
//     /*               fg         bg         border   */
//     [SchemeNorm] = { "#bbbbbb", "#222222", "#444444" },
//     [SchemeSel]  = { "#eeeeee", "#005577", "#005577" },
//     [SchemeTag1] = { "#ff0000", "#000000", "#000000" },
//     [SchemeTag2] = { "#00ff00", "#000000", "#000000" },
//     [SchemeTag3] = { "#0000ff", "#000000", "#000000" },
//     [SchemeTag4] = { "#00ffff", "#000000", "#000000" }, // Define colors for SchemeTag4
//     [SchemeTag5] = { "#ffff00", "#000000", "#000000" },
//     [SchemeTag6] = { "#ff00ff", "#000000", "#000000" },
//     [SchemeTag7] = { "#ffffff", "#000000", "#000000" },
//     [SchemeTag8] = { "#000000", "#ffffff", "#ffffff" },
//     [SchemeTag9] = { "#ff8800", "#000000", "#000000" },
// };

static const char *const autostart[] = {
  "xset", "s", "off", NULL,
  "xset", "s", "noblank", NULL,
  "xset", "-dpms", NULL,
  "dbus-update-activation-environment", "--systemd", "--all", NULL,
  "flameshot", NULL,
  "systemctl", "--user", "restart", "pipewire", NULL,
  "systemctl", "--user", "restart", "pipewire-pulse", NULL,
  "exec", "dbus-update-activation-environment --all", NULL,
  "dunst", "-config", "/home/$USER/.config/dunst/dunstrc", NULL,
  "picom", "--animations", "-b", NULL,
  "sh", "-c", "feh --randomize --bg-fill /home/$USER/.config/wallpapers/*", NULL,
  "sh", "-c", "./Nextcloud/git_repos/aznh7/dotfiles/laptop/dwm-preconfigured/scripts/status", NULL,
  "slstatus", NULL,
  "nextcloud", NULL,
  "solaar", "-w", "hide", NULL,
  "nm-applet", "--indicator", NULL,
  "blueman-applet", NULL,
  "volumeicon", NULL,
  "unclutter", NULL,
  "conky", "-c", "/home/$USER/.config/conky/qtile/gruvbox-dark-01.conkyrc", NULL,
  "rsync", "-avp", "--exclude={home_server, Nextcloud, gom, .cache, .conda, .cargo, Games, games, .local/share, .config/heroic, .rustup}", "/home/$USER/", "home_server/$USER-work/laptop_backup/flink/$(date +%Y-%m-%d)", NULL,
};

/* tagging */
// static const char *tags[] = { "", "", "", "", "" };
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// // eww tags for each workspace
// static const char *eww_tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

// static const char* eww[] = { "eww", "open" , "eww", NULL };

// static const Launcher launchers[] = {
//     /* command     name to display */
//     { eww,         "" },
// };

static const char ptagf[] = "[%s %s]";  /* format of a tag label */
static const char etagf[] = "[%s]";     /* format of an empty tag */
static const int lcaselbl = 0;          /* 1 means make tag label lowercase */

static const int tagschemes[] = {
    SchemeTag1, SchemeTag2, SchemeTag3, SchemeTag4, SchemeTag5
};

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
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
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

static Key keys[] = {
	/* modifier                     key            function                argument */
	{ MODKEY,                       XK_d,          spawn,                  {.v = launchercmd} }, // spawn rofi for launching other programs
	{ MODKEY,                       XK_Return,     spawn,                  {.v = termcmd } }, // spawn a terminal
	{ MODKEY|ShiftMask,             XK_b,          spawn,				   {.v = browsercmd}}, // open firefox profile
	{ MODKEY|ControlMask,			XK_l,		   spawn,				   SHCMD ("./Nextcloud/git_repos/aznh7/dotfiles/laptop/dwm-preconfigured/scripts/lock") }, // i3lock 
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
	{ MODKEY|ShiftMask,             XK_h,          setcfact,               {.f = +0.25} }, // increase size respective to other windows within the same area
	{ MODKEY|ShiftMask,             XK_l,          setcfact,               {.f = -0.25} }, // decrease client size respective to other windows within the same area
	{ MODKEY|ShiftMask,             XK_o,          setcfact,               {.f =  0.00} }, // reset client area
	{ MODKEY,                       XK_x,          zoom,                   {0} }, // moves the currently focused window to/from the master area (for tiled layouts)
	{ MODKEY,                       XK_Tab,        view,                   {0} }, // view last focused tag
	{ MODKEY|ShiftMask,             XK_c,          killclient,             {0} }, // close the currently focused window
	{ MODKEY,                       XK_t,          setlayout,              {.v = &layouts[0]} }, // set tile layout
	{ MODKEY|ShiftMask,             XK_t,          setlayout,              {.v = &layouts[2]} }, // set floating layout
	{ MODKEY,                       XK_f,          fullscreen,             {0} }, // toggles fullscreen for the currently selected client
	{ MODKEY,                       XK_space,      setlayout,              {0} }, // toggles between current and previous layout
	{ MODKEY|ShiftMask,             XK_m,          togglefloating,         {0} }, // toggles between tiled and floating arrangement for the currently focused client
	{ MODKEY|ShiftMask,             XK_y,          togglefakefullscreen,   {0} }, // toggles "fake" fullscreen for the selected window
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
	{ MODKEY,                       XK_b,          spawn,                  SHCMD("blueman-manager") }, // spawn blueman-manager				
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
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin,         MODKEY,         Button1,        moveorplace,    {.i = 2} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	// new click
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
};
