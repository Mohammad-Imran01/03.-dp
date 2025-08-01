#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

typedef std::vector<int> VI1;
typedef std::vector<VI1> VI2;

class ClimbingStairs {
public:
  int solve(int n) {
    int next2 = 1;
    int next1 = 0;

    for (int i = n; i >= 0; --i) {
      int curr = next1 + next2;
      next1 = next2;
      next2 = curr;
    }

    return next1;
  }
};

class Rob {
public:
  int solve(const std::vector<int> &houses) {
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

class HouseRobber2 {
  int solve(const std::vector<int> &nums, int beg, int end) {
    std::vector<int> dp(nums.size(), 0);

    dp[beg] = nums[beg];
    dp[beg + 1] = std::max(nums[beg], nums[beg + 1]);

    for (int i = beg + 2; i < end; ++i)
      dp[i] = std::max(nums[i] + dp[i - 2], dp[i - 1]);

    return dp[end - 1];
  }

public:
  int Rob(const std::vector<int> &nums) {
    if (nums.empty())
      return 0;
    if (nums.size() == 1)
      return nums.front();
    if (nums.size() == 2)
      return std::max(nums.front(), nums.back());

    return std::max(solve(nums, 0, nums.size() - 1),
                    solve(nums, 1, nums.size()));
  }
};

class UniquePaths2D {
public:
  const int MAX_LEN = 102;
  int **dp;
  int m, n;
  UniquePaths2D() {
    dp = new int *[MAX_LEN];
    for (int i = 0; i < MAX_LEN; ++i) {
      dp[i] = new int[MAX_LEN];
      std::fill(dp[i], dp[i] + MAX_LEN, -1);
    }
  }
  ~UniquePaths2D() {
    for (int i = 0; i < MAX_LEN; ++i)
      delete[] dp[i];
    delete[] dp;
  }

private:
  int solveHelper(const std::vector<std::vector<int>> &grid, int i, int j) {
    if (i >= m || j >= n || grid[i][j])
      return 0;
    if (dp[i][j] != -1)
      return dp[i][j];
    if (i == m - 1 && j == n - 1)
      return 1;
    return dp[i][j] = solveHelper(grid, i + 1, j) + solveHelper(grid, i, j + 1);
  }

public:
  int solve(const std::vector<std::vector<int>> &grid) {
    m = grid.size(), n = grid.front().size();

    return solveHelper(grid, 0, 0);
  }
};

class UniqueObstaclePaths2D {
public:
  const int MAX_LEN = 102;
  int **dp;
  UniqueObstaclePaths2D() {
    dp = new int *[MAX_LEN];
    for (int i = 0; i < MAX_LEN; ++i) {
      dp[i] = new int[MAX_LEN];
      std::fill(dp[i], dp[i] + MAX_LEN, -1);
    }
  }

private:
  int solveHelper(int m, int n, int i, int j) {
    if (i > m || j > n)
      return 0;
    if (dp[i][j] != -1)
      return dp[i][j];
    if (i == m && j == n)
      return 1;
    return dp[i][j] = solveHelper(m, n, i + 1, j) + solveHelper(m, n, i, j + 1);
  }

public:
  int solve(int m, int n) { return solveHelper(m, n, 1, 1); }
};

class MinPathSum2D {
public:
  int MAX_LEN = 0;
  int **dp;
  int m, n;
  ~MinPathSum2D() {
    for (int i = 0; i < MAX_LEN; ++i)
      delete[] dp[i];
  }

private:
  int solveHelper(const std::vector<std::vector<int>> &grid, int i, int j) {
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
  int solve(const std::vector<std::vector<int>> &grid) {
    m = grid.size(), n = grid.front().size();

    MAX_LEN = std::max(m, n) + 1;

    dp = new int *[MAX_LEN];
    for (int i = 0; i < MAX_LEN; ++i) {
      dp[i] = new int[MAX_LEN];
      std::fill(dp[i], dp[i] + MAX_LEN, -1);
    }
    return solveHelper(grid, 0, 0);
  }
};

class MinPathSumTriangle {
public:
  int solve(std::vector<std::vector<int>> &tri) {
    const int len = tri.size();

    std::vector<int> dp(len, 1e8);
    dp.front() = tri.front().front();

    for (int i = 1; i < len; ++i) {
      auto temp = std::vector<int>(len, 1e8);
      for (int j = 0; j <= i; ++j) {
        int left = (j - 1 >= 0) ? dp[j - 1] : 1e8, mid = (j < i) ? dp[j] : 1e8;
        temp[j] = tri[i][j] + std::min(left, mid);
      }
      dp = temp;
    }
    return *std::min_element(dp.begin(), dp.end());
  }
};

class FallingPathSum2D {
public:
  int solve(std::vector<std::vector<int>> mat) {
    const int len = mat.size();

    for (int i = 1; i < len; ++i) {
      for (int j = 0; j < len; ++j) {
        int left = j - 1 >= 0 ? mat[i - 1][j - 1] : 1e8;
        int up = mat[i - 1][j];
        int right = j + 1 < mat.size() ? mat[i - 1][j + 1] : 1e8;

        mat[i][j] += std::min(left, std::min(up, right));
      }
    }

    return *std::min_element(mat[len - 1].begin(), mat[len - 1].end());
  }
};

class PartitionEqualSum {

  int **dp = nullptr;
  bool help(const std::vector<int> &nums, int ind, int target) {
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
  bool solve(const std::vector<int> &nums) {
    int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);

    // odd sum cant be partitioned
    if (sum % 2)
      return false;

    dp = new int *[nums.size()];

    for (int i = 0; i < nums.size(); ++i) {
      int *temp = new int[sum + 1];
      std::fill(temp, temp + sum + 1, -1);
      dp[i] = temp;
      temp = nullptr;
    }

    return help(nums, 0, sum / 2);
  }
};

class MinCoinSum {
  int **memo = nullptr;
  int help(std::vector<int> &coins, int amount, int ind) {
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
    if (coins[ind] <= amount) {
      takeSame = 1 + help(coins, amount - coins[ind], ind);
      takeNext = 1 + help(coins, amount - coins[ind], ind + 1);
    }
    return memo[ind][amount] = std::min(ignore, std::min(takeSame, takeNext));
  }

public:
  int coinChange(std::vector<int> &coins, int amount) {
    int len = coins.size();
    memo = new int *[len];
    for (int i = 0; i < len; ++i) {
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

namespace SubSeq {
class SubsetSumEqualToK {
public:
  void solve(VI1 &arr, int K) {
    VI2 dp(arr.size() + 1, VI1(K + 1, 0));

    for (int i = 0; i <= arr.size(); ++i)
      dp[i][0] = true;

    for (int i = 1; i <= arr.size(); ++i) {
      for (int targ = 1; targ <= K; ++targ) {
        dp[i][targ] = dp[i - 1][targ] ||
                      (targ >= arr[i - 1] ? dp[i - 1][targ - arr[i - 1]] : 0);
      }
    }
  }
};
class Knapsack01 {
public:
  int solve(const VI1 &money, const VI1 &wt, int size) {
    VI1 dp(size + 1, 0);

    for (int ind = 0; ind < money.size(); ind)
      for (int w = size; w >= wt[ind]; --w)
        dp[w] = std::max(dp[w], dp[w - wt[ind]] + money[ind]);

    return dp.back();
  }
};
class KnapsackUnbounded {
  int solve(const VI1 &money, const VI1 &wt, int size) {
    VI1 dp(size + 1, 0);

    for (int w = 0; w <= size; ++w)
      for (int ind = 0; ind < money.size(); ++ind)
        dp[w] = std::max(dp[w], dp[w - wt[ind]] + money[ind]);

    return dp.back();
  }
};
class RodCut {
public:
  int solve(const VI1 &prices) {
    const int len = prices.size();
    VI2 dp(len + 1, VI1(len + 1, 0));

    for (int i = 1; i <= len; ++i) {
      for (int size = 1; size <= len; ++size) {
        dp[i][size] = (size >= i) ? std::max(dp[i - 1][size],
                                             prices[i - 1] + dp[i][size - i])
                                  : dp[i - 1][size];
      }
    }
    return dp.back().back();
  }
};
} // namespace SubSeq

namespace String {
class LCS {
  int solve(std::string t1, std::string t2) {
    int m = t1.size(), n = t2.size();
    VI2 dp(m + 1, VI1(n + 1, 0));

    for (int i = 1; i <= m; ++i) {
      for (int j = 0; j <= n; ++j) {
        if (t1[i - 1] == t2[j - 1])
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
    return dp[m][n];
  }
};

class WildcardMatch {
  std::vector<std::vector<int>> dp;
  bool func(const std::string &ptn, const std::string &str, int pInd, int ind) {
    if (pInd <= 0 && ind <= 0)
      return true;
    if (pInd <= 0)
      return false;
    if (ind <= 0) {
      for (int i = pInd; i > 0; --i)
        if (ptn[i - 1] != '*')
          return false;
      return true;
    }
    if (dp[pInd][ind] != -1)
      return dp[pInd][ind];

    if (ptn[pInd - 1] == str[ind - 1] || ptn[pInd - 1] == '?')
      return dp[pInd][ind] = func(ptn, str, pInd - 1, ind - 1);
    else if (ptn[pInd - 1] == '*')
      return dp[pInd][ind] =
                 func(ptn, str, pInd - 1, ind) || func(ptn, str, pInd, ind - 1);

    return dp[pInd][ind] = false;
  }
  bool loopBased(std::string ptn, std::string str) {
    int m = ptn.size(), n = str.size();
    std::vector<std::vector<bool>> dp(m + 1, std::vector<bool>(n + 1, false));

    dp[0][0] = true;

    for (int i = 1; i <= m; ++i)
      if (ptn[i - 1] == '*')
        dp[i][0] = dp[i - 1][0];
      else
        break;

    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= n; ++j) {
        if (ptn[i - 1] == str[j - 1] || ptn[i - 1] == '?')
          dp[i][j] = dp[i - 1][j - 1];
        else if (ptn[i - 1] == '*')
          dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
        else
          dp[i][j] = false;
      }
    }
    return dp[m][n];
  }

public:
  bool isMatching(const std::string &ptn, const std::string &str) {
    int m = ptn.size(), n = str.size();
    dp.assign(m + 1, std::vector<int>(n + 1, -1));
    return func(ptn, str, m, n);
  }
};

class LongestPalindromicSubsequence {
public:
  int solve(const std::string &str) {
    const int len = str.length();
    VI2 dp(len + 1, VI1(len + 1, 0));

    const std::string rev(str.crbegin(), str.crend());

    for (int i = 1; i <= len; ++i) {
      for (int j = 1; j <= len; ++j) {
        if (str[i - 1] == rev[j - 1])
          dp[i][j] = 1 + dp[i - 1][j - 1];
        else
          dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
      }
    }
    return dp.back().back();
  }
};

class MinInsertToMakePalindrome {
public:
  int solve(std::string s) {
    LongestPalindromicSubsequence lps;
    return s.length() - lps.solve(s);
  }
};
} // namespace String

namespace Stocks {
// buy one sell one(once);
class BuySellI {
public:
  int solve(const VI1 &stocks) {
    if (stocks.empty())
      return 0;
    int profit = 0;
    int curr = stocks.front();

    for (int i = 1; i < stocks.size(); ++i) {
      int cost = stocks.at(i) - curr;
      profit = std::max(profit, stocks.at(i) - curr);
      curr = std::min(curr, stocks[i]);
    }

    return profit;
  }
};

// can buy/sell more than once, but still sell first then buy next stock.
class BuySellII {
public:
  int maxProfit(const VI1 &prices) {
    int profit = 0;

    for (int i = 1; i < prices.size(); ++i) {
      if (prices[i] > prices[i - 1]) {
        profit += prices[i] - prices[i - 1];
      }
    }

    return profit;
  }
};
// can buy/sell at max twice, but still sell first then buy next stock.
class BuySellIII {
  std::vector<std::vector<std::vector<long long>>> dp;
  int help(const VI1 &stocks, int ind, bool buy, int left) {
    if (ind >= stocks.size() || left < 0)
      return 0;
    if (dp[ind][buy][left] != -1)
      return dp[ind][buy][left];
    if (buy) { // buy or not buy move to next
      return std::max(-stocks[ind] + help(stocks, ind + 1, false, left),
                      help(stocks, ind + 1, true, left));
    } else { // sell or not sell move to next
      return std::max(stocks[ind] + help(stocks, ind + 1, true, left - 1),
                      help(stocks, ind + 1, false, left));
    }
    return 0;
  }

public:
  int solve(const VI1 &stocks) {
    if (stocks.empty())
      return 0;
    const int len = stocks.size();
    dp.assign(len, std::vector<std::vector<long long>>(
                       2, std::vector<long long>(3, -1)));
    return help(stocks, 0, true, 2);
  }
};

} // namespace Stocks

namespace LIS {
class LIS {
public:
  int solve(const VI1 &nums) {
    int len = nums.size();
    int *dp = new int[len];
    std::fill(dp, dp+len, 1);

    for(int i = 1; i < len; ++i) {
        for(int j = 0; j < i; ++j) {
            if(nums[i] > nums[j]) {
                dp[i] = std::max(dp[i], dp[j]+1);
            }
        }
    }
    
    int res = *std::max_element(dp, dp+len);
    delete[] dp;
    
    return res;
  }
};
} // namespace LIS

int main() {
  std::cout << "\nHello, world!\n";
  std::cout << "\n/************************************/\n";
  //----------------------------------------------------
  String::WildcardMatch match;
  std::cout << std::boolalpha << match.isMatching("aa?k", "aadk");
  //----------------------------------------------------
  std::cout << "\n/************************************/\n";
  return 0;
};