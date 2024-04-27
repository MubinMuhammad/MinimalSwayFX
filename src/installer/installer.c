#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
 * the config pattern we followed in this code:
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
  COLOR_ORANGE,
  COLOR_YELLOW,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_PURPLE
};

const char *gruvbox_material_dark_colors[] = {
  "#1d2021",
  "#2b2f31",
  "#ddc7a1",
  "#ea6962",
  "#e78a4e",
  "#d8a657",
  "#a9b665",
  "#7daea3",
  "#d3869b",
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
  unsigned int state = 0;
  const char *home_dir = getenv("HOME");

  // FILE *reader_fp;
  char write_config[4096];
  char read_buffer[512];

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



  return 0;
}
