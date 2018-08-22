#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUF_SIZE 3

/* typedef */
typedef struct typeRetDivMod {
	int quotient;
	int remainder;
} RetDivMod;

typedef struct typeRetCalculateGray {
	int *bits;
	int *gray;
} RetCalculateGray;

/* prototypes */
int main(void);
RetCalculateGray calculate_gray(int number, int n);
int *calculate_binary(int *gray, int n);
RetDivMod divmod(int number, int divisor);
char *bitsToString(int *bits, int numBits);

/* functions */
int main() {
	char buf[BUF_SIZE];
	int n;
	int i;
	RetCalculateGray retValue;
	int *bitsFromGray;
	char *bits;
	char *bits2;
	char *gray;

	printf("Print a Gray table for n bits\n\n");
	printf("Number of bits? ");
	fgets(buf, BUF_SIZE, stdin);
	n = atoi(buf);
	printf("number of bits : %d\n", n);

	int range = pow(2, n);

	for (i = 0; i < range; i++) {
		retValue = calculate_gray(i, n);
		bitsFromGray = calculate_binary(retValue.gray, n);
		bits = bitsToString(retValue.bits, n);
		gray = bitsToString(retValue.gray, n);
		bits2 = bitsToString(bitsFromGray, n);
		printf("%5d --> %s --> %s --> %s\n", i, bits, gray, bits2);
		free(bits);
		free(gray);
		free(bits2);
		free(retValue.bits);
		free(retValue.gray);
		free(bitsFromGray);
	}

	printf("Done!\n");
	return 0;
}

RetCalculateGray calculate_gray(int number, int n) {
	int remainder;
	int nn;
	RetDivMod retDivMod;
	RetCalculateGray retValue;

	retValue.bits = (int *) malloc(n * sizeof(int));
	retValue.gray = (int *) malloc(n * sizeof(int));

	remainder = number;

	for (nn = 0; nn < n; nn++) {
		retDivMod = divmod(remainder, pow(2, n - 1 - nn));
		retValue.bits[nn] = retDivMod.quotient;
		remainder = retDivMod.remainder;
		if (nn == 0) {
			retValue.gray[nn] = retValue.bits[0];
		} else {
			retValue.gray[nn] = retValue.bits[nn - 1] ^ retValue.bits[nn];
		}
	}

	return (retValue);
}

int *calculate_binary(int *gray, int n) {
	int nn;
	int *bits;

	bits = (int *) malloc(n * sizeof(int));

	for (nn = 0; nn < n; nn++) {
		if (nn == 0) {
			bits[nn] = gray[0];
		} else {
			bits[nn] = bits[nn - 1] ^ gray[nn];
		}
	}

	return (bits);
}

RetDivMod divmod(int number, int divisor) {
	RetDivMod retDivMod;

	retDivMod.quotient = number / divisor;
	retDivMod.remainder = number % divisor;

	return retDivMod;
}

char *bitsToString(int *bits, int numBits) {
	int i;
	char *charBits;

	charBits = (char *) malloc(numBits * sizeof(char) + 1);
	for (i = 0; i < numBits; i++) {
		charBits[i] = '0' + bits[i];
	}
	charBits[numBits] = '\0';

	return charBits;
}
