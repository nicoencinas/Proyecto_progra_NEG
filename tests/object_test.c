/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @version 1.0
 * @date 09-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 33

/**
 * @brief Main function for OBJECT unit tests.
 *
 * You may execute ALL or a SINGLE test:
 *   1.- No parameter -> ALL tests are executed
 *   2.- A number means a particular test (identified by that number) is executed
 */
int main(int argc, char **argv)
{
    int test = 0;
    int all = 1;

    if (argc < 2)
    {
        printf("Running all tests for module Object:\n");
    }
    else
    {
        test = atoi(argv[1]);
        all = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS)
        {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test == 1)
        test1_object_create();
    if (all || test == 2)
        test2_object_create();
    if (all || test == 3)
        test3_object_create();
    if (all || test == 4)
        test1_object_destroy();
    if (all || test == 5)
        test2_object_destroy();
    if (all || test == 6)
        test1_object_get_id();
    if (all || test == 7)
        test2_object_get_id();
    if (all || test == 8)
        test1_object_set_name();
    if (all || test == 9)
        test2_object_set_name();
    if (all || test == 10)
        test3_object_set_name();
    if (all || test == 11)
        test1_object_get_name();
    if (all || test == 12)
        test2_object_get_name();
    if (all || test == 13)
        test1_object_set_desc();
    if (all || test == 14)
        test2_object_set_desc();
    if (all || test == 15)
        test3_object_set_desc();
    if (all || test == 16)
        test1_object_get_desc();
    if (all || test == 17)
        test2_object_get_desc();
    if (all || test == 18)
        test1_object_set_health();
    if (all || test == 19)
        test2_object_set_health();
    if (all || test == 20)
        test1_object_get_health();
    if (all || test == 21)
        test2_object_get_health();
    if (all || test == 22)
        test1_object_set_movable();
    if (all || test == 23)
        test2_object_set_movable();
    if (all || test == 24)
        test1_object_get_movable();
    if (all || test == 25)
        test2_object_get_movable();
    if (all || test == 26)
        test1_object_set_dependency();
    if (all || test == 27)
        test2_object_set_dependency();
    if (all || test == 28)
        test1_object_get_dependency();
    if (all || test == 29)
        test2_object_get_dependency();
    if (all || test == 30)
        test1_object_set_open();
    if (all || test == 31)
        test2_object_set_open();
    if (all || test == 32)
        test1_object_get_open();
    if (all || test == 33)
        test2_object_get_open();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_object_create()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(o != NULL);
    object_destroy(o);
}

void test2_object_create()
{
    Object *o = object_create(5);
    PRINT_TEST_RESULT(object_get_id(o) == 5);
    object_destroy(o);
}

void test3_object_create()
{
    Object *o = object_create(NO_ID);
    PRINT_TEST_RESULT(o == NULL);
}

void test1_object_destroy()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_destroy(o) == OK);
}

void test2_object_destroy()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_destroy(o) == ERROR);
}

void test1_object_get_id()
{
    Object *o = object_create(99);
    PRINT_TEST_RESULT(object_get_id(o) == 99);
    object_destroy(o);
}

void test2_object_get_id()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

void test1_object_set_name()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, "Sword") == OK);
    object_destroy(o);
}

void test2_object_set_name()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_name(o, "Sword") == ERROR);
}

void test3_object_set_name()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
    object_destroy(o);
}

void test1_object_get_name()
{
    Object *o = object_create(1);
    object_set_name(o, "Shield");
    PRINT_TEST_RESULT(strcmp(object_get_name(o), "Shield") == 0);
    object_destroy(o);
}

void test2_object_get_name()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

void test1_object_set_desc()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_desc(o, "A shiny sword") == OK);
    object_destroy(o);
}

void test2_object_set_desc()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_desc(o, "desc") == ERROR);
}

void test3_object_set_desc()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_desc(o, NULL) == ERROR);
    object_destroy(o);
}

void test1_object_get_desc()
{
    Object *o = object_create(1);
    object_set_desc(o, "An old shield");
    PRINT_TEST_RESULT(strcmp(object_get_desc(o), "An old shield") == 0);
    object_destroy(o);
}

void test2_object_get_desc()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_desc(o) == NULL);
}

void test1_object_set_health()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_health(o, 100) == OK);
    object_destroy(o);
}

void test2_object_set_health()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_health(o, 100) == ERROR);
}

void test1_object_get_health()
{
    Object *o = object_create(1);
    object_set_health(o, 50);
    PRINT_TEST_RESULT(object_get_health(o) == 50);
    object_destroy(o);
}

void test2_object_get_health()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_health(o) == -1);
}

void test1_object_set_movable()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
    object_destroy(o);
}

void test2_object_set_movable()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_movable(o, FALSE) == ERROR);
}

void test1_object_get_movable()
{
    Object *o = object_create(1);
    object_set_movable(o, TRUE);
    PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
    object_destroy(o);
}

void test2_object_get_movable()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

void test1_object_set_dependency()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_dependency(o, 2) == OK);
    object_destroy(o);
}

void test2_object_set_dependency()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_dependency(o, 2) == ERROR);
}

void test1_object_get_dependency()
{
    Object *o = object_create(1);
    object_set_dependency(o, 5);
    PRINT_TEST_RESULT(object_get_dependency(o) == 5);
    object_destroy(o);
}

void test2_object_get_dependency()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}

void test1_object_set_open()
{
    Object *o = object_create(1);
    PRINT_TEST_RESULT(object_set_open(o, 3) == OK);
    object_destroy(o);
}

void test2_object_set_open()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_set_open(o, 3) == ERROR);
}

void test1_object_get_open()
{
    Object *o = object_create(1);
    object_set_open(o, 7);
    PRINT_TEST_RESULT(object_get_open(o) == 7);
    object_destroy(o);
}

void test2_object_get_open()
{
    Object *o = NULL;
    PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}
