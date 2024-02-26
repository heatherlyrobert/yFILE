/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"


typedef struct cDUMP tDUMP;
static struct cDUMP {
   char       *terse;
   char       *name;
   char       *desc;
   char      (*provider) (FILE*);           /* function pointer               */
   tDUMP      *next;
};
static tDUMP      *s_hdump     = NULL;
static tDUMP      *s_tdump     = NULL;
static int         s_ndump     =    0;

static char   *s_nada          = "-";


/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yfile_dump_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(globals)------------------------*/
   s_hdump = s_tdump = NULL;
   s_ndump = 0;
   rc = yFILE_dump_add ("?"           , NULL ,  "inventory of dump options"                         , yfile_dumps              );
   /*> rc = yFILE_dump_add ("keys"        , yMACRO_dump         );                    <*/
   /*> rc = yFILE_dump_add ("status"      , yMODE_statuses      );                    <*/
   /*> rc = yFILE_dump_add ("macros"      , yMACRO_dump         );                    <*/
   /*> rc = yFILE_dump_add ("sreg"        , yvikeys_sreg_dump   );                    <*/
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yfile_dump_wrap         (void)
{
   tDUMP      *x_next      = NULL;
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   x_next = s_hdump;
   while (x_next != NULL) {
      DEBUG_YFILE   yLOG_sint    (s_ndump);
      x_next  = x_next->next;
      free (s_hdump->name);
      s_hdump->name  = s_nada;
      if (s_hdump->terse != s_nada)  free (s_hdump->terse);
      s_hdump->terse = s_nada;
      if (s_hdump->desc  != s_nada)  free (s_hdump->desc);
      s_hdump->desc  = s_nada;
      free (s_hdump);
      s_hdump = x_next;
      --s_ndump;
   }
   s_hdump = s_tdump = NULL;
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      finding dump records                    ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

char yfile_dump_count        (void) { return s_ndump; }

char*
yfile_dump_by_index     (char n)
{
   char        c           =    0;
   tDUMP      *x_dump      = NULL;
   if (n < 0 || n >= s_ndump)  return "n/a";
   x_dump = s_hdump;
   while (x_dump != NULL) {
      if (c == n) {
         sprintf (myFILE.g_print, "%-2d  %-12.12s  %-3.3s  %s", n, x_dump->name, x_dump->terse, x_dump->desc);
         return myFILE.g_print;
      }
      x_dump = x_dump->next;
      ++c;
   }
   return "n/a";
}

char
yfile_dump_by_terse     (char *a_terse)
{
   tDUMP      *x_dump      = NULL;
   x_dump = s_hdump;
   if (a_terse     == NULL)  return  0;
   if (a_terse [0] == '\0')  return  0;
   while (x_dump != NULL) {
      if (strcmp (a_terse, x_dump->terse) == 0)  return 1;
      x_dump = x_dump->next;
   }
   return 0;
}

char
yfile_dump_by_name      (char *a_name)
{
   tDUMP      *x_dump      = NULL;
   x_dump = s_hdump;
   if (a_name      == NULL)  return -1;
   if (a_name [0]  == '\0')  return -2;
   while (x_dump != NULL) {
      if (strcmp (a_name, x_dump->name) == 0)  return 1;
      x_dump = x_dump->next;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      add new dumps                           ----===*/
/*====================------------------------------------====================*/
static void      o___CREATE__________________o (void) {;}

char
yFILE_dump_add          (char *a_name, char *a_terse, char *a_desc, void *a_provider)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_dup       =    0;
   tDUMP      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   x_len = strlen (a_name);
   DEBUG_YFILE   yLOG_sint    (x_len);
   --rce;  if (x_len < 1) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YFILE   yLOG_spoint  (a_terse);
   --rce;  if (a_terse != NULL) {
      x_len = strlen (a_terse);
      DEBUG_YFILE   yLOG_sint    (x_len);
      --rce;  if (x_len > 3) {
         DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
         return  rce;
      }
   }
   /*---(find dup terse)-----------------*/
   x_dup = yfile_dump_by_terse (a_terse);
   DEBUG_YFILE   yLOG_sint    (x_dup);
   --rce;  if (x_dup != 0) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(find dup name)------------------*/
   x_dup = yfile_dump_by_terse (a_name);
   DEBUG_YFILE   yLOG_sint    (x_dup);
   --rce;  if (x_dup != 0) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   x_dup = yfile_dump_by_name (a_name);
   DEBUG_YFILE   yLOG_sint    (x_dup);
   --rce;  if (x_dup != 0) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   DEBUG_YFILE   yLOG_spoint  (a_provider);
   --rce;  if (a_provider == NULL) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tDUMP *) malloc (sizeof (tDUMP));
   }
   DEBUG_YFILE   yLOG_sint    (x_tries);
   DEBUG_YFILE   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YFILE   yLOG_snote   ("FAILED");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(clear)--------------------------*/
   x_new->terse = s_nada;
   x_new->name  = s_nada;
   x_new->desc  = s_nada;
   /*---(tie to linked list)-------------*/
   DEBUG_YFILE   yLOG_snote   ("link");
   x_new->next   = NULL;
   if (s_hdump == NULL)  s_hdump       = x_new;
   else                  s_tdump->next = x_new;
   s_tdump       = x_new;
   /*---(populate)-----------------------*/
   DEBUG_YFILE   yLOG_snote   ("populate");
   x_new->name     = strdup (a_name);
   if (a_terse != NULL && a_terse [0] != '\0')  x_new->terse    = strdup (a_terse);
   if (a_desc  != NULL && a_desc  [0] != '\0')  x_new->desc     = strdup (a_desc);
   x_new->provider = a_provider;
   /*---(complete)-----------------------*/
   ++s_ndump;
   DEBUG_YFILE   yLOG_sint    (s_ndump);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    generate a dump                           ----===*/
/*====================------------------------------------====================*/
static void      o___GENERATE________________o (void) {;}

char
yFILE_dump              (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDUMP      *x_curr      = NULL;
   FILE       *f           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(clear file)---------------------*/
   f = fopen (YSTR_CLIP, "w");
   DEBUG_YFILE   yLOG_point   ("f"         , f);
   if (f == NULL) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(header)-------------------------*/
   fprintf (f, "#!/usr/bin/vi\n");
   fprintf (f, "##   host          %s (%d)\n", myFILE.s_fullname, getpid ());
   fprintf (f, "##   source        %s\n", myFILE.f_title);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      fprintf (f, "##   generated     :dump %s¦\n", "(NULL)");
      fprintf (f, "##\n");
      fprintf (f, "## illegal dump name\n");
      fprintf (f, "##\n");
      fprintf (f, "## end-of-file.  done, finito, completare, whimper [Ï´···\n");
      fclose  (f);
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   fprintf (f, "##   generated     :dump %s¦\n", a_name);
   fprintf (f, "##\n");
   /*---(find)---------------------------*/
   x_curr = s_hdump;
   while (x_curr != NULL) {
      DEBUG_YFILE   yLOG_info    ("check"     , x_curr->name);
      if (strcmp (a_name, x_curr->name)  == 0)   break;
      if (strcmp (a_name, x_curr->terse) == 0)   break;
      x_curr = x_curr->next;
   }
   DEBUG_YFILE   yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      fprintf (f, "## unknown/non-existant dump name\n");
      fprintf (f, "##\n");
      fprintf (f, "## end-of-file.  done, finito, completare, whimper [Ï´···\n");
      fclose  (f);
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call provider)------------------*/
   DEBUG_YFILE   yLOG_point   ("provider"  , x_curr->provider);
   rc = x_curr->provider (f);
   DEBUG_YFILE   yLOG_value   ("rc"        , rc);
   /*---(close dump file)----------------*/
   fprintf (f, "##\n");
   fprintf (f, "## end-of-file.  done, finito, completare, whimper [Ï´···\n");
   fclose  (f);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yfile_dumps             (FILE *f)
{
   tDUMP      *x_curr      = NULL;
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   x_curr = s_hdump;
   while (x_curr != NULL) {
      DEBUG_YFILE   yLOG_info    ("printing"  , x_curr->name);
      fprintf (f, "%-12.12s § %-3.3s § %s §\n", x_curr->name, x_curr->terse, x_curr->desc);;
      x_curr = x_curr->next;
   }
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}


