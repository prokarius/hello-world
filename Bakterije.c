#include<stdio.h>
#define MIN(x,y) (x)<(y)?(x):(y)

// Encapsulates a linear mod equation.
// It requires that a and b are within a 128 bit int.
// Also, a has to be positive, and b has to be less than a
// Exception is when a = 0, then the equation is just y = x
// Because the constructor function has no logic, we need to ensure the above
// properties are upheld during the creation of the equation.
// The equation that this class encapsulates is:
// y = ax + b
typedef struct{
    __int128 a;
    __int128 b;
} Equation;


// Define the global variables for the problem.
Equation equationList[5][5]; // This is an array of the equations.
                             // Bacteria i can have up to 4 equations.
int numequation [5]; // And this will store the number of equations each bacteria has
int dr[5] = {0,1,0,-1,0}; // This will be a speedy hack to simulate bacteria movement

// OK I can't really think of a proper way to find the best possible...
// Could have done some iterative solution thing, but meh...
// Tbh I'm doing this too much of an OOP way...
// I blame the OOP modules.
// Hence set up a ghettoList with ghettoPush function.
__int128 ans[300];
int anshead = 0;

// To push into the answer list.
// This is a ghettoPush function.
void anspush(__int128 newAns){
    ans[anshead++] = newAns;
}

// Returns the best answer from the list of answer array.
// Note that answer array has type __int128. Because GCC cannot print __int128s
// we need to do some bitwise stuff and cast the output into a long long.
// The output can then be fed into a printf function.
long long bestans(){
    __int128 best = ans[0];
    for (int i=1; i<anshead; ++i){
        best = MIN (best, ans[i]);
    }
    return (long long) (best & 0x7FFFFFFFFFFFFFFFLL);
}

// Returns the GCD of two int128 numbers
// Precondition is a or b has to not be 0.
// We will handle that case seperately.
__int128 gcd(__int128 a, __int128 b){
    while (b){
        __int128 temp = a%b;
        a = b;
        b = temp;
    }
    return a;
}

// Defines the global variables needed for the Extended Euclidean Algo
__int128 Extendedx, Extendedy, Extendedd;

void ExtendedEuclid(__int128 a, __int128 b){
    if (b == 0){
        Extendedx = 1;
        Extendedy = 0;
        Extendedd = a;
        return;
    }
    ExtendedEuclid (b, a%b);
    __int128 x1 = Extendedy;
    __int128 y1 = Extendedx - (a/b) * Extendedy;
    Extendedx = x1;
    Extendedy = y1;
}

// Tries to find a y that satisfies both equations
// Then takes that y, sets it as the constant
// This will return a new equation.
Equation diophantine(Equation first, Equation second){
    __int128 newa, newb;
    __int128 gcdab = 1; // To store the gcd, if it exists
    // Check if we are doing the first case:
    if (first.a == -1 && first.b == -1){
        return second;
    }

    // We want to find the new a. There are two cases:
    // If either of the two is zero, then the new a would be zero too:
    if ((first.a == 0) | (second.a == 0)){
        newa = 0;
    }

    // Else we want to find the new a. That is just lcm of (first.a, second.a)
    // Note that gcdab will be defined no matter if we come in this function or not
    else {
        __int128 gcdab = gcd(first.a, second.a);
        newa = (first.a / gcdab) * second.a;
    }

    // Now we want to find the new b. There are three cases:
    // If both of first.a and second.a is 0, then we just need to check if
    // first.b and second.b is the same. Return b = -1 if they are not.
    if ((first.a == 0) & (second.a == 0)){
        if (first.b == second.b){
            newb = first.b;
        }
        else {
            newa = -1;
        }
    }

    // Case 2: If first.a == 0 XOR second.a == 0
    // Then we have to check if the the other equation fits the b of the first.
    // i.e. is there a solution to first.b = second.a * m + second.b
    // (Because I suck at this, Im splitting this into 2 more cases)
    // So we'll handle when first.a == 0 vs second.a == 0 differently.
    else if (first.a == 0){
        __int128 difference = first.b - second.b;
        if (difference % second.a == 0){
            // Yes it's still possible
            newb = first.b;
        }
        else {
            newa = -1;
        }
    }

    else if (second.a == 0){
        __int128 difference = second.b - first.b;
        if (difference % first.a == 0){
            // Yes it's still possible
            newb = second.b;
        }
        else {
            newa = -1;
        }
    }

    // Last case is when the two are not equal to zero.
    // We will use Chinese Remainder Theorem. Why?
    // y = ax + b can be written as y = b (mod a)
    // Then if we have two equations:
    // y1 = b1 (mod a1)
    // y2 = b2 (mod a2)
    // Then we can use CRT to solve the simultaeous equations.
    // a1x + b1 = a2x' + b2 => Cx + Dx' = E
    else {
        __int128 b1, b2, C, D, E;
        b1 = first.b;
        b2 = second.b;
        C = first.a;
        D = -second.a;
        E = b2-b1;

        // Check if this equation is solveable at all.
        if (E % gcdab == 0){
            newa = -1;
        }

        // If the above works, then we just gotta do Extended Euclidean
        else {
            ExtendedEuclid(C, D);
            // TODO
        }
    }

    // Now that everything is over, we can return the nextEquation!
    Equation nextEquation;
    nextEquation.a = newa;
    nextEquation.b = newb;
    return nextEquation;
}

// This method is the final method that we call.
// This will recursively solve the linear diophantine eqns.
// Input would be the total number of bacteria, current bacteria number
// As well as the previous equation generated from the recursion
void recursiveSolve(int currbacteria, int numbacteria, Equation prev){
    // If we have reached the end of the list, we push!
    if (currbacteria == numbacteria){
        anspush(prev.b);
    }

    // Else we recurse
    for (int i=0; i<numequation[currbacteria]; ++i){
        Equation nextEqn = diophantine(prev, equationList[currbacteria][i]);

        // But here's the thing: It can be the case that the equations are
        // unsolvable. Hence we need to set a flag in our equation should that
        // happen. The easiest way is to set a to be negative.
        if (nextEqn.b == -1){
            return;
        }
        recursiveSolve(currbacteria + 1, numbacteria, nextEqn);
    }
}

int main(){
    char ph;
    int r, c; // Stores row and column data
    int b; // Number of bacteria
    int array[51][51]; // Stores the grid that the bacteria is on
    int trap[2]; // Stores the position of the trap
    int pos[3]; // Stores the position of the current bacteria. Index 3 accounts for direction
    int state[4]; // Stores the state of the trap cells.

    // Scan in the data.
    scanf("%d %d %d", &r, &c, &b);
    scanf("%d %d", &trap[0], &trap[1]);

    // For each bacteria,
    for (int i=0; i<b; ++i){

        // Reset the state array
        for (int j=0; j<4; ++j){
            state[j] = -1;
        }

        // Scan in its position
        // Remember to subtract 1 because ones based indexing.
        // pos[0] stores the row number
        // pos[1] stores the col number
        // pos[2] stores the direction he is facing
        scanf("%d %d", &pos[0], &pos[1]);
        --pos[0];
        --pos[1];

        // As well as his original direction;
        // We want to convert his original direction into a number.
        // This represents the number of quarter turns right from facing up.
        // This allows us to do some simple integer addition later while
        // simulating.
        scanf(" %c", &ph);
        if (ph == 'R') pos[2] = 1;
        else if (ph == 'D') pos[2] = 2;
        else if (ph == 'L') pos[2] = 3;
        else if (ph == 'U') pos[2] = 0;

        // Also, scan in the grid that it will be following.
        for (int j=0; j<r; ++j){
            for (int k=0; k<c; ++k){
                scanf(" %c", &ph);
                array[j][k] = ph - '0';
            }
        }

        // Now we simulate the movement of the bacteria.
        int t = 0;
        while (t < 20500){

            // Check if the bacteria has touched the trap.
            // If it has not, we just continue the loop. But if it has
            // then we need to do some processing.
            // This will also be the time
            if (pos[0] == trap[0] && pos[1] == trap[1]){

                // Check to see if we have touched the current cell before
                if (state[pos[2]] != -1){
                    // Check if we are looping twice. This is when constant is -2.
                    // If we are, break out of the loop.
                    if (state[pos[2]] == -2){
                        break;
                    }

                    // Yes we have seen this before at time t0.
                    // Store the equation given (t0 - t)x + t0;
                    Equation newEqn;
                    newEqn.b = state[pos[2]];
                    newEqn.a = t - state[pos[2]];
                    equationList[i][numequation[i]] = newEqn;
                    ++numequation[i];

                    // Then set constant to be equal to -2 to mark that we have
                    // been here before
                    state[pos[2]] = -2;
                }

                // No this is our fist time touching this cell
                else {
                    // Therefore save the value:
                    state[pos[2]] = t;
                }
            }

            // Read the number it is on, and move to the next
            pos[2] = (pos[2] + array[pos[0]][pos[1]])%4;
            pos[0] += dr[pos[2]];
            pos[1] += dr[pos[2]+1];

            // Check if we are out of the range
            // If we are, make the bacteria kebelakang pusing
            if (pos[0] < 0 || pos[0] >= r || pos[1] < 0 || pos[1] >= c){
                pos[2] = (pos[2] + 2)%2;

                // Then handle the respective out of bounds cases:
                // Make the bacteria go back into the play area.
                if (pos[0] < 0){
                    pos[0] += 2;
                }
                else if (pos[1] < 0){
                    pos[1] += 2;
                }
                else if (pos[0] >= r){
                    pos[0] -= 2;
                }
                else if (pos[1] >= c){
                    pos[1] -= 2;
                }
            }

        // At the end of the loop, don't forget to add 1 to t.
        ++t;
        }

        // Check if the bacteria ever touched the trap once and never again
        for (int j=0; j<4; ++j){
            if (state[j] >= 0){
                Equation newEqn;
                newEqn.a = 0;
                newEqn.b = state[j];
                equationList[i][numequation[i]] = newEqn;
                ++numequation[i];
            }
        }

        // Now, for each bacteria, we need to know whether they touched the trap
        // at all. The easiest way to do that is to check the number of
        // equations we have pushed. If there are no equations:
        if (numequation[i] == 0){
            // This means that we didn't even touch the trap
            printf("-1");
            return 0;
        }

        // Phew and we are done for 1 bacteria. Now we move on to the next guy.
    }

    // Right, so we are done with all the bacteria.
    // If we are here that means the bacteria all have touched the trap in some
    // way, at some point of time. Because we don't know K, we should
    // recursively solve the equations:
    Equation placeholder = {-1,-1};
    recursiveSolve(0, b, placeholder);

    printf ("%lld\n", bestans());

    return 0;
}
