int main() {
	int a; 
	int b;
	int c;
	b = 1;
	a = 0;
	c = a && b;
	printf("%d\n", c);
	a = 1;
	c = b && a;
	printf("%d\n", c);
	return 0;
}
