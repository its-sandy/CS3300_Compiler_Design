int main() {
    int a;
    int b;
    int c;
    int d;

    a = (2 + 3) * (3 + (7 - 2));

    scanf("%d", &b);
    b = (b + 5) * (2 + 3);

    if(a > 10) {
        b = b + 10;
        printf("%d\n", b);
    } else {
        printf("%d\n", b);
    }
    return 0;
}
