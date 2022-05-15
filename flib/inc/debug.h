#ifndef _DEBUG_H
#define _DEBUG_H
#include "stdio.h"



#define DEEBUG          1
#define DEFDEBUG        1


#define EDEBUG_LOCATION   {if(DEEBUG) printf("DEBUG %s,  %d\r\n", __func__, __LINE__);}


#define DEBUG(fmt,arg...)          {if(DEFDEBUG) printf("DEBUG "fmt"\r\n",##arg);else;}


#endif /* _DEBUG_H */
