public class AVLTree {
    private NodeAVL root;

    public AVLTree() {
        this.root = null;
    }

    public void insert(int key) {
        root = insertRec(root, key);
    }

    private NodeAVL insertRec(NodeAVL node, int key) {
        if (node == null) {
            return new NodeAVL(key);
        }

        if (key < node.getKey()) {
            node.setLeft(insertRec(node.getLeft(), key));
        } else if (key > node.getKey()) {
            node.setRight(insertRec(node.getRight(), key));
        } else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && key < node.getLeft().getKey()) {
            return rotateRight(node);
        }

        if (balance < -1 && key > node.getRight().getKey()) {
            return rotateLeft(node);
        }

        if (balance > 1 && key > node.getLeft().getKey()) {
            node.setLeft(rotateLeft(node.getLeft()));
            return rotateRight(node);
        }

        if (balance < -1 && key < node.getRight().getKey()) {
            node.setRight(rotateRight(node.getRight()));
            return rotateLeft(node);
        }

        return node;
    }

    private NodeAVL rotateRight(NodeAVL y) {
        NodeAVL x = y.getLeft();
        NodeAVL T2 = x.getRight();

        x.setRight(y);
        y.setLeft(T2);

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    private NodeAVL rotateLeft(NodeAVL x) {
        NodeAVL y = x.getRight();
        NodeAVL T2 = y.getLeft();

        y.setLeft(x);
        x.setRight(T2);

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    private void updateHeight(NodeAVL node) {
        node.setHeight(1 + Math.max(height(node.getLeft()), height(node.getRight())));
    }

    private int height(NodeAVL node) {
        return (node == null) ? 0 : node.getHeight();
    }

    private int getBalance(NodeAVL node) {
        return (node == null) ? 0 : height(node.getLeft()) - height(node.getRight());
    }

    public void inOrderTraversal() {
        inOrderRec(root);
        System.out.println();
    }

    private void inOrderRec(NodeAVL node) {
        if (node != null) {
            inOrderRec(node.getLeft());
            System.out.print(node.getKey() + " ");
            inOrderRec(node.getRight());
        }
    }
}