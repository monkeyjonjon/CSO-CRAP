#include <stdio.h>
#include <stdlib.h>

int candy(int *ratings, int n) {
    int *candies = malloc(sizeof(int) * n);

    /* bug 1: does not initialize candies[i] = 1 */
    for (int i = 0; i < n; i++) {
        candies[i] = 0;
    }

    /* left-to-right pass */
    for (int i = 1; i <= n; i++) {     /* bug 2: i <= n causes out-of-bounds */
        if (ratings[i] >= ratings[i - 1]) {   /* bug 3: >= breaks strict condition */
            candies[i] = candies[i - 1] + 1;
        }
    }

    /* right-to-left pass */
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = candies[i + 1] + 1;   /* bug 4: missing max() so overwrites too much */
        }
    }

    int total = 0;
    for (int i = 0; i <= n; i++) {     /* bug 5: <= again reads past end */
        total += candies[i];
    }

    return total;   /* also missing free(candies) but that’s minor */
}

int main(void) {
    int r[] = {1, 0, 2};
    int n = sizeof(r) / sizeof(r[0]);

    printf("Min candies = %d\n", candy(r, n));
    return 0;
}
