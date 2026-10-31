#include <stdio.h>

#define A_DENSITY 650.0
#define B_DENSITY 800.0
#define C_DENSITY 700.0

int main(void)
{
    double h, w, d;
    double a, b, c;
    double m;
    int shelves;

    printf("Wardrobe mass calculator\n");
    printf("Height h (180..220 cm): ");
    if (scanf("%lf", &h) != 1 || h < 180 || h > 220) {
        printf("Incorrect height.\n");
        return 1;
    }
    printf("Width w (80..120 cm): ");
    if (scanf("%lf", &w) != 1 || w < 80 || w > 120) {
        printf("Incorrect width.\n");
        return 1;
    }
    printf("Depth d (50..90 cm): ");
    if (scanf("%lf", &d) != 1 || d < 50 || d > 90) {
        printf("Incorrect depth.\n");
        return 1;
    }

    h /= 100.0;
    w /= 100.0;
    d /= 100.0;

    shelves = (int)(h / 0.40);

     a = 2 * h * d * 0.015
                + 2 * w * d * 0.015
                + shelves * (w - 2 * 0.015) * d * 0.015;

     b = h * w * 0.005;
     c = h * w * 0.01;

    m = a * A_DENSITY
         + b * B_DENSITY
         + c * C_DENSITY;

    printf("Internal shelves: %d\n", shelves);
    printf("Wardrobe mass: %.2f kg\n", m);
    return 0;
}
