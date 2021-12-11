/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



/*====================------------------------------------====================*/
/*===----                         shared functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___SHARED__________o () { return; }

char
yfile_handlers          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_FILE   yLOG_enter   (__FUNCTION__);
   /*---(handlers)-----------------------*/
   /*> rc = yPARSE_handler_max (UMOD_MARK    , "loc_mark"  , 7.1, "cT----------", -1, yvikeys_mark_reader, yvikeys_mark_writer_all, "------------" , "a,label", "map mode location marks");   <*/
   DEBUG_FILE   yLOG_value   ("loc_mark"  , rc);
   /*> rc = yPARSE_handler_max (UMOD_VISUAL  , "visu_mark" , 7.2, "cTT---------", -1, yvikeys_visu__reader, yvikeys_visu__writer_all, "------------" , "a,beg,end", "map mode visual selections");   <*/
   DEBUG_FILE   yLOG_value   ("visu_mark" , rc);
   /*> rc = yPARSE_handler_max (SMOD_MACRO   , "macro"     , 7.3, "cO----------", -1, yMACRO_reader, yMACRO_writer, "------------" , "a,keys", "keyboard macros"           );   <*/
   DEBUG_FILE   yLOG_value   ("macro"     , rc);
   /*> rc = yPARSE_handler_max (MODE_COMMAND , "command"   , 7.4, "cO----------", -1, yvikeys_cmds_reader, yvikeys_cmds_writer, "------------" , "a,command-----------------", "command history"           );   <*/
   DEBUG_FILE   yLOG_value   ("command"   , rc);
   /*> rc = yPARSE_handler_max (MODE_SEARCH  , "search"    , 7.5, "cO----------", -1, yvikeys_srch_reader, yvikeys_srch_writer, "------------" , "a,search"                  , "search history"            );   <*/
   DEBUG_FILE   yLOG_value   ("search"    , rc);
   /*---(complete)-----------------------*/
   DEBUG_FILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yFILE_new               (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   int         n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_INPT   yLOG_note    ("can not execute until operational");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(run prepper)--------------------*/
   DEBUG_INPT  yLOG_point   ("e_prepper" , myFILE.e_prepper);
   if (myFILE.e_prepper != NULL)  rc = myFILE.e_prepper (0);
   DEBUG_OUTP   yLOG_value   ("prep"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         input related                        ----===*/
/*====================------------------------------------====================*/
static void  o___INPUT___________o () { return; }

char
yFILE_reader            (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         x_pass      =    1;
   char        x_max       =    1;
   /*---(stage check)-----------------*/
   yURG_stage_check (YURG_STAGE_INPT);
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_INPT   yLOG_note    ("can not execute until operational");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(multi-pass)---------------------*/
   while (x_pass <= x_max) {
      /*---(run prepper)----------*/
      DEBUG_INPT  yLOG_point   ("e_prepper" , myFILE.e_prepper);
      if (myFILE.e_prepper != NULL)  rc = myFILE.e_prepper (x_pass);
      DEBUG_OUTP   yLOG_value   ("prep"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      x_max = rc;
      /*---(open file)------------*/
      DEBUG_INPT  yLOG_info    ("f_title"   , myFILE.f_title);
      rc = yPARSE_planned (myFILE.f_title, NULL, NULL);
      DEBUG_OUTP   yLOG_value   ("open"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(load handlers)--------*/
      rc = yfile_handlers ();
      DEBUG_OUTP   yLOG_value   ("handlers"  , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      DEBUG_OUTP   yLOG_value   ("e_handlers", myFILE.e_handlers);
      if (myFILE.e_handlers != NULL)  rc = myFILE.e_handlers ();
      DEBUG_OUTP   yLOG_value   ("locals"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(intro)----------------*/
      rc = yPARSE_read_all ();
      DEBUG_OUTP   yLOG_value   ("yparse"    , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(close file)-----------*/
      rc = yPARSE_close ();
      DEBUG_OUTP   yLOG_value   ("close"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(run finisher)---------*/
      DEBUG_INPT  yLOG_point   ("e_finisher", myFILE.e_finisher);
      if (myFILE.e_finisher != NULL)  rc = myFILE.e_finisher (x_pass);
      DEBUG_OUTP   yLOG_value   ("prep"      , rc);
      --rce;  if (rc < 0) {
         DEBUG_INPT  yLOG_exit    (__FUNCTION__);
         return rce;
      }
      /*---(pass done)------------*/
      ++x_pass;
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP  yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        output related                        ----===*/
/*====================------------------------------------====================*/
static void  o___OUTPUT__________o () { return; }

char
yFILE_writer            (void)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         i           =    0;
   int         n           =   -1;
   /*---(stage check)-----------------*/
   yURG_stage_check (YURG_STAGE_OUTP);
   /*---(header)-------------------------*/
   DEBUG_INPT  yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_INPT   yLOG_note    ("can not execute until operational");
      DEBUG_INPT   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open file)----------------------*/
   DEBUG_INPT  yLOG_info    ("f_title"   , myFILE.f_title);
   DEBUG_INPT  yLOG_info    ("s_fullname", myFILE.s_fullname);
   DEBUG_INPT  yLOG_info    ("s_namesake", myFILE.s_namesake);
   rc = yPARSE_planned (NULL, myFILE.f_title, NULL);
   DEBUG_OUTP   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(load handlers)------------------*/
   rc = yfile_handlers ();
   if (myFILE.e_handlers != NULL)  rc = myFILE.e_handlers ();
   /*---(header)-------------------------*/
   rc = yPARSE_header  (myFILE.s_fullname, myFILE.s_vernum, myFILE.s_vertxt, myFILE.s_namesake, myFILE.s_filetype, NULL);
   /*---(intro)--------------------------*/
   rc = yPARSE_write_all ();
   DEBUG_OUTP   yLOG_value   ("yparse"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(close file)---------------------*/
   rc = yPARSE_close_out ();
   DEBUG_OUTP   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_INPT  yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_OUTP  yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ ------ [gc.320.121.32]*/ /*-[00.0000.00#.!]-*/ /*-[--.---.---.--]-*/
yFILE_writeas           (char *a_name)
{
   char        rc          =    0;
   char        x_name      [LEN_RECD]  = "";
   strlcpy (x_name, myFILE.f_name, LEN_RECD);
   if (rc >= 0)  rc = yFILE_name   (a_name);
   if (rc >= 0)  rc = yFILE_writer ();
   yFILE_name(x_name);
   return rc;
}



