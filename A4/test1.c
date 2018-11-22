
int main()
{
	int x;
	int y;
	int z;
	scanf("%d",&x);
	scanf("%d",&y);
	printf("%d\n",x);

	z = y*y;
	y = y*y;


	if(x>0)
	{
		x = y*y;
		// y = y*5;
	}
	else
	{
		// y = y*y;
		x = y*y;
	}
	z = y*y;
	return 0;
}
