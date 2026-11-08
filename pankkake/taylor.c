#include <stdio.h>
#include <math.h>

typedef double (*referencefunction)(double x);
typedef double (*coefficient)(int k);
typedef double (*power)(int k);

typedef struct {
    const char *name;
    referencefunction r;
    coefficient c;
    power p;
    double initial_value;
    int requires_unit_interval;
} functioninfo;

static double sin_tailor(int k) {
    return (k % 2 == 0 ? 1.0 : -1.0) / tgamma(2.0 * k + 2.0);
}

static double sin_precision(int k) {
    return 2.0 * k + 1.0;
}

static double cos_tailor(int k) {
    return (k % 2 == 0 ? 1.0 : -1.0) / tgamma(2.0 * k + 1.0);
}

static double cos_precision(int k) {
    return 2.0 * k;
}

static double exp_tailor(int k) {
    return 1.0 / tgamma(k + 1.0);
}

static double exp_precision(int k) {
    return (double)k;
}

static double acos_tailor(int k) {
    double coefficient = -1.0;
    int i;
    /* a(k+1) = a(k) * (2k+1)^2 / ((2k+2)(2k+3)) */
    for (i = 0; i < k; ++i)
        coefficient *= (2.0 * i + 1.0) * (2.0 * i + 1.0) /
                       ((2.0 * i + 2.0) * (2.0 * i + 3.0));
    return coefficient;
}

static double arccos_precision(int k) {
    return 2.0 * k + 1.0;
}

static void calculate_by_taylor(const functioninfo *function, double x,
                                double precision, int max_terms,
                                double *value, int *terms_used) {
    double sum = function->initial_value;
    int k;

    for (k = 0; k < max_terms; ++k) {
        double term = function->c(k) * pow(x, function->p(k));
        sum += term;
        if (fabs(term) < precision) break;
    }
    *value = sum;
    *terms_used = k + 1;
}

static int read_int(const char *prompt, int min, int max) {
    int value;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) return value;
        printf("Enter integer %d..%d\n", min, max);
        while (getchar() != '\n' && !feof(stdin)) { }
    }
}

static double read_double(const char *prompt) {
    double value;
    for (;;) {
        printf("%s", prompt);
        if (scanf("%lf", &value) == 1 && isfinite(value)) return value;
        printf("Enter a number\n");
        while (getchar() != '\n' && !feof(stdin)) { }
    }
}

int main(void) {
    const functioninfo *selected;
    double x, precision, reference_value, estimate;
    int function_count, choice, max_terms, terms_used;

    const functioninfo functions[] = {
        {"sin(x)", sin, sin_tailor, sin_precision, 0.0, 0},
        {"cos(x)", cos, cos_tailor, cos_precision, 0.0, 0},
        {"exp(x)", exp, exp_tailor, exp_precision, 0.0, 0},
        {"arccos(x)", acos, acos_tailor, arccos_precision, 1.5707963267948966, 1}
    };
    function_count = (int)(sizeof(functions) / sizeof(functions[0]));
    puts("Taylor series");
    puts("Functions:");
    for (int i = 0; i < function_count; ++i)
        printf("  %d. %s\n", i + 1, functions[i].name);

    choice = read_int("Function: ", 1, function_count);
    selected = &functions[choice - 1];
    do {
        x = read_double("x: ");
        if (selected->requires_unit_interval && (x < -1.0 || x > 1.0))
            puts("arccos: x must be -1..1");
    } while (selected->requires_unit_interval && (x < -1.0 || x > 1.0));

    do {
        precision = read_double("Precision (>= 0.000001): ");
        if (precision < 0.000001) puts("Too small");
    } while (precision < 0.000001);
    max_terms = read_int("Terms (1..1000): ", 1, 1000);

    calculate_by_taylor(selected, x, precision, max_terms, &estimate, &terms_used);
    reference_value = selected->r(x);

    printf("\n%s, x = %.10g\n", selected->name, x);
    printf("Reference: %.15g\n", reference_value);
    printf("Taylor:    %.15g\n", estimate);
    printf("Difference: %.15g\n", fabs(estimate - reference_value));
    printf("Terms: %d\n", terms_used);
    return 0;
}
