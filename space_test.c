/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @version 1.0
 * @date 09-03-2026
 * @copyright GNU Public License
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"
 
#define MAX_TESTS 34
 
/**
 * @brief Main function for SPACE unit tests.
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
        printf("Running all tests for module Space:\n");
    } else {
        test = atoi(argv[1]);
        all  = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }
 
    if (all || test ==  1) test1_space_create();
    if (all || test ==  2) test2_space_create();
    if (all || test ==  3) test3_space_create();
    if (all || test ==  4) test1_space_destroy();
    if (all || test ==  5) test2_space_destroy();
    if (all || test ==  6) test1_space_get_id();
    if (all || test ==  7) test2_space_get_id();
    if (all || test ==  8) test1_space_set_name();
    if (all || test ==  9) test2_space_set_name();
    if (all || test == 10) test3_space_set_name();
    if (all || test == 11) test1_space_get_name();
    if (all || test == 12) test2_space_get_name();
    if (all || test == 13) test1_space_add_object();
    if (all || test == 14) test2_space_add_object();
    if (all || test == 15) test3_space_add_object();
    if (all || test == 16) test1_space_remove_object();
    if (all || test == 17) test2_space_remove_object();
    if (all || test == 18) test3_space_remove_object();
    if (all || test == 19) test1_space_has_object();
    if (all || test == 20) test2_space_has_object();
    if (all || test == 21) test3_space_has_object();
    if (all || test == 22) test1_space_set_character();
    if (all || test == 23) test2_space_set_character();
    if (all || test == 24) test1_space_get_character();
    if (all || test == 25) test2_space_get_character();
    if (all || test == 26) test1_space_set_gdesc_at();
    if (all || test == 27) test2_space_set_gdesc_at();
    if (all || test == 28) test3_space_set_gdesc_at();
    if (all || test == 29) test1_space_get_gdesc_at();
    if (all || test == 30) test2_space_get_gdesc_at();
    if (all || test == 31) test1_space_discovered();
    if (all || test == 32) test2_space_discovered();
    if (all || test == 33) test1_space_print();
    if (all || test == 34) test2_space_print();
 
    PRINT_PASSED_PERCENTAGE;
 
    return 1;
}
 
void test1_space_create()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(s != NULL);
    space_destroy(s);
}
 
void test2_space_create()
{
    Space *s = space_create(10);
    PRINT_TEST_RESULT(space_get_id(s) == 10);
    space_destroy(s);
}
 
void test3_space_create()
{
    Space *s = space_create(NO_ID);
    PRINT_TEST_RESULT(s == NULL);
}

 
void test1_space_destroy()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_destroy(s) == OK);
}
 
void test2_space_destroy()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_destroy(s) == ERROR);
}
 
 
void test1_space_get_id()
{
    Space *s = space_create(55);
    PRINT_TEST_RESULT(space_get_id(s) == 55);
    space_destroy(s);
}
 
void test2_space_get_id()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}
 
void test1_space_set_name()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_set_name(s, "Forest") == OK);
    space_destroy(s);
}
 
void test2_space_set_name()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_name(s, "Forest") == ERROR);
}
 
void test3_space_set_name()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
    space_destroy(s);
}
 
void test1_space_get_name()
{
    Space *s = space_create(1);
    space_set_name(s, "Cave");
    PRINT_TEST_RESULT(strcmp(space_get_name(s), "Cave") == 0);
    space_destroy(s);
}
 
void test2_space_get_name()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_name(s) == NULL);
}
 
void test1_space_add_object()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
    space_destroy(s);
}
 
void test2_space_add_object()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}
 
void test3_space_add_object()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);
    space_destroy(s);
}
 
void test1_space_remove_object()
{
    Space *s = space_create(1);
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
    space_destroy(s);
}
 
void test2_space_remove_object()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR);
}
 
void test3_space_remove_object()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_remove_object(s, 99) == ERROR);
    space_destroy(s);
}
 
void test1_space_has_object()
{
    Space *s = space_create(1);
    space_add_object(s, 20);
    PRINT_TEST_RESULT(space_has_object(s, 20) == TRUE);
    space_destroy(s);
}
 
void test2_space_has_object()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_has_object(s, 20) == FALSE);
    space_destroy(s);
}
 
void test3_space_has_object()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_has_object(s, 20) == FALSE);
}
 
void test1_space_set_character()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_set_character(s, 5) == OK);
    space_destroy(s);
}
 
void test2_space_set_character()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_character(s, 5) == ERROR);
}
 
void test1_space_get_character()
{
    Space *s = space_create(1);
    space_set_character(s, 7);
    PRINT_TEST_RESULT(space_get_character(s) == 7);
    space_destroy(s);
}
 
void test2_space_get_character()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_character(s) == NO_ID);
}
 
void test1_space_set_gdesc_at()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc_at(s, 0, "  ~~~  ") == OK);
    space_destroy(s);
}
 
void test2_space_set_gdesc_at()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_set_gdesc_at(s, 0, "  ~~~  ") == ERROR);
}
 
void test3_space_set_gdesc_at()
{
    /* Línea fuera de rango */
    Space *s = space_create(1);
    PRINT_TEST_RESULT(space_set_gdesc_at(s, 5, "  ~~~  ") == ERROR);
    space_destroy(s);
}
 
void test1_space_get_gdesc_at()
{
    Space *s = space_create(1);
    space_set_gdesc_at(s, 2, " ^^^^^ ");
    PRINT_TEST_RESULT(strcmp(space_get_gdesc_at(s, 2), " ^^^^^ ") == 0);
    space_destroy(s);
}
 
void test2_space_get_gdesc_at()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_get_gdesc_at(s, 0) == NULL);
}
 
 
void test1_space_discovered()
{
    Space *s = space_create(1);
    PRINT_TEST_RESULT(Space_discovered(s) == OK);
    space_destroy(s);
}
 
void test2_space_discovered()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(Space_discovered(s) == ERROR);
}
 
void test1_space_print()
{
    Space *s = space_create(1);
    space_set_name(s, "Dungeon");
    space_add_object(s, 10);
    PRINT_TEST_RESULT(space_print(s) == OK);
    space_destroy(s);
}
 
void test2_space_print()
{
    Space *s = NULL;
    PRINT_TEST_RESULT(space_print(s) == ERROR);
}