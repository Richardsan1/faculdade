public class Pilha {
    private final int[] elementos;
    private int top;
    private final int capacidade;

    public Pilha(int capacidade) {
        this.capacidade = capacidade;
        this.elementos = new int[capacidade];
        this.top = -1;
    }

    public void push(int elemento) {
        if (this.top < this.capacidade - 1) {
            this.top++;
            this.elementos[this.top] = elemento;
        }
    }

    public int pop() {
        if (this.top != -1) {
            int elemento = this.elementos[this.top];
            this.top--;
            return elemento;
        }
        
        return -1;
    }

    public int getTop() {
        if (this.top != -1) {
            return this.elementos[this.top];
        }
        
        return -1;
    }

    public boolean isEmpty() {
        return this.top == -1;
    }

    public boolean isFull() {
        return this.top == this.capacidade - 1;
    }

    public int size() {
        return this.top + 1;
    }
}