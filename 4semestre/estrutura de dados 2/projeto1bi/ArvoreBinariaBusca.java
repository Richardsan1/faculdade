public class ArvoreBinariaBusca{
    private Node<Integer> root;
    
    public ArvoreBinariaBusca(){
        root = null;
    }
    public void inserir(int data){
        // cria o nó a ser inserido
        Node<Integer> novo = new Node<>(data);
        // se a arvore estiver vazia, o novo nó é a raiz
        if (this.root == null){
            this.root = novo;
            return;
        } 

        // salva o nó que estamos comparando e seu anterior
        Node<Integer> atual = this.root;
        Node<Integer> anterior = null;
        // enquanto não chegamos em uma folha
        while (atual != null){
            anterior = atual;
            // se o dado a ser inserido é menor que o atual, vamos para a esquerda
            if (data < atual.getData()){
                atual = atual.getLeft();
            } 
            // se o dado a ser inserido é maior que o atual, vamos para a direita
            else if (data > atual.getData()){
                atual = atual.getRight();
            }
            // se o dado a ser inserido é igual ao atual, não fazemos nada
            // dependendo da implementação, podemos querer inserir mesmo assim
            else {
                return;
            }
        }
        // se o dado a ser inserido é menor que o anterior, inserimos a esquerda
        if (anterior != null && data < anterior.getData()){
            anterior.setLeft(novo);
        }
        // se o dado a ser inserido é maior que o anterior, inserimos a direita 
        else if (anterior != null && data > anterior.getData()){
            anterior.setRight(novo);
        }
    }

    public Node<Integer> buscar(int data){
        Node<Integer> atual = this.root;
        // enquanto não chegamos em uma folha
        while( atual != null){
            // se encontramos o dado, retornamos o nó
            if(data == atual.getData()){
                return atual;
            }
            // se o dado a ser buscado é menor que o atual, vamos para a esquerda
            if(data < atual.getData()){
                atual = atual.getLeft();
            } 
            // se o dado a ser buscado é maior que o atual, vamos para a direita
            else {
                atual = atual.getRight();
            }
        }
        // se não encontramos o dado, retornamos null
        return null;
    }
    
    public void preOrder(Node<Integer> node){
        if (node != null){
            System.out.print(node.getData() + " ");
            preOrder(node.getLeft());
            preOrder(node.getRight());
        }
    }
    
    public void inOrder(Node<Integer> node){
        if (node != null){
            inOrder(node.getLeft());
            System.out.print(node.getData() + " ");
            inOrder(node.getRight());
        }
    }
    
    public void postOrder(Node<Integer> node){
        if (node != null){
            postOrder(node.getLeft());
            postOrder(node.getRight());
            System.out.print(node.getData() + " ");
        }
    }
    
}