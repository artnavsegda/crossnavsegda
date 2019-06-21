#include <stdbool.h>

char keys[26][7] = {
	"aqwsz",
	"bvghn",
	"cxdfv",
	"dserfcx",
	"ewrsd",
	"fdrtgvc",
	"gftyhbv",
	"hgyujnb",
	"iuojk"
	"jhuikmn"
	"kjiolm",
	"lkop",
	"mnjk",
	"nbhjm",
	"oipkl",
	"pol",
	"qwa",
	"retdf",
	"sawedxz",
	"tryfg",
	"uyihj",
	"vcfgb",
	"wqeas",
	"xzsdc",
	"ytugh",
	"zasx",
};

bool nmatch(char key, char neigh)
{
	if (strchr(keys[key-97],neigh))
		return true;
	else
		return false;
}

int main()
{
	return 0;
}

