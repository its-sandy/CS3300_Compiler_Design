int add(int x, int y)
{
	return x+y;
}

int add(int x, int y, int z)
{
	int sum;
	sum = (x + y) + z;
	return sum;
}

int main()
{
	int sum1;
	int sum2;
	int a;
	int b;
	a = 2;
	b = 3;
	sum1 = add(a, b);
	sum2 = add(a, b, 4);
	printf("%d\n", sum1);
	printf("%d\n", sum2);
	return 0;
}