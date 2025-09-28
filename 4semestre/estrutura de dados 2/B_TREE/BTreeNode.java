class BTreeNode {
    private int[] keys;            
    private final int ordem;                 
    private BTreeNode[] filhos;  
    private int n;                 
    private boolean foia;          

    public BTreeNode(int ordem, boolean foia) {
        this.ordem = ordem;
        this.foia = foia;
        this.keys = new int[2 * ordem - 1];        
        this.filhos = new BTreeNode[2 * ordem];  
        this.n = 0;                            
    }
    
    public int[] getKeys() {
        return keys;
    }
    public void setKeys(int[] keys) {
        this.keys = keys;
    }
    public int getOrdem() {
        return ordem;
    }
    public BTreeNode[] getFilhos() {
        return filhos;
    }
    public void setFilhos(BTreeNode[] filhos) {
        this.filhos = filhos;
    }
    public int getN() {
        return n;
    }
    public void setN(int n) {
        this.n = n;
    }
    public boolean isFoia() {
        return foia;
    }
    public void setFoia(boolean foia) {
        this.foia = foia;
    }
    public void setKey(int index, int key) {
        this.keys[index] = key;
    }
    public int getKey(int index) {
        return this.keys[index];
    }
    public void setFilho(int index, BTreeNode child) {
        this.filhos[index] = child;
    }
    public BTreeNode getFilho(int index) {
        return this.filhos[index];
    }
}
