import java.util.Scanner;

public class Contatore {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Inserisci un numero N: ");

		int N = 0;
		try{
        	N = input.nextInt();
		}
		catch (Exception e) {
			System.out.println("Devi inserire un numero intero.");
			input.close();
			return;
		}

        System.out.println("Numeri da 1 a " + N + ":");
        for (int i = 1; i <= N; i++) {
            System.out.println(i);
        }

        System.out.println("\nSolo i numeri pari:");
        for (int i = 1; i <= N; i++) {
            if (i % 2 == 0) {
                System.out.println(i);
            }
        }

        input.close();
    }
}
