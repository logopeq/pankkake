#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char a, b, c, d;
    int figure, x, y, can = 0;

    printf("First square:");
    scanf(" %c%c", &a, &b);
    printf("Second square:");
    scanf(" %c%c", &c, &d);

    /* Difference between columns and rows. */
    x = abs(a - c);
    y = abs(b - d);

    printf("1 - king, 2 - queen, 3 - rook, 4 - bishop, 5 - knight: ");
    scanf("%d", &figure);

    if (figure == 1 && x <= 1 && y <= 1) can = 1;
    if (figure == 2 && (x == y || x == 0 || y == 0)) can = 1;
    if (figure == 3 && (x == 0 || y == 0)) can = 1;
    if (figure == 4 && x == y) can = 1;
    if (figure == 5 && ((x == 1 && y == 2) || (x == 2 && y == 1))) can = 1;

    if (can) {
        printf("Yes, the piece can move in one turn.\n");
    } else {
        printf("No. Other possible pieces: ");

        if (figure != 1 && x <= 1 && y <= 1) printf("king ");
        if (figure != 2 && (x == y || x == 0 || y == 0)) printf("queen ");
        if (figure != 3 && (x == 0 || y == 0)) printf("rook ");
        if (figure != 4 && x == y) printf("bishop ");
        if (figure != 5 && ((x == 1 && y == 2) || (x == 2 && y == 1))) printf("knight ");

        printf("\n");
    }
    return 0;
}
