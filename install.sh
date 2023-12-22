#!/bin/env bash

function write_config() {
  cfg_dir=$HOME/.config/$1
  cfg_dir_bak=$HOME/.config/$1.bak

  if [ -d $cfg_dir ]
  then
    if [ -d $cfg_dir_bak ]
    then
      rm -fr $cfg_dir_bak
    fi

    mv $cfg_dir $cfg_dir_bak
    echo "old $cfg_dir -> $cfg_dir_bak"
  fi

  mkdir $cfg_dir
  cp -r ./$1/* $cfg_dir
}

write_config sway
write_config mako
write_config i3status
write_config alacritty
write_config wallpapers
