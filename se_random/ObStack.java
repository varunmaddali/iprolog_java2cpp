//package iProlog;
import java.util.ArrayList;

class ObStack<T> extends ArrayList<T> {
public static int[] a = new int[15];

  private static final long serialVersionUID = 1L;

  final T pop() {
    final int last = this.size() - 1;
    return this.remove(last);
  }

  final void push(final T O) {
    add(O);
  }

  final T peek() {
    return get(this.size() - 1);
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


public static void main(final String[] args) {
random(6);
    ObStack s=new ObStack();
s.push(a[1]);
System.out.println(s.peek());
s.push(a[2]);


System.out.println(s.peek());

  }

}