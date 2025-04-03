//  uma linked list consegue ser muito simples
// teoricamente essa classe nem é necessária, mas é interessante para visualizar melhor
// voce pode usar só os nós, mas para um controle melhor, essa classe é interessante
// ela possui o primeiro e o ultimo nó, e o tamanho da lista

// os metodos de adicionar dependem da necessidade, pode ser adicionado no final, no começo, em uma posição específica

public class ListaLinkada{
    private Node<Integer> primeiro;
    private Node<Integer> ultimo;
    private int tamanho;

    public ListaLinkada(){
        this.primeiro = null;
        this.ultimo = null;
        this.tamanho = 0;
    }
    // esse metodo sempre adiciona no final da lista
    //  1 - 2 - *
    //  1 - 2 - 3 - *
    public void adicionar(int elemento){
        // cria o nó
        Node<Integer> novo = new Node<>(elemento);
        // se a lista está vazia, o novo nó é o primeiro e o ultimo
        if(primeiro == null){
            primeiro = novo;
            ultimo = novo;
            // se não, o novo nó é o proximo do ultimo e o ultimo se torna o novo nó
        }else{
            ultimo.setNext(novo);
            ultimo = novo;
        }
        tamanho++;
    }
    public void adicionarPorIndice(int elemento, int index){
        // se o index ta fora do range, não faz nada
        if(index < 0 || index > tamanho){
            System.out.println("Indice inválido!");
            return;
        }
        // se o index é 0, adiciona no começo
        Node<Integer> novo = new Node<>(elemento);
        if(index == 0){
            novo.setNext(primeiro);
            primeiro = novo;
            tamanho++;
            return;
        }
        // se o index é o tamanho, adiciona no final
        if(index == tamanho){
            ultimo.setNext(novo);
            ultimo = novo;
            tamanho++;
            return;
        }
        // se não, percorre a lista até o index e adiciona o novo nó
        Node<Integer> atual = primeiro;
        for(int i = 0; i < index - 1; i++){
            // essa linha é o que nos faz andar pela lista
            atual = atual.getNext();
        }
        // ao achar a posição, essa função não substitui o nó, adiciona o novo nó na posicao atual e o nó atual se torna o proximo do novo nó
        // é possivel fazer a substituição caso necessario
        novo.setNext(atual.getNext());
        atual.setNext(novo);
        tamanho++;
        // seria tipo
        // atual.setData(elemento);
    }

    // esse metodo sempre remove no inicio da lista, caso necessario é possivel remover por um indice
    //  1 - 2 - 3 - *
    //  2 - 3 - *
    public void remover(){
        if(primeiro == null){
            System.out.println("Lista vazia!");
        }
        // se o proximo nó é null então a lista se esvaziou, portanto ultimo é null
        if (primeiro.getNext() == null){
            ultimo = null;
        }
        primeiro = primeiro.getNext();
        tamanho--;
    }

    public void removerPeloIndice(int index){
        // cria um objeto para percorrer a lista
        Node<Integer> atual = primeiro;
        // se a lista está vazia, não faz nada
        if(atual == null){
            System.out.println("Lista vazia!");
            return;
        }
        // se o index esta fora do range, não faz nada
        if (index < 0 || index > tamanho){
            System.out.println("Indice inválido!");
            return;
        }
        // se o index é 0, remove o primeiro
        if (index == 0){
            remover();
            return;
        }
        // vai percorrendo a lista até encontrar o anterior do index
        for (int i = 0; i < index-1; i++){
            atual = atual.getNext();
        }
        // após encontrar o anterior ao que queremos remover, 
        // simplesmente esquecemos ele e adicionamos o proximo do proximo nó
        atual.setNext(atual.getNext().getNext());
        // 0 - 1 - 2
        // 0 - 2
    }

    public int getTamanho(){
        return tamanho;
    }

    public Node<Integer> getPrimeiro(){
        return primeiro;
    }

    public Node<Integer> getUltimo(){
        return ultimo;
    }
    // só pra visualizar
    public void imprimir(){
        Node<Integer> atual = primeiro;
        while(atual != null){
            System.out.print(atual.getData() + " ");
            atual = atual.getNext();
        }
        System.out.println();
    }
}