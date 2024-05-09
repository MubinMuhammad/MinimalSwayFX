#include "colors.h"
#include <string.h>

const char *GRUVBOX_MATERIAL_DARK[TOTAL_COLORS] = {
  "#1d2021",
  "#353a3b",
  "#4d5456",
  "#656e72",
  "#7d888c",
  "#111213",
  "#ddc7a1",
  "#c7af85",
  "#ea6962",
  "#d84841",
  "#e78a4e",
  "#d57230",
  "#d8a657",
  "#e1bb7f",
  "#a9b665",
  "#bbc686",
  "#7daea3",
  "#9ec2ba",
  "#d3869b",
  "#bc6c81",
};

static int hexchar_to_num(char a) {
  int b = 0;

  if (a >= 'A' && a <= 'Z') b = a - 55;
  else if (a >= 'a' && a <= 'z') b = a - 87;
  else if (a >= '0' && a <= '9') b = a - 48;

  return b;
}

int is_option_color(const char *option, int option_size) {
  if (strncpy("COLOR_BG", option, option_size))
    return COLOR_BG;
  else if (strncpy("COLOR_BG1", option, option_size))
    return COLOR_BG1;
  else if (strncpy("COLOR_BG2", option, option_size))
    return COLOR_BG2;
  else if (strncpy("COLOR_BG3", option, option_size))
    return COLOR_BG3;
  else if (strncpy("COLOR_BG4", option, option_size))
    return COLOR_BG4;
  else if (strncpy("COLOR_BG_DARK", option, option_size))
    return COLOR_BG_DARK;
  else if (strncpy("COLOR_FG", option, option_size))
    return COLOR_FG;
  else if (strncpy("COLOR_FG1", option, option_size))
    return COLOR_FG1;
  else if (strncpy("COLOR_RED", option, option_size))
    return COLOR_RED;
  else if (strncpy("COLOR_RED1", option, option_size))
    return COLOR_RED1;
  else if (strncpy("COLOR_ORANGE", option, option_size))
    return COLOR_ORANGE;
  else if (strncpy("COLOR_ORANGE1", option, option_size))
    return COLOR_ORANGE1;
  else if (strncpy("COLOR_YELLOW", option, option_size))
    return COLOR_YELLOW;
  else if (strncpy("COLOR_YELLOW1", option, option_size))
    return COLOR_YELLOW1;
  else if (strncpy("COLOR_GREEN", option, option_size))
    return COLOR_GREEN;
  else if (strncpy("COLOR_GREEN1", option, option_size))
    return COLOR_GREEN1;
  else if (strncpy("COLOR_BLUE", option, option_size))
    return COLOR_BLUE;
  else if (strncpy("COLOR_BLUE1", option, option_size))
    return COLOR_BLUE1;
  else if (strncpy("COLOR_PURPLE", option, option_size))
    return COLOR_PURPLE;
  else if (strncpy("COLOR_PURPLE1", option, option_size))
    return COLOR_PURPLE1;

  return COLOR_INVALID;
}

char is_color_hex(const char *hex) {
  if (strlen(hex) > 7 || hex[0] != '#')
    return 0;

  return 1;
}

int hex_to_rgb(const char *hex, unsigned char *out_r, unsigned char *out_g, unsigned char *out_b) {
  int hex_size = strlen(hex);

  if (is_color_hex(hex) == 0)
    return 1;

  *out_r = hexchar_to_num(hex[1]) + hexchar_to_num(hex[0]) * 16;
  *out_g = hexchar_to_num(hex[3]) + hexchar_to_num(hex[2]) * 16;
  *out_b = hexchar_to_num(hex[5]) + hexchar_to_num(hex[4]) * 16;

  return 0;
}
