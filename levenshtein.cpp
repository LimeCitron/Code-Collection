#include <iostream>
#include <locale>
#include <string>
#include <vector>
using namespace std;
typedef vector<int> Vec;
const int DEF = 0xAC00;
const int MIDDLESIZE = 21;
const int LASTSIZE = 28;

class Word	// Class for storing information of Word
{
private:
	wstring original; //    Korean Unicode : {[(index of 초성×21)+ index of 중성]×28} + index of 종성 + 0xAC00
	Vec first;
	Vec middle;
	Vec last;
	Vec other;
	int size;
public:
	Word() { ; }
	Word(wstring input) : original(input)
	{
		int temp; int temp2;
		wstring::iterator pos;
		for (pos = input.begin(); pos != input.end(); ++pos)
		{
			if (*pos >= 0xAC00 && *pos <= 0xD7A3)
			{
				temp = static_cast<int> (*pos);
				temp = temp - DEF;
				temp2 = (temp % LASTSIZE);
				last.push_back(temp2);
				temp = (temp - temp2) / LASTSIZE;
				temp2 = (temp % MIDDLESIZE);
				middle.push_back(temp2);
				temp = (temp - temp2) / MIDDLESIZE;
				first.push_back(temp);
				other.push_back(-1);
			}
			else
			{
				other.push_back(*pos);
				first.push_back(-1);
				middle.push_back(-1);
				last.push_back(-1);
				continue;
			}
		}
		size = input.length();
	}
	int GetLast(int index) { return last[index]; }
	int GetMiddle(int index) { return middle[index]; }
	int GetFirst(int index) { return first[index]; }
	int GetOther(int index) { return other[index]; }
	wstring GetString() {return original; }
	int GetSize() { return size; }
};

class FindDistance
{
private:
	Word word1;
	Word word2;
public:
	FindDistance()
	{
		wstring test1;
		wstring test2;
		getline(wcin, test1);
		getline(wcin, test2);
		word1 = test1;
		word2 = test2;
	}

	int IsSame(int idx1, int idx2) // Same == 0
	{
		int count = 0;
		if (word1.GetLast(idx1) == 0 && word2.GetLast(idx2) == 0)	// there are no 종성, both two words.
		{
			count = count + CompareFirst(idx1, idx2);
			count = count + CompareMiddle(idx1, idx2);
			if (count >= 3) return 4;
			return count;
		}
		count = count + CompareFirst(idx1, idx2);
		count = count + CompareMiddle(idx1, idx2);
		count = count + CompareLast(idx1, idx2);
		count = count + CompareOther(idx1, idx2);
		if (count >= 3) return 4;
		else return count;
	}

	int CompareFirst(int idx1, int idx2)	// Compare 초성
	{
		if (word1.GetFirst(idx1) != word2.GetFirst(idx2))
		{
			if (MakeGroupFirst(word1.GetFirst(idx1)) == MakeGroupFirst(word2.GetFirst(idx2))) return 1;
			else return 2;
		}
		return 0;
	}

	int CompareMiddle(int idx1, int idx2)	// Compare 중성
	{
		if (word1.GetMiddle(idx1) != word2.GetMiddle(idx2))  return 2;
		return 0;
	}

	int CompareLast(int idx1, int idx2) // Compare 종성
	{
		if (word1.GetLast(idx1) != word2.GetLast(idx2))
		{
			if (MakeGroupLast(word1.GetLast(idx1)) == MakeGroupLast(word2.GetLast(idx2))) return 1;
			else return 2;
		}
		return 0;
	}

	int CompareOther(int idx1, int idx2)	// Compare words that are not Korean
	{
		if (word1.GetOther(idx1) == -1 && word2.GetOther(idx2) == -1)		// Both Inputs were Korean words, Not need this compare.
			return 0;
		else if (word1.GetOther(idx1) == -1 || word2.GetOther(idx2) == -1)		// Onlt one word is Korean.
			return 5;
		if (word1.GetOther(idx1) != word2.GetOther(idx2))  return 1;		// If both Inputs were not Korean words, we need to use original Levenshiein Distance.
		return 0;
	}

