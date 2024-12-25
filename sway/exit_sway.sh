#!/bin/bash

swaynag \
    -t warning \
    --text "#1d2021" \
    --button-text "#1d2021" \
    --background "#daac62" \
    --button-background "#d8a657" \
    --border "#cf9230" \
    -f "iosevka nerd font 12" \
    -m "Exit Sway?" \
    -B "Yes, exit Sway" "swaymsg exit"
