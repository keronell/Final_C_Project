#ifndef FINAL_C_PROJECT_FILEMANAGER_H
#define FINAL_C_PROJECT_FILEMANAGER_H

int	 writeStringToFile(char* str, FILE* fp,const char* msg);
int	 writeCharsToFile(char* arr,int size, FILE* fp, const char* msg);
int	 writeIntToFile(int val, FILE* fp, const char* msg);

char* readStringFromFile(FILE* fp,const char* msg);
int	 readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int	  readIntFromFile(int* val, FILE* fp, const char* msg);
char* getStrFromFile(FILE* fp);

#endif //FINAL_C_PROJECT_FILEMANAGER_H
