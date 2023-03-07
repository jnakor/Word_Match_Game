#pragma once
#include "md5.h"
#include<string>
class MD_FIVE
{
public:
	MD_FIVE();
	~MD_FIVE();
	std::string MD5_HASH(std::string encrypt);
private:
	MD5_CTX md5;
};

