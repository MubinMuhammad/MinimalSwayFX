#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "colors.h"
#include "../config.h"

#define enum_to_val(uenum, low, mid, high) \
  (uenum == LOW || uenum == THIN ? (low) : \
  (uenum == MEDIUM ? (mid) :  \
  (uenum == HIGH || uenum == THICK ? (high) : (0))))

/* global varibles */
char window_gap = enum_to_val(WINDOW_GAP, 2, 4, 8);
char window_border = enum_to_val(WINDOW_BORDER, 2, 4, 6);
float swayfx_transparancy = enum_to_val(SWAYFX_TRANSPARANCY, 0.35f, 0.55f, 0.75f);
char swayfx_blur = enum_to_val(SWAYFX_TRANSPARANCY, 3, 5, 7);
char swayfx_shadow = SWAYFX_SHADOW;
char swayfx_corner_radius = enum_to_val(SWAYFX_TRANSPARANCY, 4, 8, 12);
float swayfx_inactive_dim = enum_to_val(SWAYFX_INACTIVE_DIM, 0.05f, 0.1f, 0.2f);

/* function implementaions */
int get_option(const char *in, int in_size, 
               char *out_forward, int out_forward_size,
               char *out, int out_size, 
               char *out_extension, int out_extension_size) {
  int out_idx = 0;
  int out_extension_idx = 0;
  int idx = -1;

  for (int i = 0; i < in_size; i++) {
    if (in[i] == '~') {
      idx = i + 1;
      break;
    }
    else {
      out_forward[i] = in[i];
    }
  }

  if (idx == -1) return 0;

  for (int i = idx; i < in_size; i++) {
    if (((in[i] >= 'A' && in[i] <= 'Z') || in[i] == '_') && out_size >= out_idx - 1) {
      out[out_idx++] = in[i];
    }
    else if (out_extension_size >= out_extension_idx - 1) {
      out_extension[out_extension_idx++] = in[i];
    }
  }
  
  out[out_idx] = '\0';
  out_extension[out_extension_idx] = '\0';

  return 1;
}

void change_token(char *dest, char *first, char *mid, char *extension, int buffer_size) {
  strncat(dest, first, buffer_size + 1);
  strncat(dest, mid, buffer_size + 1);
  strncat(dest, extension, buffer_size + 1);

  if (strlen(extension) == 0 || extension[strlen(extension) - 1] != '\n')
    strncat(dest, " ", 2);
}

void token_to_option(const char *in, char *out_appended, int out_appended_size) {
  int in_size = strlen(in);
  char forward_buffer[64], buffer[64], extension_buffer[64];

  memset(forward_buffer, 0, sizeof(forward_buffer));
  memset(buffer, 0, sizeof(buffer));
  memset(extension_buffer, 0, sizeof(extension_buffer));

  if (!get_option(
    in, in_size, 
    forward_buffer, sizeof(forward_buffer), 
    buffer, sizeof(buffer), 
    extension_buffer, sizeof(extension_buffer)
  )) {
    strncat(out_appended, forward_buffer, sizeof(forward_buffer) + 1);

    if (forward_buffer[strlen(forward_buffer) - 1] != '\n')
      strncat(out_appended, " ", 2);

    return;
  }

  if (strcmp(buffer, "WALLPAPER") == 0)
    change_token(out_appended, forward_buffer, WALLPAPER, extension_buffer);
  else if (strcmp(buffer, "WALLPAPER_MODE") == 0)
    change_token(out_appended, forward_buffer, is_color_hex(WALLPAPER) ? "solid_color" : "fill", extension_buffer);
  else if (strcmp(buffer, "IF_SWAYFX") == 0)
    change_token(out_appended, forward_buffer, WINDOW_MANAGER == SWAYFX ? "\0" : "#", extension_buffer);
  else {
    strncat(out_appended, forward_buffer, sizeof(forward_buffer) + 1);
    strncat(out_appended, "~", 2);
    strncat(out_appended, buffer, sizeof(buffer) + 1);
    strncat(out_appended, extension_buffer, sizeof(extension_buffer) + 1);
  }
}

void format_file(FILE *in, FILE *out) {
  char line_buffer[1024], write_buffer[1024];
  char *tmp = NULL;
  char *token = NULL;
  write_buffer[0] = '\0';

  while (fgets(line_buffer, sizeof(line_buffer), in) != NULL) {
    tmp = strdup(line_buffer);
    while ((token = strsep(&tmp, " ")) != NULL) {
      token_to_option(token, write_buffer, sizeof(write_buffer));
    }

    fputs(write_buffer, out);
    write_buffer[0] = '\0';
    free(tmp);
  }
}

int main() {
  FILE *fp = fopen("./src/sway/config", "r");
  FILE *wfp = fopen("out.txt", "w");

  format_file(fp, wfp);

  fclose(fp);
  fclose(wfp);
  return 0;
}
