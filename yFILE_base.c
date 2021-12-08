/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



tMY         myFILE;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yFILE_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yFILE_version           (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yFILE_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yFILE_ver;
}



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yFILE_init              (void)
{
   myFILE.f_control = '-';
   strlcpy (myFILE.f_vernum  , "-´--"  , LEN_LABEL);
   strlcpy (myFILE.f_vertxt  , ""      , LEN_HUND );
   return 0;
}

char
yFILE_wrap              (void)
{
   return 0;
}

