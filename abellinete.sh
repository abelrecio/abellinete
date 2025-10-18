#!/bin/bash

TEST_ARGS=("$@")

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' 

comprobar_norminette() {
    echo -e "${BLUE}Comprobando normas de estilo con norminette...${NC}"
    mkdir -p ../errores
    cd entrega
    norminette $(ls *.c *.h | grep -v '^test_.*\.c$') > ../errores/errnorm.txt 2>&1
    cd ..
    if grep -q -v "OK!" errores/errnorm.txt; then
        echo -e "${RED}Errores de estilo detectados. Mira errores/errnorm.txt.${NC}"
        return 1
    fi
    echo -e "${GREEN}Norminette OK!${NC}"
    return 0
}


preparar_entorno() {
    echo -e "${BLUE}Preparando entorno de compilación...${NC}"
    
    if [ ! -d "entrega" ]; then
        echo -e "${RED}Error: No existe la carpeta 'entrega'${NC}"
        return 1
    fi
    
    if [ ! -f "ft_printf/test.c" ]; then
        echo -e "${RED}Error: No existe ft_printf/test.c${NC}"
        return 1
    fi
    
    cp ft_printf/test.c entrega/test_ft_printf.c
    if [ $? -ne 0 ]; then
        echo -e "${RED}Error: No se pudo copiar el test${NC}"
        return 1
    fi
    
    echo -e "${GREEN}Entorno preparado correctamente${NC}"
    return 0
}

limpiar_entorno() {
    echo -e "${BLUE}Limpiando entorno...${NC}"
    cd entrega 2>/dev/null && {
        rm -f test_ft_printf.c
        rm -f test_ft_printf_sanitizer
        rm -f test_ft_printf_valgrind  
        rm -f test_ft_printf_normal
        rm -f test_libft_sanitizer
        rm -f test_libft_valgrind
        rm -f test_libft_normal
        rm -f *.o
        rm -f a.out
        cd ..
    }
    
    cd libft 2>/dev/null && {
        rm -f test_libft_sanitizer
        rm -f test_libft_valgrind
        rm -f test_libft_normal
        rm -f *.o
        rm -f a.out
        cd ..
    }
    
    rm -f errnorm.txt
    echo -e "${GREEN}Entorno limpiado${NC}"
}

compilar_ft_printf() {
    local modo=$1
    local ejecutable=$2
    local flags_extra="$3"
    
    echo -e "${BLUE}Compilando ft_printf en modo ${modo}...${NC}"
    
    cd entrega
    
    if [ ! -f "libft.a" ]; then
        echo -e "${RED}Error: No se encuentra libft.a en entrega/${NC}"
        cd ..
        return 1
    fi
    
    local ft_printf_files="ft_printf_main.c ft_printf_char.c ft_printf_charstr.c ft_printf_format.c ft_printf_number.c ft_printf_number_utils.c ft_printf_parser.c ft_printf_pointer.c ft_printf_prefix.c ft_printf_string.c ft_printf_utils.c"
    
    for file in $ft_printf_files; do
        if [ ! -f "$file" ]; then
            echo -e "${RED}Error: No se encuentra $file${NC}"
            cd ..
            return 1
        fi
    done
    
    echo -e "${YELLOW}Archivos a compilar: $ft_printf_files test_ft_printf.c${NC}"
    
    cc $flags_extra -Wall -Wextra -Werror $ft_printf_files -Wno-error test_ft_printf.c libft.a -o $ejecutable
    
    local exit_code=$?
    cd ..
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}Error en compilación ${modo}${NC}"
        return 1
    fi
    
    echo -e "${GREEN}Compilación ${modo} exitosa${NC}"
    return 0
}

test_ft_printf_sanitizer() {
    preparar_entorno || return 1
    
    comprobar_norminette
    [ $? -ne 0 ] && echo
    
    compilar_ft_printf "AddressSanitizer" "test_ft_printf_sanitizer" "-fsanitize=address"
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación con Sanitizer.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi

    echo -e "${BLUE}Ejecutando: ./entrega/test_ft_printf_sanitizer ${TEST_ARGS[*]}${NC}"
    cd entrega
    ./test_ft_printf_sanitizer "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}Errores detectados por AddressSanitizer.${NC}"
    else
        echo -e "${GREEN}OK con AddressSanitizer.${NC}"
    fi
    
    read -p "Pulsa enter para continuar..."
}

