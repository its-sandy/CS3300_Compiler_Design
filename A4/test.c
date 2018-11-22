int main()
{
	int a = 0;
	int b = 4;
	int c;

	c = a&&b;
	printf("%d\n", c);
	c = a||b;
	printf("%d\n", c);
	c = a>b;
	printf("%d\n", c);
	c = a<b;
	printf("%d\n", c);
	c = a>=b;
	printf("%d\n", c);
	c = a<=b;
	printf("%d\n", c);
	c = a==b;
	printf("%d\n", c);
	c = a!=b;
	printf("%d\n", c);
	c = !a;
	printf("%d\n", c);
}