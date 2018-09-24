#include "cast128.h"
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <ctime>
typedef unsigned long long quint64;
typedef unsigned char quint8;
typedef unsigned int quint32;

void showComponent(quint32 x) {
	std::cout << std::hex << std::setw(8) << std::setfill('0') << std::uppercase << x << " ";
}

void showMessage(const CAST128::Message msg) {
	for (int i = 0; i < CAST128::MSG_LEN; ++i) {
		showComponent(msg[i]); std::cout << " ";
	}

	std::cout << std::endl;
}

void showKey(const CAST128::Key key) {
	for (int i = 0; i < CAST128::KEY_LEN; ++i) {
		showComponent(key[i]); std::cout << " ";
	}

	std::cout << std::endl;
}

int main() {
	CAST128 cast128;
	srand(time(NULL));
	std::cout << "================ Test 1 ================" << std::endl;
	static const CAST128::Key KEY = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
	//int messag[8];
	//int messagtoshifr[8];
	//int shifrmessag[8];
	//int resultoutmes[8];
	CAST128::Message messag[8];
	CAST128::Message resultoutmes[8];
	CAST128::Message shifrmessag[8];
	CAST128::Message msg = { 0x01555567, 0x89ABCDEF };
	for (int i = 0;i < 8;i++)
	{
		messag[i][0] = rand();
		messag[i][1] = rand();
	}
	std::cout << "(ECB) encryption" << std::endl;
	for (int i = 0;i < 8;i++)
	{
		CAST128::Message msg;
		msg[0]=messag[i][0]; msg[1] = messag[i][1];
		showMessage(msg);
		std::cout << "+++++++++++" << std::endl;
		cast128.encrypt(KEY, msg);
		shifrmessag[i][0] = msg[0]; shifrmessag[i][1] = msg[1];
		showMessage(shifrmessag[i]);
		std::cout << "-----------" << std::endl;
	}
	std::cout << std::endl << "(ECB) decryption" << std::endl;
	//long long initvec = ((long long)rand() << 32) | rand();
	//int initvector[2];
	for (int i = 0;i < 8;i++)
	{
		showMessage(shifrmessag[i]);
		std::cout << "+++++++++++" << std::endl;
		cast128.decrypt(KEY, shifrmessag[i]);
		resultoutmes[i][0] = shifrmessag[i][0];	resultoutmes[i][1] = shifrmessag[i][1];
		showMessage(resultoutmes[i]);
		std::cout << "-----------" << std::endl;
	}
	CAST128::Message initvector;
	initvector[0] = rand();
	initvector[1] = rand();
	CAST128::Message pereminitvector = {initvector[0],initvector[1]};
	for (int i = 0;i < 8;i++)
	{
		messag[i][0] = rand();
		messag[i][1] = rand();
	}
	std::cout << "Cipher block chaining (CBC) encryption" << std::endl;
	for (int i = 0;i < 8;i++)
	{
		//messagtoshifr[i] = messag[i] ^ pereminitvector[0];
		//messagtoshifr[i + 1] = messag[i + 1] ^ pereminitvector[1];
		showMessage(messag[i]);
		std::cout << "+++++++++++";
		msg[0] = messag[i][0] ^ pereminitvector[0]; msg[1] = messag[i][1] ^ pereminitvector[1];
		cast128.encrypt(KEY, msg);
		shifrmessag[i][0] = msg[0]; shifrmessag[i][1] = msg[1];
		pereminitvector[0] = shifrmessag[i][0]; pereminitvector[1] = shifrmessag[i + 1][1];
		showMessage(shifrmessag[i]);
		std::cout << "-----------" << std::endl;
	}
	std::cout << "Cipher block chaining (CBC) decryption" << std::endl;
	for (int i = 7;i > 0;i --)
	{
		showMessage(shifrmessag[i]);
		std::cout << "++++++++++++";

		/*messagtoshifr[i] = messag[i] ^ pereminitvector[1];
		messagtoshifr[i - 1] = messag[i - 1] ^ pereminitvector[0];*/
		//messagtoshifr[i] = shifrmessag[i];
		//messagtoshifr[i - 1] = shifrmessag[i - 1];
		msg[0] = shifrmessag[i][0];msg[1] = shifrmessag[i][1];
		cast128.decrypt(KEY, msg);
		resultoutmes[i][0] = msg[0]^shifrmessag[i-1][0]; resultoutmes[i][1] = msg[1]^ shifrmessag[i - 1][1];
		showMessage(resultoutmes[i]);
		std::cout << "------------" << std::endl;
	}
	showMessage(shifrmessag[0]);
	std::cout << "++++++++++++";
	msg[0] = shifrmessag[0][0];msg[1] = shifrmessag[0][1];
	cast128.decrypt(KEY, msg);
	resultoutmes[0][0] = msg[0] ^ initvector[0]; resultoutmes[0][1] = msg[1] ^ initvector[1];
	showMessage(resultoutmes[0]);
	std::cout << "------------" << std::endl;
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	std::cout << "Cipher feed back (CFB) encryption" << std::endl;
	for (int i = 0;i < 8;i++)
	{
		showMessage(messag[i]);
		std::cout << "+++++++++++" << std::endl;
		msg[0] = pereminitvector[0]; msg[1] = pereminitvector[1];
		cast128.encrypt(KEY, msg);
		shifrmessag[i][0] = msg[0]^messag[i][0]; shifrmessag[i][1] = msg[1]^messag[i][1];
		pereminitvector[0] = shifrmessag[i][0]; pereminitvector[1] = shifrmessag[i][1];
		showMessage(shifrmessag[i]);
		std::cout << "-----------" << std::endl;
	}
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	std::cout << "Cipher feed back (CFB) decryption" << std::endl;
	for (int i = 0;i < 8;i++)
	{
		showMessage(shifrmessag[i]);
		std::cout << "++++++++++++" << std::endl;
		msg[0] = pereminitvector[0]; msg[1] = pereminitvector[1];
		cast128.encrypt(KEY, msg);
		resultoutmes[i][0] = msg[0] ^ shifrmessag[i][0]; resultoutmes[i][1] = msg[1] ^ shifrmessag[i][1];
		pereminitvector[0] = shifrmessag[i][0]; pereminitvector[1] = shifrmessag[i][1];
		showMessage(resultoutmes[i]);
		std::cout << "------------" << std::endl;
	}
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	std::cout << "Output feed back (OFB) encryption" << std::endl;
	for (int i = 0;i < 8;i++)
	{
		showMessage(messag[i]);
		std::cout << "+++++++++++" << std::endl;
		msg[0] = pereminitvector[0]; msg[1] = pereminitvector[1];
		cast128.encrypt(KEY, msg);
		shifrmessag[i][0] = msg[0] ^ messag[i][0]; shifrmessag[i][1] = msg[1] ^ messag[i][1];
		pereminitvector[0] = msg[0]; pereminitvector[1] = msg[1];
		showMessage(shifrmessag[i]);
		std::cout << "-----------" << std::endl;
	}
	std::cout << "Output feed back (OFB) decryption" << std::endl;
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	for (int i = 0;i < 8;i++)
	{
		showMessage(shifrmessag[i]);
		std::cout << "++++++++++++" << std::endl;
		msg[0] = pereminitvector[0]; msg[1] = pereminitvector[1];
		cast128.encrypt(KEY, msg);
		resultoutmes[i][0] = msg[0] ^ shifrmessag[i][0]; resultoutmes[i][1] = msg[1] ^ shifrmessag[i][1];
		pereminitvector[0] = msg[0]; pereminitvector[1] = msg[1];
		showMessage(resultoutmes[i]);
		std::cout << "-----------" << std::endl;
	}
	std::cout << "Counter mode (CTR) encryption" << std::endl;
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	for (int i = 0;i < 8;i++)
	{
		msg[0]= pereminitvector[0]; msg[1] = pereminitvector[1];
		showMessage(messag[i]);
		std::cout << "+++++++++++" << std::endl;
		cast128.encrypt(KEY, msg);
		shifrmessag[i][0] = msg[0] ^ messag[i][0]; shifrmessag[i][1] = msg[1] ^ messag[i][1];
		pereminitvector[0] = pereminitvector[0] + 1; pereminitvector[1] = pereminitvector[1] + 1;
		showMessage(shifrmessag[i]);
		std::cout << "-----------" << std::endl;
	}
	pereminitvector[0] = initvector[0];pereminitvector[1] = initvector[1];
	std::cout << "Counter mode (CTR) decription" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		msg[0] = pereminitvector[0]; msg[1] = pereminitvector[1];
		showMessage(shifrmessag[i]);
		std::cout << "+++++++++++" << std::endl;
		cast128.encrypt(KEY, shifrmessag[i]);
		resultoutmes[i][0] = msg[0] ^ shifrmessag[i][0];	resultoutmes[i][1] = msg[1] ^ shifrmessag[i][1];
		pereminitvector[0] = pereminitvector[0] + 1; pereminitvector[1] = pereminitvector[1] + 1;
		showMessage(resultoutmes[i]);
		std::cout << "-----------" << std::endl;
	}
	CAST128::Message hash[2];
	hash[0][0] = KEY[0]; hash[0][1] = KEY[1];
	hash[1][0] = KEY[0]; hash[1][1] = KEY[1];
	CAST128::Key keyhash;
	CAST128::Message inithaser[2];
	std::cout << "Hash nachaljniy" << std::endl;
	showMessage(hash[0]);
	for (int i = 0; i < 8; i+=2)
	{
		keyhash[0] = messag[i][0];
		keyhash[1] = messag[i][1];
		keyhash[2] = messag[i+1][0];
		keyhash[3] = messag[i+1][1];
		hash[1][0] = hash[0][0];
		hash[1][1] = hash[0][1];
		cast128.encrypt(keyhash, hash[0]);
		hash[0][0] = hash[0][0]^hash[1][0]; hash[0][1] = hash[0][1] ^ hash[1][1];
	}
	std::cout << "Hash konechniy" << std::endl;
	showMessage(hash[0]);
	///*std::cout << "          Msg before: "; showMessage(msg);
	//cast128.encrypt(KEY, msg);
	//std::cout << "Msg after encryption: "; showMessage(msg);
	//cast128.decrypt(KEY, msg);
	//std::cout << "Msg after decryption: "; showMessage(msg);
	//std::cout << std::endl;*/

	////std::cout << "================ Test 2 ================" << std::endl;
	////CAST128::Key a = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
	////CAST128::Key b = { 0x01234567, 0x12345678, 0x23456789, 0x3456789A };
	////for (int i = 0; i < 1000000; ++i) {
	////	cast128.encrypt(b, a);
	////	cast128.encrypt(b, a + 2);
	////	cast128.encrypt(a, b);
	////	cast128.encrypt(a, b + 2);
	////}

	////def encryptBits(self, unic, mode, initvec) :
	////	res = 0
	////	blocks = []
	////	while unic != 0 :
	////		blocks.append(unic & self.MASK)
	////		unic >>= 64
	////		for i in range(len(blocks) - 1, -1, -1) :
	////			block = blocks[i]
	////			if mode == TripleDESEncrypter.ECB :
	////				block = self.encryptBlock(block)
	////				elif mode == TripleDESEncrypter.CBC :
	////				block = self.encryptBlock(block ^ initvec)
	////				initvec = block
	////				elif mode == TripleDESEncrypter.CFB :
	////				block = block ^ self.encryptBlock(initvec)
	////				initvec = block
	////				elif mode == TripleDESEncrypter.OFB :
	////				initvec = self.encryptBlock(initvec)
	////				block ^= initvec
	////				elif mode == TripleDESEncrypter.CTR :
	////				initvec %= self.MASK
	////				block ^= self.encryptBlock(initvec)
	////				initvec += (len(blocks) - i - 1)
	////			else:
	////return 0
	////	res |= block << (64 * i)
	////	return res

	////	def encryptString(self, msg, mode, initvec) :
	////	unic = TripleDESEncrypter.stringToUnicode(msg, 64)
	////	return self.encryptBits(unic, mode, initvec)

	////	def decrypt(self, msg, mode, initvec) :
	////	res = 0
	////	blocks = []
	////	while msg != 0 :
	////		blocks.append(msg & self.MASK)
	////		msg >>= 64
	////		for i in range(len(blocks) - 1, -1, -1) :
	////			block = blocks[i]
	////			if mode == TripleDESEncrypter.ECB :
	////				block = self.decryptBlock(block)
	////				elif mode == TripleDESEncrypter.CBC :
	////				old = initvec
	////				initvec = block
	////				block = old ^ self.decryptBlock(block)
	////				elif mode == TripleDESEncrypter.CFB :
	////				old = initvec
	////				initvec = block
	////				block = block ^ self.encryptBlock(old)
	////				elif mode == TripleDESEncrypter.OFB :
	////				initvec = self.encryptBlock(initvec)
	////				block ^= initvec
	////				elif mode == TripleDESEncrypter.CTR :
	////				initvec &= self.MASK
	////				block ^= self.encryptBlock(initvec)
	////				initvec += (len(blocks) - i - 1)
	////			else:
	////return 0
	////	res |= block << (64 * i)
	////	return TripleDESEncrypter.unicodeToString(res)

	//showKey(a);
	//showKey(b);
	system("pause");
	return 0;
}
