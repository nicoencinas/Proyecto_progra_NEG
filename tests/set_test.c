/**
 * @brief It tests set module
 *
 * @file set_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"
#include "set_test.h"
#include "test.h"

#define MAX_TESTS 11

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Set:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_set_create();
  if (all || test == 2)  test1_set_add();
  if (all || test == 3)  test2_set_add();
  if (all || test == 4)  test3_set_add();
  if (all || test == 5)  test4_set_add();
  if (all || test == 6)  test1_set_del();
  if (all || test == 7)  test2_set_del();
  if (all || test == 8)  test3_set_del();
  if (all || test == 9)  test1_set_find();
  if (all || test == 10) test2_set_find();
  if (all || test == 11) test3_set_find();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- set_create --- */
void test1_set_create() {
  Set *s = set_create();
  PRINT_TEST_RESULT(s != NULL);
  set_destroy(s);
}

/* --- set_add --- */
void test1_set_add() {
  /* Añadir un id válido */
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add(s, 1) == OK);
  set_destroy(s);
}

void test2_set_add() {
  /* Añadir sobre puntero NULL */
  PRINT_TEST_RESULT(set_add(NULL, 1) == ERROR);
}

void test3_set_add() {
  /* Añadir NO_ID debe fallar */
  Set *s = set_create();
  PRINT_TEST_RESULT(set_add(s, NO_ID) == ERROR);
  set_destroy(s);
}

void test4_set_add() {
  /* Añadir id duplicado debe fallar */
  Set *s = set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(set_add(s, 5) == ERROR);
  set_destroy(s);
}

/* --- set_del --- */
void test1_set_del() {
  /* Eliminar un id que existe */
  Set *s = set_create();
  set_add(s, 5);
  PRINT_TEST_RESULT(set_del(s, 5) == OK);
  set_destroy(s);
}

void test2_set_del() {
  /* Eliminar sobre puntero NULL */
  PRINT_TEST_RESULT(set_del(NULL, 5) == ERROR);
}

void test3_set_del() {
  /* Eliminar id que no existe */
  Set *s = set_create();
  PRINT_TEST_RESULT(set_del(s, 99) == ERROR);
  set_destroy(s);
}

/* --- set_find --- */
void test1_set_find() {
  /* Buscar id presente */
  Set *s = set_create();
  set_add(s, 7);
  PRINT_TEST_RESULT(set_find(s, 7) == TRUE);
  set_destroy(s);
}

void test2_set_find() {
  /* Buscar id ausente */
  Set *s = set_create();
  PRINT_TEST_RESULT(set_find(s, 7) == FALSE);
  set_destroy(s);
}

void test3_set_find() {
  /* Buscar en set NULL */
  PRINT_TEST_RESULT(set_find(NULL, 7) == FALSE);
}