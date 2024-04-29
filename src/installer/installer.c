#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "texts.h"
#include "colors.h"

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
      fprintf(stderr, "\033[0;31m[error]\033[0m: %s", msg); \
    } \
  } while (0)

void print_section_line(char ch, int length) {
  for (int i = 0; i < length; i++) {
    printf("-");
  }
  printf("\n");
}

void print_stage(const char *header, const char *desc,
                 const char *options) {
  int header_len = strlen(header);

  system("clear");
  printf("%s\n", header);
  print_section_line('-', header_len);

  if (options != NULL)
    printf("%s", options);
  if (desc != NULL)
    printf("%s", desc);
}

void print_error_stage(const char *msg) {
  system("clear");
  printf(
    "\033[0;31mError\033[0;0m\n"
    "-----\n"
    "You have provided invalid input.\n"
    "The input range is from %s", msg
  );

  for (int i = 3; i >= 1; i--) {
    fflush(stdout);
    printf("\rGoing back in %d.", i);
    sleep(1);
  }
}

void create_folder(const char *path) {
  DIR *d = opendir(path);

  if (ENOENT == errno) {
    mkdir(path, S_IRWXU | S_IRWXG | S_IRWXO);
  }
}

char is_color_hex(const char *hex, int hex_size) {
  if (hex_size > 6 || hex[0] != '#')
    return 0;

  return 1;
}

int main() {
  unsigned int input_state = 0;
  char input_char;
  char input_str[128];
  char *HOME = getenv("HOME");
  char tmp_dir[32];

  print_stage(before_header, before_desc, NULL);
  scanf(" %c", &input_char);

  if (input_char != 'y' && input_char != 'Y') {
    printf("Goodbye!\n");
    goto end;
  }

  sprintf(tmp_dir, "%s/%s", HOME, ".config");
  create_folder(tmp_dir);

  print_stage(sway_ques_header, NULL, sway_ques_options);
  scanf(" %c", &input_char);

  if (input_char != 'a' && input_char != 'b')
    print_error_stage("\'a\' to \'b\'.");
  else
    input_state |= (input_char - 'a') << 0;

  FILE *reader_fp = NULL;
  FILE *writer_fp = NULL;
  char line_buffer[128];
  char line_set[1024];

  reader_fp = fopen("./src/sway/config", "r");
  fgets(line_buffer, sizeof(line_buffer), reader_fp);

  fclose(reader_fp);
  fclose(writer_fp);

  end:
  return 0;
}
