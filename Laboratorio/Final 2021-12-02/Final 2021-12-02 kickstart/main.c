#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <assert.h>
#include "card.h"
#include "cn_match.h"

#define MAX_FILES 100
#define MAX_CARDS 100

void show_usage(const char *path) {
  printf("Usage:\n");
  printf("%s [options]\n", path);
  printf("-f <files> test TAD cn_match on the all the files listed.\n");
  printf("-v Enable verification\n");
  printf("Example: %s -vf input/example*.in\n", path);
}

//open a file with the given name, or select stdin if null.
FILE* open_file(const char* filename) {
  FILE* file = NULL;
  if (filename == NULL)
  {
    file = stdin;
  }
  else
  {
    file = fopen(filename, "r");
    if (file == NULL)
    {
      fprintf(stderr, "Error opening file %s.\n", filename);
      exit(1);
    }
  }
  return (file);
}

//close file if not stdin
void close_file(FILE* file) {
  if (file != stdin)
  {
    fclose(file);
  }
}

static void print_pass(bool pass) {
  printf(pass ? "[OK]" : "[FAIL]");
}

static unsigned int
read_cards_from_file(FILE* file, card cards[], unsigned int max_read) {
  unsigned int length=0;
  int readed=0;
  readed = fscanf(file, "%u", &length);
  if (readed != 1) {
    printf("Error reading length of match\n");
    exit(EXIT_FAILURE);
  }
  if (length > max_read) {
    printf("Input is too large!\n");
    exit(EXIT_FAILURE);
  }
  for (unsigned int i=0; i < length; i++) {
    unsigned int num=0, player=0;
    char suit;
    readed = fscanf(file, "%d:%c:%d", &num, &suit, &player);
    if (readed != 3) {
      printf("Error reading %d-th card\n", i);
      exit(EXIT_FAILURE);
    }
    cards[i] = card_new(num, suit, player);
  }
  return length;
}

//execute algorithms on the given file.
int run_file(const char* filename, bool do_verify)
{
  card cards[MAX_CARDS];
  int correct;
  int expected_winner_total = 0;
  FILE* file = NULL;
  int fails = 0;
  unsigned int array_length = 0;
  file = open_file(filename);
  printf("Reading CARDS from %s...\n", file == stdin ? "stdin" : "file");
  array_length = read_cards_from_file(file, cards, MAX_CARDS);
  // if not stdin and ask for verification, load verify info
  if (file != stdin && do_verify)
  {
    int readed=0;
    readed = fscanf(file, "%i", &correct);
    if (readed != 1) {
      printf("Error reading correctness verification data\n");
      exit(EXIT_FAILURE);
    }
    readed = fscanf(file, "%d", &expected_winner_total);
    if (readed != 1) {
      printf("Error reading expected winner total points\n");
      exit(EXIT_FAILURE);
    }
  }
  close_file(file);

  // testing
  cn_match match;
  unsigned int size=0;
  unsigned int length=0;
  int winner_points=0;
  bool size_fail=false;
  bool length_correct=false;
  bool total_fail=false;
  bool array_fail=false;
  // Building
  printf("Building match: [ ");
  match = match_new();
  for (unsigned int i=0; i < array_length; i++) {
    match = match_add(match, cards[i]);
    card_dump(cards[i]);
    printf(i != array_length - 1 ? ", " : " ");
  }
  printf("]\n");
  // Size
  size = match_size(match);
  printf("size reported: %d ", size);
  if (do_verify) {
    size_fail = (size != array_length);
    print_pass(!size_fail);
  }
  printf("\n");
  // Length
  length = match_length(match);
  printf("hands: %d ", length);
  if (do_verify) {
    length_correct = is_match_correct(match) ? (array_length == 0 ? length == 0 : length == array_length / 2) : length == 0;
    print_pass(length_correct);
  }
  printf("\n");
  // Valid match
  printf("check valid match: %s ", is_match_correct(match) ? "True" : "False");
  if (do_verify) {
    print_pass(is_match_correct(match) == correct);
  }
  printf("\n");
  // Winner points
  winner_points = winner_total_points(match);
  printf("winner points: %d ", winner_points);
  if (do_verify) {
    total_fail = winner_points != expected_winner_total;
    print_pass(!total_fail);
    if (total_fail) {
      printf(" [expected: %d]", expected_winner_total);
    }

  }
  printf("\n");
  // Array
  card *card_array = match_to_array(match);
  printf("array: [ ");
  for (unsigned int i=0; i < array_length; i++) {
    card_dump(card_array[i]);
    array_fail = array_fail || card_array[i] != cards[i];
    printf(i != array_length - 1 ? ", " : " ");
  }
  printf("] ");
  if (do_verify) {
    print_pass(!array_fail);
  }
  printf("\n");
  free(card_array);
  // Destroy
  fails = size_fail + total_fail + array_fail;
  if (!length_correct) {
    fails++;
  }
  if (is_match_correct(match) != correct) {
    fails++;
  }
  match = match_destroy(match);
  return (fails);
}

bool is_option(const char* str)
{
  return (*str == '-' && strlen(str) == 2);
}

int main(int argc, char** argv)
{
  char* filenames[MAX_FILES];
  int c = 0;
  bool do_verify = false;
  unsigned int files_count = 0;
  while ((c = getopt(argc, argv, "f:v")) != -1)
  {
    switch (c)
    {
      case 'f':
      optind--;
      while (optind < argc && !is_option(argv[optind]) &&
      files_count < MAX_FILES)
      {
        files_count++;
        filenames[files_count - 1] = argv[optind];
        optind++;
      }
      break;
      case 'v':
      do_verify = true;
      break;
      case '?':
      show_usage(argv[0]);
      exit(1);
      break;
      default:
      break;
    }
  }
  if (files_count == 0)
  {
    filenames[0] = NULL;
    files_count = 1;
    do_verify = false;
  }
  int fails = 0;
  for (unsigned int i = 0; i < files_count; i++)
  {
    printf("READING %s\n", filenames[i] == NULL ? "stdin" : filenames[i]);
    fails += run_file(filenames[i], do_verify);
    printf("DONE %s.\n\n", filenames[i] == NULL ? "stdin" : filenames[i]);
  }
  if (fails > 0 && do_verify)
  {
    printf("\n\n FAILS: %d \n\n", fails);
  }
  else if (do_verify)
  {
    printf("\n\n ALL TESTS OK \n\n");
  }
  return EXIT_SUCCESS;
}
