/* =============================================================================
  test VDP SPRITE MSXROM Library
  Version: 1.2 
  Author: mvac7
  Architecture: MSX
  Format: ROM
  Programming language: C
    
History of versions:
 - v1.2 (19/04/2018) Current version
 - v1.1 ( 2/03/2017)    
 - v1.0 (25/02/2017) First version
============================================================================= */

#include "../include/newTypes.h"
#include "../include/msxBIOS.h"
#include "../include/msxSystemVars.h"

#include "../include/VDP_TMS9918A.h"
#include "../include/VDP_SPRITES.h"




#define  HALT __asm halt __endasm   //wait for the next interrupt




//  definition of functions  ---------------------------------------------------
void WAIT(uint cicles);
char INKEY();

void CLS();

void VPRINT(byte column, byte line, char* text);  //print in screen 1 or 2
void VPOKEARRAY(uint vaddr, char* text);

void LOCATE(char x, char y);
void PRINT(char* text);

char PEEK(uint address);
uint PEEKW(uint address);

void setFont();

void setSpritesPatterns();
void showSprites(char offset);

void testSPRITES();
void testSpritePosition();
void testSpriteColor();
void testSpritePattern();
void testSpriteVisible();




// constants  ------------------------------------------------------------------

const char text01[] = "Test SDCC SPRITES MSXROM Lib"; 
const char text02[] = "           v1.2 (19/04/2018)";


const char sprcol[8]={12,2,3,7,6,8,9,14};

const char SPRITE_DATA[]={
60,66,165,129,165,153,66,60,
60,126,219,255,255,219,102,60,
108,254,254,254,124,56,16,0,
16,56,124,254,124,56,16,0,
16,56,84,254,84,16,56,0,
16,56,124,254,254,16,56,0,
0,0,0,24,24,0,0,0,
255,255,255,231,231,255,255,255,
15,31,61,63,123,124,191,191,159,239,111,31,15,5,5,29,
192,224,96,192,64,128,128,132,134,222,192,192,128,0,0,192,
5,7,26,46,111,91,92,91,95,88,111,45,22,2,2,6,
64,192,184,212,212,106,234,106,234,106,212,212,248,64,64,96,
3,7,79,207,77,79,44,30,63,63,63,63,31,2,2,6,
192,226,230,226,162,244,56,124,254,254,254,252,248,64,64,96,
5,30,63,111,87,110,63,0,7,5,7,4,6,3,2,6,
96,248,244,234,118,190,124,0,224,96,224,32,96,192,64,96,
5,7,31,63,127,127,127,125,127,127,120,63,31,4,4,12,
64,192,240,248,252,252,252,124,252,252,60,248,240,64,64,96,
7,31,63,63,127,113,127,127,127,126,62,63,31,7,2,6,
224,248,252,252,254,142,254,254,254,126,124,252,248,224,64,96,
0,7,31,63,127,113,255,255,123,124,63,31,7,2,2,6,
0,224,248,252,254,142,255,255,222,62,252,248,224,64,64,96,
5,30,63,111,87,110,63,0,7,5,7,4,6,3,2,6,
96,248,244,234,118,190,124,0,224,96,224,32,96,192,64,96
};


