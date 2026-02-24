import java.util.Scanner;

public class Fruttivendolo {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Inserisci il prezzo al kg: ");
        double prezzo = input.nextDouble();

        System.out.print("Inserisci i kg acquistati: ");
        double kg = input.nextDouble();

        double totale = prezzo * kg;

        if (totale > 20) {
            totale = totale * 0.90; // sconto del 10%
        }

        System.out.println("Totale da pagare: " + totale + " euro");
        input.close();
    }
}
