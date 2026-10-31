#include <stdio.h>
#include <ctype.h>

int main(void)
{
    int ch;
    int words = 0, numbers = 0;
    int in_word = 0, in_number = 0;

    printf("Enter one line: ");

    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* A word is a sequence of English letters only. */
        if (isalpha((unsigned char)ch)) {
            if (!in_word) ++words;
            in_word = 1;
            in_number = 0;
        } else if (isdigit((unsigned char)ch)) {
            if (!in_number) ++numbers;
            in_number = 1;
            in_word = 0;
        } else {
            in_word = 0;
            in_number = 0;
        }
    }

    printf("Words: %d\nNumbers: %d\n", words, numbers);
    return 0;
}
