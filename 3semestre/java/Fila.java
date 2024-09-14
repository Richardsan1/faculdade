public class Fila {
    private final String[] elementos;
    private int front;
    private int end;
    private final int capacidade;

    public Fila(int capacidade) {
        this.capacidade = capacidade;
        this.elementos = new String[capacidade];
        this.front = 0;
        this.end = -1;
    }

    public void enqueue(String elemento) {
        if (this.end < this.capacidade - 1) {
            this.end++;
            this.elementos[this.end] = elemento;
        }
    }

    public String dequeue() {
        if (this.front <= this.end) {
            String elemento = this.elementos[this.front];
            this.front++;
            return elemento;
        }
        return null;
    }

    public String getFront() {
        if (this.front <= this.end) {
            return this.elementos[this.front];
        }
        
        return null;
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

    public int resetFront() {
        return this.front = 0;
    }
}