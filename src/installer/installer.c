#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_option(const char *in, char *out, int out_size, char *out_extension, int out_extension_size) {
  int out_idx = 0;
  int out_extension_idx = 0;

  for (int i = 0; i < strlen(in); i++) {
    if (((in[i] >= 'A' && in[i] <= 'Z') || in[i] == '_') && out_size >= out_idx - 1) {
      out[out_idx++] = in[i];
    }
    else if (out_extension_size >= out_extension_idx - 1) {
      out_extension[out_extension_idx++] = in[i];
    }
  }
  
  out[out_idx] = '\0';
  out_extension[out_extension_idx] = '\0';
}

void text_to_option(const char *in, char *out_appended, int out_appended_size) {
  
}

void format_file(FILE *in, FILE *out) {
  char line_buffer[1024], write_buffer[1024];
  char *tmp = NULL;
  char *token = NULL;
  write_buffer[0] = '\0';

  while (fgets(line_buffer, sizeof(line_buffer), in) != NULL) {
    tmp = strdup(line_buffer);
    while ((token = strsep(&tmp, " \"")) != NULL) {
      if (token[0] == '\0')
        text_to_option(token + 1, write_buffer, sizeof(write_buffer));
      else
        strncat(write_buffer, line_buffer, sizeof(write_buffer) - strlen(line_buffer) + 1);
    }

    fputs(write_buffer, out);
    write_buffer[0] = '\0';
  }
}

int main() {
  

  return 0;
}
