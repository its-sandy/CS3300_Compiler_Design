int main() {

	int a;
	int b;
	int c;
	int z;

	scanf("%d", &a);
	scanf("%d", &b);
	c = (a + b) + ((a*b) * 128);
	z = (12 + (a*4));
	
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	printf("%d\n", z);

	return 0;
}
