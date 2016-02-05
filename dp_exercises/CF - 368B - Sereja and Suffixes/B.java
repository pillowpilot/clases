import java.util.*;

public class B{
    public static void main(String[] args){
	Scanner in = new Scanner(System.in);
	int n = in.nextInt(), m = in.nextInt();

	int[] a = new int[n];
	for(int i = 0; i < n; i++)
	    a[i] = in.nextInt();

	int[] i = new int[m];
	for(int j = 0; j < m; j++)
	    i[j] = in.nextInt();

	int[] dp = new int[n];
	dp[n-1] = 1;

	HashSet<Integer> set = new HashSet<Integer>();
	set.add(a[n-1]);
	int lastSize = set.size();

	for(int j = n - 2; j >= 0; j--){
	    set.add(a[j]);
	    if( set.size() != lastSize )
		dp[j] = dp[j+1] + 1;
	    else
		dp[j] = dp[j+1];
	    lastSize = set.size();
	}

	for(int j = 0; j < m; j++)
	    System.out.println(dp[ i[j] - 1 ]);
    }
}

// AC
