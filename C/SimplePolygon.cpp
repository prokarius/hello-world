// This code is wrong. Like there are some cases where it doesn't work.
// Looking at you TestCase 319 >:(

#include<cstdio>
#include<queue>
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

    bool operator <(const Point& other) const {
        if (abs(this->x - other.x) > EPSILON){
            return this->x < other.x;
        }
        else if (abs (this-> y - other.y) > EPSILON){
            return this->y < other.y;
        }
        return false;
    }

    bool operator ==(const Point& other) const {
        return abs(this->x - other.x) < EPSILON && abs(this->y - other.y) < EPSILON;
    }

    bool operator !=(const Point& other) const {
        return !(*this == other);
    }
};

// Public constructor, but it's in small letters because Im doing this java style
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

    double getY(double x) const {
        return (head.y) +
            (tail.y - head.y) *
            (x - head.x) /
            (tail.x - head.x + EPSILON);
    }

    double getGradient() const {
        if (abs(tail.x - head.x) > EPSILON){
            return (tail.y - head.y) / (tail.x - head.x);
        }
        return 1e12;
    }

    // This is used to compare where the lines would go.
    // Note that this will only be used when pushing a line in, so no matter what
    // other is, the y value we want to compare is always at the rightmost x value
    bool operator <(const Line& other) const {
        // Check for the Y intersection
        double x = std::min(this->tail.x, other.tail.x);
        double deltaY = this->getY(x) - other.getY(x);
        if (abs(deltaY) > EPSILON) return deltaY < 0;

        // Check for gradient
        double gradientDiff = this->getGradient() - other.getGradient();
        if (abs(gradientDiff) > EPSILON) {
            return gradientDiff > EPSILON;
        }

        // Check to see which tail is later
        if (this->tail != other.tail) {
            return this->tail < other.tail;
        }

        // Check to see which head is later
        return this->head < other.head;
    }
};

// OK time to make all the Data Structures we need
// First, an array of points
Point pointArray[40002];

// This will store all the events.
std::priority_queue<Point> eventPQ;

// And also make a BBST of Line Segments
// And a set of Points to check for duplicates
std::set<Line> lineTree;
std::set<Point> pointSet;

// Public constructor for the line class
// It will always be the case that a is before b.
// When we make the line, we will push the event into the PQ as well
Line line(Point a, Point b){
    Line newLine;
    newLine.head = a;
    newLine.tail = b;
    return newLine;
}

// This next chunk of code is ripped of straza.c, which was ripped off geekforgeeks

bool onSegment(Point p, Point q, Point r)
{
    if ((q.x < std::max(p.x, r.x) && q.x > std::min(p.x, r.x)) ||
        (q.y < std::max(p.y, r.y) && q.y > std::min(p.y, r.y)))
       return true;
    return false;
}

// Returns the orientation of the 3 given points
// 0 is collinear
// 1 is clockwise
// 2 is counterclockwise
int orientation(Point a, Point b, Point c){
    double cross = (b.y - a.y)*(c.x - b.x) - (b.x - a.x)*(c.y - b.y);
    if (abs(cross) > EPSILON){
        return (cross > 0) ? 1 : 2;
    }
    return 0;
}

// Given two line segments that are guaranteed to intersect, finds the
// intersection point of them and returns it as a double
// Ripped off Wikipedia
Point findPoint(Line one, Line two){
    Point output;
    double x1 = one.head.x;
    double y1 = one.head.y;
    double x2 = one.tail.x;
    double y2 = one.tail.y;
    double x3 = two.head.x;
    double y3 = two.head.y;
    double x4 = two.tail.x;
    double y4 = two.tail.y;

    double xtop = ((x1*y2) - (y1*x2))*(x3 - x4) - (x1 - x2)*((x3*y4) - (y3*x4));
    double ytop = ((x1*y2) - (y1*x2))*(y3 - y4) - (y1 - y2)*((x3*y4) - (y3*x4));
    double bottom = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);

    output.x = xtop/bottom;
    output.y = ytop/bottom;

    return output;
}


