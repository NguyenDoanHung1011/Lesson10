#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct motorbike_st {
	char name[20], manufacturer[10], madein[12];
	long int price;
} Motorbike;

void showMenu();
void inputData();
void sortData();
void displayData();
void displayStatistic();
void findMotorbikeManufacturer();
void saveFile();

int main(int argc, char *argv[]) {
	int choose;
	Motorbike motorbikeList[3];
	
	while(choose != 5) {
		showMenu();
		scanf("%d", &choose);
		
		switch(choose) {
			case 1: {
				inputData(motorbikeList);
				break;
			}
			case 2: {
				sortData(motorbikeList);
				displayData(motorbikeList);
				displayStatistic(motorbikeList);
				break;
			}
			case 3: {
				findMotorbikeManufacturer(motorbikeList);
				break;
			}
			case 4: {
				saveFile(motorbikeList);
				break;
			}
			case 5: {
				printf("Thoat!!");
				break;
			}
			default: {
				printf("Nhap sai!!");
				break;
			}
		}
	}
	return 0;
}

void showMenu() {
	printf("\n==========");

	printf("\n1. Input data of motorbike");	
	printf("\n2. Sort, display details information and statistic of all motorbike");	
	printf("\n3. Find the motorbike of manufacturer");	
	printf("\n4. Save to text file motorbike.txt");	
	printf("\n5. Thoat");	

	printf("\nChon: ");	
}

void inputData(Motorbike *p) {
	int i;
	
	for(i = 0; i < 3; i++) {
		printf("\n==========");
	
		printf("\nEnter Data of motorbike %d: ", i+1);
		fflush(stdin);fflush(stdout);
		
		printf("\nName: ");
		fflush(stdin);fflush(stdout);
		gets(p[i].name);	
		
		printf("\nManufacturer: ");
		fflush(stdin);fflush(stdout);
		gets(p[i].manufacturer);	
		
		printf("\nMade in: ");
		fflush(stdin);fflush(stdout);
		gets(p[i].madein);	
		
		printf("\nPrice: ");
		fflush(stdin);fflush(stdout);
		scanf("%ld", &p[i].price);	
	}
}

void sortData(Motorbike *p) {
	int i, j;
	
	for(i = 0; i < 2; i++) {
		for(j = i + 1; j < 3; j++) {
			int cmp = strcmp(p[i].manufacturer, p[j].manufacturer);
			if(cmp < 0) {
				Motorbike tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}	
}

void displayData(Motorbike *p) {
	printf("\n==========");
	printf("\n%-3s||%-20s||%-12s||%-15s||%-12s", "No", "Name", "Manufacturer", "Made In", "Price");
	
	int i;
	for(i = 0; i < 3; i++) {
		printf("\n%03d||%-20s||%-12s||%-15s||%-12ld", i+1, p[i].name, p[i].manufacturer, p[i].madein, p[i].price);
	}
}
void displayStatistic(Motorbike *p) {
	printf("\n==========");
	
	int i, j;
	int countList[3];

	for(i = 0; i < 3; i++) {
		countList[i] = 1;		
	}
	
	for(i = 0; i < 2; i++) {
		if(countList[i] == 0) {
			continue;
		}
		for(j = i+1; j < 3; j++) {
			if(countList[j] == 0) {
				continue;
			}
			int cmp = strcmp(p[i].manufacturer, p[j].manufacturer);
			if(cmp == 0) {
				countList[i]++;
				countList[j]--;
			}
		}
	}
	
	for(i = 0; i < 3; i++) {
		if(countList[i] > 0) {
			printf("\n%s has %d motorbike", p[i].manufacturer, countList[i]);
		}
	}
}
void findMotorbikeManufacturer(Motorbike *p) {
	printf("\n==========");
	
	int i, count;
	char find[15];
	
	printf("\nEnter manufacturer for search: ");
	fflush(stdin);fflush(stdout);
	gets(find);
	
	for(i = 0; i < 3; i++) {
		int cmp = strcmp(find, p[i].manufacturer);
		if(cmp == 0) {
			count++;
		}
	}
	if(count != 0) {
		printf("\n%-3s||%-20s||%-12s||%-15s||%-12s", "No", "Name", "Manufacturer", "Made In", "Price");
	}
	
	count = 0;
	
	for(i = 0; i < 3; i++) {
		int cmp = strcmp(find, p[i].manufacturer);
		if(cmp == 0) {
			count++;
			printf("\n%03d||%-20s||%-12s||%-15s||%-12ld", i+1, p[i].name, p[i].manufacturer, p[i].madein, p[i].price);
		}
	}
	if(count == 0) {
		printf("\nThere are no motorbike of this manufacturer");
	}
	
	count = 0;
}
void saveFile(Motorbike *p) {
	printf("\n==========");
	
	FILE *fp;
	
	fp = fopen("motorbike.txt", "w");
	
	if(ferror(fp)) {
		printf("Open file error!!");
	} else {
		fprintf(fp, "\n%-3s||%-20s||%-12s||%-15s||%-12s", "No", "Name", "Manufacturer", "Made In", "Price");
		int i;
		for(i = 0; i < 3; i++) {
			fprintf(fp, "\n%03d||%-20s||%-12s||%-15s||%-12ld", i+1, p[i].name, p[i].manufacturer, p[i].madein, p[i].price);
		}
		printf("\nFile saved!!");
	}
	
	fclose(fp);
}
