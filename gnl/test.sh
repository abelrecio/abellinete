#!/bin/bash

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
            exit 1
        fi
        ;;
    *) 
        echo "Opción inválida"
        exit 1
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
        exit 1
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
        0) exit 0 ;;
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
   gcc $COMPILE_FLAGS *.c
   if [ $? -ne 0 ]; then
       echo "Error de compilación"
       continue
   fi
   
   for test_file in vacio.txt solo_salto.txt linea_41_sin_salto.txt linea_41_con_salto.txt linea_42_sin_salto.txt linea_42_con_salto.txt linea_43_sin_salto.txt linea_43_con_salto.txt cinco_saltos_vacios.txt multiples_sin_salto_final.txt multiples_con_salto_final.txt alternas_termina_sin_salto.txt alternas_termina_con_salto.txt linea_gigante_sin_salto.txt linea_gigante_con_salto.txt archivo.txt el_quijote.txt no_fd.txt salto_sin_contenido.txt buffer_multiple.txt muchas_lineas_vacias.txt solo_espacios.txt caracteres_especiales.txt fin_abrupto.txt stress_fragmentacion.txt; do
       $DEBUG_CMD ./a.out $test_file
   done
   ;;
        *) echo "Opción inválida"; continue ;;
    esac
    
    if [ "$option" != "0" ]; then
        gcc $COMPILE_FLAGS *.c
        if [ $? -ne 0 ]; then
            echo "Error de compilación"
            continue
        fi
        
        $DEBUG_CMD ./a.out $file
    fi
done
