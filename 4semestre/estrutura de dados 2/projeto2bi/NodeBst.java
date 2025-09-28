public class NodeBst {
    Comparable key; // por exemplo, LocalDate ou String
    EmpresaRecord payload;
    NodeBst left, right;

    public NodeBst(Comparable key, EmpresaRecord payload) {
        this.key = key;
        this.payload = payload;
        this.left = null;
        this.right = null;
    }
}
