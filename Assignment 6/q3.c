#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int bottom_up_dp(int n, int *s, int *v, int C)
{
    int i, w;
    int M[n + 1][C + 1];

    for (i = 0; i <= n; i++)
    {
        for (w = 0; w <= C; w++)
        {
            if (i == 0 || w == 0)
            {
                M[i][w] = 0;
            }
            else if (s[i] <= w)
            {
                M[i][w] = max(v[i] + M[i-1][w - s[i]], M[i-1][w]);
            }
            else
            {
                M[i][w] = M[i-1][w];
            } 
        }
    }
    return M[n][C];
}

int main()
{
    int n, C;
    int *s;
    int *v;
    int i;

    printf("Enter the number of items n:\n");
    scanf("%d", &n);
    printf("Enter the capacity C:\n");
    scanf("%d", &C);

    s = (int *)malloc(sizeof(int) * (n+1));
    v = (int *)malloc(sizeof(int) * (n+1));

    printf("Enter the sizes of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &s[i]);

    printf("Enter the values of items (as a list, separate by spacing:\n");
    for (i = 1; i <= n; i++)
        scanf("%d", &v[i]);

    printf("The maximum value is: %d \n", bottom_up_dp(n, s, v, C));

}