//coordinate tables with a circular route 
const char posX[]={
0xAA,0xAA,0xAA,0xAA,0xAA,0xA9,0xA9,0xA9,0xA9,0xA8,0xA8,0xA7,0xA7,0xA6,0xA6,0xA5,
0xA4,0xA4,0xA3,0xA2,0xA1,0xA0,0x9F,0x9E,0x9D,0x9C,0x9B,0x9A,0x99,0x98,0x96,0x95,
0x94,0x93,0x91,0x90,0x8E,0x8D,0x8B,0x8A,0x88,0x87,0x85,0x84,0x82,0x80,0x7F,0x7D,
0x7B,0x7A,0x78,0x76,0x74,0x73,0x71,0x6F,0x6D,0x6B,0x6A,0x68,0x66,0x64,0x62,0x60,
0x5F,0x5D,0x5B,0x59,0x57,0x55,0x53,0x52,0x50,0x4E,0x4C,0x4A,0x49,0x47,0x45,0x43,
0x42,0x40,0x3E,0x3D,0x3B,0x3A,0x38,0x36,0x35,0x33,0x32,0x30,0x2F,0x2E,0x2C,0x2B,
0x29,0x28,0x27,0x26,0x25,0x23,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,0x1C,0x1B,0x1A,
0x19,0x19,0x18,0x18,0x17,0x16,0x16,0x16,0x15,0x15,0x15,0x14,0x14,0x14,0x14,0x14,
0x14,0x14,0x14,0x14,0x14,0x15,0x15,0x15,0x16,0x16,0x16,0x17,0x18,0x18,0x19,0x19,
0x1A,0x1B,0x1C,0x1C,0x1D,0x1E,0x1F,0x20,0x21,0x22,0x23,0x25,0x26,0x27,0x28,0x29,
0x2B,0x2C,0x2E,0x2F,0x30,0x32,0x33,0x35,0x36,0x38,0x39,0x3B,0x3D,0x3E,0x40,0x42,
0x43,0x45,0x47,0x49,0x4A,0x4C,0x4E,0x50,0x52,0x53,0x55,0x57,0x59,0x5B,0x5D,0x5F,
0x60,0x62,0x64,0x66,0x68,0x6A,0x6B,0x6D,0x6F,0x71,0x73,0x74,0x76,0x78,0x7A,0x7B,
0x7D,0x7F,0x80,0x82,0x84,0x85,0x87,0x88,0x8A,0x8B,0x8D,0x8E,0x90,0x91,0x93,0x94,
0x95,0x96,0x98,0x99,0x9A,0x9B,0x9C,0x9D,0x9E,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,0xA4,
0xA5,0xA6,0xA6,0xA7,0xA7,0xA8,0xA8,0xA9,0xA9,0xA9,0xA9,0xAA,0xAA,0xAA,0xAA,0xAA};

  
const char posY[]={
0x5F,0x61,0x63,0x65,0x66,0x68,0x6A,0x6C,0x6E,0x6F,0x71,0x73,0x75,0x77,0x78,0x7A,
0x7C,0x7E,0x7F,0x81,0x82,0x84,0x86,0x87,0x89,0x8A,0x8C,0x8D,0x8F,0x90,0x92,0x93,
0x94,0x95,0x97,0x98,0x99,0x9A,0x9B,0x9C,0x9E,0x9F,0x9F,0xA0,0xA1,0xA2,0xA3,0xA4,
0xA4,0xA5,0xA6,0xA6,0xA7,0xA7,0xA8,0xA8,0xA9,0xA9,0xA9,0xA9,0xAA,0xAA,0xAA,0xAA,
0xAA,0xAA,0xAA,0xAA,0xAA,0xA9,0xA9,0xA9,0xA8,0xA8,0xA8,0xA7,0xA7,0xA6,0xA5,0xA5,
0xA4,0xA3,0xA3,0xA2,0xA1,0xA0,0x9F,0x9E,0x9D,0x9C,0x9B,0x9A,0x99,0x97,0x96,0x95,
0x94,0x92,0x91,0x8F,0x8E,0x8D,0x8B,0x8A,0x88,0x86,0x85,0x83,0x82,0x80,0x7E,0x7D,
0x7B,0x79,0x77,0x76,0x74,0x72,0x70,0x6F,0x6D,0x6B,0x69,0x67,0x65,0x64,0x62,0x60,
0x5E,0x5C,0x5A,0x59,0x57,0x55,0x53,0x51,0x4F,0x4E,0x4C,0x4A,0x48,0x47,0x45,0x43,
0x41,0x40,0x3E,0x3C,0x3B,0x39,0x38,0x36,0x34,0x33,0x31,0x30,0x2F,0x2D,0x2C,0x2A,
0x29,0x28,0x27,0x25,0x24,0x23,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,0x1B,0x1B,0x1A,
0x19,0x19,0x18,0x17,0x17,0x16,0x16,0x16,0x15,0x15,0x15,0x14,0x14,0x14,0x14,0x14,
0x14,0x14,0x14,0x14,0x15,0x15,0x15,0x15,0x16,0x16,0x17,0x17,0x18,0x18,0x19,0x1A,
0x1A,0x1B,0x1C,0x1D,0x1E,0x1F,0x1F,0x20,0x22,0x23,0x24,0x25,0x26,0x27,0x29,0x2A,
0x2B,0x2C,0x2E,0x2F,0x31,0x32,0x34,0x35,0x37,0x38,0x3A,0x3C,0x3D,0x3F,0x40,0x42,
0x44,0x46,0x47,0x49,0x4B,0x4D,0x4F,0x50,0x52,0x54,0x56,0x58,0x59,0x5B,0x5D,0x5F};



