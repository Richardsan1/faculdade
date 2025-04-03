import java.util.Random;

public class Main {
    public static void main(String[] args) {
        int[] ns = {100, 500, 1000, 10000, 100000, 500000};
        int[][] seeds = {
            {7, 8, 9},       // Para n = 100
            {10, 11, 12},    // Para n = 500
            {13, 14, 15},    // Para n = 1.000
            {16, 17, 18},    // Para n = 10.000
            {19, 20, 21},    // Para n = 100.000
            {22, 23, 24}     // Para n = 500.000
        };

        System.out.println("Resultados para BST:");
        for (int i = 0; i < ns.length; i++) {
            int n = ns[i];
            int[] currentSeeds = seeds[i];
            double totalTime = 0;

            for (int seed : currentSeeds) {
                BinarySearchTree bst = new BinarySearchTree();
                Random random = new Random(seed);

                long startTime = System.nanoTime();
                for (int j = 0; j < n; j++) {
                    int value = random.nextInt(1_000_000);
                    bst.insert(value);
                }
                long endTime = System.nanoTime();
                double elapsedTime = (endTime - startTime) / 1_000_000.0;

                totalTime += elapsedTime;
                System.out.printf("n = %d, seed = %d, tempo = %.3f ms%n", n, seed, elapsedTime);
            }

            double averageTime = totalTime / currentSeeds.length;
            System.out.printf("Média para n = %d: %.3f ms%n", n, averageTime);
        }

        System.out.println("\nResultados para AVL:");
        for (int i = 0; i < ns.length; i++) {
            int n = ns[i];
            int[] currentSeeds = seeds[i];
            double totalTime = 0;

            for (int seed : currentSeeds) {
                AVLTree avl = new AVLTree();
                Random random = new Random(seed);

                long startTime = System.nanoTime();
                for (int j = 0; j < n; j++) {
                    int value = random.nextInt(1_000_000);
                    avl.insert(value);
                }
                long endTime = System.nanoTime();
                double elapsedTime = (endTime - startTime) / 1_000_000.0;

                totalTime += elapsedTime;
                System.out.printf("n = %d, seed = %d, tempo = %.3f ms%n", n, seed, elapsedTime);
            }

            double averageTime = totalTime / currentSeeds.length;
            System.out.printf("Média para n = %d: %.3f ms%n", n, averageTime);
        }
    }
}