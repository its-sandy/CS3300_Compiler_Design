#include <stdio.h>

/* if simplification
 *  - only if statement - which gets removed
 */

int main() {

    int b;

    scanf("%d", &b);

    if (0)
        printf("%d\n", b);

    return 0;
}
