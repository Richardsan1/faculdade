public class Hash{
    private static final int tableSize = 11;
    private static Integer[] hashTable = new Integer[tableSize];
    public static void main(String[] args) {
        insert(16);
        insert(10);
        insert(20);
        insert(22);
        insert(62);
        insert(82);
        printHashTable();
        // 16, 10, 20, 22, 62, 82
    }

    public static void insert(int input) {
        int pos = input % tableSize;
        if(hashTable[pos] == null) {
            hashTable[pos] = input;
        } else {
            int i = 1;
            while (true) {
                pos = (input + i) % tableSize;
                if (hashTable[pos] == null) {
                    hashTable[pos] = input;
                    break;
                } else if (i == tableSize) {
                    System.out.println("Tabela cheia");
                    return;
                }
                i++;
            }
        }
        System.out.println(input + " Inserido na posição " + pos);
    }
    public static void printHashTable() {
        for (int i = 0; i < tableSize; i++) {
            System.out.print(hashTable[i] + " ");
        }
        System.out.println();
    }
}