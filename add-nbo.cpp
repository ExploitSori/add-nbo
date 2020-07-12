#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include <arpa/inet.h>
uint32_t fpToUint32(FILE* fp){
	char* buf;
	long size =ftell(fp);
	size_t res ;
	uint8_t n[4];
	int flag = 0xff;
	fseek(fp,0,SEEK_END);
	size = ftell(fp);
	rewind(fp);
	buf = (char*)malloc(sizeof(char)*size);
	res = fread(buf,1,size,fp);
	for(int i =0;i<4;i++){
		n[i] = buf[i] & flag;
	}
	uint32_t* p = reinterpret_cast<uint32_t*>(n);
	uint32_t result = htonl(*p);
	return result;
}
int main(int argc,char* argv[]){
	FILE* fp1 = fopen(argv[1],"r");
	FILE* fp2 = fopen(argv[2],"r");
	if(fp1==NULL || fp2==NULL){
		printf("Please checking %s and %s\n",argv[1],argv[2]);
		return 0;
	}
	uint32_t num1 = fpToUint32(fp1);
	uint32_t num2 = fpToUint32(fp2);
	
	printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n",num1,num1,num2,num2,num1+num2,num1+num2);

	return 0;
}
