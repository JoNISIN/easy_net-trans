#include"libnetinfo.h"

int nLen=256;
char hostname[20];
struct hostent *pHost;
struct in_addr inAddr;
int netLen = 0;
WSADATA wsaData;

void getNetInfo(int mode){
	if(mode==1){
		if(WSAStartup(MAKEWORD(2,2),&wsaData)==SOCKET_ERROR)  
		{  
			return; 
		}
	}
	gethostname(hostname,nLen);
	pHost = gethostbyname(hostname);
	netLen = howManyIpOnNet(pHost);
}

int howManyIpOnNet(struct hostent *pHost){
	int i;
	for(i = 0;i<pHost->h_length;i++){
		if(pHost->h_addr_list[i]==NULL) return i;
	}
}

int howManyNet(struct hostent *pHost){
	return pHost->h_length;
}

char* printNetInfo(int mode){
	if(mode >= netLen) return NULL;
	if((pHost->h_addr_list[mode])!=NULL){
		 memcpy(&inAddr,pHost->h_addr_list[mode],4); 
		return inet_ntoa(inAddr);
	}
	else return NULL;
}