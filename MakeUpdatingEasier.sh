#!/bin/env bash

cfgDir=$HOME/.config

rm -fr alacritty fish i3status mako neofetch nvim sway tofi waybar
cp -r $cfgDir/alacritty $cfgDir/fish $cfgDir/i3status $cfgDir/mako \
  $cfgDir/neofetch $cfgDir/nvim $cfgDir/sway $cfgDir/tofi $cfgDir/waybar .
