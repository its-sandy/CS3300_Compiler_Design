int main() {
	int a;
	int b;
	int c;
	int e;
	a = 54;
	b = 64;
	c = (a <= b);
	c = !(c);
	e = !c;
	if (c) {
		int d;
		d = a * 3;
		printf("%d\n", d);
	}
	else {
		int f;
		f = b / 3;
		printf("%d\n", f);	
	}
	return 0;
}
