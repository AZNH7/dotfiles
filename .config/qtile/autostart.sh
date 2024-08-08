#!/usr/bin/env bash

# picom --experimental-backends --config /home/aziz/.config/picom/picom.conf &
picom --config /home/aziz/.config/picom/picom.conf &
# xrandr --output DP-1 --primary --mode 2560x1440 --pos 2560x0 --rotate normal --rate 240 --output DP-2 --mode 2560x1440 --pos 0x0 --rotate normal --rate 144 --output HDMI-A-0 --off --output HDMI-A-1 --off
xrandr --output DisplayPort-0 --primary --mode 2560x1440 --pos 2560x0 --rotate normal --rate 240 --output DisplayPort-1 --mode 2560x1440 --pos 0x0 --rotate normal --rate 144 --output HDMI-A-0 --off --output HDMI-A-1 --off
blueman-applet &
# xscreensaver -no-splash &
unclutter &
solaar -w hide & 
# cpupower-gui -p &
conky -c ~/.config/conky/qtile/gruvbox-dark-01.conkyrc &
dunst &
nitrogen --restore &
nextcloud &
# variety &
killall volumeicon &
volumeicon &
nm-applet &
xset s off -dpms &
# gphoto2 --stdout --capture-movie | ffmpeg -i - -vcodec rawvideo -pix_fmt yuv420p -threads 0 -f v4l2 /dev/video0 &
# modprobe v4l2loopback &
rsync -avp --exclude={home_server, Nextcloud, gom, .cache, .conda, .cargo, Games, games, .local/share, .config/heroic, .rustup} /home/aziz/ home_server/PC-backups/personal_PC_rsync/$(date +%Y-%m-%d)
