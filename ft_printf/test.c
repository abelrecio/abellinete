#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_CATEGORIES 25
#define CAT_WIDTH 14
#define OK_WIDTH 7
#define KO_WIDTH 5

typedef struct {
    char name[32];
    size_t passed;
    size_t failed;
} test_stats_t;

test_stats_t stats[MAX_CATEGORIES];
size_t stats_count = 0;
FILE *error_log = NULL;
int failed_tests = 0;

// Versión mejorada con Unicode siguiendo tu lógica
void print_summary(void) {
    size_t total_passed = 0, total_failed = 0;
    
    printf("\n🎯 RESUMEN POR CATEGORÍAS\n");
    printf("┌────────────────┬─────────┬───────┐\n");
    printf("│ %-14s │ %7s │ %5s │\n", "Categoria", "OK", "KO");
    printf("├────────────────┼─────────┼───────┤\n");
    
    for (size_t i = 0; i < stats_count; i++) {
        printf("│ %-14s │ %7zu │ %5zu │\n", stats[i].name, stats[i].passed, stats[i].failed);
        total_passed += stats[i].passed;
        total_failed += stats[i].failed;
    }
    
    printf("├────────────────┼─────────┼───────┤\n");
    printf("│ %-14s │ %7zu │ %5zu │\n", "TOTAL", total_passed, total_failed);
    printf("└────────────────┴─────────┴───────┘\n");
    
    printf("\n📈 Success rate: %.1f%% (%zu/%zu tests)\n", 
           (total_passed + total_failed) ? ((float)total_passed / (total_passed + total_failed)) * 100 : 100.0, 
           total_passed, total_passed + total_failed);
           
    if (total_failed == 0) {
        printf("🎉 ¡PERFECTO! Tu ft_printf funciona correctamente\n");
    } else {
        printf("⚠️  Necesitas arreglar %zu caso(s) para que sea perfecto\n", total_failed);
        printf("📄 Revisa errores/error.log para detalles específicos\n");
    }
}

// Versión ASCII como alternativa si Unicode da problemas
void print_summary_ascii(void) {
    size_t total_passed = 0, total_failed = 0;

    printf("\n[RESUMEN POR CATEGORIAS]\n");
    
    // Línea superior
    printf("+");
    for (int i = 0; i < CAT_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < OK_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < KO_WIDTH + 2; ++i) printf("-");
    printf("+\n");
    
    // Cabecera
    printf("| %-*s | %*s | %*s |\n", CAT_WIDTH, "Categoria", OK_WIDTH, "OK", KO_WIDTH, "KO");
    
    // Línea separadora
    printf("+");
    for (int i = 0; i < CAT_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < OK_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < KO_WIDTH + 2; ++i) printf("-");
    printf("+\n");
    
    // Datos
    for (size_t i = 0; i < stats_count; i++) {
        printf("| %-*s | %*zu | %*zu |\n", 
               CAT_WIDTH, stats[i].name, 
               OK_WIDTH, stats[i].passed, 
               KO_WIDTH, stats[i].failed);
        total_passed += stats[i].passed;
        total_failed += stats[i].failed;
    }
    
    // Línea separadora antes del total
    printf("+");
    for (int i = 0; i < CAT_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < OK_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < KO_WIDTH + 2; ++i) printf("-");
    printf("+\n");
    
    // Total
    printf("| %-*s | %*zu | %*zu |\n", CAT_WIDTH, "TOTAL", OK_WIDTH, total_passed, KO_WIDTH, total_failed);
    
    // Línea inferior
    printf("+");
    for (int i = 0; i < CAT_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < OK_WIDTH + 2; ++i) printf("-");
    printf("+");
    for (int i = 0; i < KO_WIDTH + 2; ++i) printf("-");
    printf("+\n");

    printf("\nSuccess rate: %.1f%% (%zu/%zu tests)\n", 
           (total_passed + total_failed) ? ((float)total_passed / (total_passed + total_failed)) * 100 : 100.0, 
           total_passed, total_passed + total_failed);

    if (total_failed == 0) {
        printf("[!] PERFECTO! Tu ft_printf funciona correctamente\n");
    } else {
        printf("[!] Necesitas arreglar %zu caso(s) para que sea perfecto\n", total_failed);
        printf("[!] Revisa errores/error.log para detalles especificos\n");
    }
}