// Returns if the trenches intersect each other
int intersect(Line a, Line b){
    int o1 = orientation(a.head, a.tail, b.head);
    int o2 = orientation(a.head, a.tail, b.tail);
    int o3 = orientation(b.head, b.tail, a.head);
    int o4 = orientation(b.head, b.tail, a.tail);

    if (o1 != o2 && o3 != o4){
        // Yes they intersect! Now, lets find where they intersect and see if it
        // lies within the line segment.
        Point output = findPoint(a, b);
        if ((output.x - a.head.x > EPSILON && a.tail.x - output.x > EPSILON) ||
            (output.y - a.head.y > EPSILON && a.tail.y - output.y > EPSILON) ||
            (output.x - b.head.x > EPSILON && b.tail.x - output.x > EPSILON) ||
            (output.y - b.head.y > EPSILON && b.tail.y - output.y > EPSILON)) {
            return 1;
        }
        else {
            return 0;
        }
    }

    // These are the collinear checks
    if (o1 == 0 && onSegment(a.head, b.head, a.tail)) return 1;
    if (o2 == 0 && onSegment(a.head, b.tail, a.tail)) return 1;
    if (o3 == 0 && onSegment(b.head, a.head, b.tail)) return 1;
    if (o4 == 0 && onSegment(b.head, a.tail, b.tail)) return 1;

    return 0;
}

// Add a new Line into the HeaPQ and see if there is an intersection
int addLine (Line newLine){
    // This gives an iterator pointing to the newLine in the tree
    // Using next and prev, I can get the previous and next elements of the tree
    auto it = lineTree.insert(newLine).first;
    auto prevLine = std::prev(it);
    auto nextLine = std::next(it);
    int output = 0;

    // We need to check if the current line intersects with the previous line
    // But only if it return a valid Line Segment
    if (it != lineTree.begin()){
        output = intersect(newLine, *prevLine);
        if (output) return 1;
    }
    if (nextLine != lineTree.end()){
        output = intersect(newLine, *nextLine);
    }
    return output;
}

// Find the line in the tree and deletes it
void deleteLine(Line newLine){
    lineTree.erase(newLine);
}

// The main meat of the function. Processes the point that we took out of the PQ
int process(Point currPoint){
    // Gets the id of the point, and the prev and next points
    int id = currPoint.id;
    Point prevPoint = pointArray[id-1];
    Point nextPoint = pointArray[id+1];
    int output = 0;

    // We have to see if the line segment corresponds to a delete or add event.
    // If the current point is farther left than the previous point, it's add event.
    if (prevPoint < currPoint){
        Line prevLine = line(prevPoint, currPoint);
        output = addLine(prevLine);
    }
    else {
        Line prevLine = line(currPoint, prevPoint);
        deleteLine(prevLine);
    }

    // Cursory check on the output:
    if (output) return 1;

    if (nextPoint < currPoint){
        Line nextLine = line(nextPoint, currPoint);
        output = addLine(nextLine);
    }
    else {
        Line nextLine = line(currPoint, nextPoint);
        deleteLine(nextLine);
    }

    return output;
}

// The solution.run() method!
void testcase(int numpoints){
    // Scan in each point and push it into the PQ.
    for (int i = 1; i <= numpoints; ++i){
        int newx, newy;
        scanf("%d %d", &newy, &newx);
        Point newPoint = point(newx, newy, i);
        pointArray[i] = newPoint;
        eventPQ.push(newPoint);
        pointSet.insert(newPoint);
    }

    // Cursory check to see if there are points which are unique
    if ((int) pointSet.size() < numpoints){
        printf("NO\n");
        return;
    }

    // Also, just to make it easy to create lines:
    pointArray[numpoints+1] = pointArray[1];
    pointArray[0] = pointArray[numpoints];

    // Now that we have all the points in the pq, start processing them!
    while (!eventPQ.empty()){
        Point nextPoint = eventPQ.top();
        eventPQ.pop();
        int stats = process(nextPoint);

        // Some bad shit happened. It's not a simple polygon.
        if (stats == 1){
            printf("NO\n");
            return;
        }
    }

    // If we reached here, we have went through the entire polygon and not found
    // intersections. It is a YES
    printf("YES\n");
    return;
}

// Keep looping until we run out of test cases
// Remember to clear the tree and the eventPQ before each run
int main(){
    int n;
    scanf("%d", &n);
    while (n){
        eventPQ = std::priority_queue<Point>();
        lineTree.clear();
        pointSet.clear();
        testcase(n);
        scanf("%d", &n);
    }
    return 0;
}
