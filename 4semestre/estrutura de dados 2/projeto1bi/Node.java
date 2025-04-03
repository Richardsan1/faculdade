public class Node<T>{
    private T data;
    private Node<T> next;
    private Node<T> previous;
    
    public Node (T data){
        this.data = data;
        this.next = null;
        this.previous = null;
    }
    public Node (T data, Node<T> previous, Node<T> next){
        this.data = data;
        this.next = next;
        this.previous = previous;
    }

    public T getData(){
        return data;
    }
    public void setData(T data){
        this.data = data;
    }
    // metodos para lista linkada
    public Node<T> getPrevious(){
        return previous;
    }
    public void setPrevious(Node<T> previous){
        this.previous = previous;
    }
    public Node<T> getNext(){
        return next;
    }
    public void setNext(Node<T> next){
        next.previous = this;
        this.next = next;
    }

    // mesmos metodos da lista linkada, mas com nomes diferentes 
    // para semantica da BST
    public Node<T> getLeft(){
        return previous;
    }
    public void setLeft(Node<T> left){
        this.previous = left;
    }
    public Node<T> getRight(){
        return this.next;
    }
    public void setRight(Node<T> right){
        this.next = right;
    }
}