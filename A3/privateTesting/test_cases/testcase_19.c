int main() {
	int fred;
	int barney;
	int pebbles;
	fred = 1023;
	barney = 21;
	pebbles = fred + barney;
	printf("%d\n", pebbles);
	pebbles = fred - barney;
	printf("%d\n", pebbles);
	pebbles = fred * barney;
	printf("%d\n", pebbles);
	pebbles = fred / barney;
	printf("%d\n", pebbles);
	pebbles = fred % barney;
	printf("%d\n", pebbles);
	barney = -barney;
	pebbles = fred + barney;
	printf("%d\n", pebbles);
	pebbles = fred - barney;
	printf("%d\n", pebbles);
	pebbles = fred * barney;
	printf("%d\n", pebbles);
	pebbles = fred / barney;
	printf("%d\n", pebbles);
	pebbles = fred % barney;
	printf("%d\n", pebbles);
	barney = -barney;
	fred = -fred;
	pebbles = fred + barney;
	printf("%d\n", pebbles);
	pebbles = fred - barney;
	printf("%d\n", pebbles);
	pebbles = fred * barney;
	printf("%d\n", pebbles);
	pebbles = fred / barney;
	printf("%d\n", pebbles);
	pebbles = fred % barney;
	printf("%d\n", pebbles);
	return 0;
}
