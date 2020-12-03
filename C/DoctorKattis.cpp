// Literal translation of the TLE java solution
#include<cstdio>
#include<unordered_map>
#include<queue>

#define MAX_N 1000001

class Kitten {
public:
    int num;
    int value;
    Kitten(int num, int value) : num(num), value(value) {}

    bool operator <(const Kitten& other) const {
        return this->value < other.value;
    }
};

int priorities[200005];
std::string names[200005];
std::unordered_map<std::string, int> mapping;
std::priority_queue<Kitten> pq;

int getNum(std::string name){
    if (mapping.find(name) != mapping.end()){
        return mapping[name];
    }

    int size = mapping.size();
    names[size] = name;
    mapping[name] = size;
    return size;
}

void arrive(int num, int infection, int queueNum){
    int priority = infection * MAX_N - queueNum;
    pq.push(Kitten(num, priority));
    priorities[num] = priority;
}

void arrive(int num, int priority){
    pq.push(Kitten(num, priority));
    priorities[num] = priority;
}

void update(int num, int newLevel){
    int oldPriority = priorities[num];
    int newPriority = oldPriority + newLevel * MAX_N;
    arrive(num, newPriority);
}

void treat(int num){
    priorities[num] = -MAX_N;
}

std::string get(){
    while (1){
        if (pq.empty()) return "The clinic is empty";
        Kitten curr = pq.top();
        if (curr.value != priorities[curr.num]) pq.pop();
        else return names[curr.num];
    }
}

int main(){
    // Scan in input
    int n;
    scanf("%d", &n);

    int num;
    char buffer[32];
    std::string name;

    for (int i = 0; i < n; ++i){
        int t;
        scanf("%d", &t);

        switch(t){
            case(0):
                scanf(" %s %d", buffer, &t);
                name = std::string(buffer);
                num = getNum(name);
                arrive(num, t, i);
                break;

            case(1):
                scanf(" %s %d", buffer, &t);
                name = std::string(buffer);
                num = getNum(name);
                update(num, t);
                break;

            case(2):
                scanf(" %s", buffer);
                name = std::string(buffer);
                num = getNum(name);
                treat(num);
                break;

            case(3):
                printf("%s\n", get().c_str());
                break;
        }
    }

    return 0;
}


// And this is the worst part about writing things in java.
// TLE all the time, esp with the NUS Competitive Programming problems

/*

import java.io.*;
import java.util.*;

class Kitten implements Comparable<Kitten>{
    int num;
    int value;

    public Kitten(int num, int value){
        this.num = num;
        this.value = value;
    }

    public int compareTo(Kitten other){
        return this.value < other.value ? 1 : -1;
    }
}

public class DoctorKattis{

    int[] priorities = new int[200005];
    String[] names = new String[200005];
    HashMap<String, Integer> mapping = new HashMap<>();
    PriorityQueue<Kitten> pq = new PriorityQueue<>();

    private final int MAX_N = 1000001;

    // Get the index number of a cat
    private int getNum(String name){
        if (mapping.containsKey(name)){
            return mapping.get(name);
        }

        // We have not seen the cat before
        int num = mapping.size();
        names[num] = name;
        mapping.put(name, num);
        return num;
    }

    // As though a cat has arrived
    // The later a cat arrives, the lower priority it gets
    private void arrive(int num, int infection, int queueNum){
        int priority = infection * MAX_N - queueNum;
        pq.add(new Kitten(num, priority));
        priorities[num] = priority;
    }

    // Overload the method for update...
    private void arrive(int num, int priority){
        pq.add(new Kitten(num, priority));
        priorities[num] = priority;
    }

    // We use lazy deletion, update the cat's priority
    private void update(int num, int newLevel){
        int oldPriority = priorities[num];
        int newPriority = oldPriority + newLevel * MAX_N;
        arrive(num, newPriority);
    }

    // Treat a cat by setting their priority to -INF.
    // That way, we keep popping their names
    private void treat(int num){
        priorities[num] = -MAX_N;
    }

    // Do the check, and return the appropriate string
    private String get(){
        Kitten curr = pq.peek();
        if (curr == null) return "The clinic is empty";
        while (curr.value != priorities[curr.num]){
            pq.poll();
            curr = pq.peek();
            if (curr == null) return "The clinic is empty";
        }

        // Mark the cat as treated
        return names[curr.num];
    }

    private void meow() throws IOException{ 
        // Scan in input
        BufferedReader r = new BufferedReader(new InputStreamReader(System.in)); 
        OutputStream log = new BufferedOutputStream (System.out);
        int n = Integer.parseInt(r.readLine());

        // Parse each query seperately
        for (int i = 0; i < n; ++i){
            String[] dlist = r.readLine().split(" ");

            int num;
            switch(Integer.parseInt(dlist[0])){
                case(0):
                    num = getNum(dlist[1]);
                    arrive(num, Integer.parseInt(dlist[2]), i);
                    break;

                case(1):
                    num = getNum(dlist[1]);
                    update(num, Integer.parseInt(dlist[2]));
                    break;

                case(2):
                    num = getNum(dlist[1]);
                    treat(num);
                    break;

                case(3):
                    log.write(get().getBytes());
                    log.write('\n');
                    break;
            }
        }

        // Everyone is fun to flush
        log.flush();
    }

    public static void main(String[] args) throws IOException{
        DoctorKattis kattis = new DoctorKattis();
        kattis.meow();
    }
}

*/

