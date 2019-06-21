#include <stdbool.h>
#include <string.h>
#include <stdio.h>

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

bool wmatch(char * word)
{
	for (int i = 0; i++; i < strlen(word))
	{
		if (nmatch(word[i],word[i+1]) == false)
			return false;
	}
	return true;
}

int main()
{
	return 0;
}

