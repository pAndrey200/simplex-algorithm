#include "simplex.h"

int main()
{

    std::vector <std::vector<float> > vec2D{    
               { 2,  1,  1, 1, 0, 0},
               { 1,  3,  2, 0, 1, 0},
               { 2,  1,  2, 0, 0, 1}};

    std::vector<float> b{180,300,240};
    std::vector<float> c{-6,-5,-4,0,0,0};


    Simplex simplex(vec2D,b,c);
    simplex.CalculateSimplex();


    return 0;
}