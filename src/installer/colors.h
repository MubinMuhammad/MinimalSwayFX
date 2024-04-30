#ifndef _COLORS_H_
#define _COLORS_H_

// Internal code, Don't Edit

enum {
  COLOR_BG,
  COLOR_BG1, // brighter/darker background (for borders)
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
const char *GRUVBOX_MATERIAL_DARK[] = {
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
