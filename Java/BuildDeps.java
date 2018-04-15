import java.util.*;

public class BuildDeps{
    private static HashMap<String, Integer> hmap = new HashMap<>();
    private static ArrayList<String> revHash = new ArrayList<>();
    private static int counter = 0;
    private static ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    private static LinkedList<Integer> topo = new LinkedList<>();
    private static int[] visited = new int[100005];

    public static void main(String[] args){
        // Scan in input
        Scanner s = new Scanner(System.in);
        int n = Integer.parseInt(s.nextLine());

        // For each line of input populate the adjlist
        for (int i=0; i<n; ++i){
            String[] splited = s.nextLine().split(" ");
            String key = splited[0].substring(0, splited[0].length() - 1);
            int hash = getHash(key);
            for (int j=1; j<splited.length; ++j){
                adjlist.get(getHash(splited[j])).add(hash);
            }
        }

        // Input the list and toposort the output
        String change = s.next();
        dfs(getHash(change));

        while (topo.size() != 0){
            System.out.println(reverseHash(topo.pollFirst()));
        }
    }

    // Returns the hash value of the input string
    // If the string is not in the hmap yet, push in a new value
    // Precon: Nothing
    // Postcon: Hashmap has the new string input, adjlist.size() = hmap.size()
    private static int getHash(String in){
        if (!hmap.containsKey(in)){
            hmap.put(in, counter);
            counter++;
            adjlist.add(new ArrayList<>());
            revHash.add(in);
            return counter-1;
        }
        return hmap.get(in);
    }

    // Reverse the hash.
    private static String reverseHash (int in){
        return revHash.get(in);
    }

    // Does basic dfs
    private static void dfs(int v){
        visited[v] = 1;
        for (int hashed : adjlist.get(v)){
            if (visited[hashed] == 0){
                dfs(hashed);
            }
        }
        topo.addFirst(v);
    }
}
