
#ifndef _FILE_H_
#define _FILE_H_
typedef struct dl {
struct Directory *dir;
struct dl *next; } dl;

typedef struct fl {
struct File *fis;
struct fl *next;
} fl;

typedef struct Directory {
char *name;
dl *director;
fl *file;
struct Directory *parentDir;
} Directory;

typedef struct File {
char *name;
int size;
char *data;
Directory *dir;
} File;
#endif
