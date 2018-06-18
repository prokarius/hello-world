import java.util.*;
import java.io.*;

public class ProgTeamSelect{
    public void run(int n, BufferedReader r) throws IOException{
        HashSet<Long> dp = new HashSet<>;
        HashMap<String, Integer> mapping = new HashMap<>;
        int numstudents = 0;
        int[][] students = new int[20][20];

        // Build the adj matrix.
        int student1, student2;
        for (i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            if (mapping.hasKey(dlist[0]){
                student1 = mapping.get(dlist[0]);
            }
            else {
                mapping.set(dlist[0], numstudents);
                student1 = numstudents++;
            }
            if (mapping.hasKey(dlist[1]){
                student2 = mapping.get(dlist[1]);
            }
            else {
                mapping.set(dlist[1], numstudents);
                student2 = numstudents++;
            }
            adjlist[student1][student2] = 1;
            adjlist[student2][student1] = 1;
        }

        // Prelim check if the number of students are divisible by 3
        if (numstudents % 3 != 0){
            System.out.println("impossible");
            return;
        }

        // Start the dp.
        dp.add(0);

    }

    public static void main(String[] args) throws IOException{
        ProgTeamSelect solution = new ProgTeamSelect;
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        while (n != 0){
            solution.run(n, r);
            n = Integer.parseInt(r.readLine());
        }
    }
}