test_ft_printf_valgrind() {
    preparar_entorno || return 1
    
    comprobar_norminette
    [ $? -ne 0 ] && echo

    compilar_ft_printf "Valgrind" "test_ft_printf_valgrind" ""
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación para Valgrind.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi

    echo -e "${BLUE}Ejecutando: valgrind --leak-check=full --error-exitcode=1 ./entrega/test_ft_printf_valgrind ${TEST_ARGS[*]}${NC}"
    cd entrega
    valgrind --leak-check=full --error-exitcode=1 --track-origins=yes ./test_ft_printf_valgrind "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}Fugas o errores detectados por Valgrind.${NC}"
    else
        echo -e "${GREEN}Sin fugas con Valgrind.${NC}"
    fi
    
    read -p "Pulsa enter para continuar..."
}

test_ft_printf_normal() {
    preparar_entorno || return 1
    
    comprobar_norminette
    [ $? -ne 0 ] && echo

    compilar_ft_printf "normal" "test_ft_printf_normal" ""
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación normal.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi

    echo -e "${BLUE}Ejecutando: ./entrega/test_ft_printf_normal ${TEST_ARGS[*]}${NC}"
    cd entrega
    ./test_ft_printf_normal "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}Todas las pruebas pasaron.${NC}"
    else
        echo -e "${YELLOW}Pruebas fallaron (exit code $exit_code).${NC}"
    fi
    
    read -p "Pulsa enter para continuar..."
}

test_libft_sanitizer() {
    echo -e "${BLUE}Compilando libft con AddressSanitizer...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca libft...${NC}"
    make -C entrega/libft fclean
    make -C entrega/libft all
    make -C entrega/libft bonus
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de libft con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando tests con AddressSanitizer...${NC}"
    cc -fsanitize=address -g \
        -Wall -Wextra -Werror \
        libft/test_*.c \
        entrega/libft/libft.a \
        -I entrega/libft \
        -o libft/test_libft_sanitizer \
        -lbsd
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación de tests con Sanitizer.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando tests con AddressSanitizer...${NC}"
    cd libft
    ./test_libft_sanitizer "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}Errores detectados con AddressSanitizer.${NC}"
    else
        echo -e "${GREEN}OK libft con AddressSanitizer - Sin errores de memoria.${NC}"
    fi
    
    rm -f libft/test_libft_sanitizer
    read -p "Pulsa enter para continuar..."
}

test_libft_valgrind() {
    echo -e "${BLUE}Compilando libft para Valgrind...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca libft...${NC}"
    make -C entrega/libft fclean
    make -C entrega/libft all
    make -C entrega/libft bonus
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de libft con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando tests para Valgrind (con símbolos de debug)...${NC}"
    cc -g -O0 \
        -Wall -Wextra -Werror \
        libft/test_*.c \
        entrega/libft/libft.a \
        -I entrega/libft \
        -o libft/test_libft_valgrind \
        -lbsd
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación de tests para Valgrind.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando Valgrind con detección completa de fugas...${NC}"
    cd libft
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=1 \
             --suppressions=/dev/null \
             ./test_libft_valgrind "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -ne 0 ]; then
        echo -e "${RED}Fugas de memoria detectadas por Valgrind.${NC}"
        echo -e "${YELLOW}Revisa el output anterior para ver los detalles.${NC}"
    else
        echo -e "${GREEN}Sin fugas de memoria - Valgrind limpio.${NC}"
    fi
    
    rm -f libft/test_libft_valgrind
    read -p "Pulsa enter para continuar..."
}

test_libft_normal() {
    echo -e "${BLUE}Compilando libft normalmente...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca libft con make...${NC}"
    make -C entrega/libft fclean
    make -C entrega/libft all
    make -C entrega/libft bonus
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de libft con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    if [ ! -f "entrega/libft/libft.a" ]; then
        echo -e "${RED}Error: No se encontró entrega/libft/libft.a${NC}"
        echo -e "${YELLOW}Verifica que el Makefile esté configurado correctamente.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando tests con la biblioteca...${NC}"
    cc -Wall -Wextra -Werror \
        libft/test_*.c \
        entrega/libft/libft.a \
        -I entrega/libft \
        -o libft/test_libft_normal \
        -lbsd
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación de tests.${NC}"
        echo -e "${YELLOW}Posibles causas:${NC}"
        echo -e "  - Falta el archivo libft.h en entrega/libft/"
        echo -e "  - Los tests esperan funciones que no están implementadas"
        echo -e "  - Problemas con la biblioteca bsd (instala libbsd-dev si falta)"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando tests: ./test_libft_normal ${TEST_ARGS[*]}${NC}"
    cd libft
    ./test_libft_normal "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}Todas las pruebas de libft pasaron correctamente.${NC}"
    else
        echo -e "${YELLOW}Algunas pruebas fallaron (exit code $exit_code).${NC}"
        echo -e "${YELLOW}Revisa el output anterior para ver qué tests fallaron.${NC}"
    fi
    
    rm -f libft/test_libft_normal
    read -p "Pulsa enter para continuar..."
}

