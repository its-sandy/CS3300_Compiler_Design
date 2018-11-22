int main() {
	int a1;
	int b1;
	int c1;
	int d1;
	a1 = 96;
	b1 = 71;
	c1 = a1 > b1;
	c1 = !c1;
	c1 = c1 && c1;
	printf("%d\n", c1);
	return 0;
}
