import java.util.Scanner;

public class OracoloNumeri {

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Inserisci un numero: ");
        int n = input.nextInt();

        if (isEven(n)) {
            System.out.println(n + " è pari.");
        } else {
            System.out.println(n + " è dispari.");
        }

        // versione opzionale: verifica se è primo
        if (isPrime(n)) {
            System.out.println(n + " è anche un numero primo!");
        }

        input.close();
    }

    public static boolean isEven(int n) {
        return n % 2 == 0;
    }

    public static boolean isPrime(int n) {
        if (n <= 1) return false;
        for (int i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) return false;
        }
        return true;
    }
}