	int MakeGroupFirst(int x)	// To Make the Similar Word Group for 초성  -> ex)  (ㄱ,ㄲ), (ㄷ,ㄸ), (ㅂ,ㅃ), (ㅅ,ㅆ), (ㅈ,ㅉ)
	{
		switch (x)
		{
		case 1: x = 0; break;
		case 4: x = 3; break;
		case 8: x = 7; break;
		case 10: x = 9; break;
		case 13: x = 12; break;
		default:;
		}
		return x;
	}
	int MakeGroupLast(int x)	// To Make the Similar Word Group for 종성  -> ex)  (ㄱ,ㄲ,ㄳ), (ㄴ,ㄵ,ㄶ), (ㄹ,ㄺ,ㄻ,ㄼ,ㄽ,ㄾ,ㄿ,ㅀ), (ㅂ,ㅄ), (ㅅ,ㅆ)
	{
		switch (x)
		{
		case 2: case 3:	x = 1; break;
		case 5: case 6: x = 4; break;
		case 9: case 10: case 11: case 12: case 13: case 14: case 15: x = 8; break;
		case 18: x = 17; break;
		case 20: x = 19; break;
		default:;
		}
		return x;
	}

	int min(int x, int y)
	{
		return x < y ? x : y;
	}
	int min(int x, int y, int z)
	{
		return x < y ? min(x, z) : min(y, z);
	}

	int EditDistance()	// Using Dynamic Programming
	{
		int m = word1.GetSize();
		int n = word2.GetSize();
		vector<Vec> dp(m + 1, Vec(n + 1, 0));
		dp[0][0] = 0;
		for (int i = 1; i <= m; i++)
		{
			if (word1.GetOther(i - 1) == -1)
				dp[i][0] = dp[i - 1][0] + 4;
			else
				dp[i][0] = dp[i - 1][0] + 1;
		}
		for (int j = 1; j <= n; j++)
		{
			if (word2.GetOther(j - 1) == -1)
				dp[0][j] = dp[0][j - 1] + 4;
			else
				dp[0][j] = dp[0][j - 1] + 1;
		}
		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				if (IsSame(i - 1, j - 1) == 0)
					dp[i][j] = dp[i - 1][j - 1];
				else // min(Substitution Cost, Insertion Cost, Deletion Cost)
					dp[i][j] = min(dp[i - 1][j - 1] + IsSame(i - 1, j - 1), dp[i][j - 1] + IsSame(i - 1, j - 1), dp[i - 1][j] + IsSame(i - 1, j - 1));
			}
		}
		PrintStage(dp);
		return dp[m][n];
	}

	int CombineKorean(int a, int b, int c)  //    Korean Unicode : {[(index of 초성×21)+ index of 중성]×28} + index of 종성 + 0xAC00
	{
		return ((a*21) + b)*28 + c + 0xAC00;
	}

	void PrintStage(vector<Vec>& a)
	{
		int m = word1.GetSize();
		int n = word2.GetSize();
		cout << "    ";
		//for(int j = 0; j <=n; j++)
			//wcout << (wchar_t)CombineKorean(word2.GetFirst(j), word2.GetMiddle(j), word2.GetLast(j)) << " ";
		cout << endl;
		for(int i = 0; i <= m; i++ )
		{
			//if(i != 0)
				//wcout << (wchar_t)CombineKorean(word1.GetFirst(i-1), word1.GetMiddle(i-1), word1.GetLast(i-1)) << " ";
			//else
				//cout << "  ";
			for(int j = 0; j <= n; j++)
				 printf("%3d ",a[i][j]);
			cout << endl;
		}
	}
};

int main(int argc, char* argv[])   // ICU를 이용해보자
{
	locale::global(locale("ko_KR.utf8"));
	FindDistance go;
	cout << "result : " << go.EditDistance() << endl;
	return 0;
}