char _LineLength;  //sprites per line. TMS9918=4; V9938=8



// Functions -------------------------------------------------------------------


//
void main(void)
{
  SCREEN(1);
  COLOR(15,4,5);
  
__asm
  ld   HL,#0xF3B0 ;LINLEN system variable
  ld   A,#32
  ld   (HL),A     ;WIDTH(32)  
__endasm;
  
  LOCATE(2,10);
  PRINT(text01);
  LOCATE(2,11);
  PRINT(text02);
  
  INKEY();
  
//------------------------------------------------------------------------------   
  SCREEN(2);
  CLS();
  setFont();
  
  VPRINT(0,0,"screen 2 (G2)");  
  
  _LineLength=4; 
  testSPRITES();


  
//---------------------------------------------------------------------only MSX2
  if (PEEK(MSXVER)>0)
  {
    SCREEN(4);  //G4 V9938 mode
    CLS();
    setFont();  
    
    VPRINT(0,0,"screen 4 (G3)");
    
    _LineLength=8; 
    testSPRITES();  
  }  
//------------------------------------------------------------------------------  
  

  
//END --------------------------------------------------------------------------  
  
  //COLOR(15,4,4);
  SCREEN(1);
  
  VPRINT(0,0,"End of the test...");
  WAIT(30*10);
  
     

//EXIT MSXDOS
/*  screen(0);
    
__asm
 	ld b,4(ix)
	ld c,#0x62
	call 5 
__endasm;*/
//end EXIT

}




/* =============================================================================
One character input (waiting)
============================================================================= */
char INKEY() __naked
{
__asm
  push IX
  ld   IX,#0
  add  IX,SP  

  call CHGET

  ld   L,A
  pop  IX
  ret
__endasm;
}



// Generates a pause in the execution of n interruptions.
// PAL: 50=1second. ; NTSC: 60=1second. 
void WAIT(uint cicles)
{
  uint i;
  for(i=0;i<cicles;i++) HALT;
}



void CLS()
{
  FillVRAM (BASE10, 0x300, 32);
}



//print in screen 1 or 2
void VPRINT(byte column, byte line, char* text)
{
  uint vaddr = BASE10 + (line*32)+column; // calcula la posicion en la VRAM
  VPOKEARRAY(vaddr, text);
}



void VPOKEARRAY(uint vaddr, char* text)
{
  while(*(text)) VPOKE(vaddr++,*(text++));
}



/* =============================================================================
   Set a position the cursor in to the specified location
   Posiciona el cursor hasta la ubicacion especificada
   x(byte) - column (0 to 31 or 39)
   y(byte) - line   (0 to 23)
============================================================================= */
void LOCATE(char x, char y) __naked
{
x;y;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   A,4(IX) ;x
  inc  A       ;incrementa las posiciones para que se situen correctamente en la pantalla
  ld   H,A
  ld   A,5(IX) ;y
  inc  A
  ld   L,A   
  call POSIT
  
  pop  IX
  ret
__endasm;

}



/* =============================================================================
   Print a text in screen
============================================================================= */
void PRINT(char* text) __naked
{ 
text;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(ix)
  ld   H,5(ix)
  
nextCHAR:  
  ld   A,(HL)
  or   A
  jr   Z,ENDnext   
  call CHPUT //Displays one character (BIOS)
  inc  HL
  jr   nextCHAR
  
ENDnext:  
  pop  IX
  ret
__endasm; 
}



char PEEK(uint address) __naked
{
  address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(IX)
  ld   H,5(IX)
  
  ld   L,(HL)
  
  pop  IX
  ret  
__endasm;
}



uint PEEKW(uint address) __naked
{
  address;
__asm
  push IX
  ld   IX,#0
  add  IX,SP
  
  ld   L,4(ix)
  ld   H,5(ix)
  ld   E,(HL)
  inc  HL
  ld   D,(HL)
  ex   DE,HL  
  
  pop  IX
  ret  
__endasm;
}




void setFont()
{
  uint ROMfont = PEEKW(CGTABL);

  CopyToVRAM(ROMfont,BASE12,0x800);        //MSX font pattern
  CopyToVRAM(ROMfont,BASE12+0x800,0x800);  //MSX font pattern
  CopyToVRAM(ROMfont,BASE12+0x1000,0x800); //MSX font pattern
  FillVRAM(BASE11,0x1800,0xF4);            //colors

  return;
}




// TEST SPRITES  ###############################################################
void testSPRITES()
{
  char posY=2;
  char key;
  
  setSpritesPatterns();
  
  VPRINT(0,posY++, "-----------------Basic Functions");
  
  // sprites 8x8
  //setupSprites(0,false); //16x16 no zoom
  VPRINT(0,posY++, "SetSpritesSize(0) SPRITES 8x8");
  SetSpritesSize(0);
  SetSpritesZoom(false);  
  showSprites(0);
  WAIT(50);
  
  // test sprites 16x16
  //setupSprites(1,false);
  VPRINT(0,posY++, "SetSpritesSize(1) SPRITES 16x16");
  SetSpritesSize(1);
  showSprites(2);
  WAIT(50);
 
  // test sprites 16x16 + zoom  
  //setupSprites(1,true);
  VPRINT(0,posY++, "SetSpritesZoom(true) SPRITES x2");
  SetSpritesZoom(true);
  WAIT(50);
  
  //test clear sprites data
  VPRINT(0,posY++, "ClearSprites()");
  ClearSprites();
  WAIT(100);
  
  setSpritesPatterns();
  VPRINT(0,posY++, "PUTSPRITE(plane,x,y,color,nSPR)");
  showSprites(2);                                                                           
 
  WAIT(50);
  posY++;
  VPRINT(0,posY++, "--------------Extended Functions");
  
  VPRINT(0,posY++, "SetSpriteVisible(plane,state)");
  testSpriteVisible();
  
  VPRINT(0,posY++, "SetSpritePattern(plane,nSPR)"); 
  testSpritePattern();
  
  VPRINT(0,posY++, "SetSpriteColor(plane,color)"); 
  testSpriteColor();
  
  VPRINT(0,posY++, "SetSpritePosition(plane,x,y)");
  testSpritePosition();
  
  WAIT(50);
  
  VPRINT(0,posY++, "SetEarlyClock(plane)");
  SetEarlyClock(7);
  WAIT(50);
  
  VPRINT(0,posY++, "UnsetEarlyClock(plane)");
  UnsetEarlyClock(7);
  WAIT(50);
  
  posY+=3;
  VPRINT(0,posY, "Press any key.");
  LOCATE(12,posY);
  key = INKEY();
  
  return;
}




// Copy sprites data from memory to VRAM
void setSpritesPatterns()
{
  HALT;
  CopyToVRAM((uint) SPRITE_DATA,BASE14,32*14);
}



// TEST PUTSPRITE  #############################################################
void showSprites(char offset)
{
  char X=0,Y=3;
  char i=0;
  
  for(i=0;i<8;i++)
  {
    PUTSPRITE(i, X*32, Y*32, sprcol[i], i+offset);
    X++;
    if(X==_LineLength)
    {
      X=0;
      Y++;
    }
  }

  return;
}



// TEST SETSPRITEVISIBLE  ######################################################
void testSpriteVisible()
{
  byte i,o;

  SetSpriteVisible(0,false);
  
  for(i=0;i<8;i++)
  {
    for(o=0;o<8;o++)
    {
      if (o==i) SetSpriteVisible(o,true);
      else SetSpriteVisible(o,false);  
    }
    WAIT(25);  
  }  
  
  return;
}





// TEST SETSPRITEPATTERN  ######################################################
void testSpritePattern()
{
  byte i;

  
  for(i=2;i<10;i++)
  {
    SetSpritePattern(7, i);
    WAIT(25);  
  }  
  
  return;
}



// TEST SETSPRITECOLOR  ########################################################
void testSpriteColor()
{
  byte i;

  
  for(i=0;i<16;i++)
  {
    SetSpriteColor(7, i);
    WAIT(25);  
  }  
  
  return;
}



// TEST SETSPRITEPOSITION  #####################################################
void testSpritePosition()
{
  uint i=0;
  uint posT = 0;

  SetSpriteColor(7, 8);  

  for(i=0;i<640;i++)
  {
    HALT;
    SetSpritePosition(7, posX[posT], posY[posT]-32);
    posT++;
    if(posT>255) posT=0;  
  }
  
  return;
}








