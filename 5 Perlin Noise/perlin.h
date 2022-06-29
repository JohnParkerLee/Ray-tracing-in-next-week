#ifndef PERLIN_H
#define PERLIN_H

#include "rtweekend.h"
// #include "algorithm"

class perlin
{
public:
    perlin()
    {
        ranfloat = new double[point_count];
        for (int i = 0; i < point_count; i++)
        {
            ranfloat[i] = random_double();
        }
        perm_x = perlin_generate_perm();
        perm_y = perlin_generate_perm();
        perm_z = perlin_generate_perm();
    }

private:
    static const int point_count = 256;
    double *ranfloat;
    int *perm_x;
    int *perm_y;
    int *perm_z;

    static int *perlin_generate_perm()
    {
        auto p = new int[point_count];
        for (int i = 0; i < perlin::point_count; i++)
            p[i] = i;
        permute(p, point_count);
        return p;
    }

    static void permute(int *p, int n)
    {
        for (int i = n - 1; i > 0; i--)
        {
            int target = random_int(0, i);
            std::swap(p[i], p[target]);
        }
    }
};

#endif