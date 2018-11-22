int main() {
	int a;
	int b;
	int c;
	a = 995;
	b = 1064;
	c = a == b;
	if (c) {
		printf("%d\n", a);
	}
	else {
		c = 1;
		printf("%d\n", b);
	}
	if (c) 
		printf("%d\n", a);
	return 0;
}
