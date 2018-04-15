import java.util.*;

public class HorrorList{
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    LinkedList<Integer> queue = new LinkedList<>();
    ArrayList<Integer> distances = new ArrayList<>();
    ArrayList<Boolean> visited = new ArrayList<>();
    private void run(){
        Scanner s = new Scanner(System.in);
        int N = s.nextInt();
        int H = s.nextInt();
        int L = s.nextInt();

        // Set up the adjlist and adjlist
        for (int i=0; i<N; ++i){
            adjlist.add(new ArrayList<>());
            distances.add(2000000000);
            visited.add(false);
        }

        // Populate the horror list
        // Set their distances to 0.
        // Push into the queue
        for (int i=0; i<H; ++i){
            int horror = s.nextInt();
            distances.set(horror, 0);
            visited.set(horror, true);
            queue.addLast(horror);
        }

        // populate the adj list
        for (int i=0; i<L; ++i){
            int start = s.nextInt();
            int end = s.nextInt();
            adjlist.get(start).add(end);
            adjlist.get(end).add(start);
        }

        // BFS while queue is not empty
        while (!queue.isEmpty()){
            int vertex = queue.pollFirst();
            int currdist = distances.get(vertex);
            for (int neighbour : adjlist.get(vertex)){
                if (!visited.get(neighbour)){
                    distances.set(neighbour, currdist + 1);
                    visited.set(neighbour, true);
                    queue.addLast(neighbour);
                }
            }
        }

        int max = -1;
        int out = -1;

        // Then go through the list and find the horrorest movie.
        for (int i=N-1; i>=0; --i){
            if (distances.get(i) >= max){
                max = distances.get(i);
                out = i;
            }
        }

        System.out.println(out);
    }

    public static void main(String[] args){
        HorrorList horrorlist = new HorrorList();
        horrorlist.run();
    }
}

