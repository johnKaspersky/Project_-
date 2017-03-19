#include<stdio.h>
#include<stdlib.h>
#include<string.h>

	int tx = 0;
	int  rx = 0;
char RX(){
	char Rx = 0;
	printf("Enter Value : ");
	
	scanf("%c",&Rx);
	return Rx;
}
int alpha(char ch){
	if(((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z'))||((ch>=65 && ch<=90)||(ch>=97 && ch<=122))){
		return 1;
		
	}
	else return 0;
}
//int isnan(char ch){
//	if((ch>='a'&& ch<='z')||(ch>='A' && ch<='Z')){
//		return 1;
		
//	}
//	else return 0;
//}
int TX(char Tx){
		
		if(alpha(Tx)){
				printf(" Value Show : %c",Tx);
		}
				

	else {
		printf(" Value no type data " );
	}
	
}

void main(){

	
	printf("Start program : \n");
	TX(RX());
    	
   	
}
