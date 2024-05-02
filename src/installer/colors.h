#ifndef _COLORS_H_
#define _COLORS_H_

// Internal code, Don't Edit

#define TOTAL_COLORS 16

enum {
  COLOR_BG = 0,
  COLOR_BG1, // darker background (for inactive borders)
  COLOR_BG2, // shades of gray
  COLOR_BG3,
  COLOR_BG4,
  COLOR_FG,
  COLOR_FG1,
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
  "#111213",
  "#292d2e",
  "#353a3b",
  "#4d5456",
  "#ddc7a1",
  "#a89984",
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
