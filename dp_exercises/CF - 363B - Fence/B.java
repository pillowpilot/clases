import java.util.Scanner;
import java.lang.Math;

public class B{
    public static void main(String[] args){
	Scanner in = new Scanner(System.in);
	    
	int n = in.nextInt(), k = in.nextInt(), minSum = 0, minIndex = 0;
	int[] h = new int[n];
	int[] dp = new int[n];
	
	for(int i = 0; i < k; i++){
	    h[i] = in.nextInt();
	    minSum += h[i];
	}
	
	dp[k-1] = minSum;
	minIndex = 1;
	for(int i = k; i < n; i++){
	    h[i] = in.nextInt();
	    dp[i] = dp[i-1] + h[i] - h[i-k];
	    if( dp[i] < minSum ){
		minSum = dp[i];
		minIndex = i - k + 2;
	    }
	}

	System.out.println(minIndex);
    }
}

// AC
