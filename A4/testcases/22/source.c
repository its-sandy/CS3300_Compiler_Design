int main() {

	int a;
	int b;
	int c;
	int z;

	scanf("%d", &a);
	scanf("%d", &b);
	c = (a + b) + (128*(a*b));
	z = (12 + (4*a));
	
	printf("%d\n", a);
	printf("%d\n", b);
	printf("%d\n", c);
	printf("%d\n", z);

	if(a*256){
		z = 2;
	}

	return 0;
}
