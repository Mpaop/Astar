#ifndef NODE
#define NODE

#include<iostream>
//#include "SmartPtr.h"

class Point
{
public: 
    int X, Y;
    Point() : X(0), Y(0){}
    Point(int x, int y) : X(x), Y(y){}
    bool operator==(const Point &p) const { return this->X == p.X && this->Y == p.Y; }
};

class Node
{
private:
    Point _point;
    unsigned _estimatedCost, _actualCost;
    Node *_previousNode;
    Node(){};

public:
    Node(int x, int y, unsigned esti, unsigned actu) : _point(x, y), _estimatedCost(esti), _actualCost(actu), _previousNode(nullptr){};
    Node(const Node &n) : _point(n.GetPoint().X, n.GetPoint().Y), _estimatedCost(n._estimatedCost), _actualCost(n._actualCost), _previousNode(n.GetPreviousNode()){};
    Node(int x, int y, Node *current, const Node &goal) : _point(x, y)
    {
        int estX = goal.GetPoint().X - x;
        int estY = goal.GetPoint().Y - y;
        _estimatedCost = estX * estX + estY * estY;

        if(current->GetPreviousNode()) _actualCost = current->GetPreviousNode()->_actualCost + 1;
        else _actualCost = 0;
        _previousNode = &(*current);
    };

    ~Node(){ _previousNode = nullptr; std::cout << "Destroy" << std::endl;};//std::cout << _point.X << " " << _point.Y << std::endl; std::cout << "Destroy" << std::endl;}
    inline unsigned GetScore(){ return _estimatedCost + _actualCost; }
    inline Point GetPoint() const {return _point;}
    inline Node *GetPreviousNode() const {return _previousNode;}
};

#endif