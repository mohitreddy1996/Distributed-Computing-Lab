#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>

#include  "shared_memory_data_structure.h"

void  main(int  argc, char *argv[])
{
     key_t          ShmKEY;
     int            ShmID;
     struct Memory  *ShmPTR;
     
     if (argc != 2) {
          printf("Use: %s #1\n", argv[0]);
          exit(1);
     }

     ShmKEY = ftok(".", 'x');
     ShmID = shmget(ShmKEY, sizeof(struct Memory), 0666);
     if (ShmID < 0) {
          printf("*** shmget error (client) ***\n");
          exit(1);
     }
     printf("	Client has received a shared memory....\n");

     ShmPTR = (struct Memory *) shmat(ShmID, NULL, 0);
     if ((int) ShmPTR == -1) {
          printf("*** shmat error (client) ***\n");
          exit(1);
     }
     printf("	Client has attached the shared memory...\n");

     while (ShmPTR->status != FILLED)
          ;
     printf("	Client found the data is ready...\n");
     printf("	Client found %d in shared memory...\n", ShmPTR->data);
     printf("	Client changing the data from %d to %d...\n", ShmPTR->data, atoi(argv[1]));
     ShmPTR->data = atoi(argv[1]);
     ShmPTR->status = CHANGED;
     printf("	Client has informed server data has been changed...\n");
     shmdt((void *) ShmPTR);
     printf("	Client has detached its shared memory...\n");
     printf("	Client exits...\n");
     exit(0);
}
