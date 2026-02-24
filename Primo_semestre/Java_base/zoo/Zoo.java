// Classe padre (astratta)
abstract class Animale {
    // Metodo da implementare nelle classi figlio
    abstract void verso();
}

// Classe figlio 1
class Cane extends Animale {
    @Override
    void verso() {
        System.out.println("Bau!");
    }
}

// Classe figlio 2
class Gatto extends Animale {
    @Override
    void verso() {
        System.out.println("Miao!");
    }
}

// Classe di test
public class Zoo {
    public static void main(String[] args) {
        Animale a1 = new Cane();
        Animale a2 = new Gatto();

        // Polimorfismo: stesso metodo, comportamenti diversi
        a1.verso();
        a2.verso();
    }
}
