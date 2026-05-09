#!/bin/bash
if [ -z "$1" ]; then
    echo "Uso: $0 <0|1> [nombre_del_test]"
    echo "  0 : Ejecución normal"
    echo "  1 : Ejecución con valgrind"
    exit 1
fi

if [ "$1" -eq 1 ]; then
    RUN_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes"
elif [ "$1" -eq 0 ]; then
    RUN_CMD=""
else
    echo "Error: El primer argumento debe ser 0 o 1."
    exit 1
fi

TEST_DIR="tests"

if [ -n "$2" ]; then
    TEST_NAME="$2"
    echo ">>> Compilando $TEST_NAME..."
    make "$TEST_DIR/$TEST_NAME"
    
    if [ $? -eq 0 ]; then
        echo ">>> Ejecutando $TEST_NAME..."
        $RUN_CMD "./$TEST_DIR/$TEST_NAME"
    else
        echo ">>> Error de compilación en $TEST_NAME."
        exit 1
    fi

else
    echo ">>> Compilando todas las pruebas..."
    make test
    
    if [ $? -eq 0 ]; then
        echo ">>> Ejecutando todas las pruebas..."
        
        for test_file in "$TEST_DIR"/*_test.c; do
            exe_name=$(basename "$test_file" .c)
            
            echo "---------------------------------------------------"
            echo ">>> Ejecutando $exe_name..."
            $RUN_CMD "./$TEST_DIR/$exe_name"
        done
    else
        echo ">>> Error durante la compilación general de pruebas."
        exit 1
    fi
fi