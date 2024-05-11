#ifndef _COLORS_H_
#define _COLORS_H_


/*
 * if you're in light mode:
 *   the enum of colors BG ending
 *   with 1..n should be darker.
 *   and the FG should be brigher.
 * if you're in dark mode:
 *   the enum of colors BG ending
 *   with 1..n should be brighter.
 *   and the FG should be darker.
 *
 * the COLOR_BG_DARK is an exception
 * it should be darker then the bg.
 * */

#define TOTAL_COLORS 20

enum {
  COLOR_BG = 0,
  COLOR_BG1,
  COLOR_BG2,
  COLOR_BG3,
  COLOR_BG4,
  COLOR_BG_DARK,
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
  COLOR_PURPLE1,
  COLOR_INVALID
};

/*
 * for the colors ending with 1,
 * if L (L of HSL) >=
 * greater than 61 decrease the L & S by
 * otherwise increase the L by 10.
 * */
extern const char *GRUVBOX_MATERIAL_DARK[TOTAL_COLORS];

// function declarations
int is_option_color(const char *option, int option_size);
char is_color_hex(const char *hex);
int hex_to_rgba_str(const char *hex, float alpha, char *out_rgb_format);

#endif
