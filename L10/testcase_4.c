float func(int x, float y){
	if(x < 0){
		y = y * 0.5;
	}
	return y;
}

float func(float x, int y){
	if(y < 0){
		x = x * 2.0;
	}
	return x;
}

int main()
{
	float val1;
	float val2;
	val1 = func(2, 3.2);
	val2 = func(2.1, 3);
	printf("%f\n", val1);
	printf("%f\n", val2);
	return 0;
}