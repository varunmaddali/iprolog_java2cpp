//package iProlog;
import java.util.ArrayList;

class ObStack<T> extends ArrayList<T> {

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
public static void main(final String[] args) {
    ObStack s=new ObStack();
s.push(5);
System.out.println(s.peek());
s.push(6);


System.out.println(s.peek());

  }

}
