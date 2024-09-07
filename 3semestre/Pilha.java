public class Pilha {
    private final String[] items;
    private int top;
    private final int capacity;

    public Pilha(int capacity) {
        this.capacity = capacity;
        this.items = new String[capacity];
        this.top = -1;
    }

    public void push(String elemento) {
        if (this.top < this.capacity - 1) {
            this.top++;
            this.items[this.top] = elemento;
        }
    }

    public String pop() {
        if (this.top != -1) {
            String elemento = this.items[this.top];
            this.top--;
            return elemento;
        }
        
        return null;
    }

    public String topElement() {
        if (this.top != -1) {
            return this.items[this.top];
        }
        
        return null;
    }
    public int getTop() {
        return this.top;
    }

    public boolean isEmpty() {
        return this.top == -1;
    }

    public boolean isFull() {
        return this.top == this.capacity - 1;
    }

    public int size() {
        return this.top + 1;
    }
}