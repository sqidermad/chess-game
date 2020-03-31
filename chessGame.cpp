#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<ctype.h>
#include<conio.h>
#include<time.h>
#define UP		0x48
#define DOWN	0x50
#define LEFT	0x4B
#define RIGHT	0x4D
#define ENTER	0xD

//1=ada isi hitam, 2=ada isi putih, 0=kosong, 240=putih, 15=hitam, 224=kuning bg, 78=tulisan

struct tile{
	int isi; //ini buat ngeeliat di tile yang kita pilih itu ada isinya ato kgk kalo 1 berarti ada isi piece hitam kalo 2 ada isi piece putih kalo 0 berarti gk ada isi
	int warna; //ini buat ngasih warna ke tile nya, dimana tilenya itu dibikin pake link list jadi warna link list yang selanjutnya itu pasti beda dan balik lg warnanya kalo udh ke selanjutnya lg
	char gbr[2]; //ini buat kasih gambar di tile nya
	char code[3]; //ini buat kasih nama code di tilenya kgk di tampilih ini itu (misalnya H3 berarti ada di barisan H dan kolom nomor 3)
	char mark[10]; //mark ini itu buat ngasih tau di tile itu tuh yang lg ngisi siapa, ratu kah raja kahh benteng kahh atau apa
	tile *next, *prev;
}*head, *tail, *temp, *curr, *temp2, *temp3, *curr1, *temp4, *temp5;

int total = 0, moveR1=0, moveR2=0, moveR3=0, moveR4=0, moveK1=0, moveK2=0;
int flag=0;//buat di menu awal

void gotoxy(int x, int y){  
    COORD coord; 
    coord.X = x;  
    coord.Y = y; 
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}//fungsi gotoxy ini diambil dari link https://puncakdunia.wordpress.com/2012/06/04/contoh-penggunaan-gotoxy-pada-c/

void warna(int color){ //fungsi buat bikin warna
HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hCon,color);
}//fungsi warna ini diambil dari link http://wenda.komputer.pcr.ac.id/2014/03/06/merubah-warna-text-dan-background-pada-c/

void tulisan(){

	printf("                          %c%c%c%c%c%c%c    %c%c    %c%c      %c%c%c%c%c%c%c      %c%c%c%c%c%c%c       %c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                        %c%c           %c%c    %c%c    %c%c           %c%c            %c%c        \n",219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                        %c%c           %c%c%c%c%c%c%c%c    %c%c           %c%c            %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                        %c%c           %c%c    %c%c    %c%c%c%c%c%c         %c%c%c%c%c         %c%c%c%c%c\n" ,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                        %c%c           %c%c    %c%c    %c%c                  %c%c            %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                        %c%c           %c%c    %c%c    %c%c                  %c%c            %c%c\n",219,219,219,219,219,219,219,219,219,219,219,219);
	printf("                          %c%c%c%c%c%c%c    %c%c    %c%c      %c%c%c%c%c%c%c    %c%c%c%c%c%c%c       %c%c%c%c%c%c%c\n",219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219,219);

}

void tilePutih(){ //fungsi ini buat bikin newNode untuk tale yang warna putih
	tile *newTile = (tile *)malloc(sizeof(tile));
	newTile->isi = 0;
	newTile->warna = 240;
	strcpy(newTile->code, "X");
	strcpy(newTile->gbr, " ");
	strcpy(newTile->mark, "NONE");
	newTile->prev = NULL;
	newTile->next = NULL;
	
	if(!head){
		head = tail = newTile;
	}else{
		tail->next = newTile;
		newTile->prev = tail;
		tail = newTile;
	}
}

void tileHitam(){//fungs ini buat bikin newNode untuk tale yang warna hitam
	tile *newTile = (tile *)malloc(sizeof(tile));
	newTile->isi = 0;
	newTile->warna = 15;
	strcpy(newTile->code, "X");
	strcpy(newTile->gbr, " ");
	strcpy(newTile->mark, "NONE");
	newTile->prev = NULL;
	newTile->next = NULL;
	if(!head){
		head = tail = newTile;
	}else{
		tail->next = newTile;
		newTile->prev = tail;
		tail = newTile;
	}
}

void tileCode(){//fungsi ini buat bikin link listnya
	char code[3];
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			tilePutih();//ini berarti dia bikin newNode yang putih
			tileHitam();//ini berarti dia bikin newNode yang hitam
		}
		for(int j=0; j<4; j++){
			tileHitam();
			tilePutih();
		}
	}
	temp = head;
	for(int i=65; i<73; i++){//ini buat ngasih code di setiap node nya sesuai dengan baris dan kolomnya
		for(int j=0; j<8; j++){
			sprintf(code, "%c%d", i, j+1);
			strcpy(temp->code, code);
			temp = temp->next;
		}
	}
}

void piecePutih(){//fungsi ini buat print gambar di node untuk yang putih (buat masukin piecenya)
	temp = head;
	while(strcmp(temp->code, "G1")!=0){
		temp = temp->next;
	}
	for(int i=0; i<8; i++){
		strcpy(temp->gbr, "A");
		temp->isi = 2;
		strcpy(temp->mark, "pawn");
		temp = temp->next;
	}
	temp = head;
	while(strcmp(temp->code, "H1")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "R");
	temp->isi = 2;
	strcpy(temp->mark, "rook");
	for(int i =0; i<7; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "R");
	temp->isi = 2;
	strcpy(temp->mark, "rook");
	temp = head;
	while(strcmp(temp->code, "H2")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "D");
	temp->isi = 2;
	strcpy(temp->mark, "knight");
	for(int i =0; i<5; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "D");
	temp->isi = 2;
	strcpy(temp->mark, "knight");
	temp = head;
	while(strcmp(temp->code, "H3")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "B");
	temp->isi = 2;
	strcpy(temp->mark, "bishop");
	for(int i =0; i<3; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "B");
	temp->isi = 2;
	strcpy(temp->mark, "bishop");
	temp = head;
	while(strcmp(temp->code, "H4")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "Q");
	temp->isi = 2;
	strcpy(temp->mark, "queen");
	temp = temp->next;
	strcpy(temp->gbr, "H");
	temp->isi = 2;
	strcpy(temp->mark, "king");
}

void pieceHitam(){//fungsi ini buat print gambar di node untuk yang hitam (buat masukin piecenya)
	temp = head;
	while(strcmp(temp->code, "B1")!=0){
		temp = temp->next;
	}
	for(int i=0; i<8; i++){
		strcpy(temp->gbr, "a");
		temp->isi = 1;
		strcpy(temp->mark, "pawn");
		temp = temp->next;
	}
	temp = head;\
	strcpy(temp->gbr, "r");
	temp->isi = 1;
	strcpy(temp->mark, "rook");
	for(int i =0; i<7; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "r");
	temp->isi = 1;
	strcpy(temp->mark, "rook");
	temp = head;
	while(strcmp(temp->code, "A2")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "d");
	temp->isi = 1;
	strcpy(temp->mark, "knight");
	for(int i =0; i<5; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "d");
	temp->isi = 1;
	strcpy(temp->mark, "knight");
	temp = head;
	while(strcmp(temp->code, "A3")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "b");
	temp->isi = 1;
	strcpy(temp->mark, "bishop");
	for(int i =0; i<3; i++){
		temp = temp->next;
	}
	strcpy(temp->gbr, "b");
	temp->isi = 1;
	strcpy(temp->mark, "bishop");
	temp = head;
	while(strcmp(temp->code, "A4")!=0){
		temp = temp->next;
	}
	strcpy(temp->gbr, "q");
	temp->isi = 1;
	strcpy(temp->mark, "queen");
	temp = temp->next;
	strcpy(temp->gbr, "h");
	temp->isi = 1;
	strcpy(temp->mark, "king");
}

void board(){//ini buat print node(print papannya)
	warna(78);
	printf("\n");
	tulisan();
	gotoxy(0, 10);
	printf(" White | Black | Name\n");
	printf("---------------------------\n");
	printf(" %-5s | %-5s | Pawn\n %-5s | %-5s | Rook\n %-5s | %-5s | Knight\n %-5s | %-5s | Bishop\n %-5s | %-5s | Queen\n %-5s | %-5s | King\n","A", "a", "R", "r", "D", "d", "B", "b", "Q", "q", "H", "h");
	curr1 = head;
	for(int i=65; i<73; i++){
		gotoxy(40,i-55);
		warna(78);
		printf("%c", i);
		for(int j=0; j<8; j++){
			warna(curr1->warna);
			printf(" %s ", curr1->gbr);
			curr1 = curr1->next;
			warna(263);
		}
		printf("\n");
	}
	gotoxy(40,18);
	warna(78);
	printf("  1  2  3  4  5  6  7  8\n");
}

int movePawnWhite(char first[3], char last[3]){//ini buat gerakin pawn yang warna putih-
	char eat1[3], eat2[3], front[3], promote[2];
	int x=0, i, j, k, l;
	i = first[0];
	j = last[0];
	k = first[1];
	l = last[1];
	if(i==71){
		if((((i-1)!=j && (i-2)!=j) || k!=l) && ((i-1)!=j || (k-1)!=l) &&  ((i-1)!=j || (k+1)!=l)){
			x=0;
			return x;
		}
	}else{
		if(((i-1)!=j || k!=l) && ((i-1)!=j || (k-1)!=l) &&  ((i-1)!=j || (k+1)!=l)){
			x=0;
			return x;
		}	
	}
	temp2 = head;
	while(temp2!= NULL){//ini buat bikin temp itu jadi ke node yang kita pilih misal kita milih buat jalanin bishop dari H3 ke F1, nahh headnya itu kan ada di A1 jadi kita bikin temp nyampe ke H3
		if(strcmp(temp2->code, first)==0){
			break;
		}else{
			temp2 = temp2->next;
		}
	}
	if((i-2)==j && k==l){//ini buat kalo dia jalan ke atas
		for(int v=1; v<i-j; v++){
			for(int z=0; z<8; z++){
				temp2 = temp2->prev;
			}
			if(temp2->isi!=0){
				return x;
			}
		}
	}
	x=1;
	sprintf(eat1, "%c%c", i-1, k-1);
	sprintf(eat2, "%c%c", i-1, k+1);
	sprintf(front, "%c%c", i-1, k);
	temp = curr = head;
	while(curr!= NULL){
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->code, eat1)==0 && temp->isi==1){
		if(strcmp(temp->mark, "king")==0){
			x=2;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='A'){
			do{
				printf("\n\n\n\n\n\nPromote to[R|D|B|Q]: ");
				gets(promote);
			}while(strcmp(promote, "R")!=0 && strcmp(promote, "D")!=0 && strcmp(promote, "B")!=0 && strcmp(promote, "Q")!=0);
			if(strcmp(promote, "R")==0){
				strcpy(temp->gbr, "R");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "D")==0){
				strcpy(temp->gbr, "D");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "B")==0){
				strcpy(temp->gbr, "B");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "Q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}else if(strcmp(temp->code, eat2)==0 && temp->isi==1){
		if(strcmp(temp->mark, "king")==0){
			x=2;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='A'){
			do{
				printf("\n\n\n\n\n\nPromote to[R|D|B|Q]: ");
				gets(promote);
			}while(strcmp(promote, "R")!=0 && strcmp(promote, "D")!=0 && strcmp(promote, "B")!=0 && strcmp(promote, "Q")!=0);
			if(strcmp(promote, "R")==0){
				strcpy(temp->gbr, "R");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "D")==0){
				strcpy(temp->gbr, "D");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "B")==0){
				strcpy(temp->gbr, "B");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "Q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}else if((strcmp(temp->code, front)==0 && temp->isi!=0) || (strcmp(temp->code, eat1)==0 && temp->isi==0) || (strcmp(temp->code, eat2)==0 && temp->isi==0)){
		x=0;
		return x;
	}else{
		if(strcmp(temp->mark, "king")==0){
			x=2;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='A'){
			do{
				printf("\n\n\n\n\n\nPromote to[R|D|B|Q]: ");
				gets(promote);
			}while(strcmp(promote, "R")!=0 && strcmp(promote, "D")!=0 && strcmp(promote, "B")!=0 && strcmp(promote, "Q")!=0);
			if(strcmp(promote, "R")==0){
				strcpy(temp->gbr, "R");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "D")==0){
				strcpy(temp->gbr, "D");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "B")==0){
				strcpy(temp->gbr, "B");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "Q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}
}

