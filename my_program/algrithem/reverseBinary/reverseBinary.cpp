#include <stdio.h>
#include <stdlib.h>

using namespace std;

class reverter {
public:
	static unsigned int doRevert(unsigned int value);
};

static void printInBinary(unsigned int value) {
	unsigned int i;
	unsigned int length = sizeof(int)*8;
	unsigned int mask = 1 << (length - 1);
	unsigned int move = length - 1;
	
	for(i=0;i<length;i++) {
		printf("%d ", (value&mask)>>move);
		mask = mask >> 1;
		move --;
	}
}

unsigned int reverter::doRevert(unsigned int value) {
	printf("From: ");
	printInBinary(value);
	printf("\n");

  unsigned int toValue = 0;
	int i;
	int length = sizeof(int)*8;
	unsigned int mask = 1 << (length - 1);
	int move = length - 1;
	
	for(i=0;i<length;i++) {
		if(move >=0) {
		  toValue |= ((value&mask)>>move);
		} else {
		  toValue |= ((value&mask)<<(-move));
		}
		move -= 2;
		mask = mask >> 1;
	}
  
	printf("  To: ");
	printInBinary(toValue);
	printf("\n");
}

int main() {
  reverter::doRevert(12345);
}
