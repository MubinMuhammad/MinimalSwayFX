#ifndef _COLORS_H_
#define _COLORS_H_

/*
 * the config pattern I followed in this code:
 * 1. sway (or swayfx)
 * 2. waybar (or i3status-rs)
 * 3. tofi
 * 4. mako
 * 5. alacritty
 * 6. fish
 * 7. neofetch
 * */

enum {
  COLOR_BG,
  COLOR_BG1, // brighter background (for borders)
  COLOR_FG,
  COLOR_RED,
  COLOR_RED1,
  COLOR_ORANGE,
  COLOR_ORANGE1,
  COLOR_YELLOW,
  COLOR_YELLOW1,
  COLOR_GREEN,
  COLOR_GREEN1,
  COLOR_BLUE,
  COLOR_BLUE1,
  COLOR_PURPLE,
  COLOR_PURPLE1
};

/*
 * for the colors ending with 1,
 * if the lightness (L of HSL) is
 * greater than 61 decrease the l by
 * 5 otherwise increase it by 5.
 * */
const char *gruvbox_material_dark_colors[] = {
  "#1d2021",
  "#292d2e",
  "#ddc7a1",
  "#ea6962",
  "#e7534b",
  "#e78a4e",
  "#ea9b66",
  "#d8a657",
  "#ddb36e",
  "#a9b665",
  "#b1be74",
  "#7daea3",
  "#8eb8af",
  "#d3869b",
  "#cd748c",
};

#endif
