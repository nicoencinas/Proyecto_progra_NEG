/**
 * @brief It tests player module
 *
 * @file player_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "player.h"
#include "player_test.h"
#include "test.h"

#define MAX_TESTS 54

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Player:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_player_create();
  if (all || test == 2)  test2_player_create();
  if (all || test == 3)  test1_player_get_id();
  if (all || test == 4)  test2_player_get_id();
  if (all || test == 5)  test1_player_set_name();
  if (all || test == 6)  test2_player_set_name();
  if (all || test == 7)  test3_player_set_name();
  if (all || test == 8)  test1_player_get_name();
  if (all || test == 9)  test2_player_get_name();
  if (all || test == 10) test1_player_set_location();
  if (all || test == 11) test2_player_set_location();
  if (all || test == 12) test3_player_set_location();
  if (all || test == 13) test1_player_get_location();
  if (all || test == 14) test2_player_get_location();
  if (all || test == 15) test1_player_set_health();
  if (all || test == 16) test2_player_set_health();
  if (all || test == 17) test1_player_get_health();
  if (all || test == 18) test2_player_get_health();
  if (all || test == 19) test1_player_add_object();
  if (all || test == 20) test2_player_add_object();
  if (all || test == 21) test3_player_add_object();
  if (all || test == 22) test1_player_remove_object();
  if (all || test == 23) test2_player_remove_object();
  if (all || test == 24) test1_player_has_object();
  if (all || test == 25) test2_player_has_object();
  if (all || test == 26) test3_player_has_object();
  if (all || test == 27) test1_player_set_gdesc();
  if (all || test == 28) test2_player_set_gdesc();
  if (all || test == 29) test1_player_get_gdesc();
  if (all || test == 30) test2_player_get_gdesc();
  if (all || test == 31) test1_player_set_damage();
  if (all || test == 32) test2_player_set_damage();
  if (all || test == 33) test1_player_get_damage();
  if (all || test == 34) test2_player_get_damage();
  if (all || test == 35) test1_player_set_dtaken();
  if (all || test == 36) test2_player_set_dtaken();
  if (all || test == 37) test1_player_get_dtaken();
  if (all || test == 38) test2_player_get_dtaken();
  if (all || test == 39) test1_player_set_max_health();
  if (all || test == 40) test2_player_set_max_health();
  if (all || test == 41) test1_player_get_max_health();
  if (all || test == 42) test2_player_get_max_health();
  if (all || test == 43) test1_player_set_max_turn();
  if (all || test == 44) test2_player_set_max_turn();
  if (all || test == 45) test1_player_get_max_turn();
  if (all || test == 46) test2_player_get_max_turn();
  if (all || test == 47) test1_player_set_n_turn();
  if (all || test == 48) test2_player_set_n_turn();
  if (all || test == 49) test1_player_get_n_turn();
  if (all || test == 50) test2_player_get_n_turn();
  if (all || test == 51) test1_player_set_teammate();
  if (all || test == 52) test2_player_set_teammate();
  if (all || test == 53) test1_player_get_teammate();
  if (all || test == 54) test2_player_get_teammate();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- player_create --- */
void test1_player_create() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(p != NULL);
  player_destroy(p);
}

void test2_player_create() {
  Player *p = player_create(NO_ID);
  PRINT_TEST_RESULT(p == NULL);
}

/* --- player_get_id --- */
void test1_player_get_id() {
  Player *p = player_create(3);
  PRINT_TEST_RESULT(player_get_id(p) == 3);
  player_destroy(p);
}

void test2_player_get_id() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_id(p) == NO_ID);
}

/* --- player_set_name / player_get_name --- */
void test1_player_set_name() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_name(p, "heroe") == OK);
  player_destroy(p);
}

void test2_player_set_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_name(p, "heroe") == ERROR);
}

void test3_player_set_name() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_name(p, NULL) == ERROR);
  player_destroy(p);
}

void test1_player_get_name() {
  Player *p = player_create(1);
  player_set_name(p, "heroe");
  PRINT_TEST_RESULT(strcmp(player_get_name(p), "heroe") == 0);
  player_destroy(p);
}

void test2_player_get_name() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_name(p) == NULL);
}

/* --- player_set_location / player_get_location --- */
void test1_player_set_location() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_location(p, 5) == OK);
  player_destroy(p);
}

void test2_player_set_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_location(p, 5) == ERROR);
}

void test3_player_set_location() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_location(p, NO_ID) == ERROR);
  player_destroy(p);
}

void test1_player_get_location() {
  Player *p = player_create(1);
  player_set_location(p, 5);
  PRINT_TEST_RESULT(player_get_location(p) == 5);
  player_destroy(p);
}

void test2_player_get_location() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_location(p) == NO_ID);
}

/* --- player_set_health / player_get_health --- */
void test1_player_set_health() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_health(p, 8) == OK);
  player_destroy(p);
}

void test2_player_set_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_health(p, 8) == ERROR);
}

