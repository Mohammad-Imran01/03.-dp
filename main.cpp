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

int main()
{
    std::cout << "\nHello, world!\n";
    //----------------------------------------------------
    ClimbingStairs climb;

    std::cout << climb.solve(3);

    //----------------------------------------------------
    std::cout << "\n/************************************/\n";
    return 0;
}