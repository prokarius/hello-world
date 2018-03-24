import java.util.*;

public class CreditCard {
    private static int check(double R, double B, double M){
        // Simulate it I guess. The round up part is a pain.
        long balance = (long) (0.5 + B*100); // This is the remaining balance in cents
        int T = 0; // This is the number of payments done
        long payment = (long) (0.5 + M*100);
        while (true){
            if (T > 1200 || balance > 5500000){
                throw new ArithmeticException("impossible");
            }
            else if (balance <= 0) return T;
            else{
                balance = (int) (balance*(1+R/100)+0.5);
                balance -= payment;
                ++T;
            }
        }
    }

    public static void main(String[] args){
        // Scan your input
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        while (n-- > 0){
            double a = s.nextDouble();
            double b = s.nextDouble();
            double c = s.nextDouble();
            try {
                System.out.println(check(a,b,c));
            }
            catch (ArithmeticException e){
                System.out.println("impossible");
            }
        }
    }
}


