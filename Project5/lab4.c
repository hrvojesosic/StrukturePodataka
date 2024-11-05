#define _CRT_SECURE_	
#include <stdio.h>
#define MAX_LINE 1024
#include <stdlib.h>

typedef struct _element* Position;
typedef struct _element{
	//data
	int exp;
	int coeff;
	//link
	Position next;
}element;
int InsertSorted(Position head, Position nE);
Position polinom_addition(Position head_one, Position head_two);
int main() {

	return 0;
}
int InsertSorted(Position head, Position nE) {
	Position temp = head;
	int numBytes = 0;
	FILE* fp=NULL;
	char buffer[1024] = { 0 };

	while (temp->next && temp->next->exp < nE->exp) {
		temp = temp->next;
	}

	if (temp->next == NULL || temp->next->exp != nE->exp) //prazna lista 
		InsertAfter(temp, nE);

	else {
		int resultCoefficient = nE->coeff + temp->next->coeff;
		if (resultCoefficient == 0) {
			DeleteAfter(temp);
			free(nE);
		}
		else {
			temp->next->coeff = resultCoefficient;
			free(nE);
		}
	}
fp = fopen("polinomi.txt", "r");
if (fp == NULL) {
	printf("Neuspjesno otvaranje datoteke.");
	return -1;
}

fgets(buffer, MAX_LINE, fp);
while (strlen(buffer)>0){
	int status = sscanf(buffer, "  %d %d %n", &temp->coeff, &temp->exp, &numBytes);

	buffer += numBytes;

}
}
Position polinom_addition(Position head_one, Position head_two) {
	Position new_head = NULL;
	Position i, j;
	i = head_one->next;
	j = head_two->next;


	return new_head;
}