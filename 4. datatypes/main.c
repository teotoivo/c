#include <stdio.h>
#include <stdbool.h>

int main() {
  
  char a = "c"; // %c
	char b[] = "aaaaaddd"; // %s

	float c = 0.123456; // 4 bytes %f
	double d = 0.123456789123456; // 8 bytes %lf

	bool e = true; // 1 byte %d

	short int h = 32767; // 2 bytes// 2 bytes (-32,768 to +32,767) %d
	unsigned short int i = 65535; // 2 bytes (0 to +65,535) %d
	short h = 32767; // 2 bytes// 2 bytes (-32,768 to +32,767) %d
	
	int j = 2147483637; // 4 bytes %d
	unsigned int k = 4294967295; // 4 bytes %u

	long long int l = 222; // 8 bytes %lld
	unsigned long long int m = 222U; // 8 bytes %llu add U to end to avoid warning

  return 0;
}