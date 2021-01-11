#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>
#define MAXN 100
class HMM
{
public:
	int N, M, T;   //N表示可能的状态数，M表示可能的观测数，T表示时间
	int O[MAXN];   //输入观测序列
	double forward[MAXN][MAXN], backward[MAXN][MAXN], pi[MAXN]; //forward表示前向概率，backward表示后向概率
	double A[MAXN][MAXN], B[MAXN][MAXN];   //A状态转移矩阵，B观测转移矩阵
	double DP[MAXN][MAXN];				//Predict中的中间结果
	int mark[MAXN][MAXN];
	int L[MAXN];						//Predict序列值
	HMM(){}
	void Input()
	{
		//输入状态转移矩阵
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= N; j++)
				std::cin >> A[i][j];
		//输入观测转移矩阵
		for (int i = 1; i <= N; i++)
			for (int j = 1; j <= M; j++)
				std::cin >> B[i][j];
		//输入初始概率
		for (int i = 1; i <= N; i++)
			std::cin >> pi[i];
		for (int i = 1; i <= T; i++)
			std::cin >> O[i];
	}
	HMM(int n,int m,int t)
	{
		N = n;
		M = m;
		T = t;
		Input();
	}
	void init_forward()
	{
		for (int i = 1; i <= N; i++)
			forward[i][1] = pi[i] * B[i][O[1]];
	}
	void init_backward()
	{
		for (int i = 1; i <= N; i++)
			backward[i][T] = 1;
	}
	void init_predict()
	{
		for (int i = 1; i <= N; i++)
			DP[i][1] = pi[i] * B[i][O[1]];
	}
	void solve()
	{
		for (int t = 2; t <= T; t++)
		{
			for (int i = 1; i <= N; i++)
			{
				mark[i][t] = 0;
				DP[i][t] = 0;
				for (int j = 1; j <= N; j++)
				{
					double tmp = DP[j][t-1] * A[j][i] * B[i][O[t]];
					if (DP[i][t] < tmp)
					{
						DP[i][t] = tmp;
						mark[i][t] = j;
					}
				}
			}
		}
		double ans = 0.0;
		for (int i = 1; i <= N; i++)
		{
			if (ans < DP[i][T])
			{
				ans = DP[i][T];
				mark[0][T + 1] = i;
			}
		}
	}
	double forward_cal()
	{
		init_forward();
		for (int t = 2; t <= T; t++)
		{
			for (int i = 1; i <= N; i++)
			{
				forward[i][t] = 0;
				for (int j = 1; j <= N; j++)
				{
					forward[i][t] += forward[j][t - 1] * A[j][i] * B[i][O[t]];  // j-->i，且i的状态取o[t]
				}
			}
		}
		double ans = 0.0;
		for (int i = 1; i <= N; i++)
			ans = ans + forward[i][T];
		return ans;
	}
	double backward_cal()
	{
		init_backward();
		for (int t = T - 1; t > 0; t--)
		{
			for (int i = 1; i <= N; i++)
			{
				backward[i][t] = 0;
				for (int j = 1; j <= N; j++)
				{
					backward[i][t] += backward[j][t + 1] * A[i][j] * B[j][O[t+1]];
				}
			}
		}
		double ans = 0.0;
		for (int i = 1; i <= N; i++)
			ans = ans + backward[i][1] * pi[i] * B[i][O[1]];
		return ans;
	}
	void get_list(int t,int pre)
	{
		L[t] = mark[pre][t + 1];
		if (t>1)
			get_list(t - 1, L[t]);
	}
	void output()
	{
		for (int i = 1; i <= T; i++)
			std::cout << L[i] << " ";
		std::cout << "\n";
	}
	void predict()
	{
		//初始化
		init_predict();
		solve();
		get_list(T, 0);
		output();
	}
};
int main()
{
	HMM work=HMM(3, 2, 3);
	std::cout << work.forward_cal() << "\n";
	std::cout << work.backward_cal() << "\n";
	work.predict();
	system("pause");
	return 0;
}
/*
0.5 0.2 0.3
0.3 0.5 0.2
0.2 0.3 0.5

0.5 0.5
0.4 0.6
0.7 0.3

0.2 0.4 0.4

1 2 1
*/