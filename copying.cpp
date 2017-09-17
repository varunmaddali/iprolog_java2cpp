#include<iostream>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>
#include<fcntl.h>

int main()
 {
   FILE *f_point;         
   

   struct timeval t1,t2;  //time structure predefined
   time_t end,start; 
 double time,start,end;
    
   int nread,i,j;

   char ch ;
    int size =1024;  
   ch ='v';//one character v .
int f1,f2;
 

 for(i=0;i<12;i++)    // here we can put 18 for 128 mb           
   {
    char block[size];
    f_point=fopen("fileA1.txt","w"); // open the file A.

    for(j=0;j<size;j++)
       {
         fputc(ch,f_point);          //Writing file A
       }
    fclose(f_point);

    f1 =open("fileA1.txt" , O_RDONLY);                          //read only 
    f2 =open("fileB1.txt" , O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR);

    gettimeofday(&t1,0);         // t1
    start=(double)t1.tv_sec+(double)t1.tv_usec*0.000001;
                 

    while ((nread = read(f1, block, sizeof(block))) > 0) //copying 
         {
           write(f2,block,nread);
          }

    gettimeofday(&t2,0);        // t2
    end=(double)t2.tv_sec+(double)t2.tv_usec*0.000001; 

    time=end-start;          // calculating time
std::cout <<"\nTime for copying ";
std::cout <<size;
std::cout <<" bytes is";
std::cout <<time;

    size=size*2;       //increase size by 2
   } 
return 0;
 }
