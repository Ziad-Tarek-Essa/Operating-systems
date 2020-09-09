#include<stdio.h>
#include<string.h>

int findLRU(int time[], int n);

int main()
{
    int i=0,j=0,n=0,x=0,y=0,no_of_pages,no_of_frames,pages[50],frames[10],k,flag1,flag2,faults=0,counter,time[10],pos,lock[10] ;

    scanf("%d",&no_of_frames );

    char t[50];
    scanf("%s",t);


    int temp;
    do
    {
        scanf("%d", &pages[i]);
        temp=pages[i];
        i++;
    }
    while(temp!=-1);
    no_of_pages=i-1;


    for(i=0; i<no_of_frames; i++)
    {
        frames[i]= -1;
    }


//----------------------------------------------------------------------------------

    if(strcmp(t,"LRU")==0)
    {

        printf("Replacement Policy = %s\n-------------------------------------\n",t);

        printf("Page   Content of Frames\n----   -----------------");
        for(i = 0; i < no_of_pages; ++i)
        {
            flag1 = flag2 = 0;

            for(j = 0; j < no_of_frames; ++j)
            {
                if(frames[j] == pages[i])
                {
                    counter++;
                    time[j] = counter;
                    flag1 = flag2 = 1;

                    printf("\n");
                    if(pages[1]>9)
                    {
                        printf("%d     ",pages[i]);
                    }
                    else
                    {
                        printf("0%d     ",pages[i]);
                    }

                    for(j=0; j<no_of_frames && frames[j]!=-1; ++j)
                    {
                        if(frames[j]>9)
                        {
                            printf("%d ",frames[j]);
                        }
                        else
                        {
                            printf("0%d ",frames[j]);
                        }
                    }
                    break;
                }
            }

            if(flag1 == 0)
            {
                for(j = 0; j < no_of_frames; ++j)
                {
                    if(frames[j] == -1)
                    {
                        counter++;
                        frames[j] = pages[i];
                        time[j] = counter;
                        flag2 = 1;
                        printf("\n");
                        if(pages[1]>9)
                        {
                            printf("%d      ",pages[i]);
                        }
                        else
                        {
                            printf("0%d     ",pages[i]);
                        }

                        for(j=0; j<no_of_frames && frames[j]!=-1; ++j)
                        {
                            if(frames[j]>9)
                            {
                                printf("%d ",frames[j]);
                            }
                            else
                            {
                                printf("0%d ",frames[j]);
                            }
                        }

                        break;
                    }
                }
            }

            if(flag2 == 0)
            {
                pos = findLRU(time, no_of_frames);
                counter++;
                faults++;
                frames[pos] = pages[i];
                time[pos] = counter;

                printf("\n");
                if(pages[1]>9)
                {
                    printf("%d F   ",pages[i]);
                }
                else
                {
                    printf("0%d F   ",pages[i]);
                }

                for(j=0; j<no_of_frames && frames[j]!=-1; ++j)
                {
                    if(frames[j]>9)
                    {
                        printf("%d ",frames[j]);
                    }
                    else
                    {
                        printf("0%d ",frames[j]);
                    }
                }


            }

        }
        printf("\n");
    }
//-------------------------------------------------------------------------------------
    if(strcmp(t,"FIFO")==0)
    {
        printf("Replacement Policy = %s\n-------------------------------------\n",t);

        printf("Page   Content of Frames\n----   -----------------\n");
        for(i=0; i<no_of_pages; i++)
        {
            flag1=flag2=0;
            for(k=0; k<no_of_frames; k++)
            {
                if(frames[k]==pages[i])
                {
                    flag1=flag2=1;
                    if(pages[1]>9)
                    {
                        printf("%d     ",pages[i]);
                    }
                    else
                    {
                        printf("0%d     ",pages[i]);
                    }

                    for(k=0; k<no_of_frames && frames[k]!=-1; k++)
                    {
                        if(frames[k]>9)
                        {
                            printf("%d ",frames[k]);
                        }
                        else
                        {
                            printf("0%d ",frames[k]);
                        }
                    }
                    break;
                }

            }

            if (flag1==0)
            {
                for(k = 0; k < no_of_frames; ++k)
                {
                    if(frames[k] == -1)
                    {
                        frames[k] = pages[i];
                        flag2 = 1;
                        if(pages[1]>9)
                        {
                            printf("%d     ",pages[i]);
                        }
                        else
                        {
                            printf("0%d     ",pages[i]);
                        }
                        for(k=0; k<no_of_frames && frames[k]!=-1; k++)
                        {
                            if(frames[k]>9)
                            {
                                printf("%d ",frames[k]);
                            }
                            else
                            {
                                printf("0%d ",frames[k]);
                            }
                        }
                        break;

                    }
                }

            }

            if (flag2==0)
            {
                frames[j]=pages[i];
                j=(j+1)%no_of_frames;
                faults++;
                if(pages[1]>9)
                {
                    printf("%d F   ",pages[i]);
                }
                else
                {
                    printf("0%d F   ",pages[i]);
                }
                for(k=0; k<no_of_frames  && frames[k]!=-1; k++)
                    if(frames[k]>9)
                    {
                        printf("%d ",frames[k]);
                    }
                    else
                    {
                        printf("0%d ",frames[k]);
                    }

            }
            printf("\n");
        }

    }
//------------------------------------------------------------------------------------------------------------------
    if(strcmp(t,"CLOCK")==0)
    {
        printf("Replacement Policy = %s\n-------------------------------------\n",t);

        printf("Page   Content of Frames\n----   -----------------\n");
        i=0;

       for(i=0; i<no_of_pages; i++){

             for(k=0; k<no_of_frames; k++){
                if(pages[i]==frames[k]){
                    flag1=1;
                    lock[k]=1;
                    break;
                }
                else
                    flag1=0;
            }
            if(flag1==1) {
                k=0;
                if(pages[1]>9){printf("%d     ",pages[i]);}
                else{printf("0%d     ",pages[i]);                }

                for(k=0; k<no_of_frames && frames[k]!=-1; k++){
                    if(frames[k]>9){printf("%d ",frames[k]);                    }
                    else       {  printf("0%d ",frames[k]);                    }
                }
                printf("\n");
            }
            else{
                k=0;
               for(k=0; k<no_of_frames; k++){
                    if(frames[y]==-1){
                        frames[y]=pages[i];
                        lock[y]=1;
                        x=0;
                        if(pages[1]>9) { printf("%d     ",pages[i]); }
                        else{ printf("0%d     ",pages[i]); }
                        for(k=0; k<no_of_frames && frames[k]!=-1; k++){
                            if(frames[k]>9){ printf("%d ",frames[k]); }
                            else{ printf("0%d ",frames[k]);}
                        }
                        y++;
                        printf("\n");
                        break;
                    }
                    else{
                        faults++;
                        if(n>=no_of_frames)
                            n=0;
                        while(lock[n]!=0){
                            lock[n]=0;
                            //printf("%d",n);
                            n++;
                            if(n>=no_of_frames)
                                n=0;
                        }
                        frames[n]=pages[i];
                        lock[n]=1;
                        n++;
                        x=0;
                        if(pages[1]>9){ printf("%d F   ",pages[i]); }
                        else  {  printf("0%d F   ",pages[i]); }

                        for(k=0; k<no_of_frames && frames[k]!=-1; k++){
                            if(frames[k]>9){ printf("%d ",frames[k]);  }
                            else{    printf("0%d ",frames[k]);   }
                        }
                        printf("\n");
                        break;
                    }
                }
            }

        }

    }



//--------------------------------------------------------------------------------------------------------
    printf("-------------------------------------");
    printf("\nNumber of page faults = %d\n", faults);
    return 0;
}

int findLRU(int time[], int n)
{
    int i, minimum = time[0], pos = 0;

    for(i = 1; i < n; ++i)
    {
        if(time[i] < minimum)
        {
            minimum = time[i];
            pos = i;
        }
    }

    return pos;
}
