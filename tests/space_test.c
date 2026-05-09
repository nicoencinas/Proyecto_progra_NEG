/**
 * @brief It tests space module
 *
 * @file space_test.c
 * @version 1.0
 * @date 06-05-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "space.h"
#include "space_test.h"
#include "test.h"

#define MAX_TESTS 45

int main(int argc, char **argv)
{
  int test = 0;
  int all = 1;

  if (argc < 2) {
    printf("Running all tests for module Space:\n");
  } else {
    test = atoi(argv[1]);
    all = 0;
    printf("Running test %d:\t", test);
    if (test < 1 || test > MAX_TESTS) {
      printf("Error: unknown test %d\n", test);
      exit(EXIT_SUCCESS);
    }
  }

  if (all || test == 1)  test1_space_create();
  if (all || test == 2)  test2_space_create();
  if (all || test == 3)  test1_space_set_name();
  if (all || test == 4)  test2_space_set_name();
  if (all || test == 5)  test3_space_set_name();
  if (all || test == 6)  test1_space_get_id();
  if (all || test == 7)  test2_space_get_id();
  if (all || test == 8)  test1_space_get_name();
  if (all || test == 9)  test2_space_get_name();
  if (all || test == 10) test1_space_set_object();
  if (all || test == 11) test2_space_set_object();
  if (all || test == 12) test1_space_get_object();
  if (all || test == 13) test2_space_get_object();
  if (all || test == 14) test1_space_add_object();
  if (all || test == 15) test2_space_add_object();
  if (all || test == 16) test3_space_add_object();
  if (all || test == 17) test1_space_remove_object();
  if (all || test == 18) test2_space_remove_object();
  if (all || test == 19) test3_space_remove_object();
  if (all || test == 20) test1_space_has_object();
  if (all || test == 21) test2_space_has_object();
  if (all || test == 22) test3_space_has_object();
  if (all || test == 23) test1_space_add_character();
  if (all || test == 24) test2_space_add_character();
  if (all || test == 25) test3_space_add_character();
  if (all || test == 26) test1_space_remove_character();
  if (all || test == 27) test2_space_remove_character();
  if (all || test == 28) test3_space_remove_character();
  if (all || test == 29) test1_space_has_character();
  if (all || test == 30) test2_space_has_character();
  if (all || test == 31) test3_space_has_character();
  if (all || test == 32) test1_space_get_character();
  if (all || test == 33) test2_space_get_character();
  if (all || test == 34) test1_space_set_gdesc_at();
  if (all || test == 35) test2_space_set_gdesc_at();
  if (all || test == 36) test3_space_set_gdesc_at();
  if (all || test == 37) test1_space_get_gdesc_at();
  if (all || test == 38) test2_space_get_gdesc_at();
  if (all || test == 39) test3_space_get_gdesc_at();
  if (all || test == 40) test1_Space_discovered();
  if (all || test == 41) test2_Space_discovered();
  if (all || test == 42) test1_space_get_discovered();
  if (all || test == 43) test2_space_get_discovered();
  if (all || test == 44) test3_space_get_discovered();

  PRINT_PASSED_PERCENTAGE;
  return 1;
}

/* --- space_create --- */
void test1_space_create() {
  Space *s = space_create(5);
  PRINT_TEST_RESULT(s != NULL);
  space_destroy(s);
}

void test2_space_create() {
  /* NO_ID debe devolver NULL */
  Space *s = space_create(-1);
  PRINT_TEST_RESULT(s == NULL);
}

/* --- space_set_name / space_get_name --- */
void test1_space_set_name() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_name(s, "sala") == OK);
  space_destroy(s);
}

void test2_space_set_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_name(s, "sala") == ERROR);
}

void test3_space_set_name() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_name(s, NULL) == ERROR);
  space_destroy(s);
}

/* --- space_get_id --- */
void test1_space_get_id() {
  Space *s = space_create(42);
  PRINT_TEST_RESULT(space_get_id(s) == 42);
  space_destroy(s);
}

void test2_space_get_id() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_id(s) == NO_ID);
}

/* --- space_get_name --- */
void test1_space_get_name() {
  Space *s = space_create(1);
  space_set_name(s, "bosque");
  PRINT_TEST_RESULT(strcmp(space_get_name(s), "bosque") == 0);
  space_destroy(s);
}

void test2_space_get_name() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_name(s) == NULL);
}

/* --- space_set_object (legacy: solo llama a set_add internamente) --- */
void test1_space_set_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_object(s, 10) == 1);
  space_destroy(s);
}

void test2_space_set_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_object(s, 10) == ERROR);
}

/* --- space_get_object --- */
void test1_space_get_object() {
  Space *s = space_create(1);
  /* Recién creado, el Set existe pero está vacío; no debe ser NULL */
  PRINT_TEST_RESULT(space_get_object(s) != NULL);
  space_destroy(s);
}

