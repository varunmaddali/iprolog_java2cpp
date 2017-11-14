import java.io.*;
//package iProlog;
/**
 * representation of a clause
 */
class Clause {
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
for(int i=0;i<=len-1;i++)
System.out.print(hgs[i]);
System.out.println("");
for(int i=0;i<=len-1;i++)
System.out.print(xs[i]);


}

public static void main(String[] args)
{
 int r[]={2,3,4,5,6};
 Clause c=new Clause(5,r,1,7,r);
 c.print_values();
}
}

