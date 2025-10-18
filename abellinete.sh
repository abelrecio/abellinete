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

test_ft_printf_sanitizer() {
    echo -e "${BLUE}Compilando ft_printf con AddressSanitizer...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca ft_printf...${NC}"
    make -C entrega/ft_printf fclean
    make -C entrega/ft_printf all
    make -C entrega/ft_printf bonus    
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de ft_printf con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando test con AddressSanitizer...${NC}"
    cc -fsanitize=address -g \
        ft_printf/test.c \
        entrega/ft_printf/libftprintf.a \
        -I entrega/ft_printf \
        -o ft_printf/test_ft_printf_sanitizer
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación de test con Sanitizer.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando test con AddressSanitizer...${NC}"
    cd ft_printf
    ./test_ft_printf_sanitizer "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    
    rm -f ft_printf/test_ft_printf_sanitizer
    read -p "Pulsa enter para continuar..."
}

test_ft_printf_valgrind() {
    echo -e "${BLUE}Compilando ft_printf para Valgrind...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca ft_printf...${NC}"
    make -C entrega/ft_printf fclean
    make -C entrega/ft_printf all
    make -C entrega/ft_printf bonus    
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de ft_printf con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando test para Valgrind (con símbolos de debug)...${NC}"
    cc -g -O0 \
        ft_printf/test.c \
        entrega/ft_printf/libftprintf.a \
        -I entrega/ft_printf \
        -o ft_printf/test_ft_printf_valgrind
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación de test para Valgrind.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando Valgrind con detección completa de fugas...${NC}"
    cd ft_printf
    valgrind --leak-check=full \
             --show-leak-kinds=all \
             --track-origins=yes \
             --error-exitcode=1 \
             ./test_ft_printf_valgrind "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
    
    rm -f ft_printf/test_ft_printf_valgrind
    read -p "Pulsa enter para continuar..."
}

test_ft_printf_normal() {
    echo -e "${BLUE}Compilando ft_printf normalmente...${NC}"
    
    echo -e "${YELLOW}Compilando biblioteca ft_printf con make...${NC}"
    make -C entrega/ft_printf fclean
    make -C entrega/ft_printf all
    make -C entrega/ft_printf bonus    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló la compilación de ft_printf con make.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    if [ ! -f "entrega/ft_printf/libftprintf.a" ]; then
        echo -e "${RED}Error: No se encontró entrega/ft_printf/libftprintf.a${NC}"
        echo -e "${YELLOW}Verifica que el Makefile esté configurado correctamente.${NC}"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${YELLOW}Compilando test con la biblioteca...${NC}"
    cc  \
        ft_printf/test.c \
        entrega/ft_printf/libftprintf.a \
        -I entrega/ft_printf \
        -o ft_printf/test_ft_printf_normal
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}Falló compilación del test.${NC}"
        echo -e "${YELLOW}Posibles causas:${NC}"
        echo -e "  - Falta el archivo ft_printf.h en entrega/ft_printf/"
        echo -e "  - El test espera funciones que no están implementadas"
        echo -e "  - Errores de sintaxis en el código"
        read -p "Pulsa enter para continuar..."
        return 1
    fi
    
    echo -e "${BLUE}Ejecutando test: ./test_ft_printf_normal ${TEST_ARGS[*]}${NC}"
    cd ft_printf
    ./test_ft_printf_normal "${TEST_ARGS[@]}"
    local exit_code=$?
    cd ..
     
    rm -f ft_printf/test_ft_printf_normal
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

menu_gnl() {
    local SRC_DIR="entrega/get_next_line"
    local TEST_DIR="gnl"

    # Verificar que existe el directorio de código fuente
    if [ ! -d "$SRC_DIR" ]; then
        echo "Error: No se encuentra el directorio $SRC_DIR/"
        return 1
    fi

    # Verificar que existe el directorio de tests
    if [ ! -d "$TEST_DIR" ]; then
        echo "Error: No se encuentra el directorio $TEST_DIR/"
        return 1
    fi

    mostrar_menu_principal() {
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
        echo "           ABELINETTE GNL"
        echo "========================================"
    }

    mostrar_menu_principal

    echo "Elige tamaño de BUFFER_SIZE:"
    echo "1. BUFFER_SIZE = 1"
    echo "2. BUFFER_SIZE = 42"
    echo "3. BUFFER_SIZE = 1000"
    echo "4. BUFFER_SIZE personalizado"
    read -p "Opción: " buffer_option

    case $buffer_option in
        1) BUFFER_SIZE=1 ;;
        2) BUFFER_SIZE=42 ;;
        3) BUFFER_SIZE=1000 ;;
        4)
            read -p "Introduce BUFFER_SIZE: " BUFFER_SIZE
            if ! [[ "$BUFFER_SIZE" =~ ^[0-9]+$ ]] || [ "$BUFFER_SIZE" -le 0 ] || [ "$BUFFER_SIZE" -gt 2147483647 ]; then
                echo "BUFFER_SIZE inválido (debe ser un número entre 1 y 2147483647)"
                return 1
            fi
            ;;
        *)
            echo "Opción inválida"
            return 1
            ;;
    esac

    echo
    echo "Elige herramienta de debugging:"
    echo "1. Valgrind (completo)"
    echo "2. Address Sanitizer (rápido)"
    read -p "Opción: " debug_option

    case $debug_option in
        1)
            COMPILE_FLAGS="-Wall -Wextra -Werror -D BUFFER_SIZE=$BUFFER_SIZE"
            DEBUG_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --show-reachable=yes --error-exitcode=1"
            ;;
        2)
            COMPILE_FLAGS="-Wall -Wextra -Werror -D BUFFER_SIZE=$BUFFER_SIZE -fsanitize=address -fsanitize=undefined -fno-sanitize-recover -g3"
            DEBUG_CMD=""
            ;;
        *)
            echo "Opción inválida"
            return 1
            ;;
    esac

    while true; do
        echo
        echo "1. Archivo vacío - busca errores de lectura sin contenido [cualquier buffer]"
        echo "2. Solo un '\n' - prueba manejo de línea vacía válida [cualquier buffer]"
        echo "3. 41 chars sin '\n' final - EOF sin newline [mejor con 42]"
        echo "4. 41 chars + '\n' + resto - lectura tras newline [mejor con 42]"
        echo "5. Exacto BUFFER_SIZE sin '\n' - límite de buffer [requiere 42]"
        echo "6. BUFFER_SIZE + '\n' + resto - desbordamiento de buffer [requiere 42]"
        echo "7. BUFFER_SIZE+1 sin '\n' - buffer insuficiente [requiere 42]"
        echo "8. BUFFER_SIZE+1 + '\n' + resto - múltiples lecturas [requiere 42]"
        echo "9. Cinco '\n' seguidos - líneas vacías repetidas [mejor con 1]"
        echo "10. Varias líneas, última sin '\n' - EOF mixto [cualquier buffer]"
        echo "11. Varias líneas completas - lectura secuencial [cualquier buffer]"
        echo "12. Líneas largas/vacías alternas, sin '\n' final [mejor con 1 o 42]"
        echo "13. Líneas largas/vacías alternas, con '\n' final [mejor con 1 o 42]"
        echo "14. Línea gigante sin '\n' - múltiples buffers [mejor con 1]"
        echo "15. Línea gigante con '\n' - gestión memoria grande [mejor con 1]"
        echo "16. Prueba general de funcionalidad básica [cualquier buffer]"
        echo "17. Texto real extenso - rendimiento y memoria [mejor con 1 o 1000]"
        echo "18. No fd, hago close en el archivo y lo mando a gnl [cualquier buffer]"
        echo "19. stdin.txt"
        echo "20. PRUEBA DEL TEST, EN LA 20, POR ALGÚN MOTIVO"
        echo "21. Salto sin contenido - termina tras \\n [cualquier buffer]"
        echo "22. Múltiplos exactos - líneas de BUFFER_SIZE exacto [requiere 42]"
        echo "23. Muchas líneas vacías - stress test con líneas vacías [mejor con 1]"
        echo "24. Solo espacios y tabs - caracteres whitespace [cualquier buffer]"
        echo "25. Caracteres especiales - UTF-8, acentos, emojis [mejor con 1]"
        echo "26. Fin abrupto - archivo truncado sin \\n [cualquier buffer]"
        echo "27. Stress fragmentación - tamaños variables de línea [requiere 1]"
        echo "28. Todos los test (redirigir la salida)"
        echo "0. Salir"

        read -p "Elige test: " option

        case $option in
            0) return 0 ;;
            1) file="vacio.txt" ;;
            2) file="solo_salto.txt" ;;
            3) file="linea_41_sin_salto.txt" ;;
            4) file="linea_41_con_salto.txt" ;;
            5) file="linea_42_sin_salto.txt" ;;
            6) file="linea_42_con_salto.txt" ;;
            7) file="linea_43_sin_salto.txt" ;;
            8) file="linea_43_con_salto.txt" ;;
            9) file="cinco_saltos_vacios.txt" ;;
            10) file="multiples_sin_salto_final.txt" ;;
            11) file="multiples_con_salto_final.txt" ;;
            12) file="alternas_termina_sin_salto.txt" ;;
            13) file="alternas_termina_con_salto.txt" ;;
            14) file="linea_gigante_sin_salto.txt" ;;
            15) file="linea_gigante_con_salto.txt" ;;
            16) file="archivo.txt" ;;
            17) file="el_quijote.txt" ;;
            18) file="no_fd.txt" ;;
            19) file="stdin" ;;
            20) file="bonus.txt" ;;
            21) file="salto_sin_contenido.txt" ;;
            22) file="buffer_multiple.txt" ;;
            23) file="muchas_lineas_vacias.txt" ;;
            24) file="solo_espacios.txt" ;;
            25) file="caracteres_especiales.txt" ;;
            26) file="fin_abrupto.txt" ;;
            27) file="stress_fragmentacion.txt" ;;
            28)
                echo "Compilando desde $SRC_DIR/..."
                gcc $COMPILE_FLAGS $SRC_DIR/*.c $TEST_DIR/main.c
                if [ $? -ne 0 ]; then
                    echo "Error de compilación"
                    continue
                fi

                test_files=(
                    "vacio.txt" "solo_salto.txt" "linea_41_sin_salto.txt" "linea_41_con_salto.txt"
                    "linea_42_sin_salto.txt" "linea_42_con_salto.txt" "linea_43_sin_salto.txt"
                    "linea_43_con_salto.txt" "cinco_saltos_vacios.txt" "multiples_sin_salto_final.txt"
                    "multiples_con_salto_final.txt" "alternas_termina_sin_salto.txt" "alternas_termina_con_salto.txt"
                    "linea_gigante_sin_salto.txt" "linea_gigante_con_salto.txt" "archivo.txt"
                    "el_quijote.txt" "no_fd.txt" "salto_sin_contenido.txt" "buffer_multiple.txt"
                    "muchas_lineas_vacias.txt" "solo_espacios.txt" "caracteres_especiales.txt"
                    "fin_abrupto.txt" "stress_fragmentacion.txt"
                )

                for test_file in "${test_files[@]}"; do
                    if [ -f "$TEST_DIR/test/$test_file" ]; then
                        echo "=== Ejecutando test: $test_file ==="
                        $DEBUG_CMD ./a.out "$TEST_DIR/test/$test_file"
                        echo
                    else
                        echo "=== Archivo no encontrado: $TEST_DIR/test/$test_file ==="
                    fi
                done
                ;;
            *) echo "Opción inválida"; continue ;;
        esac

        if [ "$option" != "0" ] && [ "$option" != "28" ]; then
            echo "Compilando desde $SRC_DIR/..."
            gcc $COMPILE_FLAGS $SRC_DIR/*.c $TEST_DIR/main.c
            if [ $? -ne 0 ]; then
                echo "Error de compilación"
                continue
            fi

            if [ -f "$TEST_DIR/test/$file" ]; then
                $DEBUG_CMD ./a.out "$TEST_DIR/test/$file"
            else
                echo "Error: No se encuentra el archivo $TEST_DIR/test/$file"
            fi
        fi
    done
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
    echo "            ║       ABELINETTE v4.0        ║"
    echo "            ║ ~pero, todavía vas por el 5? ║"
    echo "            ╠══════════════════════════════╣"
    echo "            ║                              ║"
    echo "            ║  Selecciona el proyecto:     ║"
    echo "            ║                              ║"
    echo "            ║  1) FT_PRINTF                ║"
    echo "            ║  2) LIBFT                    ║"
    echo "            ║  3) GNL                      ║"
    echo "            ║  4) Salir                    ║"
    echo "            ║                              ║"
    echo "            ╚══════════════════════════════╝"
    echo ""
    printf "                    Opción [1-4]: "
    read opt

    case $opt in
        1) menu_ft_printf ;;
        2) menu_libft ;;
	3) menu_gnl ;;
        4) echo -e "\n${GREEN}Saliendo...${NC}"; limpiar_entorno; exit 0 ;;
        *) echo -e "\n${RED}Opción inválida.${NC}"; read -p "Pulsa enter para continuar..." ;;
    esac
done
