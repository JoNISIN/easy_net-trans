#include"libfiletool.h"

fileInfo FI;

int fileSize(char *faddr_fname){
	FILE *fp;
	int counter = 0;
	Byte byteBuf;
	fp = fopen(faddr_fname,"rb");
	if(faddr_fname==NULL) {
		puts("Null File Name");
		return -1;
	}
	if(fp!=NULL){
		while(1){
			fread(&byteBuf,1,1,fp);
			if(feof(fp)) break;			
			else counter++;
		}
	}
	else{
		puts("File Open Fail");
	}
	fclose(fp);
	return counter;
}

void resetInfo(void){
	FI.file_size = 0;
	FI.file_buffer = NULL;
}

void readinBuf(char *fileif){
	if(FI.file_buffer == NULL){
		puts("NO BUFFER");
		return;
	}
	FILE *fp;
	fp = fopen(fileif,"rb");
	Byte *Bufptr = FI.file_buffer;
	if(fp == NULL) {
		puts("NO file");
		return;
	}
	while(1){
		fread(Bufptr++,1,1,fp);
		if(feof(fp)) break;
	}
}

fileInfo* getFileInfo(char *faddr_name){
	fileInfoClose();
	resetInfo();
	if(faddr_name==NULL) return NULL;
	if((FI.file_size = fileSize(faddr_name))!=-1){
		FI.file_buffer = (Byte*)malloc(FI.file_size);
		readinBuf(faddr_name);
		return &FI;
	}else{
		return NULL;
	}
}
int getFileSize(char *addr_name){
	if(addr_name==NULL)return FI.file_size;
	else return fileSize(addr_name);
}
void fileInfoClose(void){
	free(FI.file_buffer);
}

void writeBufOut(char *dest){
	if(FI.file_buffer==NULL){
		puts("Nothing in buffer");
		return;
	}
	FILE *fp;
	if(dest==NULL) fp = fopen("a.buffer.out","wb");
	else fp = fopen(dest,"wb");
	fwrite(FI.file_buffer,1,FI.file_size,fp);
}
void CopyFile(char *source,char *dest){
	if(getFileInfo(source)!=NULL)
	writeBufOut(dest);
}

Byte* getBuffer(void){
	if(FI.file_buffer==NULL) return NULL;
	else return FI.file_buffer;
}

int checkFile(char *addr_name){
	FILE *fp = fopen(addr_name,"r");
	if(fp == NULL) return 0;
	else return 1;
}

void touchFile(char *addr_name,int mode){
	if(mode==0) fopen(addr_name,"w");
	if(mode==1){
		if(!checkFile(addr_name)) fopen(addr_name,"w");
		else puts("Have Same Name File");
	}
}

void rmFile(char *addr_name,int mode){
	int len;
	char *CM_RM ="rm";
	len = strlen(CM_RM)+strlen(addr_name)+1;
	char ch;
	char *cm = (char*)malloc(sizeof(char)*len);
	memset(cm,0,len);
	sprintf(cm,"%s %s",CM_RM,addr_name);
	if(!checkFile(addr_name)) {puts("Fail Name"); return;}
	if(mode == 0) system(cm);
	if(mode == 1) {
	printf("You Will Use %s please check (Y/n)",cm);
		ch = getchar();
		fflush(stdin);
		if((ch=='y')||(ch=='Y'))system(cm);
		else return;
	}
}

int catLine(char *addr_name,char *buffer,int line,int buffer_max,int catNum){
	int i,len,count;
	FILE *fp = fopen(addr_name,"r");
	char *ptr = buffer;
	char c;
	len = (buffer_max<catNum)?buffer_max:buffer_max;
	count = 0;
	if(fp==NULL){
		puts("Not File can Catch");
		return 0;
	}
	for(i=1;i<line;){
		c = fgetc(fp);
		if(c == '\n') i++;
		if(c == EOF) return -1;
	}
	if(catNum==0){
		for(i=0;i<buffer_max;i++){
			c = fgetc(fp);
			if((c=='\n')||(c==EOF))break;
			else *ptr = c;
			ptr++;
			count++;
		}
	}
	else{
		for(i=0;i<len;i++){
			c = fgetc(fp);
			if((c=='\n')||(c==EOF))break;
			else *ptr = c;
			ptr++;
			count++;
		}
	}
	return count;
}
