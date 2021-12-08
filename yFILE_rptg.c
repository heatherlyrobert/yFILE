/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"


char
yfile_vers_status          (char *a_list)
{
   snprintf (a_list, LEN_FULL, "version %c [%-4.4s] [%-60.60s]", myFILE.f_control, myFILE.f_vernum, myFILE.f_vertxt);
   return 0;
}
