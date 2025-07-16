#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>
#include <memory>
#include <cmath>
#include <numeric>
#include <functional>
#include <memory>

typedef std::vector<int> VI1;
typedef std::vector<VI1> VI2;

class ClimbingStairs
{
public:
    int solve(int n)
    {
        int next2 = 1;
        int next1 = 0;

        for (int i = n; i >= 0; --i)
        {
            int curr = next1 + next2;
            next1 = next2;
            next2 = curr;
        }

        return next1;
    }
};

class Rob
{
public:
    int solve(const std::vector<int> &houses)
    {
        if (houses.empty())
            return 0;
        if (houses.size() == 1)
            return houses.front();
        std::vector<int> dp(houses.size(), 0);
        dp[0] = houses[0];
        dp[1] = std::max(houses[0], houses[1]);

        for (int i = 2; i < houses.size(); ++i)
            dp[i] = std::max(houses[i] + dp[i - 2], dp[i - 1]);

        return dp.back();
    }
};

class HouseRobber2
{
    int solve(const std::vector<int> &nums, int beg, int end)
    {
        std::vector<int> dp(nums.size(), 0);

        dp[beg] = nums[beg];
        dp[beg + 1] = std::max(nums[beg], nums[beg + 1]);

        for (int i = beg + 2; i < end; ++i)
            dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);

        return dp[end - 1];
    }

public:
    int Rob(const std::vector<int> &nums)
    {
        if (nums.empty())
            return 0;
        if (nums.size() == 1)
            return nums.front();
        if (nums.size() == 2)
            return std::max(nums.front(), nums.back());

        return std::max(solve(nums, 0, nums.size() - 1), solve(nums, 1, nums.size()));
    }
};

class UniquePaths2D
{
public:
    const int MAX_LEN = 102;
    int **dp;
    int m, n;
    UniquePaths2D()
    {
        dp = new int *[MAX_LEN];
        for (int i = 0; i < MAX_LEN; ++i)
        {
            dp[i] = new int[MAX_LEN];
            std::fill(dp[i], dp[i] + MAX_LEN, -1);
        }
    }
    ~UniquePaths2D()
    {
        for (int i = 0; i < MAX_LEN; ++i)
            delete[] dp[i];
        delete[] dp;
    }

private:
    int solveHelper(const std::vector<std::vector<int>> &grid, int i, int j)
    {
        if (i >= m || j >= n || grid[i][j])
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
        if (i == m - 1 && j == n - 1)
            return 1;
        return dp[i][j] = solveHelper(grid, i + 1, j) +
                          solveHelper(grid, i, j + 1);
    }

public:
    int solve(const std::vector<std::vector<int>> &grid)
    {
        m = grid.size(),
        n = grid.front().size();

        return solveHelper(grid, 0, 0);
    }
};

class UniqueObstaclePaths2D
{
public:
    const int MAX_LEN = 102;
    int **dp;
    UniqueObstaclePaths2D()
    {
        dp = new int *[MAX_LEN];
        for (int i = 0; i < MAX_LEN; ++i)
        {
            dp[i] = new int[MAX_LEN];
            std::fill(dp[i], dp[i] + MAX_LEN, -1);
        }
    }

private:
    int solveHelper(int m, int n, int i, int j)
    {
        if (i > m || j > n)
            return 0;
        if (dp[i][j] != -1)
            return dp[i][j];
        if (i == m && j == n)
            return 1;
        return dp[i][j] = solveHelper(m, n, i + 1, j) +
                          solveHelper(m, n, i, j + 1);
    }

public:
    int solve(int m, int n)
    {
        return solveHelper(m, n, 1, 1);
    }
};

class MinPathSum2D
{
public:
    int MAX_LEN = 0;
    int **dp;
    int m, n;
    ~MinPathSum2D()
    {
        for (int i = 0; i < MAX_LEN; ++i)
            delete[] dp[i];
    }

private:
    int solveHelper(const std::vector<std::vector<int>> &grid, int i, int j)
    {
        if (i >= m || j >= n)
            return 1e8;
        if (dp[i][j] != -1)
            return dp[i][j];
        if (i == m - 1 && j == n - 1)
            return grid[i][j];
        int right = 1e8, down = 1e8;

        if (i + 1 < m)
            down = solveHelper(grid, i + 1, j);
        if (j + 1 < n)
            right = solveHelper(grid, i, j + 1);

        return dp[i][j] = grid[i][j] + std::min(right, down);
    }

public:
    int solve(const std::vector<std::vector<int>> &grid)
    {
        m = grid.size(),
        n = grid.front().size();

        MAX_LEN = std::max(m, n) + 1;

        dp = new int *[MAX_LEN];
        for (int i = 0; i < MAX_LEN; ++i)
        {
            dp[i] = new int[MAX_LEN];
            std::fill(dp[i], dp[i] + MAX_LEN, -1);
        }
        return solveHelper(grid, 0, 0);
    }
};

class MinPathSumTriangle
{
public:
    int solve(std::vector<std::vector<int>> &tri)
    {
        const int len = tri.size();

        std::vector<int> dp(len, 1e8);
        dp.front() = tri.front().front();

        for (int i = 1; i < len; ++i)
        {
            auto temp = std::vector<int>(len, 1e8);
            for (int j = 0; j <= i; ++j)
            {
                int
                    left = (j - 1 >= 0) ? dp[j - 1] : 1e8,
                    mid = (j < i) ? dp[j] : 1e8;
                temp[j] = tri[i][j] + std::min(left, mid);
            }
            dp = temp;
        }
        return *std::min_element(dp.begin(), dp.end());
    }
};