void init_error_log() {
    mkdir("../errores", 0755);
    error_log = fopen("../errores/error.log", "w");
    if (error_log) {
        fprintf(error_log, "ft_printf ERROR LOG - Tests que fallaron\n");
        fprintf(error_log, "=========================================\n\n");
    }
}

void close_error_log() {
    if (error_log) {
        fprintf(error_log, "\n=== FIN DEL LOG ===\n");
        fclose(error_log);
    }
}

void init_test_category(const char *name) {
    if (stats_count < MAX_CATEGORIES) {
        strncpy(stats[stats_count].name, name, sizeof(stats[stats_count].name) - 1);
        stats[stats_count].name[sizeof(stats[stats_count].name) - 1] = '\0';
        stats[stats_count].passed = 0;
        stats[stats_count].failed = 0;
        stats_count++;
    }
}

void record_test_result(int passed) {
    if (stats_count > 0) {
        if (passed) {
            stats[stats_count - 1].passed++;
        } else {
            stats[stats_count - 1].failed++;
            failed_tests++;
        }
    }
}

int compare_outputs(const char *test_name, const char *format, int ft_ret, int orig_ret) {
    int passed = (ft_ret == orig_ret);
    record_test_result(passed);

    if (!passed && error_log) {
        fprintf(error_log, "[FAIL] %s: formato='%s' ft_printf=%d, printf=%d\n", 
                test_name, format, ft_ret, orig_ret);
        fflush(error_log);
    }
    return passed;
}

#define TEST(test_name, format_str, ft_call, printf_call) do { \
    int ft_ret = ft_call; \
    int printf_ret = printf_call; \
    compare_outputs(test_name, format_str, ft_ret, printf_ret); \
} while(0)

// Debes tener la firma de ft_printf visible para el linker
int ft_printf(const char *format, ...);

