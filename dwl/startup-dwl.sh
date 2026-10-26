#!/usr/bin/env bash

# close stdin
exec <&-

# set wallpaper to pitch black
swaybg -c 000000 &
# start waybar top bar
waybar &
wl-paste --watch cliphist store &

