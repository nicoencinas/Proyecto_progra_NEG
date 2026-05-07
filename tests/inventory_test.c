/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 13

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Inventory:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_inventory_create();
  if (all || test == 2)  test2_inventory_create();
  if (all || test == 3)  test1_inventory_add();
  if (all || test == 4)  test2_inventory_add();
  if (all || test == 5)  test3_inventory_add();
  if (all || test == 6)  test1_inventory_del();
  if (all || test == 7)  test2_inventory_del();
  if (all || test == 8)  test3_inventory_del();
  if (all || test == 9)  test1_inventory_find();
  if (all || test == 10) test2_inventory_find();
  if (all || test == 11) test3_inventory_find();
  if (all || test == 12) test1_inventory_get_inventory();
  if (all || test == 13) test2_inventory_get_inventory();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- inventory_create --- */
void test1_inventory_create() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inv != NULL);
  inventory_destroy(inv);
}

void test2_inventory_create() {
  /* max_objs 0 sigue siendo válido (límite vacío) */
  Inventory *inv = inventory_create(0);
  PRINT_TEST_RESULT(inv != NULL);
  inventory_destroy(inv);
}

/* --- inventory_add --- */
void test1_inventory_add() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_add(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_add() {
  PRINT_TEST_RESULT(inventory_add(NULL, 1) == ERROR);
}

void test3_inventory_add() {
  /* Añadir id duplicado: set_add devuelve ERROR */
  Inventory *inv = inventory_create(5);
  inventory_add(inv, 1);
  PRINT_TEST_RESULT(inventory_add(inv, 1) == ERROR);
  inventory_destroy(inv);
}

/* --- inventory_del --- */
void test1_inventory_del() {
  Inventory *inv = inventory_create(5);
  inventory_add(inv, 1);
  PRINT_TEST_RESULT(inventory_del(inv, 1) == OK);
  inventory_destroy(inv);
}

void test2_inventory_del() {
  PRINT_TEST_RESULT(inventory_del(NULL, 1) == ERROR);
}

void test3_inventory_del() {
  /* Eliminar id que no existe */
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_del(inv, 99) == ERROR);
  inventory_destroy(inv);
}

/* --- inventory_find --- */
void test1_inventory_find() {
  Inventory *inv = inventory_create(5);
  inventory_add(inv, 1);
  PRINT_TEST_RESULT(inventory_find(inv, 1) == TRUE);
  inventory_destroy(inv);
}

void test2_inventory_find() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_find(inv, 1) == FALSE);
  inventory_destroy(inv);
}

void test3_inventory_find() {
  PRINT_TEST_RESULT(inventory_find(NULL, 1) == FALSE);
}

/* --- inventory_get_inventory --- */
void test1_inventory_get_inventory() {
  Inventory *inv = inventory_create(5);
  PRINT_TEST_RESULT(inventory_get_inventory(inv) != NULL);
  inventory_destroy(inv);
}

void test2_inventory_get_inventory() {
  PRINT_TEST_RESULT(inventory_get_inventory(NULL) == NULL);
}