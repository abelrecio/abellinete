#!/bin/bash

TEST_ARGS=("$@")

comprobar_norminette() {
    echo "Comprobando normas de estilo con norminette..."
    norminette $(ls *.c | grep -v "main.c") > errnorm.txt 2>&1
    if grep -q -v "OK!" errnorm.txt; then
        echo "Errores de estilo detectados. Mira errnorm.txt."
        return 1
    fi
    return 0
}

test_sanitizer() {
    rm -f test_files/error.log
    comprobar_norminette
    [ $? -ne 0 ] && echo

    echo "Compilando con AddressSanitizer..."
    cc -fsanitize=address -Wall -Wextra -Werror *.c -o test_libft_sanitizer
	if [ $? -ne 0 ]; then
        echo "Falló compilación con Sanitizer."
        read -p "Pulsa enter…"
        return 1
    fi

    echo "Ejecutando: ./test_libft_sanitizer ${TEST_ARGS[*]}"
    ./test_libft_sanitizer "${TEST_ARGS[@]}"
    if [ $? -ne 0 ]; then
        echo "Errores en Sanitizer."
    else
        echo "OK con Sanitizer."
    fi
    read -p "Pulsa enter…"
}

test_valgrind() {
    rm -f test_files/error.log
    comprobar_norminette
    [ $? -ne 0 ] && echo

    echo "Compilando para Valgrind..."
    cc -Wall -Wextra -Werror *.c -o test_libft_valgrind -lbsd
    if [ $? -ne 0 ]; then
        echo "Falló compilación para Valgrind."
        read -p "Pulsa enter…"
        return 1
    fi

    echo "Ejecutando: valgrind --leak-check=full --error-exitcode=1 ./test_libft_valgrind ${TEST_ARGS[*]}"
    valgrind --leak-check=full --error-exitcode=1 ./test_libft_valgrind "${TEST_ARGS[@]}"
    if [ $? -ne 0 ]; then
        echo "Fugas detectadas por Valgrind."
    else
        echo "Sin fugas con Valgrind."
    fi
    read -p "Pulsa enter…"
}

test_normal() {
    rm -f test_files/error.log
    comprobar_norminette
    [ $? -ne 0 ] && echo

    echo "Compilando normalmente..."
    cc -Wall -Wextra -Werror *.c -o test_libft -lbsd
    if [ $? -ne 0 ]; then
        echo "Falló compilación normal."
        read -p "Pulsa enter…"
        return 1
    fi

    echo "Ejecutando: ./test_libft ${TEST_ARGS[*]}"
    ./test_libft "${TEST_ARGS[@]}"
    if [ $? -eq 0 ]; then
        echo "Todas las pruebas pasaron."
    else
        echo "Pruebas fallaron (exit code $?)."
    fi
    read -p "Pulsa enter…"
}

