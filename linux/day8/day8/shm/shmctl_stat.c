#include <func.h>

int main()
{
    int shmid;
    shmid=shmget(1000,4096,0600|IPC_CREAT);
    ERROR_CHECK(shmid,-1,"shmget");
    printf("shmid=%d\n",shmid);
    struct shmid_ds buf;
    int ret=shmctl(shmid,IPC_STAT,&buf);
    ERROR_CHECK(ret,-1,"shmctl");
    printf("uid=%d,mode=%o,size=%ld,attach=%ld\n",buf.shm_perm.uid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_nattch);
    return 0;
}

