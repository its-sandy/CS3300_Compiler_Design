int main() {

	int a;
	int b;
	int c;
	int z;
	int d;
	int x;
	int y;
	int p;

	scanf("%d", &c);
	scanf("%d", &d);

	a = 1;
	b = 2;

	x = (a*b) + c;
	y = a + b;
	z = a - b;
	p = (a*b) + c;

	if(a + b < 0){
		printf("%d\n",z);
		scanf("%d",&a);
		z = z + ((a*b) + c);
		printf("%d\n",z);
	}
	else{
		printf("%d\n",p);
		p = p + ((a*b) + c);
		printf("%d\n",p);
		printf("%d\n",a);
	}

	return 0;
}
