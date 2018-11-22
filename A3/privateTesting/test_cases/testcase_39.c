int main() {
	int a;
	int b;
	int c;
	a = 1054;
	b = 1064;
	c = (a >= b);
	c = !(c);
	if (c) {
		int d;
		printf("%d\n", a);
		d = a;
		a = b;
		b = d;
	}

	while (a != b) {
		printf("%d\n", a);
		a = a - 1;
	}
	return 0;
}
