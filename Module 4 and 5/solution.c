#include <stdio.h>
#include <stdlib.h>

long long int assign(int n, int** preference) {
    int mx = 1 << n;
    int i, j;
    int s;

    // Create and initialize dp array
    long long int* dp = (long long int*)malloc(mx * sizeof(long long int));
    for (int k = 0; k < mx; k++) {
        dp[k] = 0;
    }
    dp[mx - 1] = 1;

    // Proceed in bottom-up manner
    for (int mask = mx - 1; mask >= 0; mask--) {
        // Find the student
        j = mask;
        s = 0;

        // Count the number of set bits in mask
        while (j) {
            s += (j & 1);
            j /= 2;
        }

        // This is a state for student s
        for (i = 0; i < n; i++) {
            if (preference[s][i] && !(mask & (1 << i))) {
                dp[mask] += dp[mask | (1 << i)];
            }
        }
    }

    long long int result = dp[0];
    free(dp);
    return result;
}

int main() {
    int i, n, j;

    printf("How many students are there?\n");
    scanf("%d", &n);

    // Create and initialize preference matrix
    int** preference = (int*)malloc((n + 1) * sizeof(int));
    for (i = 0; i <= n; i++) {
        preference[i] = (int*)malloc(n * sizeof(int));
    }

    printf("\nEnter the preferences of each of %d students for %d subjects\n", n, n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &preference[i][j]);
        }
    }

    printf("\nTotal number of assignments that can be prepared are\n");
    printf("%lld\n", assign(n, preference));

    // Free allocated memory
    for (i = 0; i <= n; i++) {
        free(preference[i]);
    }
    free(preference);

    return 0;
}