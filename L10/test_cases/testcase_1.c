int ret(int n)
{
	return n;
}

float ret(float n)
{
	return n;
}

int main()
{
	int a;
	int i;
	float b;
	i = 5;
	a = ret(i);
	b = ret(6.5);
	printf("%d\n", a);
	printf("%f\n", b);
	return 0;
}
