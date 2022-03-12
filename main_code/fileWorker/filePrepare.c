#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filePrepare.h"

// Step One

void getFileSize(FileInfo* fileInfo);
void getFileContent(FileInfo* fileInfo);
void fillSymbolsCountArr(FileInfo* fileInfo);
void sortSymbolsCountArr(FileInfo* fileInfo);
//void initTree(FileInfo* fileInfo); // not created yet

void init(FileInfo* fileInfo) {
  getFileSize(fileInfo);
  getFileContent(fileInfo);
  fillSymbolsCountArr(fileInfo);
  sortSymbolsCountArr(fileInfo);
//  initTree(fileInfo);
}

void getFileSize(FileInfo* fileInfo) {
  fileInfo->size = 0;
  fileInfo->file = fopen("../testData/text_20byte.txt", "rb");
  if (fileInfo->file == 0) {
    perror("Open error");
    exit(1);
  }
  fseek(fileInfo->file, 0, SEEK_END);
  fileInfo->size = ftell(fileInfo->file);
  fseek(fileInfo->file, 0, SEEK_SET);
  fclose(fileInfo->file);
}

void getFileContent(FileInfo* fileInfo) {
  fileInfo->file = fopen("../testData/text_20byte.txt", "rb");
  unsigned long long readIndex = 0;
  int buffer = getc(fileInfo->file);
  while (buffer != EOF) {
    fileInfo->content[readIndex] = buffer; // pls no write (char)buffer this is break all. we should use int
    printf("%d\t", fileInfo->content[readIndex]);
    buffer = fgetc(fileInfo->file);
    readIndex++;
  }
  fclose(fileInfo->file);
  fileInfo->content[readIndex] = 0;
}

void printFileSize(FileInfo* fileInfo) {
  printf("Size of file: %llu bytes.\n", fileInfo->size);
}

void printFileAsHex(FileInfo* fileInfo) {
  for (unsigned long long i = 0; i < fileInfo->size; i++) {
    if (i % 5 == 0 && i != 0) {
      printf("\n");
    }
    printf("0x%x -> %c\t", fileInfo->content[i], fileInfo->content[i]);
  }
  printf("\n");
}

void printFileAsText(FileInfo* fileInfo) {
  for (int i = 0; fileInfo->content[i] != 0 ; ++i) {
    printf("%c", (char)fileInfo->content[i]);
  }
  printf("\n");
}

void fillSymbolsCountArr(FileInfo* fileInfo) {
  unsigned long long bufferArr[FILE_COUNT_ARR_LEN] = {0};
  for (unsigned long long i = 0; i < fileInfo->size; ++i) {
    bufferArr[fileInfo->content[i]]++;
  }
  for (int i = 0, j = 0; i < FILE_COUNT_ARR_LEN; ++i) {
    if (bufferArr[i] != 0) {
      fileInfo->symbolsCountArr[j][0] = i;
      fileInfo->symbolsCountArr[j][1] = bufferArr[i];
      j++;
    }
  }
}

void printSymbolsCountArr(FileInfo* fileInfo) {
  for (int i = 0; i < FILE_COUNT_ARR_LEN; ++i) {
    if (!(i%8)) {
      printf("\n");
    }
    printf("0x%x -> %llu\t", (int)fileInfo->symbolsCountArr[i][0], fileInfo->symbolsCountArr[i][1]);
  }
}

void sortSymbolsCountArr(FileInfo* fileInfo) {
  unsigned long long buffer[2] = {0};
  for (int i = 0; i < FILE_COUNT_ARR_LEN-1;) {
    if (fileInfo->symbolsCountArr[i][1] > fileInfo->symbolsCountArr[i+1][1] && fileInfo->symbolsCountArr[i+1][1] != 0) {
      buffer[0] = fileInfo->symbolsCountArr[i][0]; buffer[1] = fileInfo->symbolsCountArr[i][1];
      fileInfo->symbolsCountArr[i][0] = fileInfo->symbolsCountArr[i+1][0]; fileInfo->symbolsCountArr[i][1] = fileInfo->symbolsCountArr[i+1][1];
      fileInfo->symbolsCountArr[i+1][0] = buffer[0]; fileInfo->symbolsCountArr[i+1][1] = buffer[1];
      i = 0;
    } else {
      i++;
    }
  }
}

int getSymbolsCountArrLen(FileInfo* fileInfo) {
  int len = 0;
  while (fileInfo->symbolsCountArr[len][1]) {len++;}
  return len;
}
