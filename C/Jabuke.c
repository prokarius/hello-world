#include<stdio.h>

#define ABS(x) (x > 0)?(x):(-x)

typedef struct{
    int x;
    int y;
} Coord;

Coord coord(int x, int y){
    Coord out = {x, y};
    return out;
}

// Shoelace method
int getArea(Coord a, Coord b, Coord c){
    int area = 0;
    area += a.x * b.y - b.x * a.y;
    area += b.x * c.y - c.x * b.y;
    area += c.x * a.y - a.x * c.y;

    area = ABS(area);

    return area / 2;
}

int main(){
    int x, y;
    scanf("%d %d", &x, &y);

    // Double all the coordinates so we don't need doubles
    x *= 2; y *= 2;
    Coord a = coord(x, y);

    scanf("%d %d", &x, &y);
    x *= 2; y *= 2;
    Coord b = coord(x, y);

    scanf("%d %d", &x, &y);
    x *= 2; y *= 2;
    Coord c = coord(x, y);

    int area = getArea(a, b, c);

    int n;
    scanf("%d", &n);

    int out = 0;
    for (int i = 0; i < n; ++i){
        scanf("%d %d", &x, &y);
        x *= 2; y *= 2;
        Coord p = coord(x, y);

        // If the sum of the areas are the same, the point is inside the triangle
        if (getArea(a, b, p) + getArea(b, c, p) + getArea(c, a, p) == area) out++;
    }

    // Process the area by divding by 4. Or 2 then 2 again
    // This one is safe, because area is definitely even.
    area /= 2;

    printf("%d.%d\n", area/2, (area%2) * 5);
    printf("%d\n", out);

    return 0;
}

