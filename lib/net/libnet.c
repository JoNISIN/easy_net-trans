#include"libnet.h"
#define BUF_LEN 256

#ifndef ISDEC													
static WSADATA wsaData;											
static int iResult;												
static struct addrinfo *result = NULL,*ptr = NULL, hints;		
static SOCKET ConnectSocket = INVALID_SOCKET;					
static SOCKET ClientSocket = INVALID_SOCKET;					
static int CON_STATUS_FLAG = 0;									
static char buf[BUF_LEN];										
#define ISDEC 1													
#endif

SOCKET StartUpServer(int mode){
	#ifdef ISDEC
	ZeroMemory(&hints, sizeof (hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;
	
	CON_STATUS_FLAG = 0;

	// Initialize Winsock
	if(mode == 1)
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	
	iResult=getaddrinfo(NULL,DEFAULT_PORT,&hints,&result);
	if(iResult!=0){
		printf("getaddrinfo failed %d\n",iResult);
		WSACleanup();
		return 0;
	}
	
	SOCKET ListenSocket = INVALID_SOCKET;
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	
	iResult=bind(ListenSocket,result->ai_addr,(int)result->ai_addrlen);
	if(iResult==SOCKET_ERROR){
		printf("bind failed with error: %ld\n",WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	freeaddrinfo(result);
	
	if(listen(ListenSocket,SOMAXCONN)==SOCKET_ERROR){
		printf("Listen failed with Error : %ld\n",WSAGetLastError());
		WSACleanup();
		return 1;
	}
	
	ClientSocket = INVALID_SOCKET;
	
		puts("wait for connect...");
		if(ClientSocket=accept(ListenSocket,NULL,NULL)){
			if(ClientSocket==INVALID_SOCKET){
				printf("accept failed : %d\n",WSAGetLastError());
				closesocket(ListenSocket);
				WSACleanup();
				return 1;
			}
			else{
				//system("cls"); //Use if want to clean
				puts("Get Connect!\n");
				puts("Check Connect Stauts...");
				iResult=recv(ClientSocket,buf,(int)strlen("OK"),0);
				if(iResult>0){
					printf("Connect Status : %s\n",buf);
					CON_STATUS_FLAG=1;
				}
				else{
					printf("recv failed with error: %d\n", WSAGetLastError());
					closesocket(ClientSocket);
					WSACleanup();
					return 1;
				}
				if(CON_STATUS_FLAG==1){
					iResult=send(ClientSocket,"OK",(int)strlen("OK"),0);
					if (iResult == SOCKET_ERROR) {
						printf("shutdown failed with error: %d\n", WSAGetLastError());
						closesocket(ClientSocket);
						WSACleanup();
						return 1;
					}
				}
			}
		}
		return ClientSocket;
		#else
			puts("None Declare");
			return -1;
		#endif
}

SOCKET StartUpClient(char *net_addr,int mode){
	#ifdef ISDEC
	CON_STATUS_FLAG = 0;
	if(mode == 1)
	iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed: %d\n", iResult);
		return 1;
	}
	struct addrinfo *result = NULL,
					*ptr = NULL,
					hints;

	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	iResult = getaddrinfo(net_addr, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed: %d\n", iResult);
		WSACleanup();
		return 1;
	}
	//SOCKET ConnectSocket = INVALID_SOCKET;
	ConnectSocket = INVALID_SOCKET;
	
	ptr=result;
	ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,ptr->ai_protocol);
	if (ConnectSocket == INVALID_SOCKET) {
		printf("Error at socket(): %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}
	
	/*iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		closesocket(ConnectSocket);
		ConnectSocket = INVALID_SOCKET;
	}*/
	
	for(ptr=result; ptr != NULL ;ptr=ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, 
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	
	iResult=send(ConnectSocket,"OK",(int)strlen("OK"),0);
	
	if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }else{
		CON_STATUS_FLAG = 1;
	}
	if(CON_STATUS_FLAG == 1){
		puts("Check Connect Stauts...");
		iResult=recv(ConnectSocket,buf,(int)strlen("OK"),0);
		if(iResult>0){
			printf("Connect Status : %s\n",buf);
			CON_STATUS_FLAG=1;
		}
		else{
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
	}
	return ConnectSocket;
	#else
		puts("None Declare");
		return -1;
	#endif
}

int send_to(SOCKET sock,void *obj,int BYTE_LEN){
	int iResult;
	//Byte *BYTE_OBJ = (Byte*)malloc(BYTE_LEN);
	Byte *BYTE_OBJ;
	BYTE_OBJ = (Byte*)obj;
	iResult = send(sock,(char*)BYTE_OBJ,BYTE_LEN,0);
	//free(BYTE_OBJ);
	if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(sock);
        WSACleanup();
        return 1;
    }else{
		return 0;
	}
}

int read_from(SOCKET sock,void *obj_buf,int BYTE_LEN){
	int iResult;
	iResult = recv(sock,(char*)obj_buf,BYTE_LEN,0);
	if(!(iResult>0)){
		printf("recv failed with error: %d\n", WSAGetLastError());
		closesocket(sock);
		WSACleanup();
		return 1;
	}else{
		return 0;
	}
}
