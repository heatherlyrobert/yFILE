/*============================----beg-of-source---============================*/
#ifndef yFILE_PRIV
#define yFILE_PRIV yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "file management"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "apollodorus-bibliothikarios (librarian)"
#define     P_HERITAGE  "librarian of alexandria and author"
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yFILE"
#define     P_FULLNAME  "/usr/local/lib64/libyFILE"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, break away from yVIKEYS"
#define     P_VERNUM    "2.0c"
#define     P_VERTXT    "most name logic cleaned, improved, and unit tested"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/


/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <dirent.h>            /* clibc  directory reading and decoding    */
#include    <sys/stat.h>          /* clibc  standard file handling            */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yKEYS.h>             /* heatherly vi-keys key handling           */
#include    <yMODE.h>             /* heatherly vi-keys mode tracking          */
#include    <yCMD.h>              /* heatherly vi-keys command processing     */
#include    <ySRC.h>              /* heatherly vikeys source editing          */
#include    <yMAP.h>              /* heatherly vi-keys location management    */
/*---(custom other)----------------------*/
#include    <yPARSE.h>            /* heatherly file reading and writing       */
#include    <yREGEX.h>            /* heatherly regular expressions            */
/*---(done)------------------------------*/


typedef     struct dirent     tDIRENT;
typedef     struct stat       tSTAT;
#define     YFILE_BLANK      "untitled"


typedef    struct    cMY    tMY;
struct cMY {
   /*---(source)----------*/
   char        s_prog      [LEN_LABEL];     /* program name                   */
   char        s_fullname  [LEN_DESC];      /* program name with path         */
   char        s_vernum    [LEN_LABEL];     /* program version number         */
   char        s_vertxt    [LEN_DESC];      /* program version text           */
   char        s_namesake  [LEN_DESC];      /* program greek name             */
   char        s_ext       [LEN_LABEL];     /* file extention                 */
   char        s_filetype  [LEN_DESC];      /* description of file extension  */
   /*---(functions)------------*/
   char      (*e_handlers) (void);
   char      (*e_prepper)  (char a_pass);
   char      (*e_finisher) (char a_pass);
   /*---(file)-----------------*/
   char        f_control;                   /* file version control flag      */
   char        f_vernum    [LEN_LABEL];     /* file version number            */
   char        f_vertxt    [LEN_HUND];      /* file version text              */
   char        f_loc       [LEN_RECD ];     /* specific file location         */
   char        f_name      [LEN_RECD ];     /* full file name                 */
   char        f_title     [LEN_RECD ];     /* specific file base name        */
   int         f_lines;                     /* file line number               */
   char        f_recd      [LEN_RECD ];     /* current file record            */
   char        f_type      [LEN_RECD ];     /* current record verb            */
   /*---(done)-----------------*/
};
extern tMY         myFILE;



/*===[[ yFILE_test.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yfile__unit_quiet       (void);
char        yfile__unit_loud        (void);
char        yfile__unit_end         (void);
/*---(stubs)----------------*/
char        yfile__unit_handlers    (void);
char        yfile__unit_prepper     (char a_pass);
char        yfile__unit_finisher    (char a_pass);
/*---(done)-----------------*/



/*===[[ yFILE_vers.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(control)--------------*/
char        yfile_vers_controlled   (char *a_yes);
char        yFILE_control           (void);
char        yFILE_nocontrol         (void);
/*---(number)---------------*/
char        yfile_vers_bump         (char a_type);
char        yFILE_major             (void);
char        yFILE_minor             (void);
char        yFILE_inc               (void);
char        yFILE_vernum            (char *a_ver);
/*---(done)-----------------*/



/*===[[ yFILE_name.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(regex)----------------*/
char        yfile__name_prep        (char a_type, char *a_ext, char *a_base, char *a_entry, char *r_match, char *r_elen);
char        yfile__name_regex       (char a_type, char *a_ext, char *a_base, char *a_entry, char *r_match);
/*---(ext)------------------*/
char        yfile__name_stripext    (char *a_full);
/*---(path)-----------------*/
char        yfile__name_path        (char *a_path);
char        yFILE_loc               (char *a_path);



#endif
