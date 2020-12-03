import java.io.*;
import java.util.*;

class Employee{
    // The start and end of the fenwick tree positions that
    // represents their underlings
    int start;
    int end;
    int num;
    int rank;
    int time;
    long cost;

    public Employee(int rank, int time, int num){
        this.num = num;
        this.rank = rank;
        this.time = time;
    }
}   

class FenwickTree {
    int size;
    long[] fenwick;

    public FenwickTree(int n){
        this.size = n+2;
        fenwick = new long[n+2];
    }

    private int LSOne(int x){
        return x&-x;
    }

    public void update(int location, int value){
        for (int i = location; i < this.size; i += LSOne(i)){
            fenwick[i] += value;
        }
    }

    private long rsq(int end){
        long sum = 0;
        for (int i = end; i > 0; i -= LSOne(i)){
            sum += fenwick[i];
        }

        return sum;
    }

    public long rsq(int start, int end){
        return rsq(end-1) - rsq(start);
    }
}

public class PerformanceReview{

    Employee[] employees;
    ArrayList<ArrayList<Integer>> adjlist = new ArrayList<>();
    FenwickTree fenwick;
    int index = 1;

    private void process(HashSet<Employee> toProcess){
        // Find out how much time these employees have to waste
        for(Employee x : toProcess){
            x.cost = fenwick.rsq(x.start, x.end);
        }

        // And then update the fenwick tree too
        for(Employee x : toProcess){
            fenwick.update(x.start, x.time);
        }
    }

    // Do a preorder traversal of the tree to find from where to where the
    // current node's underlings are. This helps in fenwick tree rsq later
    private void dfs(int node){
        employees[node].start = index;
        index++;
        for (int underling : adjlist.get(node)){
            dfs(underling);
        }
        employees[node].end = index;
    }

    private void run() throws IOException{
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        OutputStream log = new BufferedOutputStream (System.out);

        int n = Integer.parseInt(r.readLine());
        employees = new Employee[n];
        fenwick = new FenwickTree(n);
        for (int i = 0; i < n; ++i){
            adjlist.add(new ArrayList<>());
        }

        int root = -1;
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");
            int manager = Integer.parseInt(dlist[0]) - 1;
            int rank = Integer.parseInt(dlist[1]);
            int time = Integer.parseInt(dlist[2]);

            employees[i] = new Employee(rank, time, i);
            if (manager == -2) root = i;
            else adjlist.get(manager).add(i);
        }

        // Do a traversal of the tree
        dfs(root);

        // Sort the employees by rank, and process:
        Arrays.sort(employees, (a, b) -> a.rank - b.rank);

        int currRank = -1;
        HashSet<Employee> toProcess = new HashSet<>(); 
        for (int i = 0; i < n; ++i){

            // Process all employees in the set
            // Take note that if the employees have the same ranks, they
            // do not need to give a review
            if (currRank != employees[i].rank){
                process(toProcess);
                toProcess.clear();
                currRank = employees[i].rank;
            }

            toProcess.add(employees[i]);
        }
        process(toProcess);

        // Sort them back and process each employee
        Arrays.sort(employees, (a, b) -> a.num - b.num);
        for (Employee x : employees){
            log.write(String.valueOf(x.cost).getBytes());
            log.write('\n');
        }

        log.flush();
    }

    public static void main(String[] args) throws IOException{
        PerformanceReview review = new PerformanceReview();
        review.run();
    }
}

