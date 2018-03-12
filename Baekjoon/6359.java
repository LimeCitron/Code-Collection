import java.util.*;
public class FirstClass {

	public static void main(String[] args) {
		FirstJob();
		Scanner s = new Scanner(System.in);
		int n = s.nextInt();
		for(int i = 1; i <= n; i++) {
			int input = s.nextInt();
			System.out.println(arr[input]);
		}
		return;
	}
	
	static int arr[] = new int[101];
	
	public static void FirstJob()
	{
		arr[1] = 1;
		for(int i = 2; i <= 100; i++){
			if(GetNumofFactor(i) % 2 != 0) arr[i] = arr[i-1] + 1;
			else arr[i] = arr[i-1];
		}
		return;
	}
	
	public static int GetNumofFactor(int target) {
		int result = 2;
		for(int i = 2; i < target; i++){
			if(target % i == 0) result = result + 1;
		}
		
		return result;
	}

}