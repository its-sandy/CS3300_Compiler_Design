int main() {
    int u;
    int x;
    int y;
    int z;

    y = 10;
    scanf("%d", &x);

    if (y > 20) {
        u = 3;
        z = x + y;
    } else {
        u = 4;
        z = x - y;
    }

    u = (x - y) * u;

    printf("%d\n", z);
    printf("%d\n", u);
    return 0;
}