verificar_estructura() {
    local errores=0
    
    if [ ! -d "entrega" ]; then
        echo -e "${RED}Error: No existe carpeta 'entrega'${NC}"
        errores=1
    fi
    
    if [ ! -d "ft_printf" ]; then
        echo -e "${RED}Error: No existe carpeta 'ft_printf'${NC}"
        errores=1
    fi
    
    if [ ! -d "libft" ]; then
        echo -e "${RED}Error: No existe carpeta 'libft'${NC}"
        errores=1
    fi
    
    if [ $errores -eq 1 ]; then
        echo -e "${RED}Error: Estructura de carpetas incorrecta${NC}"
        echo -e "${YELLOW}Ejecuta desde la carpeta raíz del proyecto${NC}"
        exit 1
    fi
}

menu_ft_printf() {
    while true; do
        clear
        echo ""
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

        echo "            ╔══════════════════════════════╗"
        echo "            ║      FT_PRINTF - TESTS       ║"
        echo "            ╠══════════════════════════════╣"
        echo "            ║                              ║"
        echo "            ║  1) AddressSanitizer         ║"
        echo "            ║  2) Valgrind                 ║"
        echo "            ║  3) Compilación normal       ║"
        echo "            ║  4) Volver al menú principal ║"
        echo "            ║                              ║"
        echo "            ╚══════════════════════════════╝"
        echo ""
        printf "                    Opción [1-4]: "
        read opt

        case $opt in
            1) test_ft_printf_sanitizer ;;
            2) test_ft_printf_valgrind ;;
            3) test_ft_printf_normal ;;
            4) return ;;
            *) echo -e "\n${RED}Opción inválida.${NC}"; read -p "Pulsa enter para continuar..." ;;
        esac
    done
}

menu_libft() {
    while true; do
        clear
        echo ""
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

        echo "            ╔══════════════════════════════╗"
        echo "            ║        LIBFT - TESTS         ║"
        echo "            ╠══════════════════════════════╣"
        echo "            ║                              ║"
        echo "            ║  1) AddressSanitizer         ║"
        echo "            ║  2) Valgrind                 ║"
        echo "            ║  3) Compilación normal       ║"
        echo "            ║  4) Volver al menú principal ║"
        echo "            ║                              ║"
        echo "            ╚══════════════════════════════╝"
        echo ""
        printf "                    Opción [1-4]: "
        read opt

        case $opt in
            1) test_libft_sanitizer ;;
            2) test_libft_valgrind ;;
            3) test_libft_normal ;;
            4) return ;;
            *) echo -e "\n${RED}Opción inválida.${NC}"; read -p "Pulsa enter para continuar..." ;;
        esac
    done
}

while true; do
    verificar_estructura
    limpiar_entorno
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
    echo ""
    echo "            ╔══════════════════════════════╗"
    echo "            ║       ABELINETTE v3.0        ║"
    echo "            ║ ~pero, todavía vas por el 5? ║"
    echo "            ╠══════════════════════════════╣"
    echo "            ║                              ║"
    echo "            ║  Selecciona el proyecto:     ║"
    echo "            ║                              ║"
    echo "            ║  1) FT_PRINTF                ║"
    echo "            ║  2) LIBFT                    ║"
    echo "            ║  3) Salir                    ║"
    echo "            ║                              ║"
    echo "            ╚══════════════════════════════╝"
    echo ""
    printf "                    Opción [1-3]: "
    read opt

    case $opt in
        1) menu_ft_printf ;;
        2) menu_libft ;;
        3) echo -e "\n${GREEN}Saliendo...${NC}"; limpiar_entorno; exit 0 ;;
        *) echo -e "\n${RED}Opción inválida.${NC}"; read -p "Pulsa enter para continuar..." ;;
    esac
done
