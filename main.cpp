#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>
#include <algorithm>

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

int main()
{
    std::cout << "\nHello, world!\n";
    //----------------------------------------------------

    //----------------------------------------------------
    std::cout << "\n/************************************/\n";
    return 0;
}