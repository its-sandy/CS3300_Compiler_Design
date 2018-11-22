int main() {

    int a;
    int b;
    int e;
    int c;
    int d;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    a = b;
    b = c;
    c = a;
    b = a;
    b = c;
    c = b;
    a = b;

    printf("%d\n", a);
    printf("%d\n", b);
    printf("%d\n", c);

    return 0;
}
