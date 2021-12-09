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
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("status is not ready for init");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(versioning)---------------------*/
   DEBUG_YFILE   yLOG_note    ("default versioning data");
   myFILE.f_control = '-';
   strlcpy (myFILE.f_vernum  , "-´--"  , LEN_LABEL);
   strlcpy (myFILE.f_vertxt  , ""      , LEN_HUND );
   /*---(source)-------------------------*/
   DEBUG_YFILE   yLOG_note    ("default source program data");
   strlcpy (myFILE.s_prog    , ""      , LEN_LABEL);
   strlcpy (myFILE.s_fullname, ""      , LEN_DESC );
   strlcpy (myFILE.s_vernum  , "-´--"  , LEN_LABEL);
   strlcpy (myFILE.s_vertxt  , ""      , LEN_DESC );
   strlcpy (myFILE.s_namesake, ""      , LEN_DESC );
   strlcpy (myFILE.s_ext     , ""      , LEN_LABEL);
   strlcpy (myFILE.s_filetype, ""      , LEN_DESC );
   sprintf (myFILE.f_loc     , "%s/", getcwd (NULL, 0));
   if (strcmp (myFILE.f_loc, "//") == 0)  strlcpy (myFILE.f_loc, "/", LEN_LABEL);
   /*---(functions)----------------------*/
   DEBUG_YFILE   yLOG_note    ("default function callbacks data");
   myFILE.e_handlers = NULL;
   myFILE.e_prepper  = NULL;
   myFILE.e_finisher = NULL;
   /*---(update status)------------------*/
   yMODE_init_set   (FMOD_FILE, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yFILE_whoami            (char *a_full, char *a_vernum, char *a_vertxt, char *a_namesake, char *a_ext, char *a_filetype, void *a_handlers, void *a_prepper, void *a_finisher)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_needs  (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("init must be successfully called first");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(full executable name)-----------*/
   DEBUG_YFILE   yLOG_point   ("a_full"    , a_full);
   --rce;  if (a_full == NULL) {
      DEBUG_YFILE   yLOG_note    ("requires a program name");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (myFILE.s_fullname, a_full, LEN_DESC);
   DEBUG_YFILE   yLOG_info    ("s_fullname", myFILE.s_fullname);
   /*---(program name)-------------------*/
   p = strrchr (a_full, '/');
   if (p != NULL)   strlcpy (myFILE.s_prog, p + 1 , LEN_LABEL);
   else             strlcpy (myFILE.s_prog, a_full, LEN_LABEL);
   DEBUG_YFILE   yLOG_info    ("s_prog"    , myFILE.s_prog);
   /*---(calling program version)--------*/
   DEBUG_YFILE   yLOG_point   ("a_vernum"  , a_vernum);
   --rce;  if (a_vernum != NULL) {
      strlcpy (myFILE.s_vernum, a_vernum, LEN_LABEL);
      DEBUG_YFILE   yLOG_info    ("s_vernum"  , myFILE.s_vernum);
   }
   /*---(calling program ver desc)-------*/
   DEBUG_YFILE   yLOG_point   ("a_vertxt"  , a_vertxt);
   --rce;  if (a_vertxt != NULL) {
      strlcpy (myFILE.s_vertxt, a_vertxt, LEN_DESC);
      DEBUG_YFILE   yLOG_info    ("s_vertxt"  , myFILE.s_vertxt);
   }
   /*---(calling one-line desc)----------*/
   DEBUG_YFILE   yLOG_point   ("a_namesake" , a_namesake);
   --rce;  if (a_namesake != NULL) {
      strlcpy (myFILE.s_namesake, a_namesake, LEN_DESC);
      DEBUG_YFILE   yLOG_info    ("s_namesake", myFILE.s_namesake);
   }
   /*---(default extension)--------------*/
   DEBUG_YFILE   yLOG_point   ("a_ext"     , a_ext);
   --rce;  if (a_ext == NULL) {
      DEBUG_YFILE   yLOG_note    ("requires a standard file extension");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (myFILE.s_ext, a_ext, LEN_LABEL);
   DEBUG_YFILE   yLOG_info    ("s_ext"     , myFILE.s_ext);
   /*---(calling content)----------------*/
   DEBUG_YFILE   yLOG_point   ("a_filetype", a_filetype);
   --rce;  if (a_filetype != NULL) {
      strlcpy (myFILE.s_filetype, a_filetype, LEN_DESC);
      DEBUG_YFILE   yLOG_info    ("s_filetype", myFILE.s_filetype);
   }
   /*---(handlers)-----------------------*/
   DEBUG_YFILE   yLOG_point   ("a_handlers", a_handlers);
   if (a_handlers != NULL)   myFILE.e_handlers = a_handlers;
   /*---(writer)-------------------------*/
   DEBUG_YFILE   yLOG_point   ("a_prepper" , a_prepper);
   if (a_prepper  != NULL)   myFILE.e_prepper  = a_prepper;
   /*---(writer)-------------------------*/
   DEBUG_YFILE   yLOG_point   ("a_finisher", a_finisher);
   if (a_finisher != NULL)   myFILE.e_finisher = a_finisher;
   /*---(update stage)-------------------*/
   yMODE_conf_set (FMOD_FILE, '1');
   /*---(default file name)--------------*/
   /*> yvikeys_file_name (NULL);                                                      <*/
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yFILE_wrap              (void)
{
   return 0;
}

