#include"libnetinfo.h"

#pragma comment(lib,"WS2_32.lib")

int main(void){
	getNetInfo(1);
	printf("IP=%s\n",printNetInfo(0));
	puts("0");
	printf("IP=%s\n",printNetInfo(1));
	puts("1");
	printf("IP=%s\n",printNetInfo(2));
	puts("2");
	printf("IP=%s\n",printNetInfo(3));
	puts("3");
	getchar();
	WSACleanup();
	return 0;
}