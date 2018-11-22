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
    scanf("%d", &e);

    h = a + b;
    f = ((a + b) + (a + b)) + ((a+b) + (a + b));
    g = ((a + b) + (a + b)) * ((a+b) + (a + b));
    h = ((((a + b) + (a + b)) * ((a+b) + (a + b))) + c) * d;

    if ( ((a + b) * c) >= ((a + b) * d) ) {
        printf("%d\n", a);
        printf("%d\n", b);
        printf("%d\n", c);
        printf("%d\n", d);
        printf("%d\n", e);
        printf("%d\n", f);
        printf("%d\n", g);
        printf("%d\n", h);
    } else {
        printf("%d\n", d);
        printf("%d\n", e);
        printf("%d\n", f);
        printf("%d\n", g);
        printf("%d\n", h);
        printf("%d\n", a);
        printf("%d\n", b);
        printf("%d\n", c);
    }

    return 0;
}
