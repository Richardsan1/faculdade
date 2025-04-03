public class BinarySearchTree {
    private Node root;

    public BinarySearchTree() {
        this.root = null;
    }

    public void insert(int key) {
        root = insertRec(root, key);
    }

    private Node insertRec(Node root, int key) {
        if (root == null) {
            return new Node(key);
        }
        if (key < root.getKey()) {
            root.setLeft(insertRec(root.getLeft(), key));
        } else if (key > root.getKey()) {
            root.setRight(insertRec(root.getRight(), key));
        }
        return root;
    }

    public boolean search(int key) {
        return searchRec(root, key);
    }

    private boolean searchRec(Node root, int key) {
        if (root == null) {
            return false;
        }
        if (key == root.getKey()) {
            return true;
        }
        return key < root.getKey()
                ? searchRec(root.getLeft(), key)
                : searchRec(root.getRight(), key);
    }

    public void inOrderTraversal() {
        inOrderRec(root);
        System.out.println();
    }

    private void inOrderRec(Node root) {
        if (root != null) {
            inOrderRec(root.getLeft());
            System.out.print(root.getKey() + " ");
            inOrderRec(root.getRight());
        }
    }
}