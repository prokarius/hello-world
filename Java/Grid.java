import java.util.*;

public class Grid{
  ArrayList<Integer> grid = new ArrayList<>();
  ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
  boolean[] visited = new boolean[250005];
  LinkedList<Long> queue = new LinkedList<>();
  int [] dr = {0,1,0,-1,0};
  int R;
  int C;

  public static void main(String[] args){
    Grid grid = new Grid();
    grid.run();
  }

  public long bfs(){
    if (R*C == 1){
      return 0;
    }

    queue.addLast(0L);

    while (!queue.isEmpty()){
      long v = queue.pollFirst();
      long steps = v%1000000;
      int vertex = (int) (v/1000000);
      if (vertex == R*C-1){
        return steps;
      }

      visited[vertex] = true;
      for (int neighbour : adjlist.get(vertex)){
        if (!visited[neighbour]){
          visited[neighbour] = true;
          queue.addLast(neighbour*1000000L + steps+1);
        }
      }
    }
    return -1;
  }

  public void run(){
    Scanner s = new Scanner(System.in);
    R = s.nextInt();
    C = s.nextInt();
    for (int i = 0; i<R; i++){
      char[] input = s.next().toCharArray();
      for (char ch : input){
        grid.add(ch - '0');
	    adjlist.add(new ArrayList<>());
      }
    }
    for (int i = 0; i<R*C; i++){
      int row = i/C;
      int col = i%C;
      int jumps = grid.get(i);

      for (int k = 0; k<4; k++){
        int newrow = row + (dr[k]*jumps);
    	int newcol = col + (dr[k+1]*jumps);
	    // check out of bounds
	    if (newcol < 0 || newrow < 0 || newcol >= C || newrow >= R){
          continue;
        }

  	    int newspace = newrow*C+newcol;
	    adjlist.get(i).add(newspace);
      }
    }

    // bfs from start.
    System.out.println(bfs());
  }
}
