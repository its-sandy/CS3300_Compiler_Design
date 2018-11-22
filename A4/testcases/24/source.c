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

    h = b*c;
    f = (a + (b*c)) - d;
    a = (a + (b*c)) - e;

    g = (a + (b*c)) - c;

    scanf("%d", &b);
    e = b*c;


    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);
    printf("%d\n", d);
    printf("%d\n", e);
    printf("%d\n", f);
    printf("%d\n", g);
    printf("%d\n", h);

    return 0;
}
