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
void fun()
{
	int w,x,y,z,p;
	x = 6;
	x = x+x;
	x = -x;
	c = 4;
	printf("%d\n",x);
}

void fun1()
{
	int w,x,y;
	x = 4;
	y = 3;
	w = -x;

	if(x>y)
	{
		x = x+1;
		return;
	}
	else if (x>2)
	{
		x = x+2;
		return;
	}
	else
	{
		x = x+3;
		return;
	}
	// w = x - y;
	// w = x * y;
	// w = x / y;
}