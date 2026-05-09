/**
 * @brief It tests object module
 *
 * @file object_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "object.h"
#include "object_test.h"
#include "test.h"

#define MAX_TESTS 32

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Object:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_object_create();
  if (all || test == 2)  test2_object_create();
  if (all || test == 3)  test1_object_get_id();
  if (all || test == 4)  test2_object_get_id();
  if (all || test == 5)  test1_object_set_name();
  if (all || test == 6)  test2_object_set_name();
  if (all || test == 7)  test3_object_set_name();
  if (all || test == 8)  test1_object_get_name();
  if (all || test == 9)  test2_object_get_name();
  if (all || test == 10) test1_object_set_desc();
  if (all || test == 11) test2_object_set_desc();
  if (all || test == 12) test3_object_set_desc();
  if (all || test == 13) test1_object_get_desc();
  if (all || test == 14) test2_object_get_desc();
  if (all || test == 15) test1_object_set_health();
  if (all || test == 16) test2_object_set_health();
  if (all || test == 17) test1_object_get_health();
  if (all || test == 18) test2_object_get_health();
  if (all || test == 19) test1_object_set_movable();
  if (all || test == 20) test2_object_set_movable();
  if (all || test == 21) test1_object_get_movable();
  if (all || test == 22) test2_object_get_movable();
  if (all || test == 23) test1_object_set_dependency();
  if (all || test == 24) test2_object_set_dependency();
  if (all || test == 25) test3_object_set_dependency();
  if (all || test == 26) test1_object_get_dependency();
  if (all || test == 27) test2_object_get_dependency();
  if (all || test == 28) test1_object_set_open();
  if (all || test == 29) test2_object_set_open();
  if (all || test == 30) test3_object_set_open();
  if (all || test == 31) test1_object_get_open();
  if (all || test == 32) test2_object_get_open();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- object_create --- */
void test1_object_create() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(o != NULL);
  object_destroy(o);
}

void test2_object_create() {
  Object *o = object_create(NO_ID);
  PRINT_TEST_RESULT(o == NULL);
}

/* --- object_get_id --- */
void test1_object_get_id() {
  Object *o = object_create(10);
  PRINT_TEST_RESULT(object_get_id(o) == 10);
  object_destroy(o);
}

void test2_object_get_id() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_id(o) == NO_ID);
}

/* --- object_set_name / object_get_name --- */
void test1_object_set_name() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_name(o, "espada") == OK);
  object_destroy(o);
}

void test2_object_set_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_name(o, "espada") == ERROR);
}

void test3_object_set_name() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_name(o, NULL) == ERROR);
  object_destroy(o);
}

void test1_object_get_name() {
  Object *o = object_create(1);
  object_set_name(o, "espada");
  PRINT_TEST_RESULT(strcmp(object_get_name(o), "espada") == 0);
  object_destroy(o);
}

void test2_object_get_name() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_name(o) == NULL);
}

/* --- object_set_desc / object_get_desc --- */
void test1_object_set_desc() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_desc(o, "Una espada oxidada") == OK);
  object_destroy(o);
}

void test2_object_set_desc() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_desc(o, "desc") == ERROR);
}

void test3_object_set_desc() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_desc(o, NULL) == ERROR);
  object_destroy(o);
}

void test1_object_get_desc() {
  Object *o = object_create(1);
  object_set_desc(o, "Una espada oxidada");
  PRINT_TEST_RESULT(strcmp(object_get_desc(o), "Una espada oxidada") == 0);
  object_destroy(o);
}

void test2_object_get_desc() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_desc(o) == NULL);
}

/* --- object_set_health / object_get_health --- */
void test1_object_set_health() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_health(o, 5) == OK);
  object_destroy(o);
}

void test2_object_set_health() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_health(o, 5) == ERROR);
}

void test1_object_get_health() {
  Object *o = object_create(1);
  object_set_health(o, 5);
  PRINT_TEST_RESULT(object_get_health(o) == 5);
  object_destroy(o);
}

void test2_object_get_health() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_health(o) == OBJECT_NULL);
}

/* --- object_set_movable / object_get_movable --- */
void test1_object_set_movable() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == OK);
  object_destroy(o);
}

void test2_object_set_movable() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_movable(o, TRUE) == ERROR);
}

void test1_object_get_movable() {
  Object *o = object_create(1);
  object_set_movable(o, TRUE);
  PRINT_TEST_RESULT(object_get_movable(o) == TRUE);
  object_destroy(o);
}

void test2_object_get_movable() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_movable(o) == FALSE);
}

/* --- object_set_dependency / object_get_dependency --- */
void test1_object_set_dependency() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_dependency(o, 2) == OK);
  object_destroy(o);
}

void test2_object_set_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_dependency(o, 2) == ERROR);
}

void test3_object_set_dependency() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_dependency(o, NO_ID) == ERROR);
  object_destroy(o);
}

void test1_object_get_dependency() {
  Object *o = object_create(1);
  object_set_dependency(o, 2);
  PRINT_TEST_RESULT(object_get_dependency(o) == 2);
  object_destroy(o);
}

void test2_object_get_dependency() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_dependency(o) == NO_ID);
}

/* --- object_set_open / object_get_open --- */
void test1_object_set_open() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_open(o, 3) == OK);
  object_destroy(o);
}

void test2_object_set_open() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_set_open(o, 3) == ERROR);
}

void test3_object_set_open() {
  Object *o = object_create(1);
  PRINT_TEST_RESULT(object_set_open(o, NO_ID) == ERROR);
  object_destroy(o);
}

void test1_object_get_open() {
  Object *o = object_create(1);
  object_set_open(o, 3);
  PRINT_TEST_RESULT(object_get_open(o) == 3);
  object_destroy(o);
}

void test2_object_get_open() {
  Object *o = NULL;
  PRINT_TEST_RESULT(object_get_open(o) == NO_ID);
}