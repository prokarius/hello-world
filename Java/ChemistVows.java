import java.util.*;

public class ChemistVows{
    static List<String> one = Arrays.asList(new String[] {"b", "c", "f", "h", "i", "k", "n", "o", "p", "s", "u", "v", "w", "y"});
    static List<String> two = Arrays.asList(new String[] {"ac", "ag", "al", "am", "ar", "as", "at", "au", "ba", "be", "bh", "bi", "bk", "br", "ca", "cd", "ce", "cf", "cl", "cm", "cn", "co", "cr", "cs", "cu", "db", "ds", "dy", "er", "es", "eu", "fe", "fl", "fm", "fr", "ga", "gd", "ge", "he", "hf", "hg", "ho", "hs", "in", "ir", "kr", "la", "li", "lr", "lu", "lv", "md", "mg", "mn", "mo", "mt", "na", "nb", "nd", "ne", "ni", "no", "np", "os", "pa", "pb", "pd", "pm", "po", "pr", "pt", "pu", "ra", "rb", "re", "rf", "rg", "rh", "rn", "ru", "sb", "sc", "se", "sg", "si", "sm", "sn", "sr", "ta", "tb", "tc", "te", "th", "ti", "tl", "tm", "xe", "yb", "zn", "zr"});
    static boolean dp[] = new boolean[100005];
    static boolean flag = false;
    static String name = "";
    public static void main(String[] args){
        Scanner s = new Scanner(System.in);
        int n = s.nextInt();
        while (n > 0){
            name = s.next();
            // Nasty hack
            name.concat(" ");
            // Reset the array and flag
            for (int i=0; i<=name.length(); ++i) dp[i] = false;
            flag = false;
            check (0, name.length());
            System.out.println(flag ? "YES" : "NO");
            n--;
        }
    }

    public static void check(int l, int end){
        // Check if we have reached here before
        if (dp[l]) return;
        // Check if we have reached the end of the string
        if (l == end) {
            flag = true;
            return;
        }
        // Check if the first two letters can be made by symbols
        // if yes, call the same function on the shortened version of it
        // Simple dp style question
        if (end-l > 1 && two.contains(name.substring(l,l+2))){
            dp[l] = true;
            check(l+2, end);
        }
        if (one.contains(name.substring(l,l+1))){
            dp[l] = true;
            check(l+1, end);
        }
    }
}
