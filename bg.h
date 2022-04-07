#ifndef BG_H_INCLUDED
#define BG_H_INCLUDED

const double DEG2RAD = 3.1415926535897932384/180;

// Aspect ratio
double monW = 2560.0;
double monH = 1440.0;
float aspectRatio = monW / monH;

// Star positions
const int lim = 50;
float starx[lim];
int stary[lim];
float speed = 0.1;

// Street animation
float line[25];

// bg animation
const int nVLine = 2000 / 50;
float vLineT[nVLine];
float vLineD[nVLine];

void DrawEllipse(float, float, float, float, int);


template<typename T>
T getRand(T minRange, T maxRange)
{
    return minRange + (fmod(rand(), (maxRange - minRange + 1)));
}

void randomizeArray()
{
    for(int i = 0; i < lim; i++)
    {
        starx[i] = getRand<int>(0, 2000);
        stary[i] = getRand<int>(1000, 2000);
    }
}

void incrementLine()
{
    int inc = 0;
    for(int i = 0; i < 25; i++)
    {
        line[i] = inc;
//        lineo[i] = line[i];
        inc += 80;
    }
}

void decrementLine()
{
    vLineT[0] = 2000;
    vLineD[0] = 3000;

    for(int i = 1; i < nVLine; i++)
    {
        vLineT[i] = vLineT[i - 1] - 50;
        vLineD[i] = vLineD[i - 1] - 100;
    }

}

void drawBG()
{

    // Sky
    glBegin(GL_QUADS);
    glColor3ub(201, 62, 189);
    glVertex2i(0, 1040);
    glVertex2i(2000, 1040);
    glColor3ub(109, 63, 162);
    glVertex2i(2000, 1440);
    glVertex2i(0, 1440);

    glVertex2i(0, 1440);
    glVertex2i(2000, 1440);
    glColor3ub(31, 37, 87);
    glVertex2i(2000, 1840);
    glVertex2i(0, 1840);

    glVertex2i(0, 1840);
    glVertex2i(2000, 1840);
    glColor3ub(19, 14, 18);
    glVertex2i(2000, 2240);
    glVertex2i(0, 2240);
    glEnd();

    // Stars
    glPointSize(2);
    glBegin(GL_POINTS);
    glColor3f(1.0, 1.0, 1.0);
    int it = 0;
    while(1)
    {
        it++;
        if (it == lim) break;

        starx[it] -= speed;

        if(starx[it] < 0)
        {
            starx[it] = 2000;
        }

        glVertex2i(starx[it], stary[it]);
    }
    glEnd();

    // Sun
//    double theta;
//    double cenx = 1000;
//    double ceny = 900;
//    double radius = 500;
//    int col3 = 0;
//    int col2 = 255;
//
//    glBegin(GL_POLYGON);
//    for(int i = 0; i < 360; i++)
//    {
//        glColor3ub(253, col2, col3);
//        col2 == 0 ? col2 = 0 : col2 -= 1;
//        col3 == 255 ? col3 = 0 : col3 += 1;
//
//        theta = i * DEG2RAD;
//        glVertex2d(cenx + radius * cos(theta), ceny + radius * sin(theta));
//    }
//    glEnd();

//    glColor3ub(255, 0, 0);
    DrawEllipse(1000, 900, 300, 300*aspectRatio, 360);


    // Ground
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(0, 250);
    glVertex2f(2000, 250);
    glColor3ub(126, 58, 147);
    glVertex2f(2000, 1040);
    glVertex2f(0, 1040);
    glEnd();

    // Drawing the vertical lines
    int numOfLine = 0;
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(182, 29, 129);
    while(numOfLine < nVLine)
    {
        vLineT[numOfLine] -= speed * 2.0;
        vLineD[numOfLine] -= speed * 4.0;

        if(vLineT[numOfLine] < 0)
        {
            vLineT[numOfLine] = 2000;
            vLineD[numOfLine] = 3000;
        }

        glVertex2f(vLineT[numOfLine], 1040);
        glVertex2f(vLineD[numOfLine], 0);
        numOfLine++;
    }
    glEnd();


    // Drawing horizontal lines to the horizon
    float hLine = 0;
    float rate = 50;
    while(hLine < 790 )
    {
        glLineWidth(2);
        glBegin(GL_LINES);
        glColor3ub(182, 29, 129);
        glVertex2f(0, 250 + hLine);
        glVertex2f(2000, 250 + hLine);
        glEnd();

        hLine += rate;
        if(rate > 5)
            rate /= 1.05;
        else
            rate = 5;
    }

}

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;
    int col3 = 0;
    int col2 = 255;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        glColor3ub(253, col2, col3);
        col2 == 0 ? col2 = 0 : col2 -= 1;
        col3 == 255 ? col3 = 0 : col3 += 1;
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void drawStreet()
{
    // Covering the street
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2i(0,0);
    glVertex2i(2000, 0);
    glVertex2i(2000, 240);
    glVertex2i(0, 240);
    glEnd();

    // bullshit on the street
    float speedl = 5;
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3ub(182, 29, 129);
    for(int i = 0; i < 25; i++)
    {
        line[i] -= speedl;

        if(line[i] < 0)
        {
            line[i] = 2000;
        }

        glVertex2f(line[i], 250);
        glVertex2f(line[i], 0);

    }
    glEnd();
}

#endif // BG_H_INCLUDED