class FallingPathSum2D
{
public:
    int solve(std::vector<std::vector<int>> mat)
    {
        const int len = mat.size();

        for (int i = 1; i < len; ++i)
        {
            for (int j = 0; j < len; ++j)
            {
                int left = j - 1 >= 0 ? mat[i - 1][j - 1] : 1e8;
                int up = mat[i - 1][j];
                int right = j + 1 < mat.size() ? mat[i - 1][j + 1] : 1e8;

                mat[i][j] += std::min(left, std::min(up, right));
            }
        }

        return *std::min_element(mat[len - 1].begin(), mat[len - 1].end());
    }
};

class PartitionEqualSum
{

    int **dp = nullptr;
    bool help(const std::vector<int> &nums, int ind, int target)
    {
        if (ind >= nums.size() || target < 0)
            false;
        if (!target || nums[ind] == target)
            return true;
        if (dp[ind][target] != -1)
            return dp[ind][target];
        if (help(nums, ind + 1, target - nums[ind]))
            return true;
        if (help(nums, ind + 1, target))
            return true;
        return false;
    }

public:
    bool solve(const std::vector<int> &nums)
    {
        int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);

        // odd sum cant be partitioned
        if (sum % 2)
            return false;

        dp = new int *[nums.size()];

        for (int i = 0; i < nums.size(); ++i)
        {
            int *temp = new int[sum + 1];
            std::fill(temp, temp + sum + 1, -1);
            dp[i] = temp;
            temp = nullptr;
        }

        return help(nums, 0, sum / 2);
    }
};

class MinCoinSum
{
    int **memo = nullptr;
    int help(std::vector<int> &coins, int amount, int ind)
    {
        if (ind >= coins.size() || amount < 0)
            return 1e8;
        if (amount == 0)
            return 0;

        if (memo[ind][amount] != -1)
            return memo[ind][amount];

        // 1 ignore
        // 2.a take and go to same again
        // 2.b take and next ind
        int ignore = 1e8;
        int takeSame = 1e8;
        int takeNext = 1e8;

        ignore = help(coins, amount, ind + 1);
        if (coins[ind] <= amount)
        {
            takeSame = 1 + help(coins, amount - coins[ind], ind);
            takeNext = 1 + help(coins, amount - coins[ind], ind + 1);
        }
        return memo[ind][amount] = std::min(
                   ignore,
                   std::min(
                       takeSame,
                       takeNext));
    }

public:
    int coinChange(std::vector<int> &coins, int amount)
    {
        int len = coins.size();
        memo = new int *[len];
        for (int i = 0; i < len; ++i)
        {
            int *temp = new int[amount + 1];
            std::fill(temp, temp + amount + 1, -1);
            memo[i] = temp;
            temp = nullptr;
        }
        int res = help(coins, amount, 0);

        for (int i = 0; i < len; ++i)
            delete[] memo[i];
        delete[] memo;

        return (res >= 1e8) ? -1 : res;
    }
};

namespace SubSeq
{
    class SubsetSumEqualToK
    {
    public:
        void solve(VI1 &arr, int K)
        {
            VI2 dp(arr.size() + 1, VI1(K + 1, 0));

            for (int i = 0; i <= arr.size(); ++i)
                dp[i][0] = true;

            for (int i = 1; i <= arr.size(); ++i)
            {
                for (int targ = 1; targ <= K; ++targ)
                {
                    dp[i][targ] = dp[i - 1][targ] || (targ >= arr[i - 1]
                                                          ? dp[i - 1][targ - arr[i - 1]]
                                                          : 0);
                }
            }
        }
    };
    class Knapsack01
    {
    public:
        int solve(const VI1 &money, const VI1 &wt, int size)
        {
            VI1 dp(size + 1, 0);

            for (int ind = 0; ind < money.size(); ind)
                for (int w = size; w >= wt[ind]; --w)
                    dp[w] = std::max(dp[w], dp[w - wt[ind]] + money[ind]);

            return dp.back();
        }
    };
    class KnapsackUnbounded
    {
        int solve(const VI1 &money, const VI1 &wt, int size)
        {
            VI1 dp(size + 1, 0);

            for (int w = 0; w <= size; ++w)
                for (int ind = 0; ind < money.size(); ++ind)
                    dp[w] = std::max(dp[w], dp[w - wt[ind]] + money[ind]);

            return dp.back();
        }
    };
    class RodCut
    {
    public:
        int solve(const VI1 &prices)
        {
            const int len = prices.size();
            VI2 dp(len + 1, VI1(len + 1, 0));

            for (int i = 1; i <= len; ++i)
            {
                for (int size = 1; size <= len; ++size)
                {
                    if (size >= i)
                    {
                        dp[i][size] = std::max(
                            dp[i - 1][size], prices[i - 1] + dp[i][size - i]);
                    }
                    else
                    {
                        dp[i][size] = dp[i - 1][size];
                    }
                }
            }
            return dp.back().back();
        }
    };
}

int main()
{
    std::cout << "\nHello, world!\n";
    //----------------------------------------------------

    //----------------------------------------------------
    std::cout << "\n/************************************/\n";
    return 0;
};