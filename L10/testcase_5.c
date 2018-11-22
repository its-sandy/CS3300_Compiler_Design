float fun(float a, float b)
{
	return a*b;
}

int main()
{
	float a;
	float b;
	float c;
	a = 2.1;
	b = 2.0;
	c = fun(a,b);
	printf("%f\n",c);
	return 0;
}