/* 
 * File:   filesystem.h
 * Author: Silvermoon
 *
 * Created on 6 octobre 2015, 19:39
 */

#ifndef FILESYSTEM_H
#define	FILESYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
extern FS_archive sdmcArchive;

//system stuff
void initFilesystem(void);
void exitFilesystem(void);

void openSDArchive();
void closeSDArchive();

//general fs stuff
int loadFile(char* path, void* dst, FS_archive* archive, u64 maxSize);
bool fileExists(char* path, FS_archive* archive);

//menu fs stuff
void scanDirectory(char* path,char* array[],int *size);


#ifdef	__cplusplus
}
#endif

#endif	/* FILESYSTEM_H */

