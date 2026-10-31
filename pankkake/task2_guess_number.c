#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    int mode;
    printf("Guess the number\n1 - you guess\n2 - computer guesses\nMode: ");
    if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Choose 1 or 2.\n");
        return 1;
    }

    if (mode == 1) {
        int secret, guess, attempts = 0;
        srand((unsigned)time(NULL));
        secret = rand() % 1000 + 1;
        do {
            printf("Your guess (1..1000): ");
            if (scanf("%d", &guess) != 1 || guess < 1 || guess > 1000) {
                printf("Enter a number from 1 to 1000.\n");
                return 1;
            }
            ++attempts;
            if (guess < secret) printf("Number is greater.\n");
            else if (guess > secret) printf("Number is less.\n");
        } while (guess != secret);
        printf("Correct Attempts: %d\n", attempts);
    } else {
        int left = 1, right = 1000, guess, attempts = 0;
        char answer;
        printf("Think of a number from 1 to 1000.\n");
        while (left <= right) {
            guess = (left + right) / 2;
            ++attempts;
            printf("My guess is %d. Enter >, <, or =: ", guess);
            if (scanf(" %c", &answer) != 1)
                return 1;
            if (answer == '=') {
                printf("Guessed Attempts: %d\n", attempts);
                return 0;
            }
            if (answer == '>') left = guess + 1;      /* secret is greater */
            else if (answer == '<') right = guess - 1; /* secret is less */
            else {
                printf("Use only >, <, or =.\n");
                --attempts;
            }
        }
        printf("The answers contradict each other.\n");
    }
    return 0;
}
