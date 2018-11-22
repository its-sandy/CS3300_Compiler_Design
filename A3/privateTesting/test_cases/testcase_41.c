int main() {
	int a;
	int b;
	int c;
	int g;
	int e;
	int f;
	int d1;
	a = 1054 + 20;
	b = 1064 + 10;
	c = (a >= b);
	c = !(c);
	if (!c) {
		int d;
		printf("%d\n", a);
		d = a;
		a = b;
		b = d;
	}

	d1 = !c;
	e = c || d1;
	f = a % 6;
	f = f % 2;
	f = f + 1;
	e = e % f;
	
	if (e && 1) {
		int a1;
		a1 = a;
		printf("%d\n", a1);
		a1 = a1 - 109;
		printf("%d\n", a1);
	}
	else {
		int b1;
		b1 = b;
		printf("%d\n", b1);
		b1 = b1 - 109;
		printf("%d\n", b1);
	}
	a = a * 2;
	while (a != b) {
		printf("%d\n", a);
		a = a - 1;
	}
	return 0;
}
