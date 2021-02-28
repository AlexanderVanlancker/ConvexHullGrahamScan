#include <functional>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Point.h"
#include <stack>
#include <SFML/Graphics.hpp>
#include "GrahamScanAlgorithm.h"
using namespace std;

int nrPoints(1000);
int screenW(800); //window size
int screenH(800);
int margin=100; //avoid that random coordinates are rendered too close to the window border
int minX(margin);
int maxX(screenW-margin);
int minY(margin);
int maxY(screenH-margin);

//forward declarations
void drawOnScreen(vector<Point>&, vector<Point>&);

//to add test what happens if two elements with same Y coordinate? Look at the X value.
int main() {
    GrahamScanAlgorithm algo;

    vector<Point> points(Point::fillVectorRandom(nrPoints, minX, maxX, minY, maxY));

    vector<Point> hull = algo.findConvexHull(points);
    for( Point p : hull){
        cout << p;
    }
    cout << "hull calculated" << endl;
    drawOnScreen(points,hull);

    return 0;
}


sf::CircleShape toSf(Point& p, int radius){
    sf::CircleShape shape(radius);
    shape.setFillColor(sf::Color::Black);
    shape.setOrigin(radius,radius); //this is needed to make sure that the circle is positioned on its center
    shape.setPosition(p.x,screenH-p.y); //to do: transform needed of Y-coordinate?                             
    return shape;
}


//data should have the point with minimum Y-coordinate as first element
void drawOnScreen(vector<Point>& data, vector<Point>& hullPoints){
    vector<sf::CircleShape> cirkels(data.size());
    
    //transform all data points into a vector of drawable circles
    int radius=2;        
    std::transform(data.begin(),data.end(), back_inserter(cirkels), [radius](Point& p){return toSf(p,radius);});   

    //prepare drawing of convex hull edges in blue
    sf::ConvexShape convex;
    convex.setPointCount(hullPoints.size());
    convex.setOutlineThickness(1);
    convex.setOutlineColor(sf::Color::Blue);    
    for(int i = 0; i < hullPoints.size(); i++){        
        convex.setPoint(i,sf::Vector2f(hullPoints[i].x, screenH-hullPoints[i].y));                
    }

    //prepare drawing of convex hull vertices in red
    vector<sf::CircleShape> hull;
    hull.reserve(hullPoints.size());
    for(auto hullpoint : hullPoints){            
        sf::CircleShape vertex = toSf(hullpoint,radius);
        vertex.setFillColor(sf::Color::Red);                
        hull.push_back(vertex);        
    }

    sf::RenderWindow window(sf::VideoMode(screenW,screenH), "Convex Hull");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        //draw hull
        window.draw(convex);

        //draw points
        for (auto cirkel: cirkels)
            window.draw(cirkel);     

        //draw vertices of convex hull in red
        for (auto vertex : hull)
            window.draw(vertex);
            
        //draw starting point of convex hull in green
        sf::CircleShape minP = toSf(*data.begin(),radius);
        minP.setFillColor(sf::Color::Green);
        window.draw(minP); 
        window.display();
            
    }   
}


