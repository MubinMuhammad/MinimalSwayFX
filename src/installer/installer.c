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

#define ENUM_TO_VAL(unit_enum, low, mid, high) \
  (unit_enum == LOW || unit_enum == THIN ? low : \
  (unit_enum == MEDIUM ? mid : \
  (unit_enum == HIGH || unit_enum == THICK ? high : 0)))

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
  char line_buffer[1024];

  char  window_gap = ENUM_TO_VAL(WINDOW_GAP, 2, 4, 8);
  char  window_border = ENUM_TO_VAL(WINDOW_BORDER, 2, 4, 6);
  float swayfx_transparancy = ENUM_TO_VAL(SWAYFX_TRANSPARANCY, 0.35f, 0.55f, 0.75f);
  char  swayfx_blur = ENUM_TO_VAL(SWAYFX_TRANSPARANCY, 3, 5, 7);
  char  swayfx_shadow = SWAYFX_SHADOW;
  char  swayfx_corner_radius = ENUM_TO_VAL(SWAYFX_TRANSPARANCY, 4, 8, 12);
  float swayfx_inactive_dim = ENUM_TO_VAL(SWAYFX_INACTIVE_DIM, 0.05f, 0.1f, 0.2f);

  reader_fp = fopen("./src/sway/config", "r");

  snprintf(crnt_config, 64, "%s/config", sway_dir);
  writer_fp = fopen(crnt_config, "w");

  for (int i = 0; i < 2; i++) {
    fgets(line_buffer, sizeof(line_buffer), reader_fp);
    fputs(line_buffer, writer_fp);
  }

  WRITE_TO_FILE(
    line_buffer, 
    writer_fp, 
    "output * bg %s %s\n\n",
    WALLPAPER, 
    is_color_hex(WALLPAPER) ? "solid_color" : "fill"
  );

  WRITE_TO_FILE(
    line_buffer, 
    writer_fp, 
    "gaps inner %d\n"
    "gaps outer %d\n\n"
    "default_border pixel %d\n\n"
    "default_floating_border pixel %d\n\n",
    window_gap, window_gap,
    window_border, window_border
  );

  WRITE_TO_FILE(
    line_buffer,
    writer_fp,
    "# class                 border  backgr. text    indicator child_border\n"
    "client.focused          %s %s %s #00000000 %s\n"
    "client.focused_inactive %s %s %s #00000000 %s\n"
    "client.unfocused        %s %s %s #00000000 %s\n"
    "client.urgent           %s %s %s #00000000 %s\n"
    "client.placeholder      %s %s %s #00000000 %s\n\n",
    WINDOW_MANAGER_THEME[COLOR_BG3],    WINDOW_MANAGER_THEME[COLOR_BG],
    WINDOW_MANAGER_THEME[COLOR_FG],     WINDOW_MANAGER_THEME[COLOR_BG3],
    WINDOW_MANAGER_THEME[COLOR_BG2],    WINDOW_MANAGER_THEME[COLOR_BG3],
    WINDOW_MANAGER_THEME[COLOR_FG1],    WINDOW_MANAGER_THEME[COLOR_BG2],
    WINDOW_MANAGER_THEME[COLOR_BG2],    WINDOW_MANAGER_THEME[COLOR_BG3],
    WINDOW_MANAGER_THEME[COLOR_FG1],    WINDOW_MANAGER_THEME[COLOR_BG2],
    WINDOW_MANAGER_THEME[COLOR_YELLOW], WINDOW_MANAGER_THEME[COLOR_BG],    
    WINDOW_MANAGER_THEME[COLOR_FG1],    WINDOW_MANAGER_THEME[COLOR_YELLOW],
    WINDOW_MANAGER_THEME[COLOR_BG3],    WINDOW_MANAGER_THEME[COLOR_BG],
    WINDOW_MANAGER_THEME[COLOR_FG],     WINDOW_MANAGER_THEME[COLOR_BG3]
  );

  if (WINDOW_MANAGER == SWAYFX) {
    WRITE_TO_FILE(
      line_buffer,
      writer_fp,
      "blur %s\n"
      "blur_passes %d\n"
      "blur_radius 5\n"
      "blur_xray %s\n"
      "shadows %s\n"
      "corner_radius %d\n"
      "default_dim_inactive %.3f\n",
      SWAYFX_TRANSPARANCY != NONE &&
      SWAYFX_BLUR != NONE ? "enable" : "disable",
      swayfx_blur,
      SWAYFX_BLUR_XRAY == TRUE ? "enable" : "disable",
      SWAYFX_SHADOW == TRUE ? "enable" : "disable",
      swayfx_corner_radius,
      swayfx_inactive_dim
    );
  }

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
      "    background %s%.2x\n"
      "    focused_workspace %s %s %s\n"
      "  }\n"
      "}\n\n",
      BAR_POSITION == BOTTOM ? "bottom" : "top",
      window_gap * 2,
      WINDOW_MANAGER_THEME[COLOR_BG],
      (int)((1.0f - swayfx_transparancy) * 100 + 55),
      WINDOW_MANAGER_THEME[COLOR_YELLOW1],
      WINDOW_MANAGER_THEME[COLOR_YELLOW],
      WINDOW_MANAGER_THEME[COLOR_BG]
    );

    if (WINDOW_MANAGER == SWAYFX) {
      WRITE_TO_FILE(
        line_buffer, 
        writer_fp, 
        "layer_effects \"panel\" blur %s; shadows %s; corner_radius %d",
        SWAYFX_TRANSPARANCY != NONE && SWAYFX_BLUR != NONE ? "enable" : "disable",
        SWAYFX_SHADOW == TRUE ? "enable" : "disable",
        swayfx_corner_radius
      );
    }
  }

  while (fgets(line_buffer, sizeof(line_buffer), reader_fp) != NULL) {
    fputs(line_buffer, writer_fp);
  }

  fclose(reader_fp);
  fclose(writer_fp);

  if (BAR_TYPE == WAYBAR) {
    reader_fp = fopen("./src/sway/waybar_config.jsonc", "r");

    snprintf(crnt_config, 64, "%s/waybar_config.jsonc", sway_dir);
    writer_fp = fopen(crnt_config, "w");

    fgets(line_buffer, sizeof(line_buffer), reader_fp);
    fputs(line_buffer, writer_fp);

    WRITE_TO_FILE(
      line_buffer,
      writer_fp,
      "  \"position\": \"%s\",\n"
      "  \"margin-top\": %d,\n"
      "  \"margin-bottom\": %d,\n"
      "  \"margin-left\": %d,\n"
      "  \"margin-right\": %d,\n",
      BAR_POSITION == TOP ? "top" : "bottom",
      BAR_POSITION == TOP ? window_gap : 0,
      BAR_POSITION == BOTTOM ? window_gap : 0,
      window_gap, window_gap
    );

    while (fgets(line_buffer, sizeof(line_buffer), reader_fp) != NULL) {
      fputs(line_buffer, writer_fp);
    }

    fclose(reader_fp);
    fclose(writer_fp);

    reader_fp = fopen("./src/sway/waybar_style.css", "r");

    snprintf(crnt_config, 64, "%s/waybar_style.css", sway_dir);
    writer_fp = fopen(crnt_config, "w");

    WRITE_TO_FILE(
      line_buffer, 
      writer_fp, 
      "@define-color bg      %s;\n"
      "@define-color bg1     %s;\n"
      "@define-color bg2     %s;\n"
      "@define-color bg3     %s;\n"
      "@define-color bg4     %s;\n"
      "@define-color fg      %s;\n"
      "@define-color fg1     %s;\n"
      "@define-color red     %s;\n"
      "@define-color red1    %s;\n"
      "@define-color orange  %s;\n"
      "@define-color orange1 %s;\n"
      "@define-color yellow  %s;\n"
      "@define-color yellow1 %s;\n"
      "@define-color green   %s;\n"
      "@define-color green1  %s;\n"
      "@define-color blue    %s;\n"
      "@define-color blue1   %s;\n"
      "@define-color purple  %s;\n"
      "@define-color purple1 %s;\n\n",
      WINDOW_MANAGER_THEME[COLOR_BG],
      WINDOW_MANAGER_THEME[COLOR_BG1],
      WINDOW_MANAGER_THEME[COLOR_BG2],
      WINDOW_MANAGER_THEME[COLOR_BG3],
      WINDOW_MANAGER_THEME[COLOR_BG4],
      WINDOW_MANAGER_THEME[COLOR_FG],
      WINDOW_MANAGER_THEME[COLOR_FG1],
      WINDOW_MANAGER_THEME[COLOR_RED],
      WINDOW_MANAGER_THEME[COLOR_RED1],
      WINDOW_MANAGER_THEME[COLOR_ORANGE],
      WINDOW_MANAGER_THEME[COLOR_ORANGE1],
      WINDOW_MANAGER_THEME[COLOR_YELLOW],
      WINDOW_MANAGER_THEME[COLOR_YELLOW1],
      WINDOW_MANAGER_THEME[COLOR_GREEN],
      WINDOW_MANAGER_THEME[COLOR_GREEN1],
      WINDOW_MANAGER_THEME[COLOR_BLUE],
      WINDOW_MANAGER_THEME[COLOR_BLUE1],
      WINDOW_MANAGER_THEME[COLOR_PURPLE],
      WINDOW_MANAGER_THEME[COLOR_PURPLE1]
    );
    
    /*
     * TODO: implement the config manager for waybar.
     * */

    while (fgets(line_buffer, sizeof(line_buffer), reader_fp) != NULL) {
      fputs(line_buffer, writer_fp);
    }

    fclose(reader_fp);
    fclose(writer_fp);
  }
  else if (BAR_TYPE == I3_STATUS) {
    reader_fp = fopen("./src/sway/i3status_config.toml", "r");

    snprintf(crnt_config, 64, "%s/i3status_config.toml", sway_dir);
    writer_fp = fopen(crnt_config, "w");

    

    fclose(reader_fp);
    fclose(writer_fp);
  }

  return 0;
}