void test1_player_get_health() {
  Player *p = player_create(1);
  player_set_health(p, 8);
  PRINT_TEST_RESULT(player_get_health(p) == 8);
  player_destroy(p);
}

void test2_player_get_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_health(p) == -1);
}

/* --- player_add_object / player_remove_object / player_has_object --- */
void test1_player_add_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_add_object(p, 10) == OK);
  player_destroy(p);
}

void test2_player_add_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_add_object(p, 10) == ERROR);
}

void test3_player_add_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_add_object(p, NO_ID) == ERROR);
  player_destroy(p);
}

void test1_player_remove_object() {
  Player *p = player_create(1);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_remove_object(p, 10) == OK);
  player_destroy(p);
}

void test2_player_remove_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_remove_object(p, 10) == ERROR);
}

void test1_player_has_object() {
  Player *p = player_create(1);
  player_add_object(p, 10);
  PRINT_TEST_RESULT(player_has_object(p, 10) == TRUE);
  player_destroy(p);
}

void test2_player_has_object() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_has_object(p, 10) == FALSE);
  player_destroy(p);
}

void test3_player_has_object() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_has_object(p, 10) == FALSE);
}

/* --- player_set_gdesc / player_get_gdesc --- */
void test1_player_set_gdesc() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_gdesc(p, "(o_o)") == OK);
  player_destroy(p);
}

void test2_player_set_gdesc() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_gdesc(p, "(o_o)") == ERROR);
}

void test1_player_get_gdesc() {
  Player *p = player_create(1);
  player_set_gdesc(p, "(o_o)");
  PRINT_TEST_RESULT(strcmp(player_get_gdesc(p), "(o_o)") == 0);
  player_destroy(p);
}

void test2_player_get_gdesc() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_gdesc(p) == NULL);
}

/* --- player_set_damage / player_get_damage --- */
void test1_player_set_damage() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_damage(p, 3) == OK);
  player_destroy(p);
}

void test2_player_set_damage() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_damage(p, 3) == ERROR);
}

void test1_player_get_damage() {
  Player *p = player_create(1);
  player_set_damage(p, 3);
  PRINT_TEST_RESULT(player_get_damage(p) == 3);
  player_destroy(p);
}

void test2_player_get_damage() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_damage(p) == -1);
}

/* --- player_set_dtaken / player_get_dtaken --- */
void test1_player_set_dtaken() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_dtaken(p, 2) == OK);
  player_destroy(p);
}

void test2_player_set_dtaken() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_dtaken(p, 2) == ERROR);
}

void test1_player_get_dtaken() {
  Player *p = player_create(1);
  player_set_dtaken(p, 2);
  PRINT_TEST_RESULT(player_get_dtaken(p) == 2);
  player_destroy(p);
}

void test2_player_get_dtaken() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_dtaken(p) == -1);
}

/* --- player_set_max_health / player_get_max_health --- */
void test1_player_set_max_health() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_max_health(p, 20) == OK);
  player_destroy(p);
}

void test2_player_set_max_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_max_health(p, 20) == ERROR);
}

void test1_player_get_max_health() {
  Player *p = player_create(1);
  player_set_max_health(p, 20);
  PRINT_TEST_RESULT(player_get_max_health(p) == 20);
  player_destroy(p);
}

void test2_player_get_max_health() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_max_health(p) == -1);
}

/* --- player_set_max_turn / player_get_max_turn --- */
void test1_player_set_max_turn() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_max_turn(p, 3) == OK);
  player_destroy(p);
}

void test2_player_set_max_turn() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_max_turn(p, 3) == ERROR);
}

void test1_player_get_max_turn() {
  Player *p = player_create(1);
  player_set_max_turn(p, 3);
  PRINT_TEST_RESULT(player_get_max_turn(p) == 3);
  player_destroy(p);
}

void test2_player_get_max_turn() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_max_turn(p) == -1);
}

/* --- player_set_n_turn / player_get_n_turn --- */
void test1_player_set_n_turn() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_n_turn(p, 2) == OK);
  player_destroy(p);
}

void test2_player_set_n_turn() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_n_turn(p, 2) == ERROR);
}

void test1_player_get_n_turn() {
  Player *p = player_create(1);
  player_set_n_turn(p, 2);
  PRINT_TEST_RESULT(player_get_n_turn(p) == 2);
  player_destroy(p);
}

void test2_player_get_n_turn() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_n_turn(p) == -1);
}

/* --- player_set_teammate / player_get_teammate --- */
void test1_player_set_teammate() {
  Player *p = player_create(1);
  PRINT_TEST_RESULT(player_set_teammate(p, 2) == OK);
  player_destroy(p);
}

void test2_player_set_teammate() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_set_teammate(p, 2) == ERROR);
}

void test1_player_get_teammate() {
  Player *p = player_create(1);
  player_set_teammate(p, 2);
  PRINT_TEST_RESULT(player_get_teammate(p) == 2);
  player_destroy(p);
}

void test2_player_get_teammate() {
  Player *p = NULL;
  PRINT_TEST_RESULT(player_get_teammate(p) == NO_ID);
}