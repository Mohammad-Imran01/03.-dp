#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <cmath>

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

int main()
{
    std::cout << "\nHello, world!\n";
    //----------------------------------------------------

    //----------------------------------------------------
    std::cout << "\n/************************************/\n";
    return 0;
}