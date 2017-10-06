/*
 *This Lib is for read and deal  Singal File
 *Use Function getFileInfo() will fresh File record and set a new One 
 *That for this lib bring Most Functiom Don't need More parameter
 *Only One File Information We should know in One time
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef unsigned char Byte;

typedef struct fileTrans{
	int file_size;
	Byte *file_buffer;
} fileInfo;

//int fileSize(char *faddr_fname);
fileInfo* getFileInfo(char *faddr_name);  //Start With It too Get File Info and alloc Buffer parameter set NULL can just Clean buffer
int getFileSize(char *addr_name);          //Parameter NULL Please Use It After getFileInfo  or  file name for parameter
void fileInfoClose(void);                 //free Buffer anf close File Info
void writeBufOut(char *dest);             //Got file in Buffer and Write out in disk(Enter NULL will write out"a.buffer.out")
//void CopyFile(char *source,char *dest);   //Easy Copy File Function, dest get NULL will write out "a.buffer.out"
Byte* getBuffer(void);
int checkFile(char *addr_name);           //Check File is exist
void touchFile(char *addr_name,int mode); //Creat new File // mode 0 always cover File  // mode 1 will check file exist
void rmFile(char *addr_name,int mode);    //Remove File //mode 0 not check // mode 1 will check
int catLine(char *addr_name,char *buffer,int line,int buffer_max,int catNum);  //cat line in Buffer // catNum = 0 will catch One full Line  // catNum = 1~? will cat 1~? char in a Line
