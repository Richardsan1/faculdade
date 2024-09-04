public class Fila {
    private final int[] elementos;
    private int front;
    private int end;
    private final int capacidade;

    public Fila(int capacidade) {
        this.capacidade = capacidade;
        this.elementos = new int[capacidade];
        this.front = 0;
        this.end = -1;
    }

    public void enqueue(int elemento) {
        if (this.end < this.capacidade - 1) {
            this.end++;
            this.elementos[this.end] = elemento;
        }
    }

    public int dequeue() {
        if (this.front <= this.end) {
            int elemento = this.elementos[this.front];
            this.front++;
            return elemento;
        }
        
        return -1;
    }

    public int getFront() {
        if (this.front <= this.end) {
            return this.elementos[this.front];
        }
        
        return -1;
    }

    public boolean isEmpty() {
        return this.front > this.end;
    }

    public boolean isFull() {
        return this.end == this.capacidade - 1;
    }

    public int size() {
        return this.end - this.front + 1;
    }
}