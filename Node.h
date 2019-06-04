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
    Node(const Node &n) : _point(n.GetPoint().X, n.GetPoint().Y), _estimatedCost(n._estimatedCost), _actualCost(n._actualCost), _previousNode(n.GetPreviousNode()){};
    Node(const int &x, const int &y, Node *const current, const Node *const goal) : _point(x, y)
    {
        if (goal)
        {
            int estX = goal->GetPoint().X - x;
            int estY = goal->GetPoint().Y - y;
            _estimatedCost = estX * estX + estY * estY;
        }
        else
        {
            _estimatedCost = 0;
        }
        
        if (current)
        {
            _actualCost = current->_actualCost + 1;
            _previousNode = current;
        }
        else{
            _actualCost = 0;
            _previousNode = nullptr;
        }
    };

    ~Node(){ _previousNode = nullptr;};
    inline unsigned GetScore(){ return _estimatedCost + _actualCost; }
    inline Point GetPoint() const {return _point;}
    inline Node *GetPreviousNode() const {return _previousNode;}
};

#endif