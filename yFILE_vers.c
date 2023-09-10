/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



/*====================------------------------------------====================*/
/*===----                     version control                          ----===*/
/*====================------------------------------------====================*/
static void  o___CONTROL_________o () { return; }

char         /*-> tbd --------------------------------[ ------ [gc.520.103.41]*/ /*-[02.0000.02#.G]-*/ /*-[--.---.---.--]-*/
yfile_vers_controlled   (char *a_yes)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   char        x_opt       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_snote   ("can not execute until operational");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_yes);
   --rce;  if (a_yes == NULL || a_yes [0] == '\0') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_snote   (a_yes);
   /*---(translate)----------------------*/
   if (strlen (a_yes) > 1) {
      if (strcmp ("yes", a_yes) == 0)  x_opt = 'y';
      if (strcmp ("on" , a_yes) == 0)  x_opt = 'y';
      if (strcmp ("no" , a_yes) == 0)  x_opt = 'n';
      if (strcmp ("off", a_yes) == 0)  x_opt = 'n';
   } else {
      switch (a_yes [0]) {
      case 'y' : x_opt = 'y';  break;
      case '+' : x_opt = 'y';  break;
      case '-' : x_opt = 'n';  break;
      case 'n' : x_opt = 'n';  break;
      }
   }
   /*---(bad option)---------------------*/
   DEBUG_YFILE   yLOG_schar   (x_opt);
   --rce;  if (x_opt == '-') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (myFILE.f_vertxt, "", LEN_HUND);
   /*---(turn on)------------------------*/
   if (x_opt == 'y') {
      if (myFILE.f_control == '-') {
         DEBUG_YFILE   yLOG_snote   ("turn on");
         myFILE.f_control = 'y';
         ystrlcpy (myFILE.f_vernum, "0.0a", LEN_LABEL);
      } else {
         DEBUG_YFILE   yLOG_snote   ("already on");
      }
   }
   /*---(turn off)-----------------------*/
   if (x_opt == 'n') {
      if (myFILE.f_control == 'y') {
         DEBUG_YFILE   yLOG_snote   ("turn off");
         myFILE.f_control = '-';
         ystrlcpy (myFILE.f_vernum, "-´--", LEN_LABEL);
      } else {
         DEBUG_YFILE   yLOG_snote   ("already off");
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char yFILE_control            (void)  { return yfile_vers_controlled ("y"); }
char yFILE_nocontrol          (void)  { return yfile_vers_controlled ("n"); }



/*====================------------------------------------====================*/
/*===----                     version numbering                        ----===*/
/*====================------------------------------------====================*/
static void  o___NUMBER__________o () { return; }

char         /*-> tbd --------------------------------[ ------ [ge.C70.13#.E1]*/ /*-[02.0000.03#.T]-*/ /*-[--.---.---.--]-*/
yfile_vers_bump         (char a_type)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         = -10;
   char        rc          = 0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_snote   ("can not execute until operational");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_schar   (myFILE.f_control);
   --rce;  if (myFILE.f_control != 'y') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_schar   (a_type);
   --rce;  if (a_type == '\0' || strchr ("Mmi", a_type) == NULL) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (myFILE.f_vertxt, ""   , LEN_HUND);
   /*---(tiny)---------------------------*/
   --rce;  if (a_type == 'i') {
      if (myFILE.f_vernum [3] <  'z') {
         ++(myFILE.f_vernum [3]);
         DEBUG_YFILE   yLOG_snote   ("increment updated");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      DEBUG_YFILE   yLOG_snote   ("increment already at z");
      myFILE.f_vernum [3] = '?';
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(minor)--------------------------*/
   myFILE.f_vernum [3] = 'a';
   --rce;  if (a_type == 'm') {
      if (myFILE.f_vernum [2] <  '9') {
         ++(myFILE.f_vernum [2]);
         DEBUG_YFILE   yLOG_snote   ("numeric minor updated");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (myFILE.f_vernum [2] == '9') {
         myFILE.f_vernum [2] = 'A';
         DEBUG_YFILE   yLOG_snote   ("minor switched to alpha");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (myFILE.f_vernum [2] <  'Z') {
         ++(myFILE.f_vernum [2]);
         DEBUG_YFILE   yLOG_snote   ("alpha minor updated");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      DEBUG_YFILE   yLOG_snote   ("minor already at Z");
      myFILE.f_vernum [2] = '?';
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(major)--------------------------*/
   myFILE.f_vernum [2] = '0';
   --rce;  if (a_type == 'M') {
      if (myFILE.f_vernum [0] <  '9') {
         ++(myFILE.f_vernum [0]);
         DEBUG_YFILE   yLOG_snote   ("numeric major updated");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (myFILE.f_vernum [0] == '9') {
         myFILE.f_vernum  [0] =  'A';
         DEBUG_YFILE   yLOG_snote   ("major switched to alpha");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      if (myFILE.f_vernum [0] <  'Z') {
         ++(myFILE.f_vernum[0]);
         DEBUG_YFILE   yLOG_snote   ("alpha major updated");
         DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
         return 0;
      }
      DEBUG_YFILE   yLOG_snote   ("major already at Z");
      myFILE.f_vernum [0] = '?';
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   --rce;
   DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
   return  rce;
}

char yFILE_major              (void)  { return yfile_vers_bump ('M'); }
char yFILE_minor              (void)  { return yfile_vers_bump ('m'); }
char yFILE_inc                (void)  { return yfile_vers_bump ('i'); }

char         /*-> tbd --------------------------------[ ------ [ge.880.13#.G1]*/ /*-[02.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yFILE_vernum             (char *a_ver)
{
   /*---(locals)-----------+-----------+-*/
   int         x_len       = 0;
   char        rce         = -10;
   char        x_work      [10];
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_snote   ("can not execute until operational");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_schar   (myFILE.f_control);
   --rce;  if (myFILE.f_control != 'y') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_ver);
   --rce;  if (a_ver == NULL || a_ver [0] == '\0') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_snote   (a_ver);
   x_len = strlen (a_ver);
   DEBUG_YFILE   yLOG_sint    (x_len);
   --rce;  if (x_len != 4) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy  (x_work, a_ver, LEN_LABEL);
   /*---(test chars)---------------------*/
   --rce;  if (strchr (YSTR_LOWER, x_work [3]) == 0) {
      DEBUG_YFILE   yLOG_snote   ("inc is not a-z");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr (YSTR_UPNUM, x_work [2]) == 0) {
      DEBUG_YFILE   yLOG_snote   ("minor is not 0-9A-Z");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_work [1] != '.')  {
      DEBUG_YFILE   yLOG_snote   ("no dot between major and minor");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr (YSTR_UPNUM, x_work [0]) == 0) {
      DEBUG_YFILE   yLOG_snote   ("major is not 0-9A-Z");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check increase only)------------*/
   DEBUG_YFILE   yLOG_snote   (myFILE.f_vernum);
   --rce;  if (x_work [0] <  myFILE.f_vernum [0]) {
      DEBUG_YFILE   yLOG_snote   ("major can not be less");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_work [0] == myFILE.f_vernum [0]) {
      DEBUG_YFILE   yLOG_snote   ("major same");
      if (x_work [2] <  myFILE.f_vernum [2]) {
         DEBUG_YFILE   yLOG_snote   ("minor must be Ý");
         DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (x_work [2] == myFILE.f_vernum [2]) {
         DEBUG_YFILE   yLOG_snote   ("minor same");
         if (x_work [3] <  myFILE.f_vernum [3]) {
            DEBUG_YFILE   yLOG_snote   ("inc must be Ý");
            DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
            return rce;
         }
         if (x_work [3] >= myFILE.f_vernum [3]) {
            DEBUG_YFILE   yLOG_snote   ("inc inceased or same");
         }
      }
      if (x_work [2] >  myFILE.f_vernum [2]) {
         DEBUG_YFILE   yLOG_snote   ("minor increased");
      }
   }
   if (x_work [0] >  myFILE.f_vernum [0]) {
      DEBUG_YFILE   yLOG_snote   ("major increased, all is fair");
   }
   /*---(finalize)-----------------------*/
   ystrlcpy (myFILE.f_vernum, x_work, LEN_LABEL);
   ystrlcpy (myFILE.f_vertxt, "", LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         version text                         ----===*/
/*====================------------------------------------====================*/
static void  o___TEXT____________o () { return; }

char         /*-> tbd --------------------------------[ leaf   [ge.330.114.30]*/ /*-[00.0000.03#.7]-*/ /*-[--.---.---.--]-*/
yFILE_vertxt             (char *a_txt)
{
   /*---(locals)-----------+-----------+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("can not execute until operational");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_schar   (myFILE.f_control);
   --rce;  if (myFILE.f_control != 'y') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   ystrlcpy (myFILE.f_vertxt, "", LEN_HUND);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_txt);
   --rce;  if (a_txt == NULL || a_txt [0] == '\0') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_snote   (a_txt);
   /*---(save)---------------------------*/
   ystrlcpy  (myFILE.f_vertxt, a_txt,     LEN_HUND);
   ystrltrim (myFILE.f_vertxt, ySTR_BOTH, LEN_HUND);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