while true; do
    clear
    echo "  ⬛⬛                🟩🟩🟩🟩🟩🟩🟩🟩                ⬛⬛  "
    echo "⬛⬜⬜⬛⬛        🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩        ⬛⬛⬜⬜⬛"
    echo "⬛🟧⬜⬜⬜⬛⬛  🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩  ⬛⬛⬜⬜⬜🟧⬛"
    echo "⬛🟧🟧⬜⬜⬜⬜⬜🟥🟥🟥🟥🟩🟩🟩🟩🟩🟩🟥🟥🟥🟥⬜⬜⬜⬜⬜🟧🟧⬛"
    echo "⬛🟧🟧⬜⬜⬜⬜🟥🟥🟥🟥🟥🟥🟩🟩🟩🟩🟥🟥🟥🟥🟥🟥⬜⬜⬜⬜🟧🟧⬛"
    echo "⬛🟧🟧⬜⬜🟥🟥⬜⬜⬜⬜⬜🟥🟫🟫🟫🟫🟥⬜⬜⬜⬜⬜🟥🟥⬜⬜🟧🟧⬛"
    echo "⬛🟧🟧⬜⬜🟥🟥⬜⬜⬜⬜⬜🟥🟫🟫🟫🟫🟥⬜⬜⬜⬜⬜🟥🟥⬜⬜🟧🟧⬛"
    echo "  ⬛🟧🟧🟫🟥🟥🟥🟥🟥🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟥🟥🟥🟥🟥🟫🟧🟧⬛  "
    echo "  ⬛🟧🟧🟫🟫🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟫🟫🟧🟧⬛  "
    echo "    ⬛🟫🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟩🟫⬛    "
    echo "    🟩🟩🟩🟩🟩🟩🟩🟩🟧🟧🟧🟧🟧🟧🟧🟧🟧🟧🟩🟩🟩🟩🟩🟩🟩🟩    "
    echo "  🟩🟩🟩🟩🟩🟧⬛⬛⬛🟧🟧🟧⬜⬜⬜⬜🟧🟧🟧⬛⬛⬛🟧🟩🟩🟩🟩🟩  "
    echo "🟩🟩🟩🟩⬛🟧⬛🟧🟧🟫⬛🟧⬜⬜⬜⬜⬜⬜🟧⬛🟫🟧🟧⬛🟧⬛🟩🟩🟩🟩"
    echo "🟩🟩🟩🟩⬛🟧🟧🟧🟧🟧🟫⬛⬜⬜⬜⬜⬜⬜⬛🟫🟧🟧🟧🟧🟧⬛🟩🟩🟩🟩"
    echo "      ⬛⬜🟧🟧🟧🟧🟧🟧🟧🟧⬜⬜⬜⬜🟧🟧🟧🟧🟧🟧🟧🟧⬜⬛      "
    echo "  ⬛⬛⬜⬜🟧🟧🟧⬛⬛🟧🟧🟧⬜⬜⬜⬜🟧🟧🟧⬛⬛🟧🟧🟧⬜⬜⬛⬛  "
    echo "  ⬛⬜⬜⬜🟧🟧⬛🟧🟧⬛🟧🟧⬜⬜⬜⬜🟧🟧⬛🟧🟧⬛🟧🟧⬜⬜⬜⬛  "
    echo "    ⬛⬜⬜⬜🟧🟧🟧🟧🟧🟧⬜⬜⬜⬜⬜⬜🟧🟧🟧🟧🟧🟧⬜⬜⬜⬛    "
    echo "      ⬛⬜⬜⬜🟧🟧🟧🟧⬜⬜⬜⬜⬜⬜⬜⬜🟧🟧🟧🟧⬜⬜⬜⬛      "
    echo "  ⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛  "
    echo "  ⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🟫🟫🟫🟫🟫🟫⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛  "
    echo "    ⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🟫🟫🟫🟫⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛    "
    echo "      ⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜🟫🟫⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛      "
    echo "        ⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛        "
    echo "          ⬛⬜⬜⬜⬜⬜⬜⬛⬜⬜⬜⬜⬛⬜⬜⬜⬜⬜⬜⬛          "
    echo "            ⬛⬛⬜⬜⬜⬜⬜⬛⬛⬛⬛⬜⬜⬜⬜⬜⬛⬛            "
    echo "                ⬛⬛⬜⬜⬜⬜⬜⬜⬜⬜⬜⬜⬛⬛                "
    echo "                    ⬛⬛⬛⬜⬜⬜⬜⬛⬛⬛                    "
    echo "                          ⬛⬛⬛⬛                          "
    echo "========================================"
    echo "           ABELINETTE BETA"
    echo "========================================"
    echo "1) Test con AddressSanitizer"
    echo "2) Test con Valgrind"
    echo "3) Test normal"
    echo "4) Salir"
    echo "----------------------------------------"
    read -p "Elige una opción [1-4]: " opt

    case $opt in
        1) test_sanitizer ;;
        2) test_valgrind ;;
        3) test_normal ;;
        4) echo "Saliendo…"; exit 0 ;;
        *) echo "Opción inválida."; read -p "Pulsa enter…";;
    esac
done

