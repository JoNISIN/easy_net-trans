#include"main.h"

#define VER "beta 0.5"
#define PN "EzTrans"

#define GOEND() goto END_PROC
#define ERRFEW() goto TOO_FEW
#define NAME_MAX 50
#define BUF_BLOCK_MAX 524288  /*512*1024 = 5MB*/

#define CLEAN_NBUF() memset(fnamebf,0,NAME_MAX)
#define CLEAN_PBUF() memset(PAGE_BUFFER,0,BUF_BLOCK_MAX)

Byte PAGE_BUFFER[BUF_BLOCK_MAX] = {0};

int main(int argc , char *argv[]){
	int i,status;
	int lenBuf=0;
	SOCKET sock;
	FILE *fp = NULL;
	unsigned char *Buffer=NULL;
	char fnamebf[NAME_MAX] = {0};
	Byte *getbf = NULL;
	WSADATA wsaData;
	status=WSAStartup(MAKEWORD(2,2), &wsaData);
	if (status != 0) {
		printf("WSAStartup failed: %d\n", status);
		WSACleanup();
		return 1;
	}
	if(argc>1){
		if((strlen(argv[1])==2)&&(argv[1][0]=='-')){
			switch(argv[1][1]){
				case 'f':
				if(argc < 3) ERRFEW();
				getFileInfo(argv[2]);
				printf("%s size = %d\n",argv[2],getFileSize(NULL));
				GOEND();
				case 'i':
				printf("Getting Network on your device...");
				getNetInfo(0);
				printf("OK\n");
				puts("List All Ip...");
				for(i=0;printNetInfo(i)!=NULL;i++) {
					printf("Address (%d) = %s \n",i,printNetInfo(i));
				}
				GOEND();
				case 's':
				if(argc < 4) ERRFEW();
				else{
					printf("Linking to %s ...\n",argv[2]);
					sock=StartUpClient(argv[2],0);
					if(sock==1) GOEND();
					printf("Loading File %s ...",argv[3]);
					if(getFileInfo(argv[3])==NULL){
						puts("Fail");
						GOEND();
					}else{
						puts("ok");
						printf("File Name : %s\n",argv[3]);
						lenBuf=getFileSize(NULL);
						printf("File Size : %d\n",lenBuf);
					}
					printf("Sending File...\n");
					send_to(sock,(void*)&lenBuf,sizeof(int));
					send_to(sock,getBuffer(),lenBuf);
					send_to(sock,argv[3],strlen(argv[3]));
					//send_to(sock,getBuffer,lenBuf); //神奇的結果我了解了C的真理
					puts("Complete !");
					getchar();
					GOEND();
				}
				case 'g':/*12-13新增一個參數版本*/
				if(argc < 2) ERRFEW();
				else{
					CLEAN_NBUF();//Clean Buffer
					printf("Getting Network on your device...");
					getNetInfo(0);
					printf("OK\n");
					puts("IP on your Device...");
					for(i=0;printNetInfo(i)!=NULL;i++) {
						printf("Network(%d) Ip = %s \n",i,printNetInfo(i));
					}
					puts("");
					printf("Prepare to get File ...\n");
					sock=StartUpServer(0);
					puts("");
					if(sock==1) GOEND();
					printf("Getting File %s ...\n",(argc == 3)?argv[2]:" ");
					read_from(sock,(void*)&lenBuf,sizeof(int));
					printf("Get Size = %d\n",lenBuf);
					Buffer = (Byte*)malloc(sizeof(Byte)*lenBuf);
					memset(Buffer,'\0',lenBuf);
					read_from(sock,(void*)Buffer,lenBuf);
					read_from(sock,(void*)fnamebf,NAME_MAX);
					if(argc == 3) {
						CLEAN_NBUF();
						sprintf(fnamebf,"%s",argv[2]);
					}
					printf("Get File...%s\n",fnamebf);
					fp = fopen(fnamebf,"wb");
					fwrite(Buffer,1,lenBuf,fp);
					fflush(fp);
					puts("Complete !");
					fclose(fp);
					getchar();
					free(Buffer);
					GOEND();
				}
				case 'h':
				puts("Simple Transport File in two Computer\n");
				puts("Common to use :");
				printf("Send File => EzTrans -s [IP address] [file_name]\n");
				printf(" Get File => EzTrans -g\n");
				printf("      or  => EzTrans -g [dest_file_name]\n\n");
				puts("OptionFor Program :");
				puts("	-h  			-->Help For This program");
				puts("	-v  			-->Version Info for this program");
				puts("	-s  			-->Send FIle witf program");
				puts("	-f [file_name]  -->File Size");
				puts("	-i  			-->Network Info");
				puts("");
				GOEND();
				case 'v':
				puts("EzTrans --  for Ez Connect\n");
				printf("Version : %s\n",VER);
				puts("");
				GOEND();
			default:
			puts("Error Option...");
			puts("Used \'-h\' Parameter to check option...\n");
			GOEND();
			}
		}
	}
	else{
		puts("Well Come to Used this program !");
		getNetInfo(0);
		printf("Main Ip For your Device : %s \n\n",printNetInfo(0));
TOO_FEW:
		puts("Too few parameter...");
		puts("Used \'-h\' to check option...\n");
		GOEND();
		return 0;
	}
END_PROC:
	if(fp!=NULL) fclose(fp);
	puts("End process...");
	closesocket(sock);
    WSACleanup();
	return 0;
}