#ifdef _WIN32
#include <windows.h>
#endif
#include <random>

#include <iostream>
#include <vector>

#include "fogpi/Math.hpp"

int main(int argc, char* argv[])
{
    int Closest = 0;
    int ClosestDistance = 1000000;
    int Farthest = 0;
    int FarthestDistance = 0;
    int Distance;
    int DistanceAverage;
    int Quadrant1;
    int Quadrant2;
    int Quadrant3;
    int Quadrant4;

    //Vector2D v(5.0f);

    //Vector2D v1(2.0f,10.0f);

    //v+=v1;
    //v-=v1;

    //std:: cout << v.x << " " << v.y << std::endl; 
    
    std:: vector<Vector2D> points = {};

    for (int i = 0; i < 1000; i++){
    int x = (rand() % 502)-1;
    int y = (rand() % 502)-1;
    int m = rand() % 3;
    int n = rand() % 3;
    if (m==0){
        x*=-1;
    }
    if (n==1){
        y*=-1;
    }
    if (x<0 && y<0){
        Quadrant3++;
    }
    if (x<0 && y>0){
        Quadrant4++;
    }
    if (x>0 && y<0){
        Quadrant2++;
    }
    if (x>0 && y>0){
        Quadrant1++;
    }
    // Add
    points.push_back(Vector2D(x,y));
    }
    

    for (int i;i<1000;i++){
        Distance+=Distance2D(points[i],(0,0));
        if (Distance2D(points[i],(0,0))<ClosestDistance){
            Closest = i;
            ClosestDistance = Distance2D(points[i],(0,0));
        }
        if (Distance2D(points[i],(0,0))>FarthestDistance){
            Farthest = i;
            FarthestDistance = Distance2D(points[i],(0,0));
        }
    }
    DistanceAverage=Distance/1000;
    std:: cout <<"Size: " << points.size() << std::endl;
    std:: cout <<"Closest to (0,0): " << std::endl;
    Print(points[Closest]);
    std:: cout <<"farthest from (0,0): " << std::endl;
    Print(points[Farthest]);
    std:: cout <<"Average distance: " << DistanceAverage << std::endl;
    if (Quadrant1 > Quadrant2 && Quadrant1 > Quadrant3 && Quadrant1 > Quadrant4){
        std:: cout<<"Quadrant with most points: Quadrant1 (+x,+y)"<< std::endl;
    }
    if (Quadrant2 > Quadrant1 && Quadrant2 > Quadrant3 && Quadrant2 > Quadrant4){
        std:: cout<<"Quadrant with most points: Quadrant2 (+x,-y)"<< std::endl;
    }
    if (Quadrant3 > Quadrant1 && Quadrant3 > Quadrant2 && Quadrant3 > Quadrant4){
        std:: cout<<"Quadrant with most points: Quadrant3 (-x,-y)"<< std::endl;
    }
    if (Quadrant4 > Quadrant1 && Quadrant4 > Quadrant3 && Quadrant4 > Quadrant2){
        std:: cout<<"Quadrant with most points: Quadrant4 (-x,+y)"<< std::endl;
    }
    return 0;
}