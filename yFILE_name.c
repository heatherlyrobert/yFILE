/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yFILE.h"
#include    "yFILE_priv.h"



static DIR *s_dir  = NULL;          /* directory pointer              */



/*====================------------------------------------====================*/
/*===----                  regular expression matching                 ----===*/
/*====================------------------------------------====================*/
static void      o___REGEX___________________o (void) {;}

char
yfile__name_prep        (char a_type, char *a_ext, char *a_path, char *a_entry, char *r_match, char *r_elen)
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
   /*---(open directory)-----------------*/
   s_dir = opendir (a_path);
   DEBUG_YFILE   yLOG_spoint  (s_dir);
   --rce;  if (s_dir == NULL) {
      DEBUG_YFILE   yLOG_sexitr  (__FUNCTION__, rce);
      return  rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yfile__name_regex       (char a_type, char *a_ext, char *a_path, char *a_entry, char *r_match)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tDIRENT    *x_file      = NULL;          /* directory entry pointer        */
   char        x_full      [LEN_RECD];
   tSTAT       s;
   char        x_elen      =    0;
   int         x_len       =    0;
   int         x_checked   =    0;
   int         x_matches   =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YFILE   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   rc = yfile__name_prep (a_type, a_ext, a_path, a_entry, r_match, &x_elen);
   DEBUG_YFILE   yLOG_value   ("prep"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YFILE   yLOG_delim   ("a_path"    , a_path);
   DEBUG_YFILE   yLOG_delim   ("a_entry"   , a_entry);
   while (1) {
      DEBUG_YFILE   yLOG_note    ("processing entries");
      /*---(read a directory entry)------*/
      x_file = readdir (s_dir);
      DEBUG_YFILE   yLOG_point   ("x_file"    , x_file);
      if (x_file == NULL)  break;
      ++x_checked;
      /*---(filter basics)------------------*/
      x_len = strlen (x_file->d_name);
      DEBUG_YFILE   yLOG_value   ("x_len"     , x_len);
      if (x_len < 1) continue;
      DEBUG_YFILE   yLOG_delim   ("->d_name"  , x_file->d_name);
      if (x_file->d_name [0] == '.') {
         DEBUG_YFILE   yLOG_note    ("hidden file, prefixed with dot (.)");
         continue;
      }
      /*---(stat it)------------------------*/
      sprintf (x_full, "%s%s", a_path, x_file->d_name);
      rc = stat (x_full, &s);
      DEBUG_YFILE   yLOG_value   ("stat"      , rc);
      if (rc < 0) continue;
      DEBUG_YFILE   yLOG_value   ("mode"      , s.st_mode);
      if (a_type == 'd' && !S_ISDIR (s.st_mode)) {
         DEBUG_YFILE   yLOG_note    ("looking for dirs, this is not one");
         continue;
      }
      if (a_type == 'f' && !S_ISREG (s.st_mode)) {
         DEBUG_YFILE   yLOG_note    ("looking for reg files, this is not one");
         continue;
      }
      /*---(filter by extension)---------*/
      if (x_elen > 0) {
         DEBUG_YFILE   yLOG_info    ("p.ext"     , x_file->d_name + x_len - x_elen);
         if (strncmp (x_file->d_name + x_len - x_elen, a_ext, x_elen) != 0) {
            DEBUG_YFILE   yLOG_note    ("suffix does not match, SKIP");
            continue;
         }
      }
      /*---(filter by name)--------------*/
      rc = yREGEX_filter (x_file->d_name);
      DEBUG_YFILE   yLOG_value   ("exec"      , rc);
      if (rc <= 0) {
         DEBUG_YFILE   yLOG_note    ("regex failed to match");
         continue;
      }
      /*---(check for bad characters)-------*/
      for (i = 0; i < x_len; ++i) {
         if (strchr (YSTR_FILES, x_file->d_name [i]) != NULL)   continue;
         DEBUG_YFILE   yLOG_note    ("bad character in target name");
         continue;
      }
      /*---(save)------------------------*/
      DEBUG_YFILE   yLOG_note    ("found a match");
      ++x_matches;
      if (x_matches == 1 && r_match != NULL) {
         strlcpy (r_match, x_file->d_name, LEN_RECD);
      }
      /*---(done)------------------------*/
   }
   DEBUG_YFILE   yLOG_value   ("x_checked" , x_checked);
   DEBUG_YFILE   yLOG_value   ("x_matches" , x_matches);
   /*---(close dir)----------------------*/
   DEBUG_YFILE   yLOG_note    ("closing directory");
   rc = closedir (s_dir);
   DEBUG_YFILE   yLOG_value   ("close_rc"  , rc);
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return x_matches;
}



/*====================------------------------------------====================*/
/*===----                      extension handling                      ----===*/
/*====================------------------------------------====================*/
static void      o___EXT_____________________o (void) {;}

char
yfile__name_stripext    (char *a_full)
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
yfile__name_path        (char *a_path)
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
         rc = yfile__name_regex ('d', NULL, x_final, p, t);
         DEBUG_YFILE   yLOG_value   ("matches"   , rc);
         if (rc != 1)  {
            DEBUG_YFILE   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         strlcat (x_final, t  , LEN_RECD);
         strlcat (x_final, "/", LEN_RECD);
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
   /*---(complete)-----------------------*/
   DEBUG_YFILE   yLOG_exit    (__FUNCTION__);
   return c;
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
   rc = yfile__name_path (t);
   DEBUG_YFILE   yLOG_value   ("path"      , rc);
   --rce;  if (rc < 0) {
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
yfile__name_temploc     (char *a_path)
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
   rc = yfile__name_path (a_path);
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
yfile__name             (char a_type, char *a_name)
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
   rc = yfile__name_stripext (x_work);
   DEBUG_YFILE   yLOG_value   ("stripext"  , rc);
   /*---(divide out location)------------*/
   p = strrchr (x_work, '/');
   DEBUG_YFILE   yLOG_point   ("p"         , p);
   --rce;  if (p != NULL) {
      DEBUG_YFILE   yLOG_note    ("fully qualified name, with directory");
      *p = 0;
      sprintf (x_dir, "%s/", x_work, LEN_RECD);
      rc = yfile__name_temploc (x_dir);
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
      rc = yfile__name_regex ('f', myFILE.s_ext, x_dir, p, t);
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
      rc = yfile__name_stripext (t);
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

char yFILE_name   (char *a_name) { return yfile__name ('-', a_name); }
char yFILE_browse (char *a_name) { return yfile__name ('r', a_name); }

