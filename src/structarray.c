#define PLISTMAX 4
#define PLINEMAX 100

struct priceline_s {
	int line;
	double price[PLISTMAX];
}

struct priceline_s priceline[PLINEMAX];