void test2_space_get_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_object(s) == NULL);
}

/* --- space_add_object --- */
void test1_space_add_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_object(s, 10) == OK);
  space_destroy(s);
}

void test2_space_add_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_object(s, 10) == ERROR);
}

void test3_space_add_object() {
  Space *s = space_create(1);
  /* NO_ID debe fallar */
  PRINT_TEST_RESULT(space_add_object(s, NO_ID) == ERROR);
  space_destroy(s);
}

/* --- space_remove_object --- */
void test1_space_remove_object() {
  Space *s = space_create(1);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_remove_object(s, 10) == OK);
  space_destroy(s);
}

void test2_space_remove_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_remove_object(s, 10) == ERROR);
}

void test3_space_remove_object() {
  Space *s = space_create(1);
  /* Eliminar objeto que no existe debe dar ERROR */
  PRINT_TEST_RESULT(space_remove_object(s, 99) == ERROR);
  space_destroy(s);
}

/* --- space_has_object --- */
void test1_space_has_object() {
  Space *s = space_create(1);
  space_add_object(s, 10);
  PRINT_TEST_RESULT(space_has_object(s, 10) == TRUE);
  space_destroy(s);
}

void test2_space_has_object() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_has_object(s, 10) == FALSE);
  space_destroy(s);
}

void test3_space_has_object() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_object(s, 10) == FALSE);
}

/* --- space_add_character --- */
void test1_space_add_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_character(s, 20) == OK);
  space_destroy(s);
}

void test2_space_add_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_add_character(s, 20) == ERROR);
}

void test3_space_add_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_add_character(s, NO_ID) == ERROR);
  space_destroy(s);
}

/* --- space_remove_character --- */
void test1_space_remove_character() {
  Space *s = space_create(1);
  space_add_character(s, 20);
  PRINT_TEST_RESULT(space_remove_character(s, 20) == OK);
  space_destroy(s);
}

void test2_space_remove_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_remove_character(s, 20) == ERROR);
}

void test3_space_remove_character() {
  Space *s = space_create(1);
  /* Personaje no presente */
  PRINT_TEST_RESULT(space_remove_character(s, 99) == ERROR);
  space_destroy(s);
}

/* --- space_has_character --- */
void test1_space_has_character() {
  Space *s = space_create(1);
  space_add_character(s, 20);
  PRINT_TEST_RESULT(space_has_character(s, 20) == TRUE);
  space_destroy(s);
}

void test2_space_has_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_has_character(s, 20) == FALSE);
  space_destroy(s);
}

void test3_space_has_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_has_character(s, 20) == FALSE);
}

/* --- space_get_character --- */
void test1_space_get_character() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_get_character(s) != NULL);
  space_destroy(s);
}

void test2_space_get_character() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_character(s) == NULL);
}

/* --- space_set_gdesc_at / space_get_gdesc_at --- */
void test1_space_set_gdesc_at() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(space_set_gdesc_at(s, 0, "##########") == OK);
  space_destroy(s);
}

void test2_space_set_gdesc_at() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_set_gdesc_at(s, 0, "##########") == ERROR);
}

void test3_space_set_gdesc_at() {
  Space *s = space_create(1);
  /* Línea fuera de rango */
  PRINT_TEST_RESULT(space_set_gdesc_at(s, 999, "##########") == ERROR);
  space_destroy(s);
}

void test1_space_get_gdesc_at() {
  Space *s = space_create(1);
  space_set_gdesc_at(s, 0, "##########");
  PRINT_TEST_RESULT(strcmp(space_get_gdesc_at(s, 0), "##########") == 0);
  space_destroy(s);
}

void test2_space_get_gdesc_at() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_gdesc_at(s, 0) == NULL);
}

void test3_space_get_gdesc_at() {
  Space *s = space_create(1);
  /* Línea fuera de rango */
  PRINT_TEST_RESULT(space_get_gdesc_at(s, -1) == NULL);
  space_destroy(s);
}

/* --- Space_discovered / space_get_discovered --- */
void test1_Space_discovered() {
  Space *s = space_create(1);
  PRINT_TEST_RESULT(Space_discovered(s) == OK);
  space_destroy(s);
}

void test2_Space_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(Space_discovered(s) == ERROR);
}

void test1_space_get_discovered() {
  Space *s = space_create(1);
  /* Recién creado: no descubierto */
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
  space_destroy(s);
}

void test2_space_get_discovered() {
  Space *s = space_create(1);
  Space_discovered(s);
  PRINT_TEST_RESULT(space_get_discovered(s) == TRUE);
  space_destroy(s);
}

void test3_space_get_discovered() {
  Space *s = NULL;
  PRINT_TEST_RESULT(space_get_discovered(s) == FALSE);
}