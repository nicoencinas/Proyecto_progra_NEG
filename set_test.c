/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @version 1.0
 * @date 09-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 18

/**
 * @brief Main function for SET unit tests.
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
        printf("Running all tests for module Set:\n");
    } else {
        test = atoi(argv[1]);
        all  = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test ==  1) test1_set_create();
    if (all || test ==  2) test2_set_create();
    if (all || test ==  3) test1_set_destroy();
    if (all || test ==  4) test2_set_destroy();
    if (all || test ==  5) test1_set_add();
    if (all || test ==  6) test2_set_add();
    if (all || test ==  7) test3_set_add();
    if (all || test ==  8) test4_set_add();
    if (all || test ==  9) test1_set_del();
    if (all || test == 10) test2_set_del();
    if (all || test == 11) test3_set_del();
    if (all || test == 12) test4_set_del();
    if (all || test == 13) test1_set_find();
    if (all || test == 14) test2_set_find();
    if (all || test == 15) test3_set_find();
    if (all || test == 16) test4_set_find();
    if (all || test == 17) test1_set_print();
    if (all || test == 18) test2_set_print();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_set_create()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(s != NULL);
    set_destroy(s);
}

void test2_set_create()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, 1) == FALSE);
    set_destroy(s);
}

void test1_set_destroy()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_destroy(s) == OK);
}

void test2_set_destroy()
{
    Set *s = NULL;
    PRINT_TEST_RESULT(set_destroy(s) == ERROR);
}

void test1_set_add()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_add(s, 10) == OK);
    set_destroy(s);
}

void test2_set_add()
{
    Set *s = NULL;
    PRINT_TEST_RESULT(set_add(s, 10) == ERROR);
}

void test3_set_add()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_add(s, NO_ID) == ERROR);
    set_destroy(s);
}

void test4_set_add()
{
    Set *s = set_create();
    set_add(s, 5);
    PRINT_TEST_RESULT(set_add(s, 5) == ERROR);
    set_destroy(s);
}

void test1_set_del()
{
    Set *s = set_create();
    set_add(s, 20);
    PRINT_TEST_RESULT(set_del(s, 20) == OK);
    set_destroy(s);
}

void test2_set_del()
{
    Set *s = NULL;
    PRINT_TEST_RESULT(set_del(s, 20) == ERROR);
}

void test3_set_del()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_del(s, 99) == ERROR);
    set_destroy(s);
}

void test4_set_del()
{
    Set *s = set_create();
    set_add(s, 7);
    set_del(s, 7);
    PRINT_TEST_RESULT(set_find(s, 7) == FALSE);
    set_destroy(s);
}

void test1_set_find()
{
    Set *s = set_create();
    set_add(s, 42);
    PRINT_TEST_RESULT(set_find(s, 42) == TRUE);
    set_destroy(s);
}

void test2_set_find()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, 42) == FALSE);
    set_destroy(s);
}

void test3_set_find()
{
    Set *s = NULL;
    PRINT_TEST_RESULT(set_find(s, 1) == FALSE);
}

void test4_set_find()
{
    Set *s = set_create();
    PRINT_TEST_RESULT(set_find(s, NO_ID) == FALSE);
    set_destroy(s);
}

void test1_set_print()
{
    Set *s = set_create();
    set_add(s, 1);
    set_add(s, 2);
    set_add(s, 3);
    set_print(s);
    PRINT_TEST_RESULT(TRUE);
    set_destroy(s);
}

void test2_set_print()
{
    set_print(NULL);
    PRINT_TEST_RESULT(TRUE);
}
