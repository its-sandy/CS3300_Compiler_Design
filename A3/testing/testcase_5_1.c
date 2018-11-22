int main() {
	int a;
	int b;
	int c;
	a = 95;
	b = 51;
	c = -99;
	if (a <= b) {
		printf("%d\n", a);
		c = 1;
	}
	else if(a == b){
		printf("%d\n", b);
	}
	else
	{
		while((a+b)>140)
		{
			printf("%d\n", c);
			a = a-1;
		}
	}
	printf("%d\n", c);
	return 0;
}
