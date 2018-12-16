// Same solultion sketch as the solution in C/Fire3.c

import java.util.*;
import java.io.*;

public class Fire2{
    int R;
    int C;

    char[][] grid;
    int[][] visitedYou;
    int[][] visitedFire;

    int[] dr = {0, 1, 0, -1, 0};

    // Do BFS on a given queue and grid.
    public void BFS(LinkedList<Integer> queue, int[][] playerGrid){
        while (queue.size() > 0){
            int curr = queue.pollLast();
            int oldr = curr/C;
            int oldc = curr%C;
            for (int k = 0; k < 4; ++k){
                int newr = oldr + dr[k];
                int newc = oldc + dr[k+1];
                if (newr < 0 || newc < 0 || newr >= R || newc >= C) continue;
                if (grid[newr][newc] == '#') continue;
                if (playerGrid[newr][newc] < 1<<20) continue;
                playerGrid[newr][newc] = playerGrid[oldr][oldc] + 1;
                queue.addFirst(newr*C + newc);
            }
        }
    }

    public void run(BufferedReader r) throws IOException{
        LinkedList<Integer> fireQueue = new LinkedList<>();
        LinkedList<Integer> youQueue = new LinkedList<>();

        String[] dlist = r.readLine().split(" ");
        C = Integer.parseInt(dlist[0]);
        R = Integer.parseInt(dlist[1]);

        grid = new char[R][C];
        visitedYou = new int[R][C];
        visitedFire = new int[R][C];

        // Initialise the grids
        for (int i = 0; i < R; ++i){
            for (int j = 0; j < C; ++j){
                visitedYou[i][j] = 1<<23;
                visitedFire[i][j] = 1<<22;
            }
        }

        // Scan in grid
        for (int i = 0; i < R; ++i){
            String row = r.readLine();
            for (int j = 0; j < C; ++j){
                if (row.charAt(j) == '@'){
                    visitedYou[i][j] = 0;
                    youQueue.addFirst(i*C+j);
                }
                else if (row.charAt(j) == '*'){
                    visitedFire[i][j] = 0;
                    fireQueue.addFirst(i*C+j);
                }
                grid[i][j] = row.charAt(j);
            }
        }

        // Do BFS
        BFS(youQueue, visitedYou);
        BFS(fireQueue, visitedFire);

        // Check boundaries
        int best = 1<<24;
        for (int i = 0; i < R; ++i){
            if (visitedFire[i][0] > visitedYou[i][0] && visitedYou[i][0] < best){
                best = visitedYou[i][0];
            }
            if (visitedFire[i][C-1] > visitedYou[i][C-1] && visitedYou[i][C-1] < best){
                best = visitedYou[i][C-1];
            }
        }
        for (int i = 0; i < C; ++i){
            if (visitedFire[0][i] > visitedYou[0][i] && visitedYou[0][i] < best){
                best = visitedYou[0][i];
            }
            if (visitedFire[R-1][i] > visitedYou[R-1][i] && visitedYou[R-1][i] < best){
                best = visitedYou[R-1][i];
            }
        }

        // Print the answer if we found any
        if (best > (1<<20)) System.out.println("IMPOSSIBLE");
        else System.out.println(best+1);
    }

    public static void main(String[] args) throws IOException{
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int testcases = Integer.parseInt(r.readLine());
        Fire2 fire = new Fire2();
        for (int i = 0; i < testcases; ++i){
            fire.run(r);
        }
    }
}