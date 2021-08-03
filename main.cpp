/* *****************************************************************************
 * Created by Lee Patterson Monday August 2, 2021
 *
 * Copyright 2021, Lee Patterson <https://github.com/abathur8bit>
 *
 * You may use and modify at will. Please credit me in the source.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 * ******************************************************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>

void dump(int ch);
char* readFile(const char* filename);
long fileSize(const char* filename);
bool writeFile(const char* filename,char* buffer,long size,bool verbose);

bool unix2(const char* input, const char* output, bool verbose);

void dump(int ch) {
    printf("%02X (%d)", ch, ch);
    if(isprint(ch)) {
        printf(" %c", ch);
    } else {
        printf(" .");
    }
}

char* readFile(const char* filename) {
    FILE *fp = fopen(filename, "rb");       //read in binary mode
    if(!fp) return NULL;
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    char* dest = (char*)malloc(size);
    fread(dest,size,1,fp);
    return dest;
}

long fileSize(const char* filename) {
    FILE *fp;
    fp = fopen(filename, "rb");       //read in binary mode
    if(!fp) return NULL;
    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    fclose(fp);
    return size;
}

bool writeFile(const char* filename,char* buffer,long size,bool verbose) {
    char ch;
    long index = 0;
    FILE *fp = fopen(filename, "wb");     //write in binary mode
    if(fp) {
        if(verbose) {
            printf("Stripping out CR (0x0D) from CRLF (0x0D 0x0A) \n");
        }
        while(index < size) {
            ch = *(buffer+index);
            index++;
            if(verbose) {
                printf("in : ");
                dump(ch);
                if(ch==0x0D) {
                    printf("<stripped>");
                }
                printf("\n");
            }
            if(ch!=0x0D) {
                if(verbose) {
                    printf("out: ");
                    dump(ch);
                    printf("\n");
                }
                fputc(ch, fp);
            }
        }
    }
    fflush(fp);
    fclose(fp);

    return true;
}

bool unix2(const char* input, const char* output, bool verbose) {
    long size = fileSize(input);
    if(-1 == size) return false;
    char* inFile = readFile(input);
    if(!inFile) return false;
    return writeFile(output,inFile,size,verbose);
}

int main(int argc,char* argv[]) {
    if(argc>1) {
        bool verbose = false;
        char *source=NULL,*dest=NULL;
        for(int i=1; i<argc; i++) {
            if(strcmp(argv[i],"-v") == 0) {
                verbose = true;
            } else if(!source) {
                source = argv[i];
            } else if(!dest) {
                dest = argv[i];
            }
        }
        if(!dest) dest = source;
        if(unix2(source,dest,verbose)) {
            printf("File written\n");
        } else {
            printf("File error %s\n",strerror(errno));
        }
    } else {
        printf("dos2unix by Lee Patterson http://axorion.com\n");
        printf("Strips CR (0x0D) from text files.\n");
        printf("If you don't provide a destination file, the source will be overwritten.\n");
        printf("\n");
        printf("Usage: dos2unix [-v] source [destination]\n");
        printf(" -v = verbose\n");
    }
    return 0;
}

