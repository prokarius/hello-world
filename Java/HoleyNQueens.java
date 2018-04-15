import java.util.*;

public class HoleyNQueens{
    static long total;
    static int N;
    static int M;

    public static void recursiveSolve(int curr, LinkedList<Integer> stack, boolean[][] holes){
        if (curr >= N){
            total++;
            return;
        }

        for (int i=0; i<N; ++i){
            if (holes[curr][i]){
                continue;
            }

            boolean flag = false;
            for (int j : stack){
                if (flag) break;
                int qrow = j%100;
                int qcol = j/100;
                if (qcol == i){
                    flag = true;
                    continue;
                }
                if (qrow + qcol == i + curr){
                    flag = true;
                    continue;
                }
                if (qrow - qcol == curr - i){
                    flag = true;
                    continue;
                }
            }
            if (flag) continue;
            stack.addLast(curr+i*100);
            recursiveSolve(curr+1, stack, holes);
            stack.pollLast();
        }
    }

    private static void calculate(int N, int M, Scanner s){
        boolean[][] holes = new boolean[12][12];
        LinkedList<Integer> stack = new LinkedList<>();

        for (int i=0; i<M; ++i){
            int x = s.nextInt();
            int y = s.nextInt();
            holes[x][y] = true;
        }

        total = 0;

        recursiveSolve(0, stack, holes);
        System.out.println(total);
    }


    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        N = 1;
        M = 1;
        while (N != 0){
            N = s.nextInt();
            M = s.nextInt();
            if (N != 0) calculate(N, M, s);
        }
    }
}
