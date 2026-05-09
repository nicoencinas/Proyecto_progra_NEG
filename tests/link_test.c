/**
 * @brief It tests link module
 *
 * @file link_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "link.h"
#include "link_test.h"
#include "test.h"

#define MAX_TESTS 29

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Link:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_link_create();
  if (all || test == 2)  test2_link_create();
  if (all || test == 3)  test1_link_get_id();
  if (all || test == 4)  test2_link_get_id();
  if (all || test == 5)  test1_link_set_name();
  if (all || test == 6)  test2_link_set_name();
  if (all || test == 7)  test3_link_set_name();
  if (all || test == 8)  test1_link_get_name();
  if (all || test == 9)  test2_link_get_name();
  if (all || test == 10) test1_link_set_origin();
  if (all || test == 11) test2_link_set_origin();
  if (all || test == 12) test3_link_set_origin();
  if (all || test == 13) test1_link_get_origin();
  if (all || test == 14) test2_link_get_origin();
  if (all || test == 15) test1_link_set_destination();
  if (all || test == 16) test2_link_set_destination();
  if (all || test == 17) test3_link_set_destination();
  if (all || test == 18) test1_link_get_destination();
  if (all || test == 19) test2_link_get_destination();
  if (all || test == 20) test1_link_set_direction();
  if (all || test == 21) test2_link_set_direction();
  if (all || test == 22) test3_link_set_direction();
  if (all || test == 23) test1_link_get_direction();
  if (all || test == 24) test2_link_get_direction();
  if (all || test == 25) test1_link_set_open();
  if (all || test == 26) test2_link_set_open();
  if (all || test == 27) test1_link_get_open();
  if (all || test == 28) test2_link_get_open();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- link_create --- */
void test1_link_create() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(l != NULL);
  link_destroy(l);
}

void test2_link_create() {
  Link *l = link_create(NO_ID);
  PRINT_TEST_RESULT(l == NULL);
}

/* --- link_get_id --- */
void test1_link_get_id() {
  Link *l = link_create(5);
  PRINT_TEST_RESULT(link_get_id(l) == 5);
  link_destroy(l);
}

void test2_link_get_id() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_id(l) == NO_ID);
}

/* --- link_set_name / link_get_name --- */
void test1_link_set_name() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_name(l, "puerta_norte") == OK);
  link_destroy(l);
}

void test2_link_set_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_name(l, "puerta_norte") == ERROR);
}

void test3_link_set_name() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_name(l, NULL) == ERROR);
  link_destroy(l);
}

void test1_link_get_name() {
  Link *l = link_create(1);
  link_set_name(l, "puerta_norte");
  PRINT_TEST_RESULT(strcmp(link_get_name(l), "puerta_norte") == 0);
  link_destroy(l);
}

void test2_link_get_name() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_name(l) == NULL);
}

/* --- link_set_origin / link_get_origin --- */
void test1_link_set_origin() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_origin(l, 10) == OK);
  link_destroy(l);
}

void test2_link_set_origin() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_origin(l, 10) == ERROR);
}

void test3_link_set_origin() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_origin(l, NO_ID) == ERROR);
  link_destroy(l);
}

void test1_link_get_origin() {
  Link *l = link_create(1);
  link_set_origin(l, 10);
  PRINT_TEST_RESULT(link_get_origin(l) == 10);
  link_destroy(l);
}

void test2_link_get_origin() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_origin(l) == NO_ID);
}

/* --- link_set_destination / link_get_destination --- */
void test1_link_set_destination() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_destination(l, 20) == OK);
  link_destroy(l);
}

void test2_link_set_destination() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_destination(l, 20) == ERROR);
}

void test3_link_set_destination() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_destination(l, NO_ID) == ERROR);
  link_destroy(l);
}

void test1_link_get_destination() {
  Link *l = link_create(1);
  link_set_destination(l, 20);
  PRINT_TEST_RESULT(link_get_destination(l) == 20);
  link_destroy(l);
}

void test2_link_get_destination() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_destination(l) == NO_ID);
}

/* --- link_set_direction / link_get_direction --- */
void test1_link_set_direction() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_direction(l, N) == OK);
  link_destroy(l);
}

void test2_link_set_direction() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_direction(l, N) == ERROR);
}

void test3_link_set_direction() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_direction(l, NO_DIR) == ERROR);
  link_destroy(l);
}

void test1_link_get_direction() {
  Link *l = link_create(1);
  link_set_direction(l, S);
  PRINT_TEST_RESULT(link_get_direction(l) == S);
  link_destroy(l);
}

void test2_link_get_direction() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_direction(l) == NO_DIR);
}

/* --- link_set_open / link_get_open --- */
void test1_link_set_open() {
  Link *l = link_create(1);
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == OK);
  link_destroy(l);
}

void test2_link_set_open() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_set_open(l, TRUE) == ERROR);
}

void test1_link_get_open() {
  Link *l = link_create(1);
  link_set_open(l, TRUE);
  PRINT_TEST_RESULT(link_get_open(l) == TRUE);
  link_destroy(l);
}

void test2_link_get_open() {
  Link *l = NULL;
  PRINT_TEST_RESULT(link_get_open(l) == FALSE);
}