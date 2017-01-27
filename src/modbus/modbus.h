struct tcpframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
};

struct askreadregstruct {
	unsigned short firstreg;
	unsigned short regnumber;
};

struct writeregstruct {
	unsigned short regaddress;
	unsigned short regvalue;
};

struct reqreadstruct {
	unsigned char bytestofollow;
	unsigned char bytes[254];
};

struct writemulticoilstruct {
	unsigned short firstreg;
	unsigned short regnumber;
	unsigned char bytestofollow;
	unsigned char coils[256];
};

struct writemultiregstruct {
	unsigned short firstreg;
	unsigned short regnumber;
	unsigned char bytestofollow;
	unsigned short registers[127];
};

union pdudataunion {
	struct askreadregstruct askreadregs;
	struct reqreadstruct reqread;
	struct writeregstruct writereg;
	struct writemulticoilstruct writemulticoil;
	struct writemultiregstruct writemultireg;
	unsigned short words[127];
	unsigned char bytes[254];
};

struct pduframestruct {
	unsigned char unitid;
	unsigned char fncode;
	union pdudataunion data;
};

struct mbframestruct {
	unsigned short tsid;
	unsigned short protoid;
	unsigned short length;
	struct pduframestruct pdu;
};
