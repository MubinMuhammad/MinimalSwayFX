#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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
  false = 0,
  true = !false
};

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

void print_error_msg(const char *msg) {
  system("clear");
  printf(
    "\033[0;31mError\033[0;0m\n"
    "-----\n"
    "You have provided invalid input.\n%s", msg
  );
}

char is_color_hex(const char *hex, int hex_size) {
  if (hex_size > 6 && hex[0] != '#')
    return false;

  return true;
}

int main() {
  char input_char = 0;
  char input_str[100];
  unsigned int state = 0;
  const char *home_dir = getenv("HOME");

  FILE *read_fp = NULL;
  FILE *write_fp = NULL;
  char line_buffer[200];

  system("clear");
  printf("%s\n", home_dir);
  printf(
    "Before installation\n"
    "-------------------\n"
    "\033[3;4;33mNote\033[0;0m: Make sure you have installed the required\n"
    "dependencies before you begin the installation process.\n"
    "If you are not sure, checkout the dependencies list in\n"
    "MinimalSwayFX at Github!\n\n"

    "I have read the statement above [y/n]: "
  );
  scanf(" %c", &input_char);

  if (input_char != 'y' && input_char != 'Y') {
    printf("\n----Stopped Installation----\n");
    return 0;
  }

sway_choice:
  system("clear");
  printf(
    "Which Window Manager are you using?\n"
    "-----------------------------------\n"
    "a. Sway\n"
    "b. SwayFX\n\n"

    "Input [a <-> b]: "
  );
  scanf(" %c", &input_char);

  if (input_char >= 'a' && input_char <= 'b') state |= (input_char - 'a') << 0;
  else {
    print_error_msg("The range of input is from \'a\' to \'b\'\n");
    for (int i = 3; i >= 1; i--) {
      printf("\rgoing back to option in %d.", i);
      fflush(stdout);
      sleep(1);
    }
    goto sway_choice;
  }

  read_fp = fopen("./src/sway/config", "r");
  fprintf(read_fp, "font pango:CaskaydiaCove Nerd Font 12");

  system("clear");
  printf(
    "Setting Wallpaper\n"
    "-----------------\n"
    "If you have a specific wallpaper to set,\n"
    "make sure to provide the path starting from\n"
    "$HOME otherwise, if you would like a solid\n"
    "background, provide the solid color\n"
    "in #RRGGBB hex format.\n\n"

    "Input: "
  );
  scanf("%s", &input_str[0]);

  if (is_color_hex(input_str, strlen(input_str)))
    fprintf(read_fp, "output * bg %s solid_color\n", input_str);
  else
    fprintf(read_fp, "output * bg %s fill\n", input_str);

bar_choice:
  system("clear");
  printf(
    "Setting The Bar\n"
    "-----------------\n"
    "The bar preference depends the on which\n"
    "bar you have installed from the dependencies.\n"
    "So, choose the bar you have installed.\n\n"

    "a. Waybar"
    "b. i3status-rs"

    "Input [a <-> b]: "
  );
  scanf(" %c", &input_char);

  if (input_char == 'a') {
    fprintf(
      read_fp,
      "exec waybar "
      "-c $HOME/.config/sway/waybar_config "
      "-s $HOME/.config/sway/waybar_style.css\n"
    );
  }
  else if (input_char == 'b') {
    fprintf(
      read_fp,
      "bar {\n"
      "  swaybar_command swaybar\n"
      "  status_command /usr/bin/i3status-rs $HOME/.config/i3status/config.toml\n"
      "  position top\n"
      "  font pango:CaskaydiaCove Nerd Font 12\n"
      "  colors {\n"
      "    background #050505\n"
      "    focused_workspace #97a97c #87986a #050505\n"
      "  }\n"
      "}\n"
    );
  }
  else {
    print_error_msg("The range of input is from \'a\' to \'b\'\n");
    for (int i = 3; i >= 1; i--) {
      printf("\rgoing back to option in %d.", i);
      fflush(stdout);
      sleep(1);
    }
    goto bar_choice;
  }

  fclose(read_fp);
  fclose(write_fp);
  return 0;
}
