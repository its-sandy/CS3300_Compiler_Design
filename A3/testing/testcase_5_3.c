int main() {
	int a;
	int b;
	int c;
	a = 5;
	b = 3000;
	c = 4000;
	while((a>0) && ((5/a)>=0))
	{
		int y;
		y = (b/a)+(c/a);
		printf("%d\n", y);
		a = a-1;
	}
	return 0;
}