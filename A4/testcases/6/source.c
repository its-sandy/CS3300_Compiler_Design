int main() {

	int a;
	int b;
	int c;
	int d;
	int x;
	int y;
	int z;

	x = 3;
	scanf("%d", &y);
	a = 1;
	c = (a - (a * 3)) + x;
	d = c * (y + ((5*4)*a));
	b = a + x;
	if(d){
		b = 5;
		b = b + d;
		printf("%d\n", b);
		printf("%d\n", d);
	}
	else{
		x = (c*d) + (c + (d * b));
		y = (c + (d * b)) - (b*c);

		printf("%d\n", x);
		printf("%d\n", y);
	}

	return 0;
}
