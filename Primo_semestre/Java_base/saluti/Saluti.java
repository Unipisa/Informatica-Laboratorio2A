import java.util.Scanner;

public class Saluti {

	public Saluti() {
	}
	
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        System.out.print("Come ti chiami? ");
        String nome = input.nextLine();

        String messaggio = "Benvenuto, " + nome + "!";

        if (nome.length() > 10) {
            messaggio += " — nome importante!";
        }

        System.out.println(messaggio);
        input.close();
    }
}
