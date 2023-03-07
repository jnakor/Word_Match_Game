#include "MD_FIVE.h"
#include<iostream>


MD_FIVE::MD_FIVE()
{
	MD5Init(&md5);
}


MD_FIVE::~MD_FIVE()
{
}

std::string MD_FIVE::MD5_HASH(std::string encrypt) {
	MD5Update(&md5, (unsigned char*)encrypt.c_str(), strlen((char *)encrypt.c_str()));
	unsigned char decrypt[16];
	MD5Final(&md5, decrypt);
	char RESULT[33] = { 0 };//多一个，不然bug
	for (int i = 0; i < 16; i++)
	{
		sprintf(RESULT + 2 * i, "%02x", decrypt[i]);
	}
	std::string FINAL_RESULT = RESULT;
	return FINAL_RESULT;
}