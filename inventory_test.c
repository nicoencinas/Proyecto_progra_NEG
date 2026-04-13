/**
 * @brief It tests inventory module
 *
 * @file inventory_test.c
 * @version 1.0
 * @date 09-03-2026
 * @copyright GNU Public License
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inventory.h"
#include "inventory_test.h"
#include "test.h"

#define MAX_TESTS 17

/**
 * @brief Main function for INVENTORY unit tests.
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
        printf("Running all tests for module Inventory:\n");
    } else {
        test = atoi(argv[1]);
        all  = 0;
        printf("Running test %d:\t", test);
        if (test < 1 || test > MAX_TESTS) {
            printf("Error: unknown test %d\t", test);
            exit(EXIT_SUCCESS);
        }
    }

    if (all || test ==  1) test1_inventory_create();
    if (all || test ==  2) test2_inventory_create();
    if (all || test ==  3) test1_inventory_destroy();
    if (all || test ==  4) test2_inventory_destroy();
    if (all || test ==  5) test1_inventory_add();
    if (all || test ==  6) test2_inventory_add();
    if (all || test ==  7) test3_inventory_add();
    if (all || test ==  8) test1_inventory_del();
    if (all || test ==  9) test2_inventory_del();
    if (all || test == 10) test3_inventory_del();
    if (all || test == 11) test1_inventory_find();
    if (all || test == 12) test2_inventory_find();
    if (all || test == 13) test3_inventory_find();
    if (all || test == 14) test1_inventory_get_inventory();
    if (all || test == 15) test2_inventory_get_inventory();
    if (all || test == 16) test1_inventory_print();
    if (all || test == 17) test2_inventory_print();

    PRINT_PASSED_PERCENTAGE;

    return 1;
}

void test1_inventory_create()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inv != NULL);
    inventory_destroy(inv);
}

void test2_inventory_create()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_find(inv, 1) == FALSE);
    inventory_destroy(inv);
}

void test1_inventory_destroy()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_destroy(inv) == OK);
}

void test2_inventory_destroy()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_destroy(inv) == ERROR);
}

void test1_inventory_add()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_add(inv, 10) == OK);
    inventory_destroy(inv);
}

void test2_inventory_add()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_add(inv, 10) == ERROR);
}

void test3_inventory_add()
{
    Inventory *inv = inventory_create(5);
    inventory_add(inv, 10);
    PRINT_TEST_RESULT(inventory_add(inv, 10) == ERROR);
    inventory_destroy(inv);
}

void test1_inventory_del()
{
    Inventory *inv = inventory_create(5);
    inventory_add(inv, 10);
    PRINT_TEST_RESULT(inventory_del(inv, 10) == OK);
    inventory_destroy(inv);
}

void test2_inventory_del()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_del(inv, 10) == ERROR);
}

void test3_inventory_del()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_del(inv, 99) == ERROR);
    inventory_destroy(inv);
}

void test1_inventory_find()
{
    Inventory *inv = inventory_create(5);
    inventory_add(inv, 42);
    PRINT_TEST_RESULT(inventory_find(inv, 42) == TRUE);
    inventory_destroy(inv);
}

void test2_inventory_find()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_find(inv, 42) == FALSE);
    inventory_destroy(inv);
}

void test3_inventory_find()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_find(inv, 42) == FALSE);
}

void test1_inventory_get_inventory()
{
    Inventory *inv = inventory_create(5);
    PRINT_TEST_RESULT(inventory_get_inventory(inv) != NULL);
    inventory_destroy(inv);
}

void test2_inventory_get_inventory()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_get_inventory(inv) == NULL);
}

void test1_inventory_print()
{
    Inventory *inv = inventory_create(5);
    inventory_add(inv, 1);
    inventory_add(inv, 2);
    PRINT_TEST_RESULT(inventory_print(inv) == OK);
    inventory_destroy(inv);
}

void test2_inventory_print()
{
    Inventory *inv = NULL;
    PRINT_TEST_RESULT(inventory_print(inv) == ERROR);
}
