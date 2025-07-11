#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

#define FULL_CAPACITY 20

int main(void)
{
        char storage[FULL_CAPACITY][1000]={0};
        int idx = 0;
        FILE *fptr = fopen("out.txt", "r");
        char str[1000];

        while(fgets(str, 1000, fptr))
        {
                bool seen = false;
                for(int i =0; i< idx; i++)
                {
                        if(strcmp(str, storage[i]) == 0)
                        {
                                seen = true;
                                break;
                        }
                }

                if(!seen)
                {//add to list
                        strcpy(storage[idx], str);
                        idx+=1;
                }
                if(idx == FULL_CAPACITY)
                {
                        break;
                }
        }

        for(int i=0; i < idx; i++)
        {
                printf("(%d) %s\n",i, storage[i]);
        }

        fclose(fptr);
}
