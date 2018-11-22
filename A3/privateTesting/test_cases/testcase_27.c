int main() {
	int a; 
	int b;
	int c;
	b = 96;
	a = 65;
	c = a < b;
	printf("%d\n", c);
	c = b < a;
	printf("%d\n", c);
	b = a;
	c = b < a;
	printf("%d\n", c);
	return 0;
}
