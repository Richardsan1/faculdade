public class NodeAvl {
    Comparable key;
    EmpresaRecord payload;
    NodeAvl left, right;
    int height;

    public NodeAvl(Comparable key, EmpresaRecord payload) {
        this.key = key;
        this.payload = payload;
        this.left = null;
        this.right = null;
        this.height = 1;
    }
} 
