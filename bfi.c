/*
 * BrainFuck Interpreter, BFI
 *
 * This program is a simple 'n small interpreter
 * for the brainfuck esolang
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

enum opts_e { DEF = 0b0000, PARSE = 0b0001, PRINT = 0b0010 };
// DEF : no params
// PARSE : --parse
// PRINT : --print

// prints the help manual
void help();

int main(int argc, char **argv) {
  // Variables declaration -----------------------------------------------

  // brainf*ck source file
  FILE *bf = NULL;
  // source file size, raw_buff parsing help variable
  size_t bf_size = 0, bp = 0;
  // buffer, interpreting pointer, line buffer
  char *buff = NULL, *p = NULL, line[512] = {0};

  int8_t cells[32768] = {0}, options = 0; // memory array, bfi options
  uint16_t data_ptr = 0;                // data pointer

  // Argument parsing ----------------------------------------------------

  if (argc < 2) { // missing source file
    fprintf(stderr, "ERROR: Missing brainf*ck source file to interpret\n");
    fprintf(stderr, "HELP: try bfi --help to get help\n");
    return 1;
    return 1;
  }
  if (!strcmp(argv[1], "--help")) {
    help();
    return 0;
  }
  bf = fopen(argv[1], "r");
  if (!bf) {
    fprintf(stderr, "ERROR: Can't open brainf*ck source file %s", argv[1]);
    return 1;
  }

  if (argc > 2) { // extra params proccessing
    for (int i = 2; i < argc; i++) {
      if (!strcmp(argv[i], "--parse")) {
        options |= PARSE;
      } else if (!strcmp(argv[i], "--print")) {
        options |= PRINT;
      }
    }
  }

  // Buffer initialization -----------------------------------------------

  fseek(bf, 0, SEEK_END);
  bf_size = ftell(bf); // gets source file size
  rewind(bf);

  buff = (char *)malloc(bf_size);
  if (!buff) {
    fprintf(stderr,"ERROR: Failed to allocate needed resources");
    return 1;
  }

  while (fgets(line, sizeof(line), bf)) {
    if (line[0] == '#')
      continue;
    strcpy(line, strtok(line, "#"));
    int len = strlen(line);
    if (line[len - 1] == '\n')
      line[len - 1] = '\0';

    p = line;
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
  }
  buff = realloc(buff, bp + 1);
  if (!buff) {
    fprintf(stderr,"ERROR: Failed to allocate needed resources");
    return 1;
  }
  buff[bp] = '\0';


  // params

  if (options & PARSE) {
    char p_name[strlen(argv[1]) + strlen("_p") + 1];
    strcpy(p_name, strtok(argv[1], "."));
    strcat(p_name, "_p");
    strcat(p_name, ".bf\0");
    FILE *bfi_p = fopen(p_name, "w");
    fwrite(buff, 1, bp, bfi_p);

    free(buff);
    return 0;
  }
  if (options & PRINT) {
    puts("Parsed code:");
    fwrite(buff, 1, bp, stdout);
    puts("\n");
  }
  // Interpreting --------------------------------------------------------
  p = buff;
  while (*p) {

    switch (*p) {
    case '>':
      data_ptr = (data_ptr == 32767) ? 0 : data_ptr + 1;
      break;
    case '<':
      data_ptr = (data_ptr == 0) ? 32767 : data_ptr - 1;
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
    case '[':
      if (!cells[data_ptr]) {
        short l = 1;
        while (l > 0) {
          p++;
          if (*p == '[')
            l++;
          else if (*p == ']')
            l--;
        }
      }
      break;
    case ']':
      if (cells[data_ptr]) {
        short l = 1;
        while (l > 0) {
          p--;
          if (*p == '[')
            l--;
          else if (*p == ']')
            l++;
        }
      }
      break;
    default:
      fprintf(stderr,"ERROR: unexpected character '%c'",*p);
      break;
    }

    p++;
  }

  // De-initialization ---------------------------------------------------

  free(buff);
  return 0;
}

void help() {
  // bfi help manual
  fprintf(stdout,
          "-------------BrainFuck Interpreter help manual-------------\n\n");
  fprintf(stdout, "SYNOPSIS: \n");
  fprintf(stdout,
          "\tBrainFuck Interpreter, or BFI is a simple and lightweight\n");
  fprintf(stdout, "\tBrainfuck esolang interpreter.\n");
  fprintf(stdout, "\nUSE: \n");
  fprintf(stdout, "\tthe next line is a normal bfi use: \n");
  fprintf(stdout, "\t ~> bfi <program_path.bf> [--params_list]\n");
  fprintf(stdout, "\t bfi : BFI.\n");
  fprintf(stdout, "\t program_path : the path for your brainfuck program\n");
  fprintf(stdout, "\t\t WARN: it only accepts .bf files.\n");
  fprintf(stdout, "\t --params_list : you list the optional params to give\n");
  fprintf(stdout, "\t\t to the bfi, all params start with \"--\".\n");
  fprintf(stdout, "\nPARAMS: \n");
  fprintf(stdout, "\t--parse: \n");
  fprintf(stdout, "\t\twrites the parsed code(code without commentarys,\n");
  fprintf(stdout, "\t\tnew lines, spaces, etc...) to a file named\n");
  fprintf(stdout, "\t\t<bf_code>_p.bf and DON'T interpret the program.\n");
  fprintf(stdout, "\t--print\n");
  fprintf(stdout, "\t\tprints the parsed code(coide without commentarys,\n");
  fprintf(stdout, "\t\tnew lines, spaces, etc...) to the console and\n");
  fprintf(stdout, "\t\tthen inteprets the program.\n");
  return;
}
