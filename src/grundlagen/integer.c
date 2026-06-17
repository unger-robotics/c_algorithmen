#include <stdio.h>
#include <limits.h>

int main() {

   printf("number of bits in a byte %d\n", CHAR_BIT);
   printf("CHAR = %d\n", CHAR_MIN);
   printf("CHAR = %d\n", CHAR_MAX);
   printf("UNSIGNED CHAR = %d\n", UCHAR_MAX);


   printf("INT = %d\n", INT_MIN);
   printf("INT = %d\n", INT_MAX);
   printf("UINT = %u\n", UINT_MAX);

   printf("LONG = %ld\n", LONG_MIN);
   printf("LONG = %ld\n", LONG_MAX);
   printf("ULONG = %lu\n", ULONG_MAX);
/*
	 long long int x = 0;
   unsigned long long int y = 0;
   printf("%lld\n", x);
   printf("%llu\n", y);
*/
   return(0);
}