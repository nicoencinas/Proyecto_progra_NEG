/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @version 1.0
 * @date 09-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 34

/**
 * @brief Main function for LINK unit tests.
 *
 * You may execute ALL or a SINGLE test:
 *   1.- No parameter -> ALL tests are executed
 *   2.- A number means a particular test (identified by that number) is executed
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all  = 1;

    if (argc < 2) {
        printf("Running all tests for module Link:\n");
    } else {
        test = atoi(argv[1]);
        all  = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test ==  1) test1_link_create();
    if (all || test ==  2) test2_link_create();
    if (all || test ==  3) test3_link_create();
    if (all || test ==  4) test1_link_destroy();
    if (all || test ==  5) test2_link_destroy();
    if (all || test ==  6) test1_link_get_id();
    if (all || test ==  7) test2_link_get_id();
    if (all || test ==  8) test1_link_set_name();
    if (all || test ==  9) test2_link_set_name();
    if (all || test == 10) test3_link_set_name();
    if (all || test == 11) test1_link_get_name();
    if (all || test == 12) test2_link_get_name();
    if (all || test == 13) test1_link_set_origin();
    if (all || test == 14) test2_link_set_origin();
    if (all || test == 15) test3_link_set_origin();
    if (all || test == 16) test1_link_get_origin();
    if (all || test == 17) test2_link_get_origin();
    if (all || test == 18) test1_link_set_destination();
    if (all || test == 19) test2_link_set_destination();
    if (all || test == 20) test3_link_set_destination();
    if (all || test == 21) test1_link_get_destination();
    if (all || test == 22) test2_link_get_destination();
    if (all || test == 23) test1_link_set_direction();
    if (all || test == 24) test2_link_set_direction();
    if (all || test == 25) test3_link_set_direction();
    if (all || test == 26) test1_link_get_direction();
    if (all || test == 27) test2_link_get_direction();
    if (all || test == 28) test1_link_set_open();
    if (all || test == 29) test2_link_set_open();
    if (all || test == 30) test1_link_get_open();
    if (all || test == 31) test2_link_get_open();
    if (all || test == 32) test1_link_print();
    if (all || test == 33) test2_link_print();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_link_create()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(l != NULL);
    link_destroy(l);
}

void test2_link_create()
{
    Link *l = link_create(10);
    PRINT_TEST_RESULT(link_get_id(l) == 10);
    link_destroy(l);
}

void test3_link_create()
{
    Link *l = link_create(NO_ID);
    PRINT_TEST_RESULT(l == NULL);
}

void test1_link_destroy()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_destroy(l) == OK);
}

void test2_link_destroy()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_destroy(l) == ERROR);
}

void test1_link_get_id()
{
    Link *l = link_create(77);
    PRINT_TEST_RESULT(link_get_id(l) == 77);
    link_destroy(l);
}

void test2_link_get_id()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

void test1_link_set_name()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_name(l, "North") == OK);
    link_destroy(l);
}

void test2_link_set_name()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_name(l, "North") == ERROR);
}

void test3_link_set_name()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
    link_destroy(l);
}

void test1_link_get_name()
{
    Link *l = link_create(1);
    link_set_name(l, "South");
    PRINT_TEST_RESULT(strcmp(link_get_name(l), "South") == 0);
    link_destroy(l);
}

void test2_link_get_name()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

void test1_link_set_origin()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_origin(l, 5) == OK);
    link_destroy(l);
}

void test2_link_set_origin()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_origin(l, 5) == ERROR);
}

void test3_link_set_origin()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_origin(l, NO_ID) == ERROR);
    link_destroy(l);
}

void test1_link_get_origin()
{
    Link *l = link_create(1);
    link_set_origin(l, 3);
    PRINT_TEST_RESULT(link_get_origin(l) == 3);
    link_destroy(l);
}

void test2_link_get_origin()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_origin(l) == NO_ID);
}

void test1_link_set_destination()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_destination(l, 8) == OK);
    link_destroy(l);
}

void test2_link_set_destination()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_destination(l, 8) == ERROR);
}

void test3_link_set_destination()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_destination(l, NO_ID) == ERROR);
    link_destroy(l);
}

void test1_link_get_destination()
{
    Link *l = link_create(1);
    link_set_destination(l, 9);
    PRINT_TEST_RESULT(link_get_destination(l) == 9);
    link_destroy(l);
}

void test2_link_get_destination()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_destination(l) == NO_ID);
}

void test1_link_set_direction()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(l, N) == OK);
    link_destroy(l);
}

void test2_link_set_direction()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_direction(l, N) == ERROR);
}

void test3_link_set_direction()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_direction(l, NO_DIR) == ERROR);
    link_destroy(l);
}

void test1_link_get_direction()
{
    Link *l = link_create(1);
    link_set_direction(l, S);
    PRINT_TEST_RESULT(link_get_direction(l) == S);
    link_destroy(l);
}

void test2_link_get_direction()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_direction(l) == NO_DIR);
}

void test1_link_set_open()
{
    Link *l = link_create(1);
    PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK);
    link_destroy(l);
}

void test2_link_set_open()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_set_open(l, TRUE) == ERROR);
}

void test1_link_get_open()
{
    Link *l = link_create(1);
    link_set_open(l, TRUE);
    PRINT_TEST_RESULT(link_get_open(l) == TRUE);
    link_destroy(l);
}

void test2_link_get_open()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_get_open(l) == FALSE);
}

/* --- link_print --- */

void test1_link_print()
{
    Link *l = link_create(1);
    link_set_name(l, "East");
    link_set_origin(l, 10);
    link_set_destination(l, 11);
    link_set_direction(l, E);
    link_set_open(l, TRUE);
    PRINT_TEST_RESULT(link_print(l) == OK);
    link_destroy(l);
}

void test2_link_print()
{
    Link *l = NULL;
    PRINT_TEST_RESULT(link_print(l) == ERROR);
}
