#include <stdio.h>
#include <stdlib.h>

/* This code distributes candy to children, 
based on their score, following this logic: each child gets at least 1 candy, 
if a child has a higher score than his immediate neighbor on the list, he gets more candy than his neighbor. 
The goal is to distribute the minimal amount of candy.
The output should be the minimal amount of candy (2).
*/
int candy(int *ratings, int n) {
    int *candies = malloc(sizeof(int) * n);

    // initialize the candies
    for (int i = 0; i < n; i++) {
        candies[i] = 0;
    }

    // iterate through the ratings
    for (int i = 1; i < n; i++) { /* bug 1: <= causes out of bounds */
        if (ratings[i] > ratings[i - 1]) {  /* bug 2: >= breaks strict condition */
            candies[i] = candies[i - 1] + 1;
        }
    }

    // backward pass to enforce the rule
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = candies[i + 1] + 1;   /* bug 3: missing max() so overwrites too much */
        }
    }

    // add the total
    int total = 0;
    for (int i = 0; i <= n; i++) {     /* bug 4: <= reads past end (out of bounds)*/
        total += candies[i];
    }

    free(candies); /* bug 5: missing free(candies) */
    return total;
}

int main(void) {
    int r[] = {1, 0, 2};
    int n = sizeof(r) / sizeof(r[0]);

    printf("Min candies = %d\n", candy(r, n));
    return 0;
}
