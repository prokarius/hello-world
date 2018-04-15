import java.util.*;

class BusNumber2{
    private static int[] yes = new int[400005];
    private static int[] cube = new int[75];

    public static void setting(){
        for (int i=0; i<75; ++i){
            cube[i] = i*i*i;
        }
        for (int i=0; i<75; ++i){
            for (int j=0; j<i; ++j){
                if (cube[i] + cube[j] > 400004){
                    break;
                }
                yes[cube[i]+cube[j]]++;
            }
        }
    }

    public void run (int n){
        while (yes[n]<2){
            if (n <= 0){
                System.out.println("none");
                return;
            }
            n--;
        }
        System.out.println(n);
    }

    public static void main(String[] args){
        setting();
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        BusNumber2 bus = new BusNumber2();
        bus.run(n);
    }
}
