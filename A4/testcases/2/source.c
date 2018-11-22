int main() {
    int x;
    int y;
    int z;

    scanf("%d", &x);
    scanf("%d", &y);

    z = ((x * 2) + (y * 4)) * 8;

    printf("%d\n", z);

    if ((x * 16) > 200) {
        printf("%d\n", y);
    }
}
