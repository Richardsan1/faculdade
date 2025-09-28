public class BST {
    private static class NodeBst {
        Comparable key;
        EmpresaRecord head; // início da lista ligada de registros
        NodeBst left, right;

        NodeBst(Comparable key, EmpresaRecord payload) {
            this.key = key;
            this.head = payload;
            this.left = null;
            this.right = null;
        }
    }

    private NodeBst root;

    public BST() {
        this.root = null;
    }

    public void insert(Comparable key, EmpresaRecord payload) {
        root = insertRec(root, key, payload);
    }

    private NodeBst insertRec(NodeBst node, Comparable key, EmpresaRecord payload) {
        if (node == null) return new NodeBst(key, payload);

        int cmp = key.compareTo(node.key);
        if (cmp < 0) {
            node.left = insertRec(node.left, key, payload);
        } else if (cmp > 0) {
            node.right = insertRec(node.right, key, payload);
        } else {
            // Adiciona à lista ligada de registros para esta chave
            payload.next = node.head;
            node.head = payload;
        }
        return node;
    }

    public EmpresaRecord search(Comparable key) {
        NodeBst node = root;
        while (node != null) {
            int cmp = key.compareTo(node.key);
            if (cmp == 0) return node.head;
            node = (cmp < 0) ? node.left : node.right;
        }
        return null;
    }

    // Percorre em ordem e executa callback para cada chave/lista
    public void inOrderTraversal(BiConsumer callback) {
        inOrderRec(root, callback);
    }

    private void inOrderRec(NodeBst node, BiConsumer callback) {
        if (node != null) {
            inOrderRec(node.left, callback);
            callback.accept(node.key, node.head);
            inOrderRec(node.right, callback);
        }
    }

    public int countNodes() {
        return countNodesRec(root);
    }

    private int countNodesRec(NodeBst node) {
        if (node == null) return 0;
        return 1 + countNodesRec(node.left) + countNodesRec(node.right);
    }

    public int getTreeHeight() {
        return getHeight(root);
    }

    private int getHeight(NodeBst node) {
        if (node == null) return 0;
        return 1 + Math.max(getHeight(node.left), getHeight(node.right));
    }

    // Interface funcional para callback
    public interface BiConsumer {
        void accept(Object key, EmpresaRecord lista);
    }
}