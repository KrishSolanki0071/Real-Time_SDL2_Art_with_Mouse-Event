#include "screen.h"
#include<numeric>
#include<cmath>
#undef main

//making a struct to make it look like the cube is rotating using 3rd vertex i.e 'z'
struct vec3
{   
    float x,y,z;
};

//making a function to connect all the points using the LINE function we made and to make the shape look like a 3D CUBE
struct connection
{
    int a,b;
};


void rotate(vec3& point, float x = 1, float y = 1, float z = 1)
{
    //define rotation
    float rad = 0;

    rad = x;
    point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
    point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

    rad = y;
    point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
    point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

    rad = z;
    point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
    point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;

}

void line(Screen& screen, float x1, float y1, float x2, float y2)
{
    float dx = x2 - x1;
    float dy = y2 - y1;

    //using pythagoras theorem to get the length of the line
    float length = std::sqrt(dx*dx + dy*dy);
    float angle = std::atan2(dy,dx); //will give the angle of the line

    for(float i = 0; i < length; i++)
    {
        screen.pixel(
                        x1 + std::cos(angle) * i,
                        y1 + std::sin(angle) * i
                    );  
    }

}

int main()
{

    Screen screen;


    //making a vector of VEC3 to deploy the cube points
    std::vector<vec3> points{
        {100,100,100},
        {200,100,100},
        {200,200,100},
        {100,200,100},

        {100,100,200},
        {200,100,200},
        {200,200,200},
        {100,200,200}

    };


    std::vector<connection> connections
    {
        {0,4},
        {1,5},
        {2,6},
        {3,7},

        {0,1},
        {1,2},
        {2,3},
        {3,0},

        {4,5},
        {5,6},
        {6,7},
        {7,4},
    };

    //CALCULCATE CENTROID
    vec3 c{0,0,0};
    for(auto& p : points)
    {
        c.x += p.x;
        c.y += p.y;
        c.z += p.z;
    }

    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();



    /*-------NOW WE WILL BE DEFINING OUR POINTS SO DON'T NEED THEM ANYMORE, IT WAS JUST FOR TESTING/INITIALIZING PURPOSES
    for(int i = 0; i < 100; i++)  //deploying 100 pixels on the screens randomly
    {
        screen.pixel(rand()%640, rand()%480);  //in this resolution 640X480p deploying pixels randomly using rand() function
    }

    // line(screen, 0, 0, 300, 300);
    line(screen, 100, 100, 200, 100);
    line(screen, 200, 100, 200, 200);
    line(screen, 200, 200, 100, 200);
    line(screen, 100, 200, 100, 100);
    */
    while(true)
    {
        for(auto& p : points) //displaying the rotation of the cube using the rotate function we made above
        {   
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;

            rotate(p, 0.02, 0.01, 0.04);

            p.x += c.x;
            p.y += c.y;
            p.z += c.z;

            screen.pixel(p.x,p.y);

        }

        for(auto& conn : connections)
        {
            line(screen, points[conn.a].x,
                         points[conn.a].y,
                         points[conn.b].x,
                         points[conn.b].y);
        }

        screen.show(); //displaying the pixels
        screen.clear(); //clearing the screen after displaying the same pixels again and again as they don't accumulate on the screen as if you don't then we will run out of RAM
        screen.input(); //what we are checking is if the user clicked the X button i.e close window  
        SDL_Delay(30);
    }
    return 0;
}