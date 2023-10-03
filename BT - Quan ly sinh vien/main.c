#include <stdio.h>
#include <stdlib.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

typedef struct ST_Book {
	char ten[30], theloai[30];
	int giatien, namxuatban; 
} Book;

void showMenu();
void inputBook(Book *p);
void sortGerne(Book *p);
void sortPublishYear(Book *p);
void displayBook(Book *p);
void findBookbyGerne(Book *p);
void saveFile(Book *p);

int main(int argc, char *argv[]) {
	int choose;
	Book bookList[3];
	
	do {
		showMenu();
		scanf("%d", &choose);
		
		switch(choose) {
			case 1: {
				inputBook(bookList);
				break;
			}
			case 2: {
				sortGerne(bookList);
				displayBook(bookList);
				sortPublishYear(bookList);
				break;
			}
			case 3: {
				findBookbyGerne(bookList);
				break;
			}
			case 4: {
				saveFile(bookList);
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
	} while(choose != 5);
	return 0;
}

void showMenu() {
	printf("\n==========");
	printf("\n1. Nhap du lieu cua tung quyen sach");
	printf("\n2. Sap xep, hien thi thong tin chi tiet cung tung quyen sach theo the loai (Z->A). Thong ke sach theo nam xuat ban.");
	printf("\n3. Tim quyen sach theo the loai");
	printf("\n4. Ghi vao tap tin nhi phan book.dat");
	printf("\n5. Thoat");
	printf("\nChon: ");
}

void inputBook(Book *p) {
	int i;
	for(i = 0; i < 3; i++) {
		printf("\n==========");
		printf("\nNhap quyen sach %d:", i+1);
	
		printf("\nTen: ");
		fflush(stdin);fflush(stdout);
		gets(p[i].ten);
		
		printf("\nThe loai: ");
		fflush(stdin);fflush(stdout);
		gets(p[i].theloai);
		
		printf("\nGia tien: ");
		fflush(stdin);fflush(stdout);
		scanf("%d", &p[i].giatien);
		
		printf("\nNam xuat ban: ");
		fflush(stdin);fflush(stdout);
		scanf("%d", &p[i].namxuatban);
	}
}

void sortGerne(Book *p) {
	int i, j;
	char tmp[10];
	for(i = 0; i < 2; i++) {
		for(j = i+1; j < 3; j++) {
			int cmp = strcmp(p[i].theloai, p[j].theloai); 
				if(cmp < 0) {
					Book tmp = p[i];
					p[i] = p[j];
					p[j] = tmp;
				}
		}
	}
}

void sortPublishYear(Book *p) {
	int i, j;
	int countList[3];
	for(i=0;i<3;i++) {
		countList[i] = 1;
	}
	for(i=0;i<2;i++) {
		if(countList[i] == 0) {
			continue;
		}
		for(j=i+1;j<3;j++) {
			if(countList[j] == 0) {
				continue;
			}
			if(p[i].namxuatban == p[j].namxuatban) {
				countList[i]++;
				countList[j]--;
			}
		}
	}
	for(i=0;i<3;i++) {
		if(countList[i] > 0) {
			printf("\nNam %d co %d quyen sach", p[i].namxuatban, countList[i]);
		}
	}	
}

void displayBook(Book *p) {
	int i;
	
	printf("\n%-3s||%-30s||%-30s||%-10s||%-15s", "STT", "Ten", "The loai", "Gia tien", "Nam xuat ban");
	for(i = 0; i < 3; i++) {
		printf("\n%03d||%-30s||%-30s||%-10d||%-15d", i+1, p[i].ten, p[i].theloai, p[i].giatien, p[i].namxuatban);
	}
	
	printf("\n==========");
}

void findBookbyGerne(Book *p) {
	printf("\n==========");
	char theloai[50];
	
	printf("\nNhap the loai sach ban muon tim: ");
	fflush(stdin);fflush(stdout);
	gets(theloai);
	fflush(stdin);fflush(stdout);
	
	int i;
	int count=0;
	
	for(i=0;i<3;i++){
		int cmp=strcmp(theloai,p[i].theloai);
		if(cmp==0){
			count++;
	    }
	}
	if(count!=0){
		printf("\n%-3s||%-30s||%-30s||%-10s||%-15s","STT","Ten","The loai","Gia tien","Nam san xuat");
	}
	
	count = 0;
	
	for(i=0;i<3;i++){
		int cmp=strcmp(theloai,p[i].theloai);
		if(cmp==0){
			count++;
			printf("\n%03d||%-30s||%-30s||%-10d||%-15d", i+1, p[i].ten, p[i].theloai, p[i].giatien, p[i].namxuatban);
		}
	}
	if(count==0){
		printf("\nKhong co quyen sach thuoc the loai nay");
	}
}

void saveFile(Book *p){
	FILE *fp;
	fp = fopen("book.dat","wb");
	if(ferror(fp)) {
		printf("\nMo file bi loi");
	} else {
		fwrite(p, sizeof(Book), 3, fp);	
		printf("\nLuu file thanh cong");
	}
	fclose(fp);
}
