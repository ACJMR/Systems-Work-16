#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  key = ftok("file",'R');
  shmid = shmget(key, 200, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *)0, 0);

  if(!data[0]){
    printf("segment created!\n");
  }
  else{
    printf("contents: %s\n",data);
  }

  printf("Do you want to change contents?\n");
  char answer[200];
  fgets(answer,200,stdin);

  if (!strcmp(answer,"yes\n")){
    printf("Please enter string to be stored:\n");
    fgets(answer,200,stdin);
    answer[strlen(answer)-1] = 0;
    strcpy(data,answer);
  }

  printf("Do you want to delete contents?\n");
  fgets(answer,200,stdin);
  if (!strcmp(answer,"yes\n")){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("Deleted\n");
  }
  return 0;
}
