#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int maxPoints(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize <= 2) {
        return pointsSize;
    }

    int max_points = 2;

    for (int i = 0; i < pointsSize; i++) {
        int duplicate_slopes = 0;
        
        for (int j = i + 1; j < pointsSize; j++) {
            int count = 2;
            int dx1 = points[j][0] - points[i][0];
            int dy1 = points[j][1] - points[i][1];
            
            int g1 = gcd(dx1, dy1);
            if (g1 != 0) {
                dx1 /= g1;
                dy1 /= g1;
            }

            for (int k = j + 1; k < pointsSize; k++) {
                int dx2 = points[k][0] - points[i][0];
                int dy2 = points[k][1] - points[i][1];
                
                int g2 = gcd(dx2, dy2);
                if (g2 != 0) {
                    dx2 /= g2;
                    dy2 /= g2;
                }

                if (dx1 == dx2 && dy1 == dy2) {
                    count++;
                }
            }
            
            if (count > max_points) {
                max_points = count;
            }
        }
    }

    return max_points;
}

