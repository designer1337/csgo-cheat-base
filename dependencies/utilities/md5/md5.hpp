#pragma once
#define md5_length 16

typedef struct
{
	unsigned int	buf[4];
	unsigned int	bits[2];
	unsigned char	in[64];
} md5_context;

namespace utilities::md5 {
	void init(md5_context* context);
	void update(md5_context* context, unsigned char const* buf, unsigned int len);
	void final(unsigned char digest[md5_length], md5_context* context);

	char* print(unsigned char* digest, int hashlen);

	unsigned int pseduo_random(unsigned int nSeed);
}