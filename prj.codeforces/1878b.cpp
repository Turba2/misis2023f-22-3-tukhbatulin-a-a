

#include <iostream>
int main()
{
    int a;
    std::cin >> a;
    while (a--)
    {
        int n; 
        std::cin >> n;
        for (int i = 1; i <= 2 * n - 1; i += 2) std:: cout << i << " ";
        std::cout << std::endl;
    }

    return 0;
}
