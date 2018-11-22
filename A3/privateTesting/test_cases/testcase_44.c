int kwame () {
	int earth;
	earth = 44;
	printf("%d\n", earth);
	return 0;
}

int wheeler () {
	int fire;
	int b;
	b = kwame();
	fire = 55;
	printf("%d\n", fire);
	return 0;
}

int linka () {
	int wind;
	int b;
	b = wheeler();
	wind = 66;
	printf("%d\n", wind);
	return 0;
}

int gi () {
	int water;
	int b;
	b = linka();
	water = 77;
	printf("%d\n", water);
	return 0;
}

int maTi () {
	int heart;
	int b;
	b = gi();
	heart = 33;
	printf("%d\n", heart);
	return 0;
}


int main() {
	int a;
	a = maTi();
	return 0;
}
