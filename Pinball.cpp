#include<cstdio>
#include<set>

#define EPSILON 1e-6

double abs(double input){
    if (input < 0) return -input;
    return input;
}

// Implement the point class
struct Point {
    double x;
    double y;
    int id;

    // A point is less than another point if it is above it
    // Note that there is not vertical or horizontal line
    // So we only need to compare the y
    bool operator <(const Point& other) const {
        return this->y < other.y;
    }

    bool operator ==(const Point& other) const {
        return abs(this->x - other.x) < EPSILON && abs(this->y - other.y) < EPSILON;
    }

    bool operator != (const Point& other) const {
        return !(*this == other);
    }
};

// Public constructor, java style
Point point(int x, int y, int id){
    Point newPoint;
    newPoint.x = x;
    newPoint.y = y;
    newPoint.id = id;
    return newPoint;
}

// Line class
struct Line {
    Point head;
    Point tail;

    // Given a y value, return the X value that this line intersects
    double getX(double y) const {
        return (head.x) +
            (tail.x - head.x) *
            (y - head.y) /
            (tail.y - head.y);
    }

    // Returns the gradient of the line
    double getGradient() const {
        return (tail.y - head.y) / (tail.x - head.x);
    }

};

// Public constructor of Line.
// We make sure that Point a will always be above Point b
// When we make the line, we will push the events into the PQ as well.
// However, we will not do it in this function.
Line line (Point a, Point b){
    Line newLine;
    newLine.head = a;
    newLine.tail = b;
    return newLine;
}

/* DATA STRUCTURES */

// First an array of Lines
Line lineArray[100005];

// We also need a BBST of Line Segments
std::set<Line> lineTree;

int main(){
    int n;
    for (int i = 0; i < n; ++i){
        double headx, heady, tailx, taily;
        scanf ("%lf %lf %lf %lf", &headx, &heady, &tailx, &taily);


    }
}
