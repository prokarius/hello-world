import java.util.*;

public class ErdosNumbers{
    private HashMap<String, Integer> hmap = new HashMap<>();
    private int hashcounter = 0;
    private ArrayList<HashSet<Integer>> adjlist = new ArrayList<>();
    private ArrayList<String> output = new ArrayList<>();
    private ArrayList<Integer> distance = new ArrayList<>();

    private int getHash(String author){
        if (!hmap.containsKey(author)){
            hmap.put(author, hashcounter);
            hashcounter++;
            adjlist.add(new HashSet<>());
        }
        return hmap.get(author);
    }

    public void run(){
        // Scan in input
        Scanner s = new Scanner(System.in);
        while (s.hasNext()){
            String[] collabs = s.nextLine().split(" ");
            output.add(collabs[0]);

            // Calculate the hash of the author
            int authorHash = getHash(collabs[0]);
            for (int i=1; i<collabs.length; ++i){
                int collaberHash = getHash(collabs[i]);
                adjlist.get(collaberHash).add(authorHash);
                adjlist.get(authorHash).add(collaberHash);
            }
        }

        // Set all the distances to INF first
        for (int i=0; i<hashcounter; ++i){
            distance.add(200000000);
        }

        LinkedList<Integer> queue = new LinkedList<>();

        // We now have our adjlist
        // BFS from erdos.
        int erdos = getHash("PAUL_ERDOS");
        queue.addFirst(erdos);
        distance.set(erdos, 0);

        while (!queue.isEmpty()){
            int vertex = queue.pollLast();
            for (int next : adjlist.get(vertex)){
                if (distance.get(next) > 1 + distance.get(vertex)){
                    queue.addFirst(next);
                    distance.set(next, distance.get(vertex) + 1);
                }
            }
        }

        for (String out : output){
            System.out.printf("%s ", out);
            if (distance.get(getHash(out)) == 200000000){
                System.out.printf("no-connection\n");
            }
            else{
                System.out.printf("%d\n", distance.get(getHash(out)));
            }
        }
    }

    public static void main(String[] args){
        ErdosNumbers start = new ErdosNumbers();
        start.run();
    }
}

