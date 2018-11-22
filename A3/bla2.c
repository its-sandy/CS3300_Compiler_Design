int b;

int main() {
	int a;
	a = 6;
	a = a + a;
	b = 2;
	printf("%d\n", a);
	return 0;
}

int c;
int fun()
{
	int w,x,y,z,p;
	x = 6;
	x = x+x;
	x = -x;
	c = 4;
	printf("%d\n",x);

	if(x>c)
		return x;
	c = c+1;
	if(x>c)
		return x;
	c = c+1;
	return c;
}