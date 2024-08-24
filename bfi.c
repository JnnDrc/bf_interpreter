#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  // Variables declaration -----------------------------------------------

  FILE *bf = NULL;
  size_t bf_size = 0, bp = 0;
  char *buff = NULL, *raw_buff = NULL, *p = NULL;

  char cells[32768] = {0};
  short data_ptr = 0;

  // Argument parsing ----------------------------------------------------

  if (argc < 2) {
    fprintf(stderr, "Missing brainf*ck source file to interpret");
    return 1;
  }
  if (strcmp(strrchr(argv[1], '.'), ".bf")) {
    fprintf(stderr, "%s is not a brainf*ck source file", argv[1]);
    return 1;
  }
  bf = fopen(argv[1], "r");
  if (!bf) {
    fprintf(stderr, "Can't open brainf*ck source file %s", argv[1]);
    return 1;
  }

  // Buffer initialization -----------------------------------------------

  fseek(bf, 0, SEEK_END);
  bf_size = ftell(bf);
  raw_buff = (char *)malloc(bf_size);
  rewind(bf);
  if (!raw_buff) {
    fclose(bf);
    return 1;
  }

  fread(raw_buff, 1, bf_size, bf);
  fclose(bf);

  buff = (char *)malloc(bf_size);
  if (!buff) {
    free(raw_buff);
    return 1;
  }
  p = raw_buff;
  while (*p) {
    switch (*p) {
    case '>':
    case '<':
    case '+':
    case '-':
    case '.':
    case ',':
    case '[':
    case ']':
      buff[bp] = *p;
      bp++;
      break;
    default:
      break;
    }
    p++;
  }
  buff = realloc(buff, bp);
  if (!buff) {
    free(raw_buff);
  }
  free(raw_buff);
  // Interpreting --------------------------------------------------------
  if (argc > 2) {
    if (!strcmp(argv[2], "--print-parsed")) {
      puts("Parsed code:");
      fwrite(buff, 1, bp, stdout);
      puts("\n");
    }
  }
  p = buff;
  while (*p) {

    switch (*p) {
    case '>':
      data_ptr = data_ptr == 32767 ? 0 : data_ptr + 1;
      break;
    case '<':
      data_ptr = data_ptr == 0 ? 32767 : data_ptr - 1;
      break;
    case '+':
      cells[data_ptr]++;
      break;
    case '-':
      cells[data_ptr]--;
      break;
    case '.':
      putc(cells[data_ptr], stdout);
      break;
    case ',':
      cells[data_ptr] = getc(stdin);
      break;
    case '[': // TODO nested loops
      if (!cells[data_ptr]) {
        short skip = 0;
        while (*p != ']' && skip == 0) {
          if (*p == '[') {
            skip++;
          }
          if (*p == ']' && skip > 0) {
            skip--;
          }
          p++;
        }
        p += 2;
      }
      break;
    case ']':
      if (cells[data_ptr]) {
        short skip = 0;
        while (*p != '[' && skip == 0) {
          if (*p == ']') {
            skip++;
          }
          if (*p == ']' && skip > 0) {
            skip--;
          }
          p--;
        }
      }
      break;
    default:
      break;
    }

    p++;
  }

  // De-initialization ---------------------------------------------------

  free(buff);
  return 0;
}