int main(void) {
    init_error_log();

    printf("TESTING ft_printf vs printf\n");
    printf("===========================\n");

    // === TESTS BÁSICOS ===
    init_test_category("Basico");
    TEST("básico", "Básico: %d", ft_printf("Básico: %d\n", 42), printf("Básico: %d\n", 42));
    TEST("solo texto", "Solo texto", ft_printf("Solo texto\n"), printf("Solo texto\n"));
    TEST("string vacía", "", ft_printf(""), printf(""));

    // === FLAGS PRECEDENCIA ===
    init_test_category("Flags");
    TEST("doble -", "%--10d", ft_printf("Doble -: %--10d|\n", 42), printf("Doble -: %--10d|\n", 42));
    TEST("doble 0", "%0010d", ft_printf("Doble 0: %0010d\n", 42), printf("Doble 0: %0010d\n", 42));
    TEST("- antes 0", "%-010d", ft_printf("- antes 0: %-010d|\n", 42), printf("- antes 0: %-010d|\n", 42));
    TEST("0 antes -", "%0-10d", ft_printf("0 antes -: %0-10d|\n", 42), printf("0 antes -: %0-10d|\n", 42));
    TEST("triple flags", "%-0-10d", ft_printf("Triple: %-0-10d|\n", 42), printf("Triple: %-0-10d|\n", 42));

    // === PRECISIÓN ===
    init_test_category("Precision");
    TEST("0 + precisión", "%08.5d", ft_printf("0 + prec: %08.5d\n", 42), printf("0 + prec: %08.5d\n", 42));
    TEST("0 + prec negativo", "%08.5d neg", ft_printf("0 + prec neg: %08.5d\n", -42), printf("0 + prec neg: %08.5d\n", -42));
    TEST("prec < número", "%.2d", ft_printf("Prec < num: %.2d\n", 12345), printf("Prec < num: %.2d\n", 12345));
    TEST("CRÍTICO: %.0d con 0", "%.0d val 0", ft_printf("Prec 0 val 0: %.0d|\n", 0), printf("Prec 0 val 0: %.0d|\n", 0));
    TEST("%.0d con 42", "%.0d val 42", ft_printf("Prec 0 val 42: %.0d|\n", 42), printf("Prec 0 val 42: %.0d|\n", 42));
    TEST("TU EJEMPLO", "%0.9d", ft_printf("Tu ejemplo: %0.9d\n", 42), printf("Tu ejemplo: %0.9d\n", 42));
    TEST("width + prec", "%015.9d", ft_printf("Con width: %015.9d\n", 42), printf("Con width: %015.9d\n", 42));
    TEST("solo punto", "%.d", ft_printf("Solo punto: %.d\n", 42), printf("Solo punto: %.d\n", 42));
    TEST("CRÍTICO: %.d con 0", "%.d val 0", ft_printf("Solo punto 0: %.d\n", 0), printf("Solo punto 0: %.d\n", 0));

    // === WIDTH vs PRECISION ===
    init_test_category("Width/Prec");
    TEST("width < precisión", "%5.10d", ft_printf("W<P: %5.10d\n", 42), printf("W<P: %5.10d\n", 42));
    TEST("width = precisión", "%5.5d", ft_printf("W=P: %5.5d\n", 42), printf("W=P: %5.5d\n", 42));
    TEST("width/prec grandes", "%50.30d", ft_printf("Grande: %50.30d\n", 42), printf("Grande: %50.30d\n", 42));

    // === LÍMITES NUMÉRICOS ===
    init_test_category("Limites");
    TEST("INT_MAX", "%d INT_MAX", ft_printf("MAX: %d\n", INT_MAX), printf("MAX: %d\n", INT_MAX));
    TEST("INT_MAX prec", "%.20d INT_MAX", ft_printf("MAX prec: %.20d\n", INT_MAX), printf("MAX prec: %.20d\n", INT_MAX));
    TEST("INT_MIN", "%d INT_MIN", ft_printf("MIN: %d\n", INT_MIN), printf("MIN: %d\n", INT_MIN));
    TEST("INT_MIN flag 0", "%020d INT_MIN", ft_printf("MIN 0: %020d\n", INT_MIN), printf("MIN 0: %020d\n", INT_MIN));
    TEST("INT_MIN prec", "%.15d INT_MIN", ft_printf("MIN prec: %.15d\n", INT_MIN), printf("MIN prec: %.15d\n", INT_MIN));

    // === VALOR 0 ===
    init_test_category("Valor 0");
    TEST("0 básico", "%d val 0", ft_printf("0 básico: %d\n", 0), printf("0 básico: %d\n", 0));
    TEST("0 con width", "%5d val 0", ft_printf("0 width: %5d|\n", 0), printf("0 width: %5d|\n", 0));
    TEST("0 con flag 0", "%05d val 0", ft_printf("0 flag0: %05d\n", 0), printf("0 flag0: %05d\n", 0));
    TEST("0 left align", "%-5d val 0", ft_printf("0 left: %-5d|\n", 0), printf("0 left: %-5d|\n", 0));
    TEST("0 con precisión", "%.5d val 0", ft_printf("0 prec: %.5d\n", 0), printf("0 prec: %.5d\n", 0));

    // === STRINGS ===
    init_test_category("Strings");
    TEST("CRÍTICO: string NULL", "%s NULL", ft_printf("NULL: %s\n", (char *)NULL), printf("NULL: %s\n", (char *)NULL));
    TEST("string vacía", "%s empty", ft_printf("Empty: '%s'\n", ""), printf("Empty: '%s'\n", ""));
    TEST("string precisión", "%.3s", ft_printf("Str prec: %.3s\n", "Hello"), printf("Str prec: %.3s\n", "Hello"));
    TEST("CRÍTICO: %.0s", "%.0s", ft_printf("Str prec 0: %.0s|\n", "Hello"), printf("Str prec 0: %.0s|\n", "Hello"));
    TEST("NULL + precisión", "%.3s NULL", ft_printf("NULL prec: %.3s\n", (char *)NULL), printf("NULL prec: %.3s\n", (char *)NULL));
    TEST("string width", "%10s", ft_printf("Str width: %10s|\n", "Hi"), printf("Str width: %10s|\n", "Hi"));
    TEST("string left", "%-10s", ft_printf("Str left: %-10s|\n", "Hi"), printf("Str left: %-10s|\n", "Hi"));
    TEST("string larga", "%.50s", ft_printf("Long str: %.50s\n", "This is a very long string for testing purposes"), printf("Long str: %.50s\n", "This is a very long string for testing purposes"));

    // === HEXADECIMAL ===
    init_test_category("Hexadecimal");
    TEST("hex 0", "%x val 0", ft_printf("Hex 0: %x\n", 0), printf("Hex 0: %x\n", 0));
    TEST("CRÍTICO: %.0x con 0", "%.0x val 0", ft_printf("Hex prec 0: %.0x|\n", 0), printf("Hex prec 0: %.0x|\n", 0));
    TEST("hex case", "%x vs %X", ft_printf("Hex: %x vs %X\n", 255, 255), printf("Hex: %x vs %X\n", 255, 255));
    TEST("hex flag 0", "%08x", ft_printf("Hex 0: %08x\n", 255), printf("Hex 0: %08x\n", 255));
    TEST("hex precisión", "%.8x", ft_printf("Hex prec: %.8x\n", 255), printf("Hex prec: %.8x\n", 255));
    TEST("hex máximo", "%x max", ft_printf("HEX MAX: %x\n", UINT_MAX), printf("HEX MAX: %x\n", UINT_MAX));
    TEST("hex flag 0 + prec", "%08.5x", ft_printf("Hex 0+prec: %08.5x\n", 255), printf("Hex 0+prec: %08.5x\n", 255));

    // === UNSIGNED ===
    init_test_category("Unsigned");
    TEST("unsigned 0", "%u val 0", ft_printf("Uns 0: %u\n", 0u), printf("Uns 0: %u\n", 0u));
    TEST("UINT_MAX", "%u UINT_MAX", ft_printf("Uns MAX: %u\n", UINT_MAX), printf("Uns MAX: %u\n", UINT_MAX));
    TEST("CRÍTICO: %.0u con 0", "%.0u val 0", ft_printf("Uns prec 0: %.0u|\n", 0u), printf("Uns prec 0: %.0u|\n", 0u));

    // === POINTER ===
    init_test_category("Pointer");
    TEST("pointer NULL", "%p NULL", ft_printf("Ptr NULL: %p\n", (void *)NULL), printf("Ptr NULL: %p\n", (void *)NULL));
    int x = 42;
    TEST("pointer válido", "%p", ft_printf("Ptr: %p\n", &x), printf("Ptr: %p\n", &x));

    // === CHAR ===
    init_test_category("Char");
    TEST("char normal", "%c", ft_printf("Char: %c\n", 'A'), printf("Char: %c\n", 'A'));
    TEST("char null", "%c val 0", ft_printf("Char 0: '%c'\n", 0), printf("Char 0: '%c'\n", 0));
    TEST("char width", "%5c", ft_printf("Char w: '%5c'|\n", 'A'), printf("Char w: '%5c'|\n", 'A'));
    TEST("char tab", "%c tab", ft_printf("Char tab: '%c'\n", '\t'), printf("Char tab: '%c'\n", '\t'));
    TEST("char newline", "%c newline", ft_printf("Char newline: '%c'\n", '\n'), printf("Char newline: '%c'\n", '\n'));
    TEST("char ASCII alto", "%c 127", ft_printf("Char ASCII: '%c'\n", 127), printf("Char ASCII: '%c'\n", 127));

    // === PORCENTAJE ===
    init_test_category("Porcentaje");
    TEST("porcentaje", "%%", ft_printf("Percent: %%\n"), printf("Percent: %%\n"));

    // === ASTERISCO ===
    init_test_category("Asterisco");
    TEST("width asterisco", "%*d", ft_printf("Width *: %*d|\n", 10, 42), printf("Width *: %*d|\n", 10, 42));
    TEST("precision asterisco", "%.*d", ft_printf("Prec *: %.*d\n", 5, 42), printf("Prec *: %.*d\n", 5, 42));
    TEST("width+prec asterisco", "%*.*d", ft_printf("W+P *: %*.*d\n", 10, 5, 42), printf("W+P *: %*.*d\n", 10, 5, 42));
    TEST("CRÍTICO: * width negativo", "%*d neg width", ft_printf("* neg W: %*d|\n", -10, 42), printf("* neg W: %*d|\n", -10, 42));
    TEST("CRÍTICO: * prec negativa", "%.*d neg prec", ft_printf("* neg P: %.*d\n", -5, 42), printf("* neg P: %.*d\n", -5, 42));
    TEST("string * width", "%*s", ft_printf("Str *: %*s|\n", 10, "Hi"), printf("Str *: %*s|\n", 10, "Hi"));
    TEST("string * precision", "%.*s", ft_printf("Str .*: %.*s|\n", 3, "Hello"), printf("Str .*: %.*s|\n", 3, "Hello"));
    TEST("flag 0 + asterisco", "%0*d", ft_printf("0 + *: %0*d\n", 8, 42), printf("0 + *: %0*d\n", 8, 42));
    TEST("flag - + asterisco", "%-*d", ft_printf("- + *: %-*d|\n", 8, 42), printf("- + *: %-*d|\n", 8, 42));

    // === FORMATO MIXTO ===
    init_test_category("Mixto");
    TEST("formato mixto", "múltiples specs", ft_printf("Mix: %d %s %c %x\n", 42, "test", 'Z', 255), printf("Mix: %d %s %c %x\n", 42, "test", 'Z', 255));
    TEST("leak test múltiple", "múltiple specs", ft_printf("Leak test 1: %s %d %x\n", "test", 42, 255), printf("Leak test 1: %s %d %x\n", "test", 42, 255));

    // === FLAGS BONUS ===
    init_test_category("Bonus");
    TEST("flag +", "%+d", ft_printf("Flag +: %+d\n", 42), printf("Flag +: %+d\n", 42));
    TEST("flag + negativo", "%+d neg", ft_printf("Flag + neg: %+d\n", -42), printf("Flag + neg: %+d\n", -42));
    TEST("flag space", "% d", ft_printf("Flag space: % d\n", 42), printf("Flag space: % d\n", 42));
    TEST("flag space neg", "% d neg", ft_printf("Flag space neg: % d\n", -42), printf("Flag space neg: % d\n", -42));
    TEST("CRÍTICO: + vs space", "%+ d", ft_printf("+ vs space: %+ d\n", 42), printf("+ vs space: %+ d\n", 42));
    TEST("flag # hex", "%#x", ft_printf("Flag # hex: %#x\n", 42), printf("Flag # hex: %#x\n", 42));
    TEST("flag # HEX", "%#X", ft_printf("Flag # HEX: %#X\n", 42), printf("Flag # HEX: %#X\n", 42));
    TEST("CRÍTICO: # con 0", "%#x val 0", ft_printf("Flag # con 0: %#x\n", 0), printf("Flag # con 0: %#x\n", 0));
    TEST("flag # octal", "%#o", ft_printf("Flag # octal: %#o\n", 42), printf("Flag # octal: %#o\n", 42));

    // === OCTAL ===
    init_test_category("Octal");
    TEST("octal básico", "%o", ft_printf("Octal: %o\n", 42), printf("Octal: %o\n", 42));
    TEST("octal valor 0", "%o val 0", ft_printf("Octal 0: %o\n", 0), printf("Octal 0: %o\n", 0));
    TEST("CRÍTICO: %.0o con 0", "%.0o val 0", ft_printf("Octal %.0o: %.0o|\n", 0, 0), printf("Octal %.0o: %.0o|\n", 0, 0));
    TEST("octal flag 0", "%08o", ft_printf("Octal flag 0: %08o\n", 42), printf("Octal flag 0: %08o\n", 42));
    TEST("octal máximo", "%o max", ft_printf("OCT MAX: %o\n", UINT_MAX), printf("OCT MAX: %o\n", UINT_MAX));

    // === EDGE CASES ===
    init_test_category("EdgeCases");
    TEST("+ y 0", "%+08d", ft_printf("Multi flags: %+08d\n", 42), printf("Multi flags: %+08d\n", 42));
    TEST("- y +", "%-+10d", ft_printf("Multi flags: %-+10d|\n", 42), printf("Multi flags: %-+10d|\n", 42));
    TEST("# y 0 hex", "%#08x", ft_printf("Multi flags: %#08x\n", 42), printf("Multi flags: %#08x\n", 42));
    TEST("todos los flags", "%-+#010x", ft_printf("All flags: %-+#010x|\n", 42), printf("All flags: %-+#010x|\n", 42));
    TEST("precedencia compleja", "%+0*.*d", ft_printf("Complex: %+0*.*d\n", 10, 5, 42), printf("Complex: %+0*.*d\n", 10, 5, 42));
    TEST("width neg + flags", "%+*d neg width", ft_printf("Neg width flags: %+*d|\n", -10, 42), printf("Neg width flags: %+*d|\n", -10, 42));
    TEST("width = 0", "%0d", ft_printf("Width 0: %0d\n", 42), printf("Width 0: %0d\n", 42));
    TEST("precision .000", "%.000d", ft_printf("Multi 0: %.000d\n", 42), printf("Multi 0: %.000d\n", 42));

    // === %i ===
    init_test_category("%i");
    TEST("%i básico", "%i", ft_printf("%%i básico: %i\n", 42), printf("%%i básico: %i\n", 42));
    TEST("%i con flags", "%+08i", ft_printf("%%i flags: %+08i\n", 42), printf("%%i flags: %+08i\n", 42));
    TEST("%i precisión", "%.5i", ft_printf("%%i prec: %.5i\n", 42), printf("%%i prec: %.5i\n", 42));

    // === EXAM 42 ===
    init_test_category("Exam42");
    TEST("exam: %s empty", "%s empty", ft_printf("%s", ""), printf("%s", ""));
    TEST("exam: %d=0", "%d val 0", ft_printf("%d", 0), printf("%d", 0));
    TEST("exam: %x=0", "%x val 0", ft_printf("%x", 0), printf("%x", 0));
    TEST("exam: %.10s", "%.10s", ft_printf("%.10s", "hello"), printf("%.10s", "hello"));
    TEST("exam: %10.5s", "%10.5s", ft_printf("%10.5s", "hello world"), printf("%10.5s", "hello world"));
    TEST("exam: %-10.5s", "%-10.5s", ft_printf("%-10.5s", "hello world"), printf("%-10.5s", "hello world"));
    TEST("exam: %*d", "%*d", ft_printf("%*d", 5, 42), printf("%*d", 5, 42));
    TEST("exam: %.*s", "%.*s", ft_printf("%.*s", 3, "hello"), printf("%.*s", 3, "hello"));
    TEST("exam: %*.*d", "%*.*d", ft_printf("%*.*d", 8, 5, 42), printf("%*.*d", 8, 5, 42));
    TEST("conteo final", "count test", ft_printf("Test count final: %d caracteres", 42), printf("Test count final: %d caracteres", 42));

    close_error_log();
    print_summary();

    return failed_tests;
}
