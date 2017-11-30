import java.io.*;
//package iProlog;
/**
 * representation of a clause
 */
class Clause {

public static int[] a = new int[15];
  Clause(final int len, final int[] hgs, final int base, final int neck, final int[] xs) {
    this.hgs = hgs; // head+goals pointing to cells in cs
    this.base = base; // heap where this starts
    this.len = len; // length of heap slice
    this.neck = neck; // first after the end of the head
    this.xs = xs; // indexables in head
  }

  final int len;
  final int[] hgs;
  final int base;
  final int neck;
  final int[] xs;
void print_values()
{
System.out.println("the values are len:"+len);
System.out.println("the values are base:"+base);
System.out.println("the values are neck:"+neck);
for(int i=0;i<=4;i++)
System.out.println(hgs[i]);
System.out.println("");
for(int i=0;i<=4;i++)
System.out.println(xs[i]);


}

public static void random(int k)
{
int f= 435,b=786,m=85;
a[0]=6;
int i=0;
while(i<10)
{
int result=((a[i]*f)*b)%m;
i++;
a[i]=result;
}
}

public static void main(String[] args)
{
random(6);
int o=a[1];
int o1=a[2];
int o2=a[3];
int o3=a[4];
int o4=a[5];
 int r[]={o,o1,o2,o3,o4};
 Clause c=new Clause(a[6],r,a[7],a[8],r);
 c.print_values();
}
}