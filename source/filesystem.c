
#include "filesystem.h"
FS_archive sdmcArchive;

static inline void unicodeToChar(char* dst, u16* src, int max)
{
	if(!src || !dst)return;
	int n=0;
	while(*src && n<max-1){*(dst++)=(*(src++))&0xFF;n++;}
	*dst=0x00;
}

void initFilesystem(void)
{
	fsInit();
	sdmcInit();
}

void exitFilesystem(void)
{
	sdmcExit();
	fsExit();
}

void openSDArchive()
{
	sdmcArchive=(FS_archive){0x00000009, (FS_path){PATH_EMPTY, 1, (u8*)""}};
	FSUSER_OpenArchive(NULL, &sdmcArchive);
}

void closeSDArchive()
{
	FSUSER_CloseArchive(NULL, &sdmcArchive);
}

bool fileExists(char* path, FS_archive* archive)
{
	if(!path || !archive)return false;

	Result ret;
	Handle fileHandle;

	ret=FSUSER_OpenFile(NULL, &fileHandle, *archive, FS_makePath(PATH_CHAR, path), FS_OPEN_READ, FS_ATTRIBUTE_NONE);
	if(ret!=0)return false;

	ret=FSFILE_Close(fileHandle);
	if(ret!=0)return false;

	return true;
}


void scanDirectory(char* path,char* array[],int *size)
{
	if(!path)return;

	Handle dirHandle;
        int i=0;
	FS_path dirPath=FS_makePath(PATH_CHAR, path);
	FSUSER_OpenDirectory(NULL, &dirHandle, sdmcArchive, dirPath);
	
	static char fullPath[1024];
	u32 entriesRead;
	do
	{
		static FS_dirent entry;
		memset(&entry,0,sizeof(FS_dirent));
		entriesRead=0;
		FSDIR_Read(dirHandle, &entriesRead, 1, &entry);
		if(entriesRead)
		{
			strncpy(fullPath, path, 1024);
			int n=strlen(fullPath);
			unicodeToChar(&fullPath[n], entry.name, 1024-n);
                        n=strlen(fullPath);
                        if(n>5 && !strcmp(".txt", &fullPath[n-4])){
                            array[i]=malloc(n*sizeof(char));
                            strcpy(array[i],fullPath);
                            i++;
                        }
			
		}
	}while(entriesRead);
        *size=i;
	FSDIR_Close(dirHandle);
        
}
