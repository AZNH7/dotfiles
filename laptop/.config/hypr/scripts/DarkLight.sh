#!/bin/bash
set -x
# Define the path
wallpaper_path="$HOME/.config/hqtile/wallpapers"
hypr_config_path="$HOME/.config/hypr"

# Define the GTK themes for light and dark modes
# Catppuccin
#light_gtk_theme="Catppuccin-Latte-Standard-Mauve-light"
#dark_gtk_theme="Catppuccin-Mocha-Standard-Mauve-dark"
#light_icon_theme="Shiny-Light-Icons"
#dark_icon_theme="Shiny-Dark-Icons"

# Mac-OS Like
#light_gtk_theme="Mojave-Light"
#dark_gtk_theme="Mojave-Dark"
#light_icon_theme="McMojave-circle"
#dark_icon_theme="McMojave-circle-dark"

pkill swaybg

# Initialize swww if needed
swww query || swww init

# Set swww options
swww="swww img"
effect="--transition-bezier .43,1.19,1,.4 --transition-fps 60 --transition-type grow --transition-pos 0.925,0.977 --transition-duration 2"

# Define functions for notifying user and updating symlinks
notify_user() {
	notify-send -h string:x-canonical-private-synchronous:sys-notify -u normal "Switching to $1 mode"
}

# Determine the current wallpaper mode by checking a configuration file
if [ "$(cat ~/.wallpaper_mode)" = "light" ]; then
  current_mode="light"
  next_mode="dark"
else
  current_mode="dark"
  next_mode="light"
fi
path_param=$(echo $next_mode | sed 's/.*/\u&/')

notify_user "$next_mode"
ln -sf "${hypr_config_path}/waybar/style/style-${next_mode}.css" "${hypr_config_path}/waybar/style.css"
ln -sf "${hypr_config_path}/mako/styles/config-${next_mode}" "${hypr_config_path}/mako/config"
ln -sf "${hypr_config_path}/wofi/styles/style-${next_mode}.css" "${hypr_config_path}/wofi/style.css"

gtk_theme="${next_mode}_gtk_theme"
icon_theme="${next_mode}_icon_theme"

gsettings set org.gnome.desktop.interface gtk-theme "${!gtk_theme}"
gsettings set org.gnome.desktop.interface icon-theme "${!icon_theme}"

# Find the next wallpaper if one exists
current_wallpaper="$(cat ~/.current_wallpaper)"
next_wallpaper="${current_wallpaper/_"$current_mode"/_"$next_mode"}"

if ! [ -f "$next_wallpaper" ]; then
  next_wallpaper="$(find "${wallpaper_path/"${path_param}"}" -type f -iname "*_"${next_mode}".jpg" -print0 | shuf -n1 -z | xargs -0)"
fi

$swww "${next_wallpaper}" $effect

# Update the configuration file to reflect the new wallpaper mode and current wallpaper
echo "$next_mode" > ~/.43
echo "$next_wallpaper" > ~/.current_wallpaper

sleep 2
exec ~/.config/hypr/scripts/Startup.sh &
