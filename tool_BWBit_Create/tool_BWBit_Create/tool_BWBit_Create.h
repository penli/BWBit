
#ifndef PI
  #define PI 3.141592653
#endif

#define BIT_0  1
#define BIT_1  1
#define BIT_2  1
#define BIT_3  1
#define BIT_4  1
#define BIT_5  1
#define BIT_6  1
#define BIT_7  1

#define BWBIT_TAG_LEN             5
#define MAX_BWBit_BUFFER_SZIE     1024*10

enum{PLANAR,COMPRESSED};
enum{FILE_OPENED,FILE_CLOSED,FILE_INIT};

#define BWBIT_OK        0
#define BWBIT_FILE       -1
#define UNKNOW_FILE      -2
#define ERROR_FILE_SIZE  -3
#define XPOS_OUTOF_LIMIT -4
#define YPOS_OUTOF_LIMIT -4

typedef struct BWBit_tag
{
  unsigned int unHeight;
  unsigned int unWidth;
  char cBWBitTag[BWBIT_TAG_LEN];
  unsigned int unCompressFlag; 
}BWBit;
