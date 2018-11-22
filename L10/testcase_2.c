int pow(int n, int i, int k)
{
	if(i > k) {
		return 1;
	}
	return n * (pow(n, i+1, k));
}

float pow(float n, int i, int k)
{
	if(i > k) {
		return 1.0;
	}
	return n * (pow(n, i+1, k));
}

int main()
{
	int a;
	float b;
	a = 2;
	a = pow(a, 1, 5);
	b = pow(3.2, 1, 5);
	printf("%f\n", b);
	printf("%d\n", a);
	return 0;
}
