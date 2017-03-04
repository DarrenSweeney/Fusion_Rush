// Copyright 2015 GameSparks Ltd 2015, Inc. All Rights Reserved.
#include <GameSparks/GSUtil.h>

#include <mbedtls/sha256.h>

using namespace GameSparks::Util;

static const gsstl::string base64_chars =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz"
			"0123456789+/";


static inline bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}

/*
For the following two methods:

Copyright (C) 2004-2008 Rene Nyffenegger

This source code is provided 'as-is', without any express or implied
warranty. In no event will the author be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this source code must not be misrepresented; you must not
claim that you wrote the original source code. If you use this source code
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original source code.

3. This notice may not be removed or altered from any source distribution.

Rene Nyffenegger rene.nyffenegger@adp-gmbh.ch

*/
gsstl::string GameSparks::Util::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
	gsstl::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (i = 0; (i < 4); i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for (j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while ((i++ < 3))
			ret += '=';

	}

	return ret;

}

gsstl::string GameSparks::Util::base64_decode(gsstl::string const& encoded_string) {
	gsstl::string::size_type in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	gsstl::string ret;

	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i == 4) {
			for (i = 0; i < 4; i++)
				char_array_4[i] = (unsigned char)base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j < 4; j++)
			char_array_4[j] = 0;

		for (j = 0; j < 4; j++)
			char_array_4[j] = (unsigned char)base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

static gsstl::string sha256(const gsstl::string& in)
{
	unsigned char output[32];
	mbedtls_sha256((const unsigned char*)&in[0], in.size(), output, 0);

	gsstl::string ret(32, 0x00);
	std::copy(output, output+32, ret.begin());
	return ret;
}

#include <cassert>

static gsstl::string str_xor(const gsstl::string& a, const gsstl::string& b)
{
	assert(a.size() == b.size());
	gsstl::string ret(a.size(), 0x00);

	for(size_t i=0; i!=a.size(); ++i)
	{
		ret[i] = a[i] ^ b[i];
	}
	return ret;
}


static gsstl::string hmac_sha256(gsstl::string key, const gsstl::string& message)
{
	// https://en.wikipedia.org/wiki/Hash-based_message_authentication_code

	static const int blocksize = 512 / 8;

	if(key.size() > blocksize)
	{
		key = sha256(key); // keys longer than blocksize are shortened
	}
	if(key.size() < blocksize)
	{
		// keys shorter than blocksize are zero-padded
		key = key + gsstl::string(blocksize - key.size(), 0x00);
	}

	gsstl::string o_key_pad(blocksize, 0x5c);
	o_key_pad = str_xor(o_key_pad, key);

	gsstl::string i_key_pad(blocksize, 0x36);
	i_key_pad = str_xor(i_key_pad, key);

	return sha256(o_key_pad + sha256(i_key_pad + message));
}

gsstl::string GameSparks::Util::getHMAC(gsstl::string nonce, gsstl::string appSecret)
{
	gsstl::string tmp = hmac_sha256(appSecret, nonce);
	gsstl::string str = base64_encode((const unsigned char*)tmp.data(), (unsigned int)tmp.size());
	return str;
}

bool GameSparks::Util::shouldConnect()
{
	return true;
}

