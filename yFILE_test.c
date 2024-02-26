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
   yPARSE_config  (YPARSE_AUTO, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   yMODE_init (MODE_MAP);
   yMODE_init_after ();
   yKEYS_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yFILE_init ();
   yFILE_init_after ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yfile__unit_loud       (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yFILE_unit" };
   yPARSE_config  (YPARSE_AUTO, NULL, YPARSE_ONETIME, YPARSE_FIELD, YPARSE_FILL);
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yURG_by_name  ("yparse"       , YURG_ON);
   yURG_by_name  ("yvihub"       , YURG_ON);
   yURG_by_name  ("ymode"        , YURG_ON);
   yURG_by_name  ("ykeys"        , YURG_ON);
   yURG_by_name  ("yfile"        , YURG_ON);
   DEBUG_YFILE   yLOG_info     ("yFILE"      , yFILE_version   ());
   yMODE_init (MODE_MAP);
   yMODE_init_after ();
   yKEYS_unit_handlers ();
   yKEYS_init  ();
   yKEYS_init_after ();
   yFILE_init ();
   yFILE_init_after ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yfile__unit_end        (void)
{
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   yFILE_wrap ();
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}



/*====================------------------------------------====================*/
/*===----                   unit testing stubs                         ----===*/
/*====================------------------------------------====================*/
static void  o___STUBS___________o () { return; }

char
yfile__unit_handlers    (void)
{
   return 0;
}

char
yfile__unit_prepper     (char a_pass)
{
   return 0;
}

char
yfile__unit_finisher    (char a_pass)
{
   return 0;
}

char
yfile__unit_dump        (FILE *f)
{
   fprintf (f, "first\n");
   fprintf (f, "second\n");
   fprintf (f, "third\n");
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


