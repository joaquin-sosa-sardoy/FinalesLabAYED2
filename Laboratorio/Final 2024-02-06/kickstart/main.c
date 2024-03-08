#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "domino.h"
#include "domino_line.h"

#define MAX_FILES 100
#define MAX_TILES 100

// FUNCIONES COMPLEMENTARIAS

unsigned int doubles_count(domino_line line)
{
    unsigned int res = 0u;
    /*
     * COMPLETAR
     *
     */
    struct _line_node *aux = line_iterator_begin(line);
    while(aux!=NULL && domino_is_double(line_iterator_get(aux))){
        res = res + domino_down(line_iterator_get(aux)) + domino_up(line_iterator_get(aux));
        aux = line_iterator_next(aux);
    }
    return res;
}

bool is_in_line(domino_line line, domino tile)
{
    bool found = false;
    /*
     * COMPLETAR
     *
     */
    struct _line_node *aux = line_iterator_begin(line);
    while(aux!=NULL && !found){
        if(domino_matches(line_iterator_get(aux), tile)){
            found = true;
        }
        aux = line_iterator_next(aux);
    }
    return found;
}

void show_usage(const char* path)
{
    printf("Usage:\n");
    printf("%s [options]\n", path);
    printf("-f <files> test TAD Domino-Line on the all the files listed.\n");
    printf("-v Enable verification\n");
    printf("Example: %s -vf input/example*.in\n", path);
}

// open a file with the given name, or select stdin if null.
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

// close file if not stdin
void close_file(FILE* file)
{
    if (file != stdin)
    {
        fclose(file);
    }
}

static void print_tile(domino t)
{
    printf("%d:%d", domino_up(t), domino_down(t));
}

static void print_pass(bool pass)
{
    printf(pass ? "[OK]" : "[FAIL]");
}

static unsigned int
read_tiles_from_file(FILE* file, domino tiles[], unsigned int max_read)
{
    unsigned int length = 0;
    int readed = 0;
    readed = fscanf(file, "%u", &length);
    if (readed != 1)
    {
        printf("Error reading length of line of play\n");
        exit(EXIT_FAILURE);
    }
    if (length > max_read)
    {
        printf("Input is too large!\n");
        exit(EXIT_FAILURE);
    }
    for (unsigned int i = 0; i < length; i++)
    {
        int num_up = 0, num_down = 0;
        readed = fscanf(file, "%d:%d", &num_up, &num_down);
        if (readed != 2)
        {
            printf("Error reading %d-th tile\n", i);
            exit(EXIT_FAILURE);
        }
        tiles[i] = domino_new(num_up, num_down);
    }
    return length;
}

// execute algorithms on the given file.
int run_file(const char* filename, bool do_verify)
{
    domino tiles[MAX_TILES];
    int correct[MAX_TILES];
    int expected_total = 0;
    FILE* file = NULL;
    int fails = 0;
    unsigned int array_length = 0;
    file = open_file(filename);
    printf("Reading TILES from %s...\n", file == stdin ? "stdin" : "file");
    array_length = read_tiles_from_file(file, tiles, MAX_TILES);
    // if not stdin and ask for verification, load verify info
    // INITIALIZE correct array
    for (unsigned int i = 0u; i < MAX_TILES; ++i)
    {
        correct[i] = 0;
    }
    if (file != stdin && do_verify)
    {
        int readed = 0;
        for (unsigned int i = 0u; i < array_length; i++)
        {
            readed = fscanf(file, "%d", &correct[i]);
            if (readed != 1)
            {
                printf("Error reading correctness verification data\n");
                exit(EXIT_FAILURE);
            }
        }
        readed = fscanf(file, "%d", &expected_total);
        if (readed != 1)
        {
            printf("Error reading expected total points\n");
            exit(EXIT_FAILURE);
        }
    }
    close_file(file);
    // Testing TAD Domino-Line
    domino_line line;
    unsigned int length = 0;
    int total_points = 0;
    bool correct_fail = false;
    bool length_fail = false;
    bool total_fail = false;
    bool array_fail = false;
    // Building
    printf("Building domino-line: [ ");
    line = line_new(tiles[0]);
    print_tile(tiles[0]);
    for (unsigned int i = 1; i < array_length; i++)
    {
        line = line_add(line, tiles[i]);
        printf(", ");
        print_tile(tiles[i]);
    }
    printf("]\n");
    // Length
    length = line_length(line);
    printf("length reported: %d ", length);
    if (do_verify)
    {
        length_fail = (length != array_length);
        print_pass(!length_fail);
    }
    printf("\n");
    // Correct tiles
    printf("check correct tiles: [ ");
    for (unsigned int i = 0; i < array_length; i++)
    {
        bool is_correct = line_n_correct(line, i);
        print_tile(tiles[i]);
        printf(is_correct ? " (T)" : " (F)");
        printf(i != array_length - 1 ? ", " : " ");
        correct_fail = correct_fail || is_correct != correct[i];
    }
    printf("] ");
    if (do_verify)
    {
        print_pass(!correct_fail);
        if (correct_fail)
        {
            printf("\n");
            printf("verify expected    : [ ");
            for (unsigned int i = 0; i < array_length; i++)
            {
                print_tile(tiles[i]);
                printf(correct[i] ? " (T)" : " (F)");
                printf(i != array_length - 1 ? ", " : " ");
            }
            printf("]");
        }
    }
    printf("\n");
    // Total points
    total_points = line_total_points(line);
    printf("total points: %d ", total_points);
    if (do_verify)
    {
        total_fail = total_points != expected_total;
        print_pass(!total_fail);
        if (total_fail)
        {
            printf(" [expected: %d]", expected_total);
        }
    }
    printf("\n");
    // Array
    domino* line_array = line_to_array(line);
    printf("array: [ ");
    for (unsigned int i = 0; i < array_length; i++)
    {
        print_tile(line_array[i]);
        array_fail = array_fail || line_array[i] != tiles[i];
        printf(i != array_length - 1 ? ", " : " ");
    }
    printf("] ");
    if (do_verify)
    {
        print_pass(!array_fail);
    }
    printf("\n");
    free(line_array);
    // Destroy
    line = line_destroy(line);

    fails = length_fail + correct_fail + total_fail + array_fail;
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
