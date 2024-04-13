#ifndef FINAL_C_PROJECT_STRINGTOOLBOX_H
#define FINAL_C_PROJECT_STRINGTOOLBOX_H


#define MAX_STR_LEN 256


char*	getStrExactName(const char* msg);
char*	myGets(char* buffer, int size, FILE* fp);
char*	getDynStr(char* str);
char* getStrExactNameFromFile(const char* msg, FILE* fp);


#endif //FINAL_C_PROJECT_STRINGTOOLBOX_H
