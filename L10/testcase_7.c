int q;
float r;

int pow(int n, int i, int k)
{
	int z;
	if(i > k) {
		z =  1;
	}
	else
		z =  n * (pow(n, i+1, k));
	printf("%d\n",z);
	printf("%d\n",q);
	printf("%f\n",r);
	return z;
}

float pow(float n, int i, int k)
{
	float z;
	if(i > k) {
		z = 1.0;
	}
	else
		z = n * (pow(n, i+1, k));
	printf("%f\n",z);
	printf("%d\n",q);
	printf("%f\n",r);
	return z;
}

int main()
{
	int a;
	float b;
	a = 2;
	printf("%d\n",q);
	printf("%f\n",r);
	q = 1111;
	r = 1111.1111;
	printf("%d\n",q);
	printf("%f\n",r);
	a = pow(a, 1, 5);
	b = pow(3.2, 1, 5);
	printf("%f\n", b);
	printf("%d\n", a);
	return 0;
}
