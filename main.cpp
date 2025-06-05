#include <iostream>

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