// tool_BWBit_Create.cpp : main project file.

#include  "stdafx.h"
#include  "tool_BWBit_Create.h"
#include  <fstream>
#include <math.h>

using namespace std;



inline int WriteBit(unsigned int nWidth,unsigned  int nHeight,
	               unsigned int xPos,unsigned int yPos, unsigned char * const BWBitBuffer )
{
	unsigned int unPos = 0;

    if( nWidth*8 < xPos )
		return XPOS_OUTOF_LIMIT;

    if( nHeight*8 < yPos )
		return YPOS_OUTOF_LIMIT;
   
	BWBitBuffer[ xPos/8+yPos*nWidth ] |= xPos%8;
	return BWBIT_OK;
}

void createCircle(unsigned int nWidth, unsigned int nHeight, unsigned int radius, float step,
	             unsigned char * const BWBitBuffer)
{

	int xPos=0,yPos=0;
	float fAngle=0.0;

	for( fAngle = 0.0 ; fAngle<2*PI; fAngle+=step )
	{
	   WriteBit(nWidth,nHeight,radius*sin(fAngle),radius*cos(fAngle),BWBitBuffer);
	}
}

void createRect(unsigned int nWidth, unsigned int nHeight,
	           unsigned int rectLeft,unsigned int rectRight,
			   unsigned int rectTop,unsigned int rectBottom,
			   unsigned char * const BWBitBuffer)
{
	unsigned int xPos=0,yPos=0;

	for( xPos = rectLeft ; xPos<rectRight; xPos++ )
	  for( yPos = rectTop ; yPos<rectBottom; yPos++ )
	   WriteBit(nWidth,nHeight,xPos,yPos,BWBitBuffer);
}

void createHLine(unsigned int nWidth, unsigned int nHeight,
	            unsigned int yPos, unsigned int nLeft,unsigned int nRight,
                unsigned char * const BWBitBuffer)
{
	unsigned int xPos;

	for( xPos = nLeft ; xPos< nRight; xPos++ )
	   WriteBit(nWidth,nHeight,xPos,yPos,BWBitBuffer);
}


int main()
{
   ofstream examplefile("example.BWBit",ios::binary);

   BWBit mBWBit;
   unsigned char uaBWBit[MAX_BWBit_BUFFER_SZIE]={0};

   mBWBit.unHeight = 32;
   mBWBit.unWidth  = 32;

   mBWBit.cBWBitTag[0] = 'B';
   mBWBit.cBWBitTag[1] = 'W';
   mBWBit.cBWBitTag[2] = 'B';
   mBWBit.cBWBitTag[3] = 'i';
   mBWBit.cBWBitTag[4] = 't';
  
   mBWBit.unCompressFlag = PLANAR;
   
   if ( !examplefile.is_open() )
   {
      return -1;
   }

   examplefile.write( (char *)&(mBWBit.unWidth), sizeof(int) );
   examplefile.write( (char *)&(mBWBit.unHeight), sizeof(int) );
   examplefile.write( (char *)&(mBWBit.cBWBitTag),sizeof(mBWBit.cBWBitTag));  
   examplefile.write( (char *)&(mBWBit.unCompressFlag), sizeof(mBWBit.unCompressFlag));

   //createCircle(mBWBit.unWidth,mBWBit.unHeight,5,0.1,uaBWBit);
   //createRect(mBWBit.unWidth,mBWBit.unHeight,0,0,128,128,uaBWBit);
   createHLine(mBWBit.unWidth,mBWBit.unHeight,0,0,128,uaBWBit);

   examplefile.write( (char *)&(uaBWBit), sizeof(uaBWBit));
   
   examplefile.close();
 
   return 0;
}
