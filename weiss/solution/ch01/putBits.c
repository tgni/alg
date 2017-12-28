#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char buf[1024] = {0};
static unsigned int counter = 0;

void initbuf(void)
{
    counter = 0;
    memset(buf, 0, 1024);
}
void Hex2Str(unsigned int N)
{
    if(N>=2){
        Hex2Str(N/2);
    }
    if(counter == 8)
        buf[counter++] = 0x20;
    else if((counter > 8) && ((counter-8) % 9 == 0))
        buf[counter++] = 0x20;
    buf[counter++] = 0x30 + (N%2);
        
}
void padzero(unsigned int len)
{
    int i;
    for(i=0; i<len; i++){
        if(counter == 8)
            buf[counter++] = 0x20;
        else if((counter > 8) && ((counter-8) % 9 == 0))
            buf[counter++] = 0x20;
        buf[counter++] = 0x30;
    }
}
//calculate N's length
int CalN(unsigned int N)
{
   int cc = 1;
   while(N/2){
       cc++; 
       N /= 2;
   }
   return cc;
}
void Putbits(unsigned int N, unsigned int length)
{
    unsigned int Nlen = 0;
    Nlen = CalN(N);
    if(Nlen < length)
        padzero(length - Nlen); 
    Hex2Str(N); 
}
int main(void)
{
    unsigned int tmp = 0x99;
    unsigned int tmp1 = 0x0;
    unsigned int tmp2 = 0xaaaa;
    //we should initbuf before use Putbits. Max Putbits equals 1024 
    initbuf();
    Putbits(tmp,32);
    Putbits(tmp2,32);
    Putbits(tmp2,24);
    Putbits(0x1,1);
    Putbits(0x2,2);
    printf("buf:%s\n",buf);
    //write buf to file
    //ignored
    return 0;
}