int movePawnBlack(char first[3], char last[3]){//ini buat gerakin pawn yang warna hitam
	char eat1[3], eat2[3], front[3], promote[2];
	int x=0, i, j, k, l;
	i = first[0];
	j = last[0];
	k = first[1];
	l = last[1];
	if(i==66){
		if((((i+1)!=j && (i+2)!=j) || k!=l) && ((i+1)!=j || (k+1)!=l) &&  ((i+1)!=j || (k-1)!=l)){
			x=0;
			return x;
		}	
	}else{
		if(((i+1)!=j || k!=l) && ((i+1)!=j || (k+1)!=l) &&  ((i+1)!=j || (k-1)!=l)){
			x=0;
			return x;
		}	
	}
	temp2 = head;
	while(temp2!= NULL){//ini buat bikin temp itu jadi ke node yang kita pilih misal kita milih buat jalanin bishop dari H3 ke F1, nahh headnya itu kan ada di A1 jadi kita bikin temp nyampe ke H3
		if(strcmp(temp2->code, first)==0){
			break;
		}else{
			temp2 = temp2->next;
		}
	}
	if((i+2)==j && k==l){//ini buat kalo dia jalan ke bawah
		for(int v=1; v<j-i; v++){
			for(int z=0; z<8; z++){
				temp2 = temp2->next;
			}
			if(temp2->isi!=0){
				return x;
			}
		}
	}
	x=1;
	sprintf(eat1, "%c%c", i+1, k+1);
	sprintf(eat2, "%c%c", i+1, k-1);
	sprintf(front, "%c%c", i+1, k);
	temp = curr = head;
	while(curr!= NULL){
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->code, eat1)==0 && temp->isi==2){
		if(strcmp(temp->mark, "king")==0){
			x=3;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='H'){
			do{
				printf("\n\n\n\n\n\nPromote to[r|d|b|q]: ");
				gets(promote);	
			}while(strcmp(promote, "r")!=0 && strcmp(promote, "d")!=0 && strcmp(promote, "b")!=0 && strcmp(promote, "q")!=0);
			if(strcmp(promote, "r")==0){
				strcpy(temp->gbr, "r");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "d")==0){
				strcpy(temp->gbr, "d");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "b")==0){
				strcpy(temp->gbr, "b");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}else if(strcmp(temp->code, eat2)==0 && temp->isi==2){
		if(strcmp(temp->mark, "king")==0){
			x=3;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='H'){
			do{
				printf("\n\n\n\n\n\nPromote to[r|d|b|q]: ");
				gets(promote);	
			}while(strcmp(promote, "r")!=0 && strcmp(promote, "d")!=0 && strcmp(promote, "b")!=0 && strcmp(promote, "q")!=0);
			if(strcmp(promote, "r")==0){
				strcpy(temp->gbr, "r");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "d")==0){
				strcpy(temp->gbr, "d");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "b")==0){
				strcpy(temp->gbr, "b");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}else if((strcmp(temp->code, front)==0 && temp->isi!=0) || (strcmp(temp->code, eat1)==0 && temp->isi==0) || (strcmp(temp->code, eat2)==0 && temp->isi==0)){
		x=0;
		return x;
	}else{
		if(strcmp(temp->mark, "king")==0){
			x=3;
			return x;
		}
		strcpy(temp->gbr, curr->gbr);
		strcpy(temp->mark, curr->mark);
		temp->isi = curr->isi;
		curr->isi = 0;
		strcpy(curr->gbr, " ");
		strcpy(curr->mark, "NONE");
		if(j=='H'){
			do{
				printf("\n\n\n\n\n\nPromote to[r|d|b|q]: ");
				gets(promote);	
			}while(strcmp(promote, "r")!=0 && strcmp(promote, "d")!=0 && strcmp(promote, "b")!=0 && strcmp(promote, "q")!=0);
			if(strcmp(promote, "r")==0){
				strcpy(temp->gbr, "r");
				strcpy(temp->mark, "rook");
			}else if(strcmp(promote, "d")==0){
				strcpy(temp->gbr, "d");
				strcpy(temp->mark, "knight");
			}else if(strcmp(promote, "b")==0){
				strcpy(temp->gbr, "b");
				strcpy(temp->mark, "bishop");
			}else{
				strcpy(temp->gbr, "q");
				strcpy(temp->mark, "queen");
			}
		}
		return x;
	}
}

int moveBishop(char first[3], char last[3]){//ini buat gerakin bishop yang warna putih dan hitam sama saja
	int x=0, i, j, k, l, y=0; //x untuk melempar hasil(return), first tempat awal, last yang di tuju
	i = first[0];//1=kiri atas, 2=kanan atas, 3=kiri bawah, 4=kanan bawah
	j = last[0];//misal yaa dia pilih dari H3 jalan ke F3 berarti, i itu nampung H, k nampung 3 yang dari H3, j nampung F, l nampung 3 yang dari F3
	k = first[1];
	l = last[1];
	temp2 = head;
	while(temp2!= NULL){//ini buat bikin temp itu jadi ke node yang kita pilih misal kita milih buat jalanin bishop dari H3 ke F1, nahh headnya itu kan ada di A1 jadi kita bikin temp nyampe ke H3
		if(strcmp(temp2->code, first)==0){
			break;
		}else{
			temp2 = temp2->next;
		}
	}
	for(int a=1; a<=8; a++){//ini fungsi buat falidasi jalannya boleh ato gk
		if((i-a)==j && (k-a)==l){//ini buat kalo dia jalan miring ke kiri atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<9; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i-a)==j && (k+a)==l){//ini buat kalo dia jalan miring ke kanan atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<7; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && (k+a)==l){//ini buat kalo dia jalan miring ke kanan bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<9; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && (k-a)==l){//ini buat kalo dia jalan miring ke kiri bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<7; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else{
			x=0;
			y=0;
		}
	}
	if(y==0){
		return x;
	}
	x=1;
	temp = curr = head;
	while(curr!= NULL){//sama kayak fungsi while(temp2 != NULL) tapi ini buat curr
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){//sama kayak fungsi while(curr != NULL) tapi ini buat temp dan ini dia kalo jalannya dari H3 ke F1 berarti tempnya bukan ke H3 yang ke H3 curr yang ini buat ke F1
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->mark, "king")==0 && temp->isi==1){
		x=2;
		return x;
	}else if(strcmp(temp->mark, "king")==0 && temp->isi==2){
		x=3;
		return x;
	}
	strcpy(temp->gbr, curr->gbr);//buat pindahin dari H3 ke F1
	strcpy(temp->mark, curr->mark);
	temp->isi = curr->isi;
	curr->isi = 0;
	strcpy(curr->gbr, " ");
	strcpy(curr->mark, "NONE");
	return x;
}

