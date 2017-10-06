#include<stdio.h>
#include<string.h>
#include<Winsock2.h>
#pragma comment(lib,"WS2_32.lib")

//If have not used WSAStartup mode choose 1  ; If You Open WSAStartup mode can type any thing
void getNetInfo(int mode);

//get Your Windows Device Have How many connected net
int howManyIpOnNet(struct hostent *pHost);

//get Your Windows Device Have How many net can use
int howManyNet(struct hostent *pHost);

char* printNetInfo(int mode);