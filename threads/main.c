#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>
int arr[100][100];
int arr1[100][100];
int arr2[100][100];
int x,y,x1,y1;
struct v {
   int i; /* row */
   int j; /* column */
};
void *runner(void *param) {
   struct v *data = param; // the structure that holds our data
   int n, sum = 0; //the counter and sum

   //Row multiplied by column
   for(n = 0; n< x; n++){
      sum += arr[data->i][n] * arr1[n][data->j];
   }
   //assign the sum to its coordinate
   arr2[data->i][data->j] = sum;

   //Exit the thread
   pthread_exit(0);
}
int space_remover(char* met2ta3a[],char command[])
{
    int i=0;
    met2ta3a[i]=strtok(command," ");
//starts with space
    if (met2ta3a[i]==NULL)
    {
        return 1;
    }
    while(met2ta3a[i] != NULL)
    {
        i++;
        met2ta3a[i]=strtok(NULL," ");
    }
    return 1;
}
int main()
{
    FILE *fp1,*fp2;
    char str[100];
    char *met[100];
    int kk=0,i,j;
    fp1=fopen("INPUT.txt","r");
    fp2=fopen("output.txt","w");
    if (!fp1)
        return 1;
   // fscanf(fp1,"%[^\n]", str);
   fgets(str, 100, fp1);
    space_remover(met,str);
    x=atoi(met[1]);
    y=atoi(met[0]);

  for(i=0;i<y;i++){
    fgets(str, 100, fp1);
     space_remover(met,str);
   for(j=0;j<x;j++){
    //puts(met[j]);
    arr[i][j]=atoi(met[j]);
   }
   met[0]='\0';
   }


   for (i = 0; i < y; i++) {
        for (j = 0; j < x; j++) {
                printf("%d  ",arr[i][j]);
  }
  printf("\n");
  }



//  printf("%d   %d",arr[0][3],arr[0][4]);



printf("\n\n\n\n\n\n");

   fgets(str, 100, fp1);
    space_remover(met,str);
    x1=atoi(met[1]);
    y1=atoi(met[0]);
    int arr1[y1][x1];
  for(i=0;i<y1;i++){
    fgets(str, 100, fp1);
     space_remover(met,str);
   for(j=0;j<x1;j++){
    //puts(met[j]);
    arr1[i][j]=atoi(met[j]);
   }
   }


   for (i = 0; i < y1; i++) {
        for (j = 0; j < x1; j++) {
                printf("%d  ",arr1[i][j]);
  }
  printf("\n");
  }

  int count = 0;
   for(i = 0; i < y; i++) {
      for(j = 0; j < x1; j++) {
         //Assign a row and column for each thread
         struct v *data = (struct v *) malloc(sizeof(struct v));
         data->i = i;
         data->j = j;
         /* Now create the thread passing it data as a parameter */
         pthread_t tid;       //Thread ID
         pthread_attr_t attr; //Set of thread attributes
         //Get the default attributes
         pthread_attr_init(&attr);
         //Create the thread
         pthread_create(&tid,&attr,runner,data);
         //Make sure the parent waits for all thread to complete
         pthread_join(tid, NULL);
         count++;
      }
   }

    printf("\n\n\n\n");

     for (i = 0; i < y; i++) {
        for (j = 0; j < x1; j++) {
                printf("kokoooooooo\n");
                printf("%d  ",arr2[i][j]);
  }
  printf("\n");
  }


    fclose(fp1);
    fclose(fp2);
    return 0;
}
