#ifndef HSE_ZIP_FILE_PREPARE_H
#define HSE_ZIP_FILE_PREPARE_H

#define FILE_SIZE 10000 // program don't work if size <= 1000
#define FILE_NAME_SIZE 100
#define FILE_COUNT_ARR_LEN 256
#define CODE_SIZE 256

typedef struct {
  unsigned long long size;
  unsigned long long symbolsCountArr[FILE_COUNT_ARR_LEN][2]; //first -> symbol as hex (int) | second -> symbol count
  int content[FILE_SIZE];
  char fileName[FILE_NAME_SIZE];
  FILE* file;
}FileInfo;

typedef struct BIN_TREE {
  int symbol; // bit -> 0~255 -> 00~ff
//  unsigned char isSymbol; // I don't know what it is
  unsigned int symbolCount;
  unsigned char code[CODE_SIZE]; // need more
  unsigned long long priorityLvl;
  unsigned int deepLevel;
  struct BIN_TREE *left, *right, *top;
}BinTree;

void init(FileInfo* fileInfo);
void printFileAsHex(FileInfo* fileInfo);
void printFileSize(FileInfo* fileInfo);
void printFileAsText(FileInfo* fileInfo);
void printSymbolsCountArr(FileInfo* fileInfo);

void getFileSize(FileInfo* fileInfo);
void getFileContent(FileInfo* fileInfo);
void fillSymbolsCountArr(FileInfo* fileInfo);
void sortSymbolsCountArr(FileInfo* fileInfo);

#endif //HSE_ZIP_FILE_PREPARE_H
