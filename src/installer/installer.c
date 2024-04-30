#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "colors.h"
#include "../../config.h"

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
  char line_buffer[128];

  reader_fp = fopen("./src/sway/config", "r");

  snprintf(crnt_config, 64, "%s/config", sway_dir);
  writer_fp = fopen(crnt_config, "w");

  for (int i = 0; i < 2; i++) {
    fgets(line_buffer, 128, reader_fp);
    fputs(line_buffer, writer_fp);
  }

  snprintf(
    line_buffer,
    128,
    "output * bg %s %s",
    WALLPAPER,
    is_color_hex(WALLPAPER) ? "solid_color" : "fill"
  );

  fputs(line_buffer, writer_fp);

  fclose(reader_fp);
  fclose(writer_fp);

  return 0;
}
