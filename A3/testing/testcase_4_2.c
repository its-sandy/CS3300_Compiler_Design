int x1;
int y1;
int M1;

int wrapper()
{
	return powmod(x1, y1, M1);
}

int powmod(int x, int y, int M)
{
	int ret;
	if(y==0) return 1;
	ret = powmod(x, y/2, M);
	ret = (ret*ret)%M;
	if(y%2)
	{
		ret = (ret*x)%M;
	}
	return ret;
}

int main() {
	int ret1;
	x1 = 2;
	y1 = 12;
	M1 = 1000;
	ret1 = wrapper();
	printf("%d\n", ret1);
	return 0;
}