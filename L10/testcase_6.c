float fun(float a)
{
	float b;
	b = a*a;
	printf("%f\n",a);
	printf("%f\n",b);
	return b*a;
}

int main()
{
	float a;
	float b;
	float c;
	a = 2.1;
	b = 2.0;
	c = fun(a);
	printf("%f\n",c);
	return 0;
}