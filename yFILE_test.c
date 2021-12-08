/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char          unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
yfile__unit_quiet      (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yFILE_unit" };
   yPARSE_init  ('y', NULL, '-');
   yPARSE_delimiters  ("");
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yFILE_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yfile__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yFILE_unit" };
   yPARSE_init  ('y', NULL, '-');
   yPARSE_delimiters  ("");
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("yparse"       , YURG_ON);
   yURG_name  ("keys"         , YURG_ON);
   yURG_name  ("file"         , YURG_ON);
   DEBUG_SCRP   yLOG_info     ("yFILE"      , yFILE_version   ());
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yFILE_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yfile__unit_end        (void)
{
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   yFILE_wrap ();
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   unit testing accessor                      ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESSOR________o () { return; }

char*        /*-> unit test accessor -----------------[ ------ [gs.950.221.M1]*/ /*-[03.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yFILE__unit             (char *a_question, int a_ref)
{
   /*---(locals)-----------+-----------+-*/
   int         rc          = -1;
   char        x_name      [LEN_LABEL];
   char        t           [LEN_DESC ];
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "FILE             : question not understood");
   /*---(selection)----------------------*/
   if        (strcmp (a_question, "version"   )    == 0) {
      snprintf (unit_answer, LEN_FULL, "FILE version     : %c  %-4.4s  %2då%sæ", myFILE.f_control, myFILE.f_vernum, strlen (myFILE.f_vertxt), myFILE.f_vertxt);
   /*> } else if (strcmp (a_question, "recd"      )    == 0) {                                                                <* 
    *>    snprintf (yVIKEYS__unit_answer, LEN_FULL, "FILE recd        : %s", myVIKEYS.f_recd);                                <* 
    *> } else if (strcmp (a_question, "loc"       )    == 0) {                                                                <* 
    *>    if (myVIKEYS.f_loc [0] == 0)  snprintf (yVIKEYS__unit_answer, LEN_FULL, "FILE loc         : -");                    <* 
    *>    else                          snprintf (yVIKEYS__unit_answer, LEN_FULL, "FILE loc         : %s", myVIKEYS.f_loc);   <* 
    *> } else if (strcmp (a_question, "title"     )    == 0) {                                                                <* 
    *>    snprintf (yVIKEYS__unit_answer, LEN_FULL, "FILE title       : %s", myVIKEYS.f_title);                               <*/
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


