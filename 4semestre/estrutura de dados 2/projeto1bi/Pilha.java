import java.util.EmptyStackException;

public class Pilha<T> {
    private Node<T> top;
    private int size;

    public void push(T item) {
        Node<T> newNode = new Node<>(item);
        newNode.setNext(top);
        top = newNode;
        size++;
    }

    public T pop() {
        if (isEmpty()) throw new EmptyStackException();
        T item = top.getData();
        top = top.getNext();
        size--;
        return item;
    }

    public T peek() {
        if (isEmpty()) throw new EmptyStackException();
        return top.getData();
    }

    public boolean isEmpty() {
        return top == null;
    }

    public int size() {
        return size;
    }
}