# include <stdio.h>

# define min(a, b) ((a) < (b) ? (a) : (b))
# define max(a, b) ((a) > (b) ? (a) : (b))

struct point {
    int x;
    int y;
};

struct rectangle {
    struct point p1;
    struct point p2;
};

/* makepoint: crea un punto con las componentes x e y */

struct point makepoint(int x, int y) {
    struct point punto_out;

    punto_out.x = x;
    punto_out.y = y;
    return punto_out;
}

int ptinrect(struct point pt, struct rectangle rect) {
    return pt.x >= rect.p1.x && pt.x < rect.p2.x && pt.y >= rect.p1.y && pt.y < rect.p2.y;
}

struct rectangle canonrect(struct rectangle rect) {

    struct rectangle temp;

    temp.p1.x = min(rect.p1.x, rect.p2.x);
    temp.p1.y = min(rect.p1.y, rect.p2.y);
    temp.p2.x = max(rect.p1.x, rect.p2.x);
    temp.p2.y = max(rect.p1.y, rect.p2.y);
    return temp;
}

int main() {
    struct rectangle screen;
    struct point middle;
    struct point origin, *pp;

    pp = &origin;

    printf("el origen es (%d, %d)\n", (*pp).x, (*pp).y);
    
    screen.p1 = makepoint(0,0);
    screen.p2 = makepoint(100, 100);
    middle = makepoint((screen.p1.x + screen.p2.x)/2, (screen.p1.y + screen.p2.y)/2);

    return 0;
}