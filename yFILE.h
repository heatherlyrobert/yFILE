/*============================----beg-of-source---============================*/
#ifndef yFILE
#define yFILE yes




/*===[[ yFILE_base.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
/*---(support)--------------*/
char*       yFILE_version           (void);
/*---(program)--------------*/
char        yFILE_init              (void);
char        yFILE_init_after        (void);
char        yFILE_whoami            (char *a_full, char *a_vernum, char *a_vertxt, char *a_namesake, char *a_ext, char *a_filetype, void *a_handlers, void *a_prepper, void *a_finisher);
char        yFILE_wrap              (void);
/*---(done)-----------------*/



/*===[[ yFILE_test.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/
char*       yFILE__unit             (char *a_question, int a_ref);



/*===[[ yFILE_vers.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(control)--------------*/
char        yFILE_control           (void);
char        yFILE_nocontrol         (void);
/*---(number)---------------*/
char        yFILE_major             (void);
char        yFILE_minor             (void);
char        yFILE_inc               (void);
char        yFILE_vernum            (char *a_ver);
/*---(text)-----------------*/
char        yFILE_vertxt            (char *a_txt);
/*---(done)-----------------*/



/*===[[ yFILE_name.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yFILE_loc               (char *a_path);
char        yFILE_name              (char *a_name);
char        yFILE_browse            (char *a_name);



/*===[[ yFILE_io.c ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yFILE_new               (void);
char        yFILE_reader            (void);
char        yFILE_writer            (void);
char        yFILE_writeas           (char *a_name);



/*===[[ yFILE_dump.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yFILE_dump_add          (char *a_name, char *a_terse, char *a_desc, void *a_provider);
char        yFILE_dump              (char *a_name);



#endif
/*============================----end-of-source---============================*/
