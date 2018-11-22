int main() {

	int a;
	int b;
	int x;
	int y;
	int z;
	int p;

	scanf("%d", &x);
	scanf("%d", &b);
	a = b * (1+x);
	
	if(x-1){
		scanf("%d", &x);
		x = (x * x) + (a * a);
		y = (x * x) + (a * a);
		printf("%d\n", x);
		printf("%d\n", y);
		z = 1;
	}
	else{
		scanf("%d", &x);
		x = (x * x) + (a * a);
		scanf("%d", &a);
		y = (x * x) + (a * a); 
		printf("%d\n", x);
		printf("%d\n", y);
		p = 1;
	}

	return 0;
}
