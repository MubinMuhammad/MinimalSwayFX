#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void text_to_option(const char *in, char *out_appended, int out_appended_size) {
  int in_size = strlen(in);
  char forward_buffer[64], buffer[64], extension_buffer[64];

  forward_buffer[0] = '\0';
  buffer[0] = '\0';
  extension_buffer[0] = '\0';

  get_option(
    in, in_size, 
    forward_buffer, sizeof(forward_buffer), 
    buffer, sizeof(buffer), 
    extension_buffer, sizeof(extension_buffer)
  );
}

void format_file(FILE *in, FILE *out) {
  char line_buffer[1024], write_buffer[1024];
  char *tmp = NULL;
  char *token = NULL;
  write_buffer[0] = '\0';

  while (fgets(line_buffer, sizeof(line_buffer), in) != NULL) {
    tmp = strdup(line_buffer);
    while ((token = strsep(&tmp, " ")) != NULL) {
      text_to_option(token, write_buffer, sizeof(write_buffer));
    }

    fputs(write_buffer, out);
    write_buffer[0] = '\0';
    free(tmp);
  }
}

int main() {
  FILE *fp = fopen("in.txt", "r");
  FILE *wfp = fopen("out.txt", "w");

  format_file(fp, wfp);

  fclose(fp);
  fclose(wfp);
  return 0;
}
