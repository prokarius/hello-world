import java.io.*;
import java.util.*;

// Encapsulates an edge in the adjlist
class Edge{
    int start;
    int end;
    int distance;

    public Edge(int start, int end, int distance){
        this.start = start;
        this.end = end;
        this.distance = distance;
    }
}

// Dijkstra states!
class DijkState implements Comparable<DijkState>{
    int distance; // Just because we want to bfs stuff
    int curr;
    String added;

    public DijkState(int distance, int curr, String word){
        this.distance = distance;
        this.curr = curr;
        this.added = word;
    }

    public int compareTo (DijkState other){
        if (this.distance == other.distance){
            return this.added.compareTo(other.added);
        }
        return this.distance - other.distance;
    }
}

public class WordLadder{
    String[] words;
    int length;
    ArrayList<ArrayList<Edge>> adjList = new ArrayList<>();
    PriorityQueue<DijkState> dijkstra = new PriorityQueue<>();

    private String bridgeWord(int first, int second){
        String firstWord = words[first];
        String secondWord = words[second];

        char[] output = new char[length];

        // State 0 => have not hit the first different letter yet
        // State 1 => have used the first word
        // State 2 => have used the second word
        int state = 0;

        for (int i = 0; i < length; ++i){
            if (firstWord.charAt(i) == secondWord.charAt(i)){
                output[i] = firstWord.charAt(i);
            }

            // If we have used the first word, now use the second
            else if (state == 1){
                output[i] = secondWord.charAt(i);
            }

            // If we have used the second word, now use the first
            else if (state == 2){
                output[i] = firstWord.charAt(i);
            }

            // If not we have not used either, and it's the first time we meet a
            // different letter, choose the letter that is lexicographically smaller
            else if (firstWord.charAt(i) < secondWord.charAt(i)){
                output[i] = firstWord.charAt(i);
                state = 1;
            }

            else { // secondWord.charAt(i) < firstWord.charAt(i)
                output[i] = secondWord.charAt(i);
                state = 2;
            }
        }

        return new String(output);
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in));
        int n = Integer.parseInt(r.readLine());
        words = new String[n];

        for (int i = 0; i < n; ++i){
            adjList.add(new ArrayList<>());
            String word = r.readLine();
            words[i] = word;
        }

        length = words[0].length();

        // Create the adjList
        for (int i = 0; i < n-1; ++i){
            String word1 = words[i];
            for (int j = i+1; j < n; ++j){
                String word2 = words[j];

                int numDiff = 0;
                for (int k = 0; k < length; ++k){
                    if (word1.charAt(k) != word2.charAt(k)){
                        numDiff++;
                    }
                }

                // If there is too many differences, give up
                if (numDiff > 2) continue;

                adjList.get(i).add(new Edge(i, j, numDiff));
                adjList.get(j).add(new Edge(j, i, numDiff));
            }
        }

        // Initialise visited array
        boolean[] visited = new boolean[n];
        boolean[] visitedAddWord = new boolean[n];

        // Do dijkstra
        boolean ended = false;
        DijkState curr = new DijkState(0, 0, "0");
        dijkstra.add(new DijkState(0, 0, "0"));
        while (!dijkstra.isEmpty()){
            curr = dijkstra.poll();

            // Have we reached the end?
            if (curr.curr == 1){
                ended = true;
                break;
            }

            // Have we already added a word?
            if (curr.added.equals("0")){

                // If we have already visited the word before, continue
                if (visited[curr.curr]) continue;

                // If not, mark as visited
                visited[curr.curr] = true;

                // For each neighbour, see if we can go there
                for (Edge neighbour : adjList.get(curr.curr)){

                    // If the distance is 1, just go there
                    if (neighbour.distance == 1){
                        dijkstra.add(new DijkState(curr.distance + 1, neighbour.end, "0"));
                    }

                    // Else, the distance is 2
                    if (neighbour.distance == 2 && !visitedAddWord[neighbour.end]){
                        String newWord = bridgeWord(neighbour.start, neighbour.end);
                        dijkstra.add(new DijkState(curr.distance + 2, neighbour.end, newWord));
                    }
                }
            }

            // We have already added a word!
            else {
                // If we have already visited the word before, continue
                if (visitedAddWord[curr.curr]) continue;

                // Visit the word
                visitedAddWord[curr.curr] = true;

                // For each neighbour, see if we can go there
                for (Edge neighbour : adjList.get(curr.curr)){

                    // If the distance is 1, just go there
                    if (neighbour.distance == 1){
                        dijkstra.add(new DijkState(curr.distance + 1, neighbour.end, curr.added));
                    }
                }
            }
        }

        // If we are here, we check if the state is null
        if (!ended){
            System.out.println("0");
            System.out.println("-1");
            return;
        }

        System.out.println(curr.added);
        System.out.println(curr.distance);
    }

    public static void main(String[] args) throws IOException{
        WordLadder wordLadder = new WordLadder();
        wordLadder.run();
    }
}
