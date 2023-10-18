#ifndef __built_in_h
#define __built_in_h

//--- 8-bit
#define Lo(param) ((char *)&param)[0]
#define Hi(param) ((char *)&param)[1]
#define Higher(param) ((char *)&param)[2]
#define Highest(param) ((char *)&param)[3]

#define lo(param) ((char *)&param)[0]
#define hi(param) ((char *)&param)[1]
#define higher(param) ((char *)&param)[2]
#define highest(param) ((char *)&param)[3]

//--- 16-bit
#define LoWord(param) ((unsigned *)&param)[0]
#define HiWord(param) ((unsigned *)&param)[1]

#define loword(param) ((unsigned *)&param)[0]
#define hiword(param) ((unsigned *)&param)[1]

//--- 32-bit
#define HigherWord(param) ((unsigned *)&param)[2]
#define HighestWord(param) ((unsigned *)&param)[3]

#define higherword(param) ((unsigned *)&param)[2]
#define highestword(param) ((unsigned *)&param)[3]

#define LoDWord(param) ((unsigned long *)&param)[0]
#define HiDWord(param) ((unsigned long *)&param)[1]

#define lodword(param) ((unsigned long *)&param)[0]
#define hidword(param) ((unsigned long *)&param)[1]

#endif    //__built_in_h
