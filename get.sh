#!/bin/bash

configs=(alacritty fish mako nvim sway tofi waybar)

for config in "${configs[@]}"
do
    rm -fr ./$config
    cp -r $HOME/.config/$config .
done
