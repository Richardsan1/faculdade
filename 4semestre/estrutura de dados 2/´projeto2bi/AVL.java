public class AVL {
    private static class NodeAvl {
        Comparable key;
        EmpresaRecord head; // início da lista ligada de registros
        NodeAvl left, right;
        int height;

        NodeAvl(Comparable key, EmpresaRecord payload) {
            this.key = key;
            this.head = payload;
            this.left = null;
            this.right = null;
            this.height = 1;
        }
    }

    private NodeAvl root;

    public AVL() {
        this.root = null;
    }

    public void insert(Comparable key, EmpresaRecord payload) {
        root = insertRec(root, key, payload);
    }

    private NodeAvl insertRec(NodeAvl node, Comparable key, EmpresaRecord payload) {
        if (node == null) return new NodeAvl(key, payload);

        int cmp = key.compareTo(node.key);
        if (cmp < 0) {
            node.left = insertRec(node.left, key, payload);
        } else if (cmp > 0) {
            node.right = insertRec(node.right, key, payload);
        } else {
            // Adiciona à lista ligada de registros para esta chave
            payload.next = node.head;
            node.head = payload;
            return node;
        }

        node.height = 1 + Math.max(height(node.left), height(node.right));
        int balance = getBalance(node);

        // Rotações AVL
        if (balance > 1 && key.compareTo(node.left.key) < 0) return rightRotate(node);
        if (balance < -1 && key.compareTo(node.right.key) > 0) return leftRotate(node);
        if (balance > 1 && key.compareTo(node.left.key) > 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }
        if (balance < -1 && key.compareTo(node.right.key) < 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }
        return node;
    }

    public EmpresaRecord search(Comparable key) {
        NodeAvl node = root;
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

    private void inOrderRec(NodeAvl node, BiConsumer callback) {
        if (node != null) {
            inOrderRec(node.left, callback);
            callback.accept(node.key, node.head);
            inOrderRec(node.right, callback);
        }
    }

    public int countNodes() {
        return countNodesRec(root);
    }

    private int countNodesRec(NodeAvl node) {
        if (node == null) return 0;
        return 1 + countNodesRec(node.left) + countNodesRec(node.right);
    }

    public int getTreeHeight() {
        return height(root);
    }

    private int height(NodeAvl node) {
        return node == null ? 0 : node.height;
    }

    private int getBalance(NodeAvl node) {
        return node == null ? 0 : height(node.left) - height(node.right);
    }

    private NodeAvl rightRotate(NodeAvl y) {
        NodeAvl x = y.left;
        NodeAvl T2 = x.right;
        x.right = y;
        y.left = T2;
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        return x;
    }

    private NodeAvl leftRotate(NodeAvl x) {
        NodeAvl y = x.right;
        NodeAvl T2 = y.left;
        y.left = x;
        x.right = T2;
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        return y;
    }

    public boolean isBalanced() {
        return isBalancedRec(root);
    }

    private boolean isBalancedRec(NodeAvl node) {
        if (node == null) return true;
        int balance = getBalance(node);
        return Math.abs(balance) <= 1 && isBalancedRec(node.left) && isBalancedRec(node.right);
    }

    // Interface funcional para callback
    public interface BiConsumer {
        void accept(Object key, EmpresaRecord lista);
    }
}