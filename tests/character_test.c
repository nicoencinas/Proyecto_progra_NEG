/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @author NICOLAS
 * @version 1.1
 * @date 09-03-2026
 * @copyright GNU Public License
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"
 
#define MAX_TESTS 38
 
/**
 * @brief Main function for CHARACTER unit tests.
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
        printf("Running all tests for module Character:\n");
    } else {
        test = atoi(argv[1]);
        all  = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }
 
    if (all || test ==  1) test1_character_create();
    if (all || test ==  2) test2_character_create();
    if (all || test ==  3) test3_character_create();
    if (all || test ==  4) test1_character_destroy();
    if (all || test ==  5) test2_character_destroy();
    if (all || test ==  6) test1_character_get_id();
    if (all || test ==  7) test2_character_get_id();
    if (all || test ==  8) test1_character_set_name();
    if (all || test ==  9) test2_character_set_name();
    if (all || test == 10) test3_character_set_name();
    if (all || test == 11) test1_character_get_name();
    if (all || test == 12) test2_character_get_name();
    if (all || test == 13) test1_character_set_gdesc();
    if (all || test == 14) test2_character_set_gdesc();
    if (all || test == 15) test3_character_set_gdesc();
    if (all || test == 16) test1_character_get_gdesc();
    if (all || test == 17) test2_character_get_gdesc();
    if (all || test == 18) test1_character_set_location();
    if (all || test == 19) test2_character_set_location();
    if (all || test == 20) test3_character_set_location();
    if (all || test == 21) test1_character_get_location();
    if (all || test == 22) test2_character_get_location();
    if (all || test == 23) test1_character_set_health();
    if (all || test == 24) test2_character_set_health();
    if (all || test == 25) test3_character_set_health();
    if (all || test == 26) test1_character_get_health();
    if (all || test == 27) test2_character_get_health();
    if (all || test == 28) test1_character_set_friendly();
    if (all || test == 29) test2_character_set_friendly();
    if (all || test == 30) test1_character_get_friendly();
    if (all || test == 31) test2_character_get_friendly();
    if (all || test == 32) test1_character_set_message();
    if (all || test == 33) test2_character_set_message();
    if (all || test == 34) test3_character_set_message();
    if (all || test == 35) test1_character_get_message();
    if (all || test == 36) test2_character_get_message();
    if (all || test == 37) test1_character_print();
    if (all || test == 38) test2_character_print();
 
    PRINT_PASSED_PERCENTAGE;
 
    return 1;
}
 
void test1_character_create()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(c != NULL);
    character_destroy(c);
}
 
void test2_character_create()
{
    Character *c = character_create(7);
    PRINT_TEST_RESULT(character_get_id(c) == 7);
    character_destroy(c);
}
 
void test3_character_create()
{
    Character *c = character_create(NO_ID);
    PRINT_TEST_RESULT(c == NULL);
}
 
void test1_character_destroy()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_destroy(c) == OK);
}
 
void test2_character_destroy()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_destroy(c) == ERROR);
}
 
void test1_character_get_id()
{
    Character *c = character_create(15);
    PRINT_TEST_RESULT(character_get_id(c) == 15);
    character_destroy(c);
}
 
void test2_character_get_id()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}
 
void test1_character_set_name()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_name(c, "Guide") == OK);
    character_destroy(c);
}
 
void test2_character_set_name()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_name(c, "Guide") == ERROR);
}
 
void test3_character_set_name()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_name(c, NULL) == ERROR);
    character_destroy(c);
}
 
void test1_character_get_name()
{
    Character *c = character_create(1);
    character_set_name(c, "Goblin");
    PRINT_TEST_RESULT(strcmp(character_get_name(c), "Goblin") == 0);
    character_destroy(c);
}
 
void test2_character_get_name()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_name(c) == NULL);
}
 
void test1_character_set_gdesc()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_gdesc(c, "^_^") == OK);
    character_destroy(c);
}
 
void test2_character_set_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_gdesc(c, "^_^") == ERROR);
}
 
void test3_character_set_gdesc()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_gdesc(c, NULL) == ERROR);
    character_destroy(c);
}
 
void test1_character_get_gdesc()
{
    Character *c = character_create(1);
    character_set_gdesc(c, "o_O");
    PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "o_O") == 0);
    character_destroy(c);
}
 
void test2_character_get_gdesc()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}
 
void test1_character_set_location()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_location(c, 5) == OK);
    character_destroy(c);
}
 
void test2_character_set_location()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_location(c, 5) == ERROR);
}
 
void test3_character_set_location()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_location(c, NO_ID) == ERROR);
    character_destroy(c);
}
 
void test1_character_get_location()
{
    Character *c = character_create(1);
    character_set_location(c, 5);
    PRINT_TEST_RESULT(character_get_location(c) == 5);
    character_destroy(c);
}
 
void test2_character_get_location()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_location(c) == NO_ID);
}
 
void test1_character_set_health()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_health(c, 100) == OK);
    character_destroy(c);
}
 
void test2_character_set_health()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_health(c, 100) == ERROR);
}
 
void test3_character_set_health()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_health(c, -5) == ERROR);
    character_destroy(c);
}
 
void test1_character_get_health()
{
    Character *c = character_create(1);
    character_set_health(c, 75);
    PRINT_TEST_RESULT(character_get_health(c) == 75);
    character_destroy(c);
}
 
void test2_character_get_health()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_health(c) == -1);
}
 
void test1_character_set_friendly()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
    character_destroy(c);
}
 
void test2_character_set_friendly()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}
 
void test1_character_get_friendly()
{
    Character *c = character_create(1);
    character_set_friendly(c, TRUE);
    PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
    character_destroy(c);
}
 
void test2_character_get_friendly()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}
 
void test1_character_set_message()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_message(c, "Hello traveler!") == OK);
    character_destroy(c);
}
 
void test2_character_set_message()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_set_message(c, "Welcome to the castle!") == ERROR);
}
 
void test3_character_set_message()
{
    Character *c = character_create(1);
    PRINT_TEST_RESULT(character_set_message(c, NULL) == ERROR);
    character_destroy(c);
}
 
void test1_character_get_message()
{
    Character *c = character_create(1);
    character_set_message(c, "Welcome to the castle!");
    PRINT_TEST_RESULT(strcmp(character_get_message(c), "Welcome to the castle!") == 0);
    character_destroy(c);
}
 
void test2_character_get_message()
{
    Character *c = NULL;
    PRINT_TEST_RESULT(character_get_message(c) == NULL);
}
 
void test1_character_print()
{
    Character *c = character_create(40);
    character_set_name(c, "Guide");
    character_set_gdesc(c, "(^_^)");
    character_set_location(c, 121);
    character_set_health(c, 10);
    character_set_friendly(c, TRUE);
    character_set_message(c, "Welcome to the castle!");
    PRINT_TEST_RESULT(character_print(c) == OK);
    character_destroy(c);
}
 
void test2_character_print()
{
    Character *c = character_create(41);
    character_set_name(c, "Goblin");
    character_set_gdesc(c, ">:-(");
    character_set_location(c, 11);
    character_set_health(c, 5);
    character_set_friendly(c, FALSE);
    character_set_message(c, "I will crush you!");
    PRINT_TEST_RESULT(character_print(c) == OK);
    character_destroy(c);
}