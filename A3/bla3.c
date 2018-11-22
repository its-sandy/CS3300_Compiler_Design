int main() {
	int a,b,c,d,e;
	a = 6;
	b = 2;

	c = a>b;
	
	while(c)
	{
		printf("%d\n",b);
		a = a--;
		c = a>b;
	}

	if(c)
		a=1;
	// else
	// 	a=2;
	return 0;
}