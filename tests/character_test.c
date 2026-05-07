/**
 * @brief It tests character module
 *
 * @file character_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "character.h"
#include "character_test.h"
#include "test.h"

#define MAX_TESTS 41

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Character:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_character_create();
  if (all || test == 2)  test2_character_create();
  if (all || test == 3)  test1_character_get_id();
  if (all || test == 4)  test2_character_get_id();
  if (all || test == 5)  test1_character_set_name();
  if (all || test == 6)  test2_character_set_name();
  if (all || test == 7)  test3_character_set_name();
  if (all || test == 8)  test1_character_get_name();
  if (all || test == 9)  test2_character_get_name();
  if (all || test == 10) test1_character_set_gdesc();
  if (all || test == 11) test2_character_set_gdesc();
  if (all || test == 12) test1_character_get_gdesc();
  if (all || test == 13) test2_character_get_gdesc();
  if (all || test == 14) test1_character_set_location();
  if (all || test == 15) test2_character_set_location();
  if (all || test == 16) test3_character_set_location();
  if (all || test == 17) test1_character_get_location();
  if (all || test == 18) test2_character_get_location();
  if (all || test == 19) test1_character_set_health();
  if (all || test == 20) test2_character_set_health();
  if (all || test == 21) test3_character_set_health();
  if (all || test == 22) test1_character_get_health();
  if (all || test == 23) test2_character_get_health();
  if (all || test == 24) test1_character_set_friendly();
  if (all || test == 25) test2_character_set_friendly();
  if (all || test == 26) test1_character_get_friendly();
  if (all || test == 27) test2_character_get_friendly();
  if (all || test == 28) test1_character_set_message();
  if (all || test == 29) test2_character_set_message();
  if (all || test == 30) test3_character_set_message();
  if (all || test == 31) test1_character_get_message();
  if (all || test == 32) test2_character_get_message();
  if (all || test == 33) test1_character_set_following();
  if (all || test == 34) test2_character_set_following();
  if (all || test == 35) test1_character_get_following();
  if (all || test == 36) test2_character_get_following();
  if (all || test == 37) test1_character_set_damage();
  if (all || test == 38) test2_character_set_damage();
  if (all || test == 39) test1_character_get_damage();
  if (all || test == 40) test2_character_get_damage();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- character_create --- */
void test1_character_create() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(c != NULL);
  character_destroy(c);
}

void test2_character_create() {
  Character *c = character_create(NO_ID);
  PRINT_TEST_RESULT(c == NULL);
}

/* --- character_get_id --- */
void test1_character_get_id() {
  Character *c = character_create(7);
  PRINT_TEST_RESULT(character_get_id(c) == 7);
  character_destroy(c);
}

void test2_character_get_id() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_id(c) == NO_ID);
}

/* --- character_set_name / character_get_name --- */
void test1_character_set_name() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, "goblin") == OK);
  character_destroy(c);
}

void test2_character_set_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_name(c, "goblin") == ERROR);
}

void test3_character_set_name() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_name(c, NULL) == ERROR);
  character_destroy(c);
}

void test1_character_get_name() {
  Character *c = character_create(1);
  character_set_name(c, "goblin");
  PRINT_TEST_RESULT(strcmp(character_get_name(c), "goblin") == 0);
  character_destroy(c);
}

void test2_character_get_name() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_name(c) == NULL);
}

/* --- character_set_gdesc / character_get_gdesc --- */
void test1_character_set_gdesc() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_gdesc(c, "o(o_o)") == OK);
  character_destroy(c);
}

void test2_character_set_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_gdesc(c, "o(o_o)") == ERROR);
}

void test1_character_get_gdesc() {
  Character *c = character_create(1);
  character_set_gdesc(c, "o(o_o)");
  PRINT_TEST_RESULT(strcmp(character_get_gdesc(c), "o(o_o)") == 0);
  character_destroy(c);
}

void test2_character_get_gdesc() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_gdesc(c) == NULL);
}

/* --- character_set_location / character_get_location --- */
void test1_character_set_location() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_location(c, 5) == OK);
  character_destroy(c);
}

void test2_character_set_location() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_location(c, 5) == ERROR);
}

void test3_character_set_location() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_location(c, NO_ID) == ERROR);
  character_destroy(c);
}

void test1_character_get_location() {
  Character *c = character_create(1);
  character_set_location(c, 5);
  PRINT_TEST_RESULT(character_get_location(c) == 5);
  character_destroy(c);
}

void test2_character_get_location() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_location(c) == NO_ID);
}

/* --- character_set_health / character_get_health --- */
void test1_character_set_health() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_health(c, 10) == OK);
  character_destroy(c);
}

void test2_character_set_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_health(c, 10) == ERROR);
}

void test3_character_set_health() {
  /* Salud negativa debe quedar en 0 */
  Character *c = character_create(1);
  character_set_health(c, -5);
  PRINT_TEST_RESULT(character_get_health(c) == 0);
  character_destroy(c);
}

void test1_character_get_health() {
  Character *c = character_create(1);
  character_set_health(c, 10);
  PRINT_TEST_RESULT(character_get_health(c) == 10);
  character_destroy(c);
}

void test2_character_get_health() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_health(c) == -1);
}

/* --- character_set_friendly / character_get_friendly --- */
void test1_character_set_friendly() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == OK);
  character_destroy(c);
}

void test2_character_set_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_friendly(c, TRUE) == ERROR);
}

void test1_character_get_friendly() {
  Character *c = character_create(1);
  character_set_friendly(c, TRUE);
  PRINT_TEST_RESULT(character_get_friendly(c) == TRUE);
  character_destroy(c);
}

void test2_character_get_friendly() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_friendly(c) == FALSE);
}

/* --- character_set_message / character_get_message --- */
void test1_character_set_message() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, "Hola aventurero") == OK);
  character_destroy(c);
}

void test2_character_set_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_message(c, "Hola") == ERROR);
}

void test3_character_set_message() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_message(c, NULL) == ERROR);
  character_destroy(c);
}

void test1_character_get_message() {
  Character *c = character_create(1);
  character_set_message(c, "Hola aventurero");
  PRINT_TEST_RESULT(strcmp(character_get_message(c), "Hola aventurero") == 0);
  character_destroy(c);
}

void test2_character_get_message() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_message(c) == NULL);
}

/* --- character_set_following / character_get_following --- */
void test1_character_set_following() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_following(c, 3) == OK);
  character_destroy(c);
}

void test2_character_set_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_following(c, 3) == ERROR);
}

void test1_character_get_following() {
  Character *c = character_create(1);
  character_set_following(c, 3);
  PRINT_TEST_RESULT(character_get_following(c) == 3);
  character_destroy(c);
}

void test2_character_get_following() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_following(c) == NO_ID);
}

/* --- character_set_damage / character_get_damage --- */
void test1_character_set_damage() {
  Character *c = character_create(1);
  PRINT_TEST_RESULT(character_set_damage(c, 5) == OK);
  character_destroy(c);
}

void test2_character_set_damage() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_set_damage(c, 5) == ERROR);
}

void test1_character_get_damage() {
  Character *c = character_create(1);
  character_set_damage(c, 5);
  PRINT_TEST_RESULT(character_get_damage(c) == 5);
  character_destroy(c);
}

void test2_character_get_damage() {
  Character *c = NULL;
  PRINT_TEST_RESULT(character_get_damage(c) == 0);
}