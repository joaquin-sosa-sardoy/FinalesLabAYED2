#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>
#include <assert.h>

#include "card.h"
#include "unogame.h"
#include "pretty_helpers.h"

#define MAX_FILES 150
#define MAX_CARDS 150

typedef struct s_cardplay {
    card_t card;
    player_t next_player;
} cardplay_t;

void show_usage(const char *path)
{
    printf("Usage:\n");
    printf("%s [options]\n", path);
    printf("-f <files> test TAD Uno-Game on the all the files listed.\n");
    printf("-v Enable verification\n");
    printf("Example: %s -vf input/example*.in\n", path);
}

//open a file with the given name, or select stdin if null.
FILE* open_file(const char* filename)
{
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
void close_file(FILE* file)
{
    if (file != stdin)
    {
        fclose(file);
    }
}

static bool same_card(card_t c1, card_t c2) {
    type_t c1_type = card_get_type(c1);
    bool same_num = card_samenum(c1, c2);
    bool same_color = card_samecolor(c1, c2);
    bool same_type = c1_type == card_get_type(c2);
    return (c1_type == normal && same_type && same_num && same_color) ||
           (c1_type != normal && same_type && same_color);
}

static void print_card(card_t card)
{
    type_t type=card_get_type(card);
    color_t color=card_get_color(card);
    char type_chr= type == normal ? 'n':
                   type == change_color ? 'c':
                   type == skip ? 's':
                   '?';
    char color_chr= color == red ? 'r':
                    color == green ? 'g':
                    color == blue ? 'b':
                    color == yellow ? 'y':
                    '?';
    if (color==red) color_red();
    else if (color==green) color_green();
    else if (color==blue) color_blue();
    else if (color==yellow) color_gold();
    printf("[%d%c:%c]", card_get_number(card), color_chr, type_chr);
    color_no_color();
}

static void print_pass(bool pass)
{
    if (pass) color_lightgreen();
    else color_lightred();
    printf(pass ? "[OK]" : "[FAIL]");
    color_no_color();
}

static void print_arrayplay(cardplay_t array[], unsigned int size) {
    assert(size > 0);
    for (int i=size-1; i > 0; i--) {
        print_card(array[i].card);
        printf(" %d -> ", array[i - 1].next_player);
    }
    print_card(array[0].card);
    printf(" -1 -> NULL ");
}

static unsigned int
read_pile_from_file(FILE* file, cardplay_t cards_played[], unsigned int max_read) {
    unsigned int length=0;
    int readed=0;
    readed = fscanf(file, "%u ", &length);
    if (readed != 1) {
        printf("Error reading length of discard pile\n");
        exit(EXIT_FAILURE);
    }
    if (length > max_read) {
        printf("Input is too large!\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i=0; i < length; i++) {
        int read_num=0, read_player=0;
        char read_color=0, read_type=0;
        readed = fscanf(file, "[%d%c:%c] ==> P%d ", &read_num,
                                                    &read_color,
                                                    &read_type,
                                                    &read_player);
        if (readed != 4) {
            printf("Error reading %d-th card [%d]\n", i, length);
            exit(EXIT_FAILURE);
        }
        // Parsing vars
        bool bad_number=false, bad_color=false, bad_type=false, bad_player=false;
        color_t color;
        type_t type;
        unsigned int num;
        player_t next_player;
        // Check readed number
        bad_number = !(0 <= read_num && read_num < 10);
        num = (unsigned int) read_num;
        // Check readed color
        if (read_color == 'r') color = red;
        else if (read_color == 'g') color = green;
        else if (read_color == 'b') color = blue;
        else if (read_color == 'y') color = yellow;
        else bad_color=true;
        // Check readed type
        if (read_type=='n') type = normal;
        else if (read_type=='c') type = change_color;
        else if (read_type=='s') type = skip;
        else bad_type=true;
        // Check readed player
        bad_player = read_player >= NUM_PLAYERS || read_player < 0;
        next_player = (player_t) read_player;
        // Check format
        if (bad_number || bad_color || bad_type || bad_player) {
            printf("BAD FORMAT: %s\n", bad_number ? "Wrong card number":
                                       bad_color  ? "Wrong color":
                                       bad_type   ? "Wrong card type":
                                       bad_player ? "Wrong next-player number":
                                       "???");
            printf("reading input: [%d%c:%c] P%d\n", read_num,
                                                     read_color,
                                                     read_type,
                                                     read_player);
            exit(EXIT_FAILURE);
        }
        cards_played[i].card = card_new(num, color, type);
        cards_played[i].next_player = next_player;
    }
    return length;
}

//execute algorithms on the given file.
int run_file(const char* filename, bool do_verify)
{
    cardplay_t cards_played[MAX_CARDS];
    cardplay_t build_pile[MAX_CARDS];
    int expected_valid = 0;
    FILE* file = NULL;
    int fails = 0;
    unsigned int length = 0;
    file = open_file(filename);
    printf("Reading PILE from %s...\n", file == stdin ? "stdin" : filename);
    length = read_pile_from_file(file, cards_played, MAX_CARDS);
    // if not stdin and ask for verification, load verify info
    if (file != stdin && do_verify)
    {
        int readed=0;
        readed = fscanf(file, "%d", &expected_valid);
        if (readed != 1) {
            printf("Error reading expected valid-pile flag\n");
            exit(EXIT_FAILURE);
        }
    }
    close_file(file);
    // Testing TAD Uno-Game
    unogame_t uno;
    bool stackness_fail=false;
    bool length_fail=false;
    bool valid_fail=false;
    bool nextplayer_fail=false;
    bool color_fail=false;
    bool array_fail=false;
    int nextplayer_fail_index=0;
    int stackness_fail_index=0;
    int color_fail_index=0;
    // 
    printf("input          : ");
    print_arrayplay(cards_played, length);
    printf("\n");
    // Building
    printf("building pile  : ");
    uno = uno_newgame(cards_played[0].card);
    for (int i=0; i < (int) length; i++) {
        cardplay_t cur_play = cards_played[i];
        if (!nextplayer_fail && uno_nextplayer(uno)!=cur_play.next_player) {
            nextplayer_fail_index = i;
            nextplayer_fail = true;
        }
        if (!stackness_fail && !same_card(uno_topcard(uno), cur_play.card)) {
            stackness_fail = true;
            stackness_fail_index = i;
        }
        if (!color_fail &&
             uno_currentcolor(uno) != card_get_color(cur_play.card)) {
            color_fail = true;
            color_fail_index = i;

        }
        build_pile[i].card = uno_topcard(uno);
        build_pile[i].next_player = uno_nextplayer(uno);
        if (i + 1 < (int) length)
            uno = uno_addcard(uno, cards_played[i + 1].card);
    }
    print_arrayplay(build_pile, length);
    if (do_verify) {
        print_pass(!stackness_fail && !nextplayer_fail && !color_fail);
        color_white();
        if (stackness_fail)
            printf("\nbad element index: %d", stackness_fail_index);
        if (nextplayer_fail)
            printf("\nbad player index: %d", nextplayer_fail_index + 1);
        if (color_fail)
            printf("\nbad color index: %d", color_fail_index);
        color_no_color();
    }
    printf("\n");
    // Length
    unsigned int reported_length = uno_count(uno);
    printf("length reported: %d ",reported_length);
    if (do_verify) {
        length_fail = (length != reported_length);
        print_pass(!length_fail);
    }
    printf("\n");
    // Next player
    printf("next player    : %d ", uno_nextplayer(uno));
    if (do_verify) {
        nextplayer_fail = (uno_nextplayer(uno) != cards_played[length -1].next_player);
        print_pass(!nextplayer_fail);
        if (nextplayer_fail) {
            color_white();
            printf("\nexpected next player: %d", cards_played[length -1].next_player);
        }
    }
    printf("\n");

    // Valid pile
    printf("valid pile     : %s ", uno_validpile(uno) ? "true":" false");
    if (do_verify) {
        valid_fail = (uno_validpile(uno) != expected_valid);
        print_pass(!valid_fail);
    }
    printf("\n");
    // Array
    card_t *pile_cards = uno_pile_to_array(uno);
    printf("array          : [ ");
    for (unsigned int i=0; i < reported_length; i++) {
        print_card(pile_cards[i]);
        array_fail = array_fail || !same_card(pile_cards[i], build_pile[i].card);
        printf(i != reported_length - 1 ? ", " : " ");
    }
    printf("] ");
    if (do_verify) {
        print_pass(!array_fail);
    }
    printf("\n");
    free(pile_cards);
    // Destroy
    uno = uno_destroy(uno);

    fails = stackness_fail + color_fail + nextplayer_fail + length_fail +
            valid_fail + array_fail;
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
    color_no_color();
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
        color_red();
        printf("\n\n FAILS: %d \n\n", fails);
        color_no_color();
    }
    else if (do_verify)
    {
        color_white();
        printf("\n\n ALL TESTS OK \n\n");
        color_no_color();
    }
    return EXIT_SUCCESS;
}
