int main() {

    int a;
    int b;
    int c;
    int d;

    int e;
    int f;
    int g;
    int h;


    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);
    scanf("%d", &d);

    e = 5 * b;
    h = d * 7;

    if ( a > 30 ) {
        f = (5 * b) + c;

        printf("%d\n", a);
        printf("%d\n", b);
        printf("%d\n", c);
        printf("%d\n", d);
        printf("%d\n", e);
        printf("%d\n", f);
        printf("%d\n", h);
    } else {
        g = (5 * b) + d;
        b = d;
        g = (5 * b) + (d*7);

        printf("%d\n", a);
        printf("%d\n", b);
        printf("%d\n", c);
        printf("%d\n", d);
        printf("%d\n", e);
        printf("%d\n", g);
        printf("%d\n", h);
    }

    return 0;
}
