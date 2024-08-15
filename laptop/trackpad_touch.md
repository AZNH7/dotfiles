To enable taping on touchpad, create a file /etc/X11/xorg.conf.d/30-touchpad.conf:

```
Section "InputClass"
        Identifier "touchpad catchall"
        Driver "libinput"
        Option "Tapping" "on"
EndSection
```

To get natural scrolling with touchpad, edit /usr/share/X11/xorg.conf.d/40-libinput.conf file:

```
Section "InputClass"
        Identifier "libinput touchpad catchall"
        MatchIsTouchpad "on"
        MatchDevicePath "/dev/input/event*"
        Driver "libinput"
        Option "NaturalScrolling" "True"
EndSection
```