int moveRook(char first[3], char last[3]){//ini buat gerakin rook yang warna putih dan hitam sama saja
	int x=0, i, j, k, l, y=0; //x untuk melempar hasil(return), first tempat awal, last yang di tuju
	i = first[0];//1=kiri atas, 2=kanan atas, 3=kiri bawah, 4=kanan bawah
	j = last[0];//misal yaa dia pilih dari H3 jalan ke F3 berarti, i itu nampung H, k nampung 3 yang dari H3, j nampung F, l nampung 3 yang dari F3
	k = first[1];
	l = last[1];
	temp2 = head;
	while(temp2!= NULL){//ini buat bikin temp itu jadi ke node yang kita pilih misal kita milih buat jalanin bishop dari H3 ke F1, nahh headnya itu kan ada di A1 jadi kita bikin temp nyampe ke H3
		if(strcmp(temp2->code, first)==0){
			break;
		}else{
			temp2 = temp2->next;
		}
	}
	for(int a=1; a<=8; a++){//ini fungsi buat falidasi jalannya boleh ato gk
		if((i-a)==j && k==l){//ini buat kalo dia jalan ke atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<8; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && k==l){//ini buat kalo dia jalan ke bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<8; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if(i==j && (k+a)==l){//ini buat kalo dia jalan ke kanan
			for(int v=1; v<l-k; v++){
				temp2 = temp2->next;
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if(i==j && (k-a)==l){//ini buat kalo dia jalan ke kiri
			for(int v=1; v<k-l; v++){
				temp2 = temp2->prev;
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else{
			x=0;
			y=0;
		}
	}
	if(y==0){
		return x;
	}
	x=1;
	temp = curr = head;
	while(curr!= NULL){//sama kayak fungsi while(temp2 != NULL) tapi ini buat curr
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){//sama kayak fungsi while(curr != NULL) tapi ini buat temp dan ini dia kalo jalannya dari H3 ke F1 berarti tempnya bukan ke H3 yang ke H3 curr yang ini buat ke F1
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->mark, "king")==0 && temp->isi==1){
		x=2;
		return x;
	}else if(strcmp(temp->mark, "king")==0 && temp->isi==2){
		x=3;
		return x;
	}
	if(curr->isi == 1 && strcmp(curr->code, "A1")==0){
		moveR1++;
	}else if(curr->isi == 1 && strcmp(curr->code, "A8")==0){
		moveR3++;
	}else if(curr->isi == 2 && strcmp(curr->code, "H1")==0){
		moveR2++;
	}else if(curr->isi == 2 && strcmp(curr->code, "H8")==0){
		moveR4++;
	}
	strcpy(temp->gbr, curr->gbr);//buat pindahin dari H3 ke F1
	strcpy(temp->mark, curr->mark);
	temp->isi = curr->isi;
	curr->isi = 0;
	strcpy(curr->gbr, " ");
	strcpy(curr->mark, "NONE");
	return x;
}

int moveQueen(char first[3], char last[3]){//ini buat gerakin bishop yang warna putih dan hitam sama saja
	int x=0, i, j, k, l, y=0; //x untuk melempar hasil(return), first tempat awal, last yang di tuju
	i = first[0];//1=kiri atas, 2=kanan atas, 3=kiri bawah, 4=kanan bawah
	j = last[0];//misal yaa dia pilih dari H3 jalan ke F3 berarti, i itu nampung H, k nampung 3 yang dari H3, j nampung F, l nampung 3 yang dari F3
	k = first[1];
	l = last[1];
	temp2 = head;
	while(temp2!= NULL){//ini buat bikin temp itu jadi ke node yang kita pilih misal kita milih buat jalanin bishop dari H3 ke F1, nahh headnya itu kan ada di A1 jadi kita bikin temp nyampe ke H3
		if(strcmp(temp2->code, first)==0){
			break;
		}else{
			temp2 = temp2->next;
		}
	}
	for(int a=1; a<=8; a++){//ini fungsi buat falidasi jalannya boleh ato gk
		if((i-a)==j && k==l){//ini buat kalo dia jalan ke atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<8; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && k==l){//ini buat kalo dia jalan ke bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<8; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if(i==j && (k+a)==l){//ini buat kalo dia jalan ke kanan
			for(int v=1; v<l-k; v++){
				temp2 = temp2->next;
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if(i==j && (k-a)==l){//ini buat kalo dia jalan ke kiri
			for(int v=1; v<k-l; v++){
				temp2 = temp2->prev;
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i-a)==j && (k-a)==l){//ini buat kalo dia jalan miring ke kiri atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<9; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i-a)==j && (k+a)==l){//ini buat kalo dia jalan miring ke kanan atas
			for(int v=1; v<i-j; v++){
				for(int z=0; z<7; z++){
					temp2 = temp2->prev;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && (k+a)==l){//ini buat kalo dia jalan miring ke kanan bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<9; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else if((i+a)==j && (k-a)==l){//ini buat kalo dia jalan miring ke kiri bawah
			for(int v=1; v<j-i; v++){
				for(int z=0; z<7; z++){
					temp2 = temp2->next;
				}
				if(temp2->isi!=0){
					return x;
				}
			}
			y=1;
			break;
		}else{
			x=0;
			y=0;
		}
	}
	if(y==0){
		return x;
	}
	x=1;
	temp = curr = head;
	while(curr!= NULL){//sama kayak fungsi while(temp2 != NULL) tapi ini buat curr
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){//sama kayak fungsi while(curr != NULL) tapi ini buat temp dan ini dia kalo jalannya dari H3 ke F1 berarti tempnya bukan ke H3 yang ke H3 curr yang ini buat ke F1
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->mark, "king")==0 && temp->isi==1){
		x=2;
		return x;
	}else if(strcmp(temp->mark, "king")==0 && temp->isi==2){
		x=3;
		return x;
	}
	strcpy(temp->gbr, curr->gbr);//buat pindahin dari H3 ke F1
	strcpy(temp->mark, curr->mark);
	temp->isi = curr->isi;
	curr->isi = 0;
	strcpy(curr->gbr, " ");
	strcpy(curr->mark, "NONE");
	return x;
}

int moveKnight(char first[3], char last[3]){//ini buat gerakin kuda yang warna putih dan hitam sama saja
	int x=0, i, j, k, l, y=0; //x untuk melempar hasil(return), first tempat awal, last yang di tuju
	i = first[0];//1=kiri atas, 2=kanan atas, 3=kiri bawah, 4=kanan bawah
	j = last[0];//misal yaa dia pilih dari H3 jalan ke F3 berarti, i itu nampung H, k nampung 3 yang dari H3, j nampung F, l nampung 3 yang dari F3
	k = first[1];
	l = last[1];
	if(((i-2)!=j || (k-1)!=l) && ((i-2)!=j || (k+1)!=l) &&  ((i-1)!=j || (k-2)!=l) &&  ((i-1)!=j || (k+2)!=l) &&  
	((i+1)!=j || (k-2)!=l) &&  ((i+1)!=j || (k+2)!=l) &&  ((i+2)!=j || (k-1)!=l) &&  ((i+2)!=j || (k+1)!=l)){
		x=0;
		return x;
	}
	x=1;
	temp = curr = head;
	while(curr!= NULL){
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->mark, "king")==0 && temp->isi==1){
		x=2;
		return x;
	}else if(strcmp(temp->mark, "king")==0 && temp->isi==2){
		x=3;
		return x;
	}
	strcpy(temp->gbr, curr->gbr);//buat pindahin dari H3 ke F1
	strcpy(temp->mark, curr->mark);
	temp->isi = curr->isi;
	curr->isi = 0;
	strcpy(curr->gbr, " ");
	strcpy(curr->mark, "NONE");
	return x;
}

int kingSkak(int turn, char kingCode[3]){
	int skak=0, test=0;
	int batas = kingCode[1]-48;
	curr = head;
	while(strcmp(curr->code, kingCode)!=0){
		curr = curr->next;
	}
	temp2 = curr;
	if(turn==1){
		for(int i=0; i<7; i++){
			if(temp2->prev == NULL){
				temp2 = curr;
				break;
			}
			if(batas==8){
				break;
			}
			temp2 = temp2->prev;
		}
		if(strcmp(temp2->gbr, "a")==0){
			skak=1;
			return skak;
		}
	}else{
		for(int i=0; i<7; i++){
			if(temp2->next == NULL){
				temp2 = curr;
				break;
			}
			if(batas==1){
				break;
			}
			temp2 = temp2->next;
		}
		if(strcmp(temp2->gbr, "A")==0){
			skak=1;
			return skak;
		}
	}
	temp2 = curr;
	for(int p=0; p=8-batas; p++){
		for(int i=0; i<7; i++){
			if(temp2->prev == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->prev;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "b")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "B")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	temp2 = curr;
	for(int p=0; p=batas-1; p++){
		for(int i=0; i<7; i++){
			if(temp2->next == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->next;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "b")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "B")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	temp2 = curr;
	do{
		for(int i=0; i<8; i++){
			if(temp2->prev == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->prev;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "r")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "R")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}while(temp2 != NULL);
	temp2 = curr;
	do{
		for(int i=0; i<8; i++){
			if(temp2->next == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->next;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "r")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "R")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}while(temp2 != NULL);
	temp2 = curr;
	if(turn==1){
		for(int i=0; i<9; i++){
			if(temp2->prev == NULL){
				temp2 = curr;
				break;
			}
			if(batas==1){
				break;
			}
			temp2 = temp2->prev;
		}
		if(strcmp(temp2->gbr, "a")==0){
			skak=1;
			return skak;
		}
	}else{
		for(int i=0; i<9; i++){
			if(temp2->next == NULL){
				temp2 = curr;
				break;
			}
			if(batas==8){
				break;
			}
			temp2 = temp2->next;
		}
		if(strcmp(temp2->gbr, "A")==0){
			skak=1;
			return skak;
		}
	}
	temp2 = curr;
	for(int p=0; p<batas-1; p++){
		for(int i=0; i<9; i++){
			if(temp2->prev == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->prev;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "b")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "B")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	temp2 = curr;
	for(int p=0; p<8-batas; p++){
		for(int i=0; i<9; i++){
			if(temp2->next == NULL){
				test = 1;
				temp2 = curr;
				break;
			}
			temp2 = temp2->next;
		}
		if(test==1){
			test = 0;
			break;
		}
		if(turn==1){
			if(strcmp(temp2->gbr, "b")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "B")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->gbr, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	int k = kingCode[1];
	temp2 = curr;
	for(int i=0; i<k-48-1; i++){
		temp2 = temp2->prev;
		if(turn==1){
			if(strcmp(temp2->gbr, "r")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "R")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	temp2 = curr;
	for(int i=0; i<8-k-48; i++){
		temp2 = temp2->next;
		if(turn==1){
			if(strcmp(temp2->gbr, "r")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}else{
			if(strcmp(temp2->gbr, "R")==0){
				skak=1;
				return skak;
			}else if(strcmp(temp2->mark, "Q")==0){
				skak=1;
				return skak;
			}else if(temp2->isi!=0){
				skak = 0;
				break;
			}
		}
	}
	int i1 = kingCode[0];
	int k1 = kingCode[1];
	int av = 0;
	char ij1[2], ij2[2], ij3[2], ij4[2], ij5[2], ij6[2], ij7[2], ij8[2];
	sprintf(ij1, "%c%d", i1-2, k1-1-48);
	sprintf(ij2, "%c%d", i1-2, k1+1-48);
	sprintf(ij3, "%c%d", i1-1, k1-2-48);
	sprintf(ij4, "%c%d", i1-1, k1+2-48);
	sprintf(ij5, "%c%d", i1+1, k1-2-48);
	sprintf(ij6, "%c%d", i1+1, k1+2-48);
	sprintf(ij7, "%c%d", i1+2, k1-1-48);
	sprintf(ij8, "%c%d", i1+2, k1+1-48);
	temp3 = head;
	if(turn==1){
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij1)!=0){
			if(i1==65 || i1==66 || k1-48==1){
				av = 1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij2)!=0){
			if(i1==65 || i1==66 || k1-48==8){
				av = 1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij3)!=0){
			if(i1==65 || k1-48==1 || k1-48==2){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij4)!=0){
			if(i1==65 || k1-48==7 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij5)!=0){
			if(i1==72 || k1-48==1 || k1-48==2){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij6)!=0){
			if(i1==72 || k1-48==7 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij7)!=0){
			if(i1==72 || i1==71 || k1-48==1){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij8)!=0){
			if(i1==72 || i1==71 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "d")==0 && av==0){
			skak=1;
			return skak;
		}
	}else{
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij1)!=0){
			if(i1==65 || i1==66 || k1-48==1){
				av = 1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij2)!=0){
			if(i1==65 || i1==66 || k1-48==8){
				av = 1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av = 0;
		temp3 = head;
		while(strcmp(temp3->code, ij3)!=0){
			if(i1==65 || k1-48==1 || k1-48==2){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij4)!=0){
			if(i1==65 || k1-48==7 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij5)!=0){
			if(i1==72 || k1-48==1 || k1-48==2){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij6)!=0){
			if(i1==72 || k1-48==7 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij7)!=0){
			if(i1==72 || i1==71 || k1-48==1){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
		av=0;
		temp3 = head;
		while(strcmp(temp3->code, ij8)!=0){
			if(i1==72 || i1==71 || k1-48==8){
				av=1;
				break;
			}
			temp3 = temp3->next;
		}
		if(strcmp(temp3->gbr, "D")==0 && av==0){
			skak=1;
			return skak;
		}
	}
	skak = 0;
	return skak;
}

int moveKing(int turn, char first[3], char last[3]){//ini buat gerakin rook yang warna putih dan hitam sama saja
	int x=0, i, j, k, l, A, B, y=0, move, skak=0; //x untuk melempar hasil(return), first tempat awal, last yang di tuju
	i = first[0];//1=kiri atas, 2=kanan atas, 3=kiri bawah, 4=kanan bawah
	j = last[0];//misal yaa dia pilih dari H3 jalan ke F3 berarti, i itu nampung H, k nampung 3 yang dari H3, j nampung F, l nampung 3 yang dari F3
	k = first[1];
	l = last[1];
	A = k-48;
	B = l-48;
	if(A==5 && B==3){
		temp4 = head;
		if(turn==1){
			if(moveK1!=0 || moveR1!=0){
				x=0;
				return x;
			}
		}else{
			if(moveK2!=0 || moveR2!=0){
				x=0;
				return x;
			}
		}
		while(strcmp(temp4->code, first)!=0){
			temp4 = temp4->next;
		}
		temp5 = head;
		while(strcmp(temp5->code, first)!=0){
			temp5 = temp5->next;
		}
		for(int p=0; p<A-2; p++){
			temp5 = temp5->prev;
			if(temp5->isi!=0){
				x=0;
				return x;               
			}
		}//cek apakah jalan kosong
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}//di raja
		if(skak==1){
			x=0;
			return x;
		}
		temp4 = temp4->prev;//tile 4
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}
		if(skak==1){
			x=0;
			return x;                  
		}
		temp4 = temp4->prev;//tile 3
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}
		if(skak==1){
			x=0;
			return x;
		}
		temp5 = temp4 = head;
		if(turn==2){
			while(strcmp(temp5->code, "H1")!=0){
				temp5 = temp5->next;
			}
		}
		while(strcmp(temp4->code, first)!=0){
			temp4 = temp4->next;
		}
		x=1;
		strcpy(temp4->prev->gbr, temp5->gbr);
		strcpy(temp4->prev->mark, temp5->mark);
		temp4->prev->isi = temp5->isi;
		temp5->isi = 0;
		strcpy(temp5->gbr, " ");
		strcpy(temp5->mark, "NONE");
		strcpy(temp4->prev->prev->gbr, temp4->gbr);
		strcpy(temp4->prev->prev->mark, temp4->mark);
		temp4->prev->prev->isi = temp4->isi;
		temp4->isi = 0;
		strcpy(temp4->gbr, " ");
		strcpy(temp4->mark, "NONE");
		if(turn==1){
			moveK1++;
			moveR1++;
		}else{
			moveK2++;
			moveR2++;
		}
		return x;				
	}else if(A==5 && B==7){
		temp4 = head;
		if(turn==1){
			if(moveK1!=0 || moveR3!=0){
				x=0;
				return x;
			}
		}else{
			if(moveK2!=0 || moveR4!=0){
				x=0;
				return x;
			}
		}
		while(strcmp(temp4->code, first)!=0){
			temp4 = temp4->next;
		}//ke king
		temp5 = head;
		while(strcmp(temp5->code, first)!=0){
			temp5 = temp5->next;
		}
		for(int p=0; p<7-A; p++){
			temp5 = temp5->next;
			if(temp5->isi!=0){
				x=0;
				return x;              
			}
		}//cek kosong gk jalannya
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}//di raja
		if(skak==1){
			x=0;
			return x;
		}
		temp4 = temp4->next;//tile 6
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}
		if(skak==1){
			x=0;
			return x;
		}
		temp4 = temp4->next;//tile 7
		if(turn==1){
			skak = kingSkak(2, temp4->code);
		}else{
			skak = kingSkak(1, temp4->code);
		}
		if(skak==1){
			x=0;
			return x;
		}
		temp5 = temp4 = head;
		if(turn==2){
			while(strcmp(temp5->code, "H8")!=0){
				temp5 = temp5->next;
			}
		}else{
			while(strcmp(temp5->code, "A8")!=0){
				temp5 = temp5->next;
			}
		}
		while(strcmp(temp4->code, first)!=0){
			temp4 = temp4->next;
		}
		x=1;
		strcpy(temp4->next->gbr, temp5->gbr);
		strcpy(temp4->next->mark, temp5->mark);
		temp4->next->isi = temp5->isi;
		temp5->isi = 0;
		strcpy(temp5->gbr, " ");
		strcpy(temp5->mark, "NONE");
		strcpy(temp4->next->next->gbr, temp4->gbr);
		strcpy(temp4->next->next->mark, temp4->mark);
		temp4->next->next->isi = temp4->isi;
		temp4->isi = 0;
		strcpy(temp4->gbr, " ");
		strcpy(temp4->mark, "NONE");
		if(turn==1){
			moveK1++;
			moveR3++;
		}else{
			moveK2++;
			moveR4++;
		}
		return x;				
	}
	if(((i-1)!=j || (k-1)!=l) && ((i-1)!=j || k!=l) &&  ((i-1)!=j || (k+1)!=l) &&  (i!=j || (k-1)!=l) &&  
	(i!=j || (k+1)!=l) &&  ((i+1)!=j || (k-1)!=l) &&  ((i+1)!=j || k!=l) &&  ((i+1)!=j || (k+1)!=l)){
		x=0;
		return x;
	}
	x=1;
	temp = curr = head;
	while(curr!= NULL){
		if(strcmp(curr->code, first)==0){
			break;
		}else{
			curr = curr->next;
		}
	}
	while(temp != NULL){
		if(strcmp(temp->code, last)==0){
			break;
		}else{
			temp = temp->next;
		}
	}
	if(strcmp(temp->mark, "king")==0 && temp->isi==1){
		x=2;
		return x;
	}else if(strcmp(temp->mark, "king")==0 && temp->isi==2){
		x=3;
		return x;
	}
	if(curr->isi == 1){
		moveK1++;
	}else if(curr->isi == 2){
		moveK2++;
	}
	strcpy(temp->gbr, curr->gbr);//buat pindahin dari H3 ke F1
	strcpy(temp->mark, curr->mark);
	temp->isi = curr->isi;
	curr->isi = 0;
	strcpy(curr->gbr, " ");
	strcpy(curr->mark, "NONE");
	return x;
}

void cantMove(){
	gotoxy(80, 15);
	printf("Can't do move\n");
}

void moving(int turn, char color[11], int tempWarna){//funsi ini buat milij apa yang mau di gerakin
	char move[3];
	char to[3];
	int i=0, x=0, gerak, warna, z=0, skak=0;
	curr = head;
	warna = tempWarna;
awal:
	do{
		z=0;
		temp2 = curr;
		gerak = getch();
		if(gerak == RIGHT){
			if(curr->next == NULL){
				curr = curr;
			}else{
				temp2->warna = warna;
				curr = curr->next;
				warna = curr->warna;
				curr->warna = 224;
			}
		}else if(gerak == LEFT){
			if(curr->prev == NULL){
				curr = curr;
			}else{
				temp2->warna = warna;
				curr = curr->prev;
				warna = curr->warna;
				curr->warna = 224;	
			}
		}else if(gerak == UP){
			temp3 = curr;
			for(int v=0; v<8; v++){
				if(curr->prev == NULL){
					z=1;
					break;
				}
				temp2->warna = warna;
				curr = curr->prev;
			}
			if(z==1){
				curr = temp3;
				curr->warna = 224;
			}else{
				warna = curr->warna;
				curr->warna = 224;	
			}
		}else if(gerak == DOWN){
			temp3 = curr;
			for(int v=0; v<8; v++){
				if(curr->next == NULL){
					z=1;
					break;
				}
				temp2->warna = warna;
				curr = curr->next;
			}
			if(z==1){
				curr = temp3;
				curr->warna = 224;
			}else{
				warna = curr->warna;
				curr->warna = 224;	
			}
		}else if(gerak == ENTER){
			break;
		}
		system("cls");
		board();
		gotoxy(80, 13);
		printf("%s\n", color);
	}while(total==0);
	i = 0;
	strcpy(move, curr->code);
	gotoxy(80, 14);
	printf("Move piece on tile : %s\n", move);
	if(turn==2){//buat falidasi kalo yang jalan yang putih dia gk bisa milih punya si hitem
		if(curr->isi==1){
			gotoxy(80, 15);
			printf("Can't move enemy piece\n");
			goto awal;
		}
	}else{
		if(curr->isi==2){
			gotoxy(80, 15);
			printf("Can't move enemy piece\n");
			goto awal;
		}
	}
	if(curr->isi == 0){
		gotoxy(80, 15);
		printf("No piece on tile\n");
		goto awal;
	}
	temp = curr;
lagi:
	do{
		z=0;
		temp2 = temp;
		gerak = getch();
		if(gerak == RIGHT){
			if(temp->next==NULL){
				temp = temp;
			}else{
				temp2->warna = warna;
				temp = temp->next;
				warna = temp->warna;
				temp->warna = 224;
			}
		}else if(gerak == LEFT){
			if(temp->prev==NULL){
				temp = temp;
			}else{
				temp2->warna = warna;
				temp = temp->prev;
				warna = temp->warna;
				temp->warna = 224;
			}
		}else if(gerak == UP){
			temp3 = temp;
			for(int v=0; v<8; v++){
				if(temp->prev == NULL){
					z=1;
					break;
				}
				temp2->warna = warna;
				temp = temp->prev;
			}
			if(z==1){
				temp = temp3;
				temp->warna = 224;
			}else{
				warna = temp->warna;
				temp->warna = 224;
			}
		}else if(gerak == DOWN){
			temp3 = temp;
			for(int v=0; v<8; v++){
				if(temp->next == NULL){
					z=1;
					break;
				}
				temp2->warna = warna;
				temp = temp->next;
			}
			if(z==1){
				temp = temp3;
				temp->warna = 224;
			}else{
				warna = temp->warna;
				temp->warna = 224;
			}
		}else if(gerak == ENTER){
			temp->warna = warna;
			break;
		}
		system("cls");
		board();
		gotoxy(80, 13);
		printf("%s\n", color);
	}while(total==0);
	i = 0;
	strcpy(to, temp->code);
	gotoxy(80, 14);
	printf("Move to: %s\n", to);
	if(strcmp(curr->mark, "pawn")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu pawn dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = movePawnWhite(move, to);
	}else if(strcmp(curr->mark, "pawn")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu pawn dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = movePawnBlack(move, to);
	}else if(strcmp(curr->mark, "bishop")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu bishop dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveBishop(move, to);
	}else if(strcmp(curr->mark, "bishop")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu bishop dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveBishop(move, to);
	}else if(strcmp(curr->mark, "knight")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu knight dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveKnight(move, to);
	}else if(strcmp(curr->mark, "knight")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu knight dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveKnight(move, to);
	}else if(strcmp(curr->mark, "rook")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu rook dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveRook(move, to);
	}else if(strcmp(curr->mark, "rook")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu rook dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveRook(move, to);
	}else if(strcmp(curr->mark, "queen")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu queen dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveQueen(move, to);
	}else if(strcmp(curr->mark, "queen")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu queen dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveQueen(move, to);
	}else if(strcmp(curr->mark, "king")==0 && curr->isi==2){//buat kalo yang dipilih buat dijalanin itu king dan warna putih karena isinya 2 dan 2 itu berarti di tile itu ada isi warna putih
		if(temp->isi == 2){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveKing(turn, move, to);
	}else if(strcmp(curr->mark, "king")==0 && curr->isi==1){//buat kalo yang dipilih buat dijalanin itu KING dan warna hitam karena isinya 1 dan 1 itu berarti di tile itu ada isi warna hitam
		if(temp->isi == 1){//buat falidasi dia gk boleh jalan ketempat temennya sendiri(makan temennya sendiri)
			cantMove();
			goto lagi;
		}else
		x = moveKing(turn, move, to);
	}
	if(x==0){//ini buat falidasi jalannya boleh ato kgk (ada yang halangin gk)
		gotoxy(80, 14);
		printf("Invalid move\n\n");
		gotoxy(80, 15);
		system("pause");
		temp = head;
		tempWarna = temp->warna;
		temp->warna = 224;
		warna = 240;
		system("cls");
		board();
		gotoxy(80, 13);
		printf("%s\n", color);
		moving(turn, color, warna);
	}if(x==2){
		system("cls");
		printf("____    __    ____  __    __   __  .___________. _______    ____    __    ____  __  .__   __.\n");
		printf("\\   \\  /  \\  /   / |  |  |  | |  | |           ||   ____|   \\   \\  /  \\  /   / |  | |  \\ |  |\n");
		printf(" \\   \\/    \\/   /  |  |__|  | |  | `---|  |----`|  |__       \\   \\/    \\/   /  |  | |   \\|  |\n");
		printf("  \\            /   |   __   | |  |     |  |     |   __|       \\            /   |  | |  . `  |\n");
		printf("   \\    /\\    /    |  |  |  | |  |     |  |     |  |____       \\    /\\    /    |  | |  |\\   |\n");
		printf("    \\__/  \\__/     |__|  |__| |__|     |__|     |_______|       \\__/  \\__/     |__| |__| \\__|\n");                                                                                
		getchar();
		total = 1;
		return;
	}else if(x==3){
		system("cls");
		printf(".______    __          ___       ______  __  ___    ____    __    ____  __  .__   __.\n");
		printf("|   _  \\  |  |        /   \\     /      ||  |/  /    \\   \\  /  \\  /   / |  | |  \\ |  |\n");
		printf("|  |_)  | |  |       /  ^  \\   |  ,----'|  '  /      \\   \\/    \\/   /  |  | |   \\|  |\n");
		printf("|   _  <  |  |      /  /_\\  \\  |  |     |    <        \\            /   |  | |  . `  |\n");
		printf("|  |_)  | |  `----./  _____  \\ |  `----.|  .  \\        \\    /\\    /    |  | |  |\\   |\n");
		printf("|______/  |_______/__/     \\__\\ \\______||__|\\__\\        \\__/  \\__/     |__| |__| \\__|\n");                                                                      
		getchar();
		total = 1;
		return;
	}
	if(turn==2){
		temp2 = head;
		while(strcmp(temp2->gbr, "h")!=0){
			temp2 = temp2->next;
		}
		skak = kingSkak(turn, temp2->code);
	}else{
		temp2 = head;
		while(strcmp(temp2->gbr, "H")!=0){
			temp2 = temp2->next;
		}
		skak = kingSkak(turn, temp2->code);
	}
	if(skak==1){
		gotoxy(80, 15);
		printf("Skak\n");
		gotoxy(80, 16);
		system("pause");
	}
}

void popALL(){
	while(head){
		temp = head;
		if(head==tail){
			head = tail = NULL;
		}else{
			head = temp->next;
			head->prev = NULL;
			temp->next = NULL;
		}
		free(temp);
	}
}

void chess(){
	
	int turn=0, tempWarna;
	char color[11];
	
	tileCode();
	pieceHitam();
	piecePutih();
	do{
		temp = head;
		tempWarna = temp->warna;
		temp->warna = 224;
		system("cls");
		board();
		turn = 2;
		gotoxy(80, 13);
		printf("White turn\n");
		strcpy(color, "White turn");
		moving(turn, color, tempWarna);
		if(total!=0){
			break;
		}
		temp = head;
		tempWarna = temp->warna;
		temp->warna = 224;
		system("cls");
		board();
		turn = 1;
		gotoxy(80, 13);
		printf("Black turn\n");
		strcpy(color, "Black turn");
		moving(turn, color, tempWarna);
	}while(total==0);
	popALL();
}

void loadbar(){
	printf("\n\n\t\t\t\t");
	for(int i=0; i<44; i++){
		printf("%c", 219);
		Sleep(125);
	}
	system("cls");
}

int quitMenu(){

	static char quitOpsi[2][10] = {("  Yes  "),("  No  ")};
	char ch;
	int fflag = -1;
	quitOpsi[0][0] = '\0';
	quitOpsi[0][7] = '\0';
	quitOpsi[1][0] = '\0';
	quitOpsi[1][7] = '\0';

	for(;;){
	system("cls");
	for (int k=0;k<5;k++)puts("");
	for(int k=0;k<5;k++) printf("\t");
	printf("     Are you sure :");
	for (int k=0;k<4;k++)puts("");

	for(int i=0; i<2 ;++i){
		for(int k=0;k<6;k++) printf("\t");
		for(int j=0;j<10;++j){
			printf("%c",quitOpsi[i][j]);
		}
		puts("");
		puts("");
	}
	printf("\n\n");
	for(int o=0;o<4;o++) printf("\t");
	printf("  Press enter to select, arrow to move ");


		ch = getch();
		if(ch == UP){
			if (fflag >0){
				--(fflag);
			} 
			quitOpsi[fflag][0] = '-';
			quitOpsi[fflag][7] = '-';
			quitOpsi[fflag+1][0] = '\0';
			quitOpsi[fflag+1][7] = '\0';
		}else if ( ch == DOWN){
			if(fflag<1){
				++(fflag);
			}
			quitOpsi[fflag][0] = '-';
			quitOpsi[fflag][7] = '-';
			quitOpsi[fflag-1][0] = '\0';
			quitOpsi[fflag-1][7] = '\0';
		}

		if(ch == ENTER){
			if (fflag == 0){
			return fflag;
			}
			else {
				fflag = 1;
				return fflag;
			}
		}
	}
}

void howToPlay(){
	system("cls");
	printf("\t\t\t\t\t\t\t How To Play\n\n\n");
	printf("\t- The king moves exactly one square horizontally, vertically, or diagonally.\n\t  A special move with the king known as castling is allowed only once per player, per game (see below).\n\n");
	printf("\t- A rook moves any number of vacant squares in a horizontal or vertical direction.\n\t  It also is moved when castling.\n\n");
	printf("\t- A bishop moves any number of vacant squares in any diagonal direction.\n\n");
	printf("\t- The queen moves any number of vacant squares in a horizontal, vertical, or diagonal direction.\n\n");
	printf("\t- A knight moves to the nearest square not on the same rank, file, or diagonal.\n\t  (This can be thought of as moving two squares horizontally then one square vertically,\n\t   or moving one square horizontally then two squares vertically—i.e. in an \"L\" pattern.)\n\t  The knight is not blocked by other pieces: it jumps to the new location.\n\n");
	printf("\t- Pawns have the most complex rules of movement:\n");
	printf("\t\to A pawn moves straight forward one square, if that square is vacant. If it has not yet moved,\n\t\t  a pawn also has the option of moving two squares straight forward, provided both squares are vacant.\n\t\t  Pawns cannot move backwards.\n");
	printf("\t\to Pawns are the only pieces that capture differently from how they move.\n\t\t  A pawn can capture an enemy piece on either of the two squares diagonally in front of the pawn\n\t\t  (but cannot move to those squares if they are vacant).\n\n");
	printf("\t- Pawn Promotion\n\t  If a player advances a pawn to its eighth rank, the pawn is then promoted (converted) to a queen,\n\t  rook, bishop, or knight of the same color at the choice of the player(a queen is usually chosen).\n\t  The choice is not limited to previously captured pieces. Hence it is theoretically possible for\n\t  a player to have up to nine queens or up to ten rooks, bishops, or knights if all of their pawns\n\t  are promoted. If the desired piece is not available, the player should call the arbiter to provide the piece.\n\n");
	printf("\t- Casting\n");
	printf("\t  Castling consists of moving the king two squares towards a rook, then placing the rook on the other\n\t  side of the king, adjacent to it. Castling is only permissible if all of the following conditions hold:\n");
	printf("\t\to The king and rook involved in castling must not have previously moved;\n\t\to There must be no pieces between the king and the rook;\n\t\to The king may not currently be in check, nor may the king pass through or end up in a square that\n\t\t  is under attack by an enemy piece (though the rook is permitted to be under attack and to pass\n\t\t  over an attacked square);\n\t\to The king and the rook must be on the same rank.\n\n");
	printf("\t- Check\n");
	printf("\t  A king is in check when it is under attack by at least one enemy piece. A piece unable to move because\n\t  it would place its own king in check (it is pinned against its own king) may still deliver check to the\n\t  opposing player. It is illegal to make a move that places or leaves one's king in check.\n\t  The possible ways to get out of check are:\n");
	printf("\t\to Move the king to a square where it is not in check.\n\t\to Capture the checking piece (possibly with the king).\n\t\to Block the check by placing a piece between the king and the opponent's threatening piece\n\n");
	system("pause");
}

void menu(){
	char opsi[3][100]={("   Play"),("   How to Play"),("   Quit")};
	char ch='\0';
	int fflag;
	
	flag=-1;
	
	printf("\n\n\n");
	for(;;){
		system("cls");
		printf("\n\n\n\n\n");
		for(int i=0;i<3;++i){
			puts("");
			for(int k=0;k<21;k++) printf("\t");
			for(int j=0;j<22;++j) printf("%c",opsi[i][j]);
			puts("");
		}
		printf("\n\n");
		for(int k=0;k<19;k++) printf("\t");
		printf("    Press Enter To Select [Arrow To Move]");
		
		ch = getch();
		if(ch==DOWN){
			if(flag<2){
				++flag;
			}
			opsi[flag][0]='-';
			opsi[flag-1][0]='\0';
			opsi[flag][21]='-';
			opsi[flag-1][21]='\0';
		}
		else if(ch==UP){
			if(flag>0){
				--flag;
			}
			opsi[flag][0]='-';
			opsi[flag+1][0]='\0';
			opsi[flag][21]='-';
			opsi[flag+1][21]='\0';
		}
		if(ch==ENTER){
			if(flag==0){
				chess(); 
				total = 0;
				flag = 0;
				moveR1 = moveR2 = moveR3 = moveR4 = moveK1 = moveK2 = 0;
				menu();
				return;
			}
			else if(flag==1){
				howToPlay();
				menu();
				return;
			}
			else if(flag==2){
				fflag = quitMenu();
				if(fflag==0){
					return;
				}
				else{
					menu();
					return;
				}
			}
		}
	}
}

void awal(){
	gotoxy(0,15);
	int y;
	for (int i=15;i>4;i--){
		gotoxy(0,i);
		tulisan();
		Sleep(100);
		system("cls");	
	}
	gotoxy(0,5);
	tulisan();
	loadbar();
	menu();
}

int main(){
	warna(78);
	awal();
	getchar();
	return 0;
}
