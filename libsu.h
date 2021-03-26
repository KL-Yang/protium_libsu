#ifndef H_LIBSU_SRC_LIBSU_PROTIUM
#define H_LIBSU_SRC_LIBSU_PROTIUM

#define SU_READONLY 0
#define SU_CREATE   1
#define SU_UPDATE   2
#define SU_SUCCESS  0

#define SU_INT16    0
#define SU_INT32    1
#define SU_FLOAT    2
#define SU_IBMF     3   //ibm float, unlikely
#define SU_UNKNOWN  4

typedef struct protium_suid_struct * SUID_t;

int su_open(SUID_t *id, const char *path, int flag);
int su_ninst(SUID_t id);
int su_nsamp(SUID_t id, int ns);    //get or set ns
int su_read(SUID_t id, const char *name, void *buff, int first, int nmemb);
int su_write(SUID_t id, const char *name, void *buff, int first, int nmemb);
int su_close(SUID_t id);
//TODO: su_translate(id, SU_MAP_NAME/SU_MAP_INFO), translate
//SU_MAP_NAME: only translate names
//SU_MAP_INFO: redifine all of the su_attr_t field
//two type of translate

#endif
