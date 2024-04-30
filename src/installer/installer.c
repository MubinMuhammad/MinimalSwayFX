#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "colors.h"
#include "../../config.h"

// Internal code, Don't Edit

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

#define ERROR(e, msg) \
  do { \
    if (e) { \
      fprintf(stderr, "[\033[0;31merror\033[0m]: %s", msg); \
      exit(1); \
    } \
  } while (0)

#define WRITE_TO_FILE(buffer, file_ptr, format, ...) \
  do { \
    snprintf(buffer, sizeof(buffer), format, __VA_ARGS__); \
    fputs(buffer, file_ptr); \
  } while (0)


/**/
char folder_exist(const char *path) {
  struct stat st;
  if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
    return 1;
  }

  return 0;
}

char folder_create(const char *path) {
  if (mkdir(path, 0777) == -1) {
    return 1;
  }

  return 0;
}

char is_color_hex(const char *hex) {
  if (strlen(hex) > 7 || hex[0] != '#')
    return 0;

  return 1;
}

int enum_to_val(int unit_enum, int low, int mid, int high) {
  if (unit_enum == NONE)
    return 0;
  if (unit_enum == LOW || unit_enum == THIN)
    return low;
  if (unit_enum == MEDIUM)
    return mid;
  if (unit_enum == HIGH || unit_enum == THICK)
    return high;

  return 0;
}

int main(int argc, char *argv[]) {
  char *HOME = getenv("HOME");
  char config_dir[32];
  char sway_dir[64];
  char crnt_config[64];
  char bak_dir[64];

  snprintf(config_dir, 32, "%s/.config", HOME);
  snprintf(sway_dir, 64, "%s/.config/sway", HOME);
  snprintf(bak_dir, 64, "%s/.config/sway_bak", HOME);

  if (!folder_exist(config_dir)) {
    folder_create(config_dir);
  }

  if (!folder_exist(sway_dir)) {
    folder_create(sway_dir);
  }
  else {
    ERROR(
      rename(sway_dir, bak_dir), 
      "Failed to move old config to new dir!\n"
    );
    folder_create(sway_dir);
  }
  
  FILE *reader_fp = NULL;
  FILE *writer_fp = NULL;
  char line_buffer[512];

  reader_fp = fopen("./src/sway/config", "r");

  snprintf(crnt_config, 64, "%s/config", sway_dir);
  writer_fp = fopen(crnt_config, "w");

  for (int i = 0; i < 2; i++) {
    fgets(line_buffer, 128, reader_fp);
    fputs(line_buffer, writer_fp);
  }

  WRITE_TO_FILE(
    line_buffer, 
    writer_fp, 
    "output * bg %s %s\n\n",
    WALLPAPER, 
    is_color_hex(WALLPAPER) ? "solid_color" : "fill"
  );

  int window_gap = enum_to_val(WINDOW_GAP, 4, 8, 12);
  WRITE_TO_FILE(
    line_buffer, 
    writer_fp, 
    "gaps inner %d\n"
    "gaps outer %d\n\n",
    window_gap, window_gap
  );

  int window_border = enum_to_val(WINDOW_BORDER, 1, 2, 4);
  WRITE_TO_FILE(
    line_buffer, 
    writer_fp, 
    "default_border pixel %d\n"
    "default_floating_border pixel %d\n\n",
    window_border, window_border
  );

  if (BAR_TYPE == WAYBAR) {
    WRITE_TO_FILE(
      line_buffer, 
      writer_fp, 
      "exec waybar "
      "-c $HOME/.config/sway/waybar_config "
      "-s $HOME/.config/sway/waybar_style.css\n\n",
      NULL
    );
  }
  else if (BAR_TYPE == I3_STATUS) {
    WRITE_TO_FILE(
      line_buffer, 
      writer_fp, 
      "bar {\n"
      "  swaybar_command swaybar\n"
      "  status_command /usr/bin/i3status-rs $HOME/.config/sway/i3status_config.toml\n"
      "  position %s\n"
      "  gaps %d\n"
      "  font pango:CaskaydiaCove Nerd Font Bold 12\n"
      "  colors {\n"
      "    background %s\n"
      "    focused_workspace %s %s %s\n"
      "  }\n"
      "}\n\n",
      BAR_POSITION == BOTTOM ? "bottom" : "top",
      window_gap * 2,
      WINDOW_MANAGER_THEME[COLOR_BG],
      WINDOW_MANAGER_THEME[COLOR_YELLOW1],
      WINDOW_MANAGER_THEME[COLOR_YELLOW],
      WINDOW_MANAGER_THEME[COLOR_BG]
    );
  }

  fclose(reader_fp);
  fclose(writer_fp);

  return 0;
}
