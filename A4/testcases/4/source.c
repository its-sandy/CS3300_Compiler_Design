int main() {
    int x;
    int y;
    int z;
    int a;
    int b;
    int c;
    int d;

    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &z);

    a = 4 + (x + y);
    b = (x+y) * 3;
    c = 5 * (x+y);
    d = ((x+y) * 3) + 7;

    scanf("%d", &x);
    d = (x+y) + ((x+y) + 3);

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", d);

    return 0;
}
