#include<stdio.h>
#include<math.h>

void mos(){
    int i, j, k, m, maax = -1;
    double bowl, pos[35][2];
    scanf ("%d %lf", &m, &bowl);
    bowl /= 2;
    double bb = (bowl + 0.000004)*(bowl + 0.000004);
    for (i=0; i<m; i++){scanf ("%lf %lf", &pos[i][0], &pos[i][1]);}

    // Find the two intersection points
    for (i=0; i<m-1; i++){
        for (j=i+1; j<m; j++){
            // Check if there are intersections

            //x3 = x2 +- h ( y1 - y0 ) / d
            //y3 = y2 -+ h (x1 - x0 ) / d
            double x0 = pos[i][0], x1 = pos[j][0];
            double y0 = pos[i][1], y1 = pos[j][1];
            double x = x1 - x0;
            double y = y1 - y0;
            double d = sqrt(x*x + y*y)/2;
            if (d > bowl+0.000005) continue;

            double h = sqrt(bowl*bowl - d*d);

            double x2 = (x0 + x1)/2;
            double y2 = (y0 + y1)/2;
            double in01 = x2 + h*y/(2*d), in11 = x2 - h*y/(2*d);
            double in00 = y2 - h*x/(2*d), in10 = y2 + h*x/(2*d);


            int o = 0;
            // We have the points.
            for (k=0; k<m; k++){
                double xm = (pos[k][1] - in00);
                double ym = (pos[k][0] - in01);
                if (xm*xm + ym*ym < bb) ++o;
            }
            if (o > maax) maax = o;

            o = 0;
            for (k=0; k<m; k++){
                double xm = (pos[k][1] - in10);
                double ym = (pos[k][0] - in11);
                if (xm*xm + ym*ym < bb) ++o;
            }
            if (o > maax) maax = o;
        }
    }
    if (maax == -1) printf ("1\n");
    else printf ("%d\n", maax);
}

int main(){
    int n;
    scanf ("%d", &n);
    while (n--){
        mos();
    }
    return 0;
}
