#!/bin/env bash

configArray=("alacritty" "fish" "i3status" \
             "mako" "neofetch" "nvim" "sway" \
             "tofi" "waybar")

configDir=$HOME/.config

printf "\n------Installation Begins------\n\n"

# if any of the above mentioned
# config exists in teh system,
# move the config to a $config_bak
# folder.
for config in "${configArray[@]}"; do
  if [ -d "$configDir/$config" ]; then
    echo "$configDir/$config -> $configDir/${config}_bak"
    mv $configDir/$config $configDir/${config}_bak
  fi
done

# copy my config to the ~/.config
# folder.
for config in "${configArray[@]}"; do
  cp -r ./$config $configDir/${config}
done

printf "\n-------Installation Ends-------\n\n"
