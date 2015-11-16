#include"orange.h"
#include<stdio.h>
#include<stdlib.h>

#define ORANGE_MIN_SIZE 1

Orange orangeCreate(short size, Month expirationMonth, int maxNumberOfFoodCompanies, int sellingPrice) {
	if(	size < ORANGE_MAX_SIZE || size < ORANGE_MIN_SIZE
		|| expirationMonth < JAN || expirationMonth > DEC
		|| sellingPrice <= 0 || maxNumberOfFoodCompanies <= 0){
		return NULL;
	}

	Orange newOrange = (Orange)malloc(sizeof(struct orange_t));
	if(newOrange == NULL) {
		return NULL;
	}
	
	newOrange -> size = size;
	newOrange -> expirationMonth = expirationMonth;
	newOrange -> maxNumberOfFoodCompanies = maxNumberOfFoodCompanies;
	newOrange -> sellingPrice = sellingPrice;
	
	newOrange -> foodCompanies = malloc(sizeof(char *) * maxNumberOfFoodCompanies);

   	if(newOrange -> foodCompanies == NULL){
		free(newOrange);
		return NULL;
	}
	
	for(int i = 0 ; i < maxNumberOfFoodCompanies ; i++){
		newOrange -> foodCompanies[i] = NULL;
	}

	return newOrange;
}


