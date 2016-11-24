struct one {
	char a;
	char b;
};

struct two {
	struct one c;
	struct one d;
};

void firstfunction(void *source, void *dest, int size)
{
	//memcpy(dest,source,size)
}

void secondfunction(struct two *onedata)
{
	struct two twodata;
	firstfunction(&onedata->c,&twodata.c,2);
}

void main()
{
	struct two onedata;
	secondfunction(&onedata);
}

