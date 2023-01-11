/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



typedef struct  dirent    tENTRY;
#define         B_ENTRY   'e'
static char     s_name    [LEN_PATH]  = "";
static DIR     *s_dir     = NULL;



typedef  struct cKEEP  tKEEP;
struct cKEEP {
   char        name           [LEN_PATH];
   char        sort           [LEN_PATH];
};



/*====================------------------------------------====================*/
/*===----                  regular expression matching                 ----===*/
/*====================------------------------------------====================*/
static void      o___REGEX___________________o (void) {;}

char
yfile_name__prep        (char a_type, char *a_ext, char *a_path, char *a_entry, char *r_match, char *r_elen)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(default)------------------------*/
   DEBUG_YFILE   yLOG_spoint  (r_match);
   if (r_match != NULL)  strlcpy (r_match, "", LEN_RECD);
   DEBUG_YFILE   yLOG_spoint  (r_match);
   if (r_elen  != NULL)  *r_elen = 0;
   s_dir = NULL;
   /*---(type)---------------------------*/
   DEBUG_YFILE   yLOG_schar   (a_type);
   --rce;  if (a_type == 0 || strchr ("fd", a_type) == NULL) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(extension)----------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_ext);
   --rce;  if (a_type == 'f' && a_ext != NULL && a_ext [0] != '\0') {
      DEBUG_YFILE   yLOG_snote   (a_ext);
      x_len = strlen (a_ext);
      DEBUG_YFILE   yLOG_sint    (x_len);
      if (x_len > 10) {
         DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (r_elen != NULL)  *r_elen = x_len;
   }
   /*---(base)---------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_path);
   --rce;  if (a_path == NULL || a_path [0] == '\0') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(entry)--------------------------*/
   DEBUG_YFILE   yLOG_spoint  (a_entry);
   --rce;  if (a_entry == NULL || a_entry [0] == 0) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(compile search)-----------------*/
   rc = yREGEX_comp (a_entry);
   DEBUG_YFILE   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_snote   ("could not compile search");
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(create the list)----------------*/
   rc = ySORT_btree (B_ENTRY, "entry");
   DEBUG_YFILE   yLOG_value   ("B_ENTRY"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yfile_name__wrap        (void)
{
   /*---(local variables)--+-----+-----+-*/
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(purge entries)------------------*/
   rc = ySORT_purge (B_ENTRY);
   DEBUG_YFILE   yLOG_sint    (rc);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yfile_name__open        (char a_path [LEN_PATH])
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_point   ("s_dir"     , s_dir);
   --rce;  if (s_dir  != NULL) {
      DEBUG_YFILE   yLOG_note    ("a directory is already open");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_info    ("a_path"    , a_path);
   /*---(open)---------------------------*/
   s_dir = opendir (a_path);
   DEBUG_YFILE   yLOG_point   ("open"      , s_dir);
   --rce;  if (s_dir == NULL) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save off)-----------------------*/
   DEBUG_YFILE   yLOG_note    ("success, location open");
   strlcpy (s_name, a_path, LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yfile_name__close       (void)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_point   ("s_dir"     , s_dir);
   --rce;  if (s_dir  == NULL) {
      DEBUG_YFILE   yLOG_note    ("directory already closed");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(open)---------------------------*/
   rc = closedir (s_dir);
   DEBUG_YFILE   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(ground)-------------------------*/
   DEBUG_YFILE   yLOG_note    ("success, location closed");
   s_dir = NULL;
   strlcpy (s_name, ""    , LEN_PATH);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yfile_name__filter      (char a_type, char *a_ext, char a_elen, char a_path [LEN_PATH], tENTRY *a_entry)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_full      [LEN_RECD];
   tSTAT       s;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YFILE   yLOG_point   ("a_entry"   , a_entry);
   --rce;  if (a_entry  == NULL) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(cut out trash)------------------*/
   l = strlen (a_entry->d_name);
   if (l == 1 && strcmp (a_entry->d_name, "."  ) == 0) {
      DEBUG_YFILE   yLOG_note    ("self dir reference (.)");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (l == 2 && strcmp (a_entry->d_name, ".." ) == 0) {
      DEBUG_YFILE   yLOG_note    ("parent dir reference (..)");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (l > 1 && strcmp (a_entry->d_name + (l - 1), "~") == 0) {
      DEBUG_YFILE   yLOG_note    ("tilde/temp file");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (l > 4 && strcmp (a_entry->d_name + (l - 4), ".swp") == 0) {
      DEBUG_YFILE   yLOG_note    ("swap file");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(filter by extension)---------*/
   if (a_elen > 0) {
      DEBUG_YFILE   yLOG_info    ("ext"       , a_entry->d_name + l - a_elen);
      if (strncmp (a_entry->d_name + l - a_elen, a_ext, a_elen) != 0) {
         DEBUG_YFILE   yLOG_note    ("suffix does not match, SKIP");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(make full name)-----------------*/
   sprintf (x_full, "%s%s", a_path, a_entry->d_name);
   DEBUG_YFILE   yLOG_info    ("x_full"    , x_full);
   /*---(get stat)-----------------------*/
   rc = lstat (x_full, &s);
   DEBUG_YFILE   yLOG_value   ("lstat"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(filter on type)-----------------*/
   if (a_type == 'd' && !S_ISDIR (s.st_mode)) {
      DEBUG_YFILE   yLOG_note    ("non-directory when looking for directories");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (a_type == 'f' && !S_ISREG (s.st_mode)) {
      DEBUG_YFILE   yLOG_note    ("non-regular file looking for files");
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(check for bad characters)-------*/
   for (i = 0; i < l; ++i) {
      if (strchr (YSTR_FILES, a_entry->d_name [i]) == NULL) {
         DEBUG_YFILE   yLOG_note    ("bad character in target name");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return 0;
      }
   }
   /*---(complete)-----------------------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
yfile_name__hook        (tENTRY *a_entry)
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   int         c           =    0;
   char        x_name      [LEN_PATH]  = "";
   tKEEP      *x_keep      =    0;
   char       *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(create)-------------------------*/
   x_keep = (tKEEP *) malloc (sizeof (tKEEP));
   DEBUG_YFILE   yLOG_point   ("x_keep"    , x_keep);
   --rce;  if (x_keep == NULL) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   strlcpy (x_name, a_entry->d_name, LEN_PATH);
   strlcpy (x_keep->name, x_name, LEN_PATH);
   /*---(case insensistive sort)---------*/
   DEBUG_YFILE   yLOG_info    ("x_name"    , x_name);
   strllower (x_name, LEN_PATH);
   DEBUG_YFILE   yLOG_info    ("lower"     , x_name);
   /*---(hidden files mixed in)----------*/
   p = x_name;
   if (a_entry->d_name [0] == '.') ++p;
   DEBUG_YFILE   yLOG_info    ("p"         , p);
   strlcpy (x_keep->sort, p, LEN_PATH);
   /*---(before)-------------------------*/
   c  = ySORT_count   (B_ENTRY);
   rc = ySORT_by_name (B_ENTRY, x_keep->sort, NULL);
   DEBUG_YFILE   yLOG_complex ("before"    , "%4dc, %4drc", c, rc);
   --rce;  if (rc >= 0) {
      DEBUG_YFILE   yLOG_note    ("already exists, do not duplicate");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(into tsae list)-----------------*/
   rc = ySORT_hook (B_ENTRY, x_keep, x_keep->sort, NULL);
   DEBUG_YFILE   yLOG_value   ("hook"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   rc = ySORT_prepare (B_ENTRY);
   DEBUG_YFILE   yLOG_value   ("prepare"   , rc);
   if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(after)--------------------------*/
   c  = ySORT_count   (B_ENTRY);
   rc = ySORT_by_name (B_ENTRY, x_keep->sort, NULL);
   DEBUG_YFILE   yLOG_complex ("after"     , "%4dc, %4drc", c, rc);
   /*---(complete)-----------------------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yfile_name__gather      (char a_type, char *a_ext, char a_elen, char a_path [LEN_PATH])
{
   /*---(local variables)--+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tENTRY     *x_entry     = NULL;
   tSTAT       s;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(open)---------------------------*/
   rc = yfile_name__open (a_path);
   DEBUG_YFILE   yLOG_value   ("open"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk directory)-----------------*/
   --rce; while (1) {
      /*---(read)------------------------*/
      x_entry = readdir (s_dir);
      DEBUG_YFILE   yLOG_point   ("x_entry"   , x_entry);
      if (x_entry == NULL)                      break;
      /*---(filter)----------------------*/
      rc = yfile_name__filter (a_type, a_ext, a_elen, a_path, x_entry);
      if (rc <  0) {
         DEBUG_YFILE   yLOG_note    ("trouble with entry");
         continue;
      }
      if (rc == 0) {
         DEBUG_YFILE   yLOG_note    ("entry filtered out");
         continue;
      }
      /*---(hook)------------------------*/
      rc = yfile_name__hook (x_entry);
      if (rc <  0) {
         DEBUG_YFILE   yLOG_note    ("could not add entry");
         continue;
      }
      /*---(done)------------------------*/
   }
   /*---(close dir)----------------------*/
   rc = yfile_name__close ();
   DEBUG_YFILE   yLOG_value   ("close"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yfile_name__regex       (char a_type, char *a_ext, char *a_path, char *a_entry, char *r_match)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_elen      =    0;
   int         x_checked   =    0;
   int         x_matches   =    0;
   tKEEP      *x_keep      = NULL;
   char        n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yfile_name__prep (a_type, a_ext, a_path, a_entry, r_match, &x_elen);
   DEBUG_YFILE   yLOG_value   ("prep"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_delim   ("a_path"    , a_path);
   DEBUG_YFILE   yLOG_delim   ("a_entry"   , a_entry);
   /*---(open)---------------------------*/
   rc = yfile_name__gather (a_type, a_ext, x_elen, a_path);
   DEBUG_YFILE   yLOG_value   ("gather"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk directory)-----------------*/
   n = ySORT_by_cursor (B_ENTRY, '[', &x_keep);
   DEBUG_YFILE   yLOG_value   ("n"         , n);
   while (n >=  0) {
      DEBUG_YFILE   yLOG_info    ("name"      , x_keep->name);
      ++x_checked;
      /*---(filter by name)--------------*/
      rc = yREGEX_filter (x_keep->name);
      DEBUG_YFILE   yLOG_value   ("exec"      , rc);
      if (rc <= 0) {
         DEBUG_YFILE   yLOG_note    ("regex failed to match");
      }
      /*---(save)------------------------*/
      else {
         DEBUG_YFILE   yLOG_note    ("found a match");
         ++x_matches;
         if (x_matches == 1 && r_match != NULL) {
            strlcpy (r_match, x_keep->name, LEN_RECD);
         }
      }
      /*---(next)------------------------*/
      n = ySORT_by_cursor (B_ENTRY, '>', &x_keep);
      DEBUG_YFILE   yLOG_value   ("n"         , n);
      /*---(done)------------------------*/
   }
   /*---(wrap)---------------------------*/
   rc = yfile_name__wrap ();
   DEBUG_YFILE   yLOG_value   ("wrap"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(report-out)---------------------*/
   DEBUG_YFILE   yLOG_value   ("x_checked" , x_checked);
   DEBUG_YFILE   yLOG_value   ("x_matches" , x_matches);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return x_matches;
}



/*====================------------------------------------====================*/
/*===----                      extension handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___EXT_____________________o (void) {;}

char
yfile_name__stripext    (char *a_full)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   int         x_elen      =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_senter  (__FUNCTION__);
   /*---(check extension)----------------*/
   DEBUG_YFILE   yLOG_snote   (myFILE.s_ext);
   x_elen = strllen (myFILE.s_ext, LEN_LABEL);
   DEBUG_YFILE   yLOG_sint    (x_elen);
   if (x_elen <= 0) {
      DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(deal with null/empty)-----------*/
   DEBUG_YFILE   yLOG_spoint  (a_full);
   --rce;  if (a_full == NULL || a_full [0] == 0) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check lengths)------------------*/
   x_len    = strllen (a_full, LEN_RECD);
   DEBUG_YFILE   yLOG_sint    (x_len);
   --rce;  if (x_len < 2) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_len < x_elen + 1) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check extension)----------------*/
   DEBUG_YFILE   yLOG_snote   (a_full + x_len - x_elen - 1);
   --rce;  if (strcmp (a_full + x_len - x_elen, myFILE.s_ext) != 0)  {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_schar   (a_full [x_len - x_elen - 1]);
   --rce;  if (a_full [x_len - x_elen - 1] != '.') {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(update)-------------------------*/
   a_full [x_len - x_elen - 1] = '\0';
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         path handling                        ----===*/
/*====================------------------------------------====================*/
static void      o___PATH____________________o (void) {;}

char
yfile_name__path        (char *a_path, char *a_depth)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_curr      [LEN_RECD];
   char        x_work      [LEN_RECD];
   char        t           [LEN_RECD];
   char        x_final     [LEN_RECD];
   int         x_len       =    0;
   char       *p           = NULL;               /* strtok pointer            */
   char       *q           = "/";                /* strtok delimeters         */
   char       *r           = NULL;               /* strtok context variable   */
   int         c           =    0;
   char        x_matches   =    1;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(deal with null/empty)-----------*/
   DEBUG_YFILE   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL || a_path [0] == 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_info    ("a_path"    , a_path);
   strlcpy (x_work, a_path, LEN_RECD);
   strlcpy (a_path, "", LEN_RECD);
   if (a_depth != NULL)  *a_depth = -1;
   /*---(absolute marker)----------------*/
   getcwd (x_curr, LEN_RECD);
   if (strncmp (x_work, "./", 2) == 0) {
      strlcpy (x_final, x_curr, LEN_RECD);
      strlcat (x_final, "/"   , LEN_RECD);
      x_work [0] = '/';
   } else if (x_work [0] == '/')  strlcpy (x_final, "/", LEN_RECD);
   else                           strlcpy (x_final, myFILE.f_loc, LEN_RECD);
   DEBUG_YFILE   yLOG_info    ("x_final"   , x_final);
   x_len = strlen (x_final);
   /*---(loop)---------------------------*/
   p = strtok_r (x_work, q, &r);
   --rce;  while (p != NULL) {
      /*---(head)------------------------*/
      DEBUG_YFILE   yLOG_info    ("p"         , p);
      /*---(goto parent)-----------------*/
      if (strcmp (p, "..") == 0) {
         if (x_len > 1)  x_final [--x_len] = '\0';
         p = strrchr (x_final, '/');
         if (p != NULL)  p [1] = '\0';
      }
      /*---(goto child)------------------*/
      else {
         rc = yfile_name__regex ('d', NULL, x_final, p, t);
         DEBUG_YFILE   yLOG_value   ("regex"     , rc);
         if (rc <= 0)  {
            DEBUG_YFILE   yLOG_complex ("miss"      , "level %d had no match", c);
            DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         if (rc > 1)  x_matches = 2;
         strlcat (x_final, t  , LEN_RECD);
         strlcat (x_final, "/", LEN_RECD);
         DEBUG_YFILE   yLOG_info    ("x_final"   , x_final);
      }
      /*---(next)------------------------*/
      DEBUG_YFILE   yLOG_info    ("x_final"   , x_final);
      ++c;
      x_len = strlen (x_final);
      p = strtok_r (NULL, q, &r);
      /*---(done)------------------------*/
   }
   /*---(save)---------------------------*/
   DEBUG_YFILE   yLOG_value   ("levels"    , c);
   strlcpy (a_path, x_final, LEN_RECD);
   if (a_depth != NULL)  *a_depth = c;
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return x_matches;
}

char         /*-> tbd --------------------------------[ leaf   [gc.C55.124.30]*/ /*-[01.0000.112.!]-*/ /*-[--.---.---.--]-*/
yFILE_loc               (char *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   int         x_len       =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("can not execute until operational");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(deal with null/empty)-----------*/
   DEBUG_YFILE   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL || a_path [0] == 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_info    ("a_path"    , a_path);
   /*---(save)---------------------------*/
   strlcpy (t, a_path, LEN_RECD);
   rc = yfile_name__path (t, NULL);
   DEBUG_YFILE   yLOG_value   ("path"      , rc);
   --rce;  if (rc != 1) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save)---------------------------*/
   strlcpy (myFILE.f_loc  , t, LEN_RECD);
   DEBUG_YFILE   yLOG_info    ("f_loc"     , myFILE.f_loc);
   sprintf (myFILE.f_title, "%s%s.%s"   , myFILE.f_loc, myFILE.f_name, myFILE.s_ext);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> tbd --------------------------------[ leaf   [gc.C55.124.30]*/ /*-[01.0000.112.!]-*/ /*-[--.---.---.--]-*/
yfile_name__temploc     (char *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tSTAT       s;
   int         x_len       =    0;
   char        t           [LEN_RECD];
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("can not execute until operational");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(deal with null/empty)-----------*/
   DEBUG_YFILE   yLOG_point   ("a_path"    , a_path);
   --rce;  if (a_path == NULL || a_path [0] == 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_info    ("a_path"    , a_path);
   /*---(update)-------------------------*/
   rc = yfile_name__path (a_path, NULL);
   DEBUG_YFILE   yLOG_value   ("path"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        file base name                        ----===*/
/*====================------------------------------------====================*/
static void      o___NAME____________________o (void) {;}

char         /*-> tbd --------------------------------[ leaf   [gc.C55.124.30]*/ /*-[01.0000.112.!]-*/ /*-[--.---.---.--]-*/
yfile_name              (char a_type, char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        x_work      [LEN_RECD]   = "";
   char        x_dir       [LEN_RECD]   = "";
   char        t           [LEN_RECD];
   char       *p           = NULL;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (FMOD_FILE)) {
      DEBUG_YFILE   yLOG_note    ("can not execute until operational");
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(deal with empties)--------------*/
   DEBUG_YFILE   yLOG_point   ("a_name"    , a_name);
   if (a_name == NULL || a_name [0] == 0) {
      DEBUG_YFILE   yLOG_note    ("a_name was null, using defaults");
      strlcpy (myFILE.f_name , YFILE_BLANK, LEN_RECD);
      sprintf (myFILE.f_title, "%s%s.%s"   , myFILE.f_loc, myFILE.f_name, myFILE.s_ext);
      DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(relative vs absolute)-----------*/
   if (a_name [0] == '/')  strlcpy  (x_work, a_name, LEN_RECD);
   else                    snprintf (x_work, LEN_RECD, "%s%s", myFILE.f_loc, a_name);
   DEBUG_YFILE   yLOG_info    ("x_work"    , x_work);
   /*---(strip extensions)---------------*/
   rc = yfile_name__stripext (x_work);
   DEBUG_YFILE   yLOG_value   ("stripext"  , rc);
   /*---(divide out location)------------*/
   p = strrchr (x_work, '/');
   DEBUG_YFILE   yLOG_point   ("p"         , p);
   --rce;  if (p != NULL) {
      DEBUG_YFILE   yLOG_note    ("fully qualified name, with directory");
      *p = 0;
      sprintf (x_dir, "%s/", x_work, LEN_RECD);
      rc = yfile_name__temploc (x_dir);
      if (rc < 0) {
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return rc;
      }
   } else {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for bad characters)-------*/
   p++;
   x_len = strllen (p, LEN_RECD);
   DEBUG_YFILE   yLOG_value   ("x_len"     , x_len);
   /*---(check for regex)----------------*/
   --rce;  if (a_type == 'r' && x_len > 0) {
      if (x_len <= 0) {
         DEBUG_YFILE   yLOG_note    ("file regex empty");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      rc = yfile_name__regex ('f', myFILE.s_ext, x_dir, p, t);
      if (rc <= 0) {
         DEBUG_YFILE   yLOG_note    ("regex not found");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      if (rc >  1) {
         DEBUG_YFILE   yLOG_note    ("too many matches found");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      rc = yfile_name__stripext (t);
      strlcpy (myFILE.f_name , t, LEN_RECD);
   }
   /*---(check for fixed name)-----------*/
   else if (x_len > 0) {
      for (i = 0; i < x_len; ++i) {
         if (strchr (YSTR_FILES, p [i]) != NULL)   continue;
         DEBUG_YFILE   yLOG_note    ("bad character in file name");
         DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
         return rce;
      }
      strlcpy (myFILE.f_name , p         , LEN_RECD);
   }
   /*---(check for empty, again)---------*/
   else {
      strlcpy (myFILE.f_name , YFILE_BLANK, LEN_RECD);
   }
   /*---(report out)---------------------*/
   sprintf (myFILE.f_title, "%s%s.%s", x_dir, myFILE.f_name, myFILE.s_ext);
   DEBUG_YFILE   yLOG_info    ("f_loc"     , myFILE.f_loc);
   DEBUG_YFILE   yLOG_info    ("f_name"    , myFILE.f_name);
   DEBUG_YFILE   yLOG_info    ("f_title"   , myFILE.f_title);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yFILE_name   (char *a_name) { return yfile_name ('-', a_name); }
char yFILE_browse (char *a_name) { return yfile_name ('r', a_name); }

