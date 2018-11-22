int main() {
    int x;
    int y;
    int z;

    scanf("%d", &x);

    y = 12;
    z = x + y;

    printf("%d\n", z);

    x = 32;
    z = (x + y) * (x - y);

    printf("%d\n", z);

    if (x < 15) {
        z = x - y;
        printf("%d\n", z);
    } else {
        z = x + y;
        printf("%d\n", z);
    }

    return 0;
}
