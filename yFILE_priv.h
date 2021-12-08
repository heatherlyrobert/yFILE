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
#define     P_VERNUM    "2.0b"
#define     P_VERTXT    "most version logic cleaned, improved, and unit tested"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/


/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
/*---(custom core)-----------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
/*---(custom vikeys)---------------------*/
#include    <yKEYS.h>             /* heatherly vi-keys key handling           */
#include    <yMODE.h>             /* heatherly vi-keys mode tracking          */
/*---(custom other)----------------------*/
#include    <yPARSE.h>            /* heatherly file reading and writing       */
/*---(done)------------------------------*/



typedef    struct    cMY    tMY;
struct cMY {
   /*---(file)-----------------*/
   char        f_control;                   /* file version control flag      */
   char        f_vernum    [LEN_LABEL];     /* file version number            */
   char        f_vertxt    [LEN_HUND];      /* file version text              */
   /*---(done)-----------------*/
};
extern tMY         myFILE;



/*===[[ yFILE_test.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yfile__unit_quiet       (void);
char        yfile__unit_loud        (void);
char        yfile__unit_end         (void);



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



#endif
