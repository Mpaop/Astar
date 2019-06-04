#include <iostream>
#include <vector>
#include <algorithm>
#include "Node.h"

using std::cout;
using std::endl;
using std::vector;

enum eMapNode{
    Open, Close, Start, Goal, Wall, Floor, MAX
};

enum eDirection{
    Right, Down, Left, Up, DirMAX
};

//隣接するノードの座標を取得する
Point GetAdjacentNodeIndex(const Point &point, const int &dir)
{
    switch (dir)
    {
    case Right:
        return Point(point.X + 1, point.Y);
    case Down:
        return Point(point.X, point.Y + 1);
    case Left:
        return Point(point.X - 1, point.Y);
    case Up:
        return Point(point.X, point.Y - 1);
    default:
        return Point();
    }
}

const int mapX = 5, mapY = 5;

//マップ
eMapNode Map[mapY][mapX] = 
{
    {Floor, Floor, Floor, Floor, Floor},
    {Floor, Floor, Wall, Floor, Wall},
    {Start, Floor, Wall, Floor, Floor},
    {Floor, Wall, Floor, Wall, Floor},
    {Floor, Wall, Goal, Floor, Floor},
};

char GetMapChip(eMapNode node){
    switch(node){
        case Open: return '*';
        case Close: return '=';
        case Start: return 'S';
        case Goal: return 'G';
        case Wall: return '@';
        case Floor: return '_';
        default: return ' ';
    }
}

int main(){
    cout << "Before AStar" << std::endl;
    for(auto &y : Map){
        for(auto &x : y) std::cout << GetMapChip(x);
        std::cout << std::endl;
    }

    cout << endl;

    //スタートとゴールのノード
    Node goal(2, 4, nullptr, nullptr);
    Node *start = new Node(0, 2, nullptr, &goal);
    Node *currentNode = start;

    vector<Node*> openNodes = {start};
    vector<Node*> closedNodes;

    while(!openNodes.empty())
    {
        //隣接するノードを取得
        for (size_t i = 0; i < eDirection::DirMAX; ++i)
        {
            auto pt = GetAdjacentNodeIndex(currentNode->GetPoint(), i);
            //マップ範囲外へのアクセスは禁止
            if (pt.X < 0 || pt.X >= mapX || pt.Y < 0 || pt.Y >= mapY) continue;
            
            //検索済みならスキップ
            if(std::find_if(closedNodes.begin(), closedNodes.end(), [pt](Node *n){return n->GetPoint() == pt;}) != closedNodes.end()) continue;

            //移動可能ならopenNodesに追加
            if (Map[pt.Y][pt.X] == eMapNode::Floor || Map[pt.Y][pt.X] == eMapNode::Goal) openNodes.push_back(new Node(pt.X, pt.Y, currentNode, &goal));
        }


        //検索済みのノードをクローズする
        closedNodes.push_back(currentNode);
        Map[currentNode->GetPoint().Y][currentNode->GetPoint().X] = eMapNode::Close;
        int idx;
        for (idx = 0; idx < openNodes.size(); ++idx) if(openNodes[idx]->GetPoint() == currentNode->GetPoint()) break;
        openNodes.erase(openNodes.begin() + idx);

        //最もコストの低いノードを検索
        if(!openNodes.empty())
        { 
            currentNode = openNodes[0];
            for(auto &n : openNodes) if(n->GetScore() < currentNode->GetScore()) currentNode = n;
        }

        //ゴールノードであるかを確認
        if(currentNode->GetPoint() == goal.GetPoint()) break;
    }

    //ゴールをGに変える
    Map[currentNode->GetPoint().Y][currentNode->GetPoint().X] = eMapNode::Goal;
    auto tempNode = currentNode->GetPreviousNode();

    //探索した経路を描画
    while(tempNode->GetPreviousNode()){
        Map[tempNode->GetPoint().Y][tempNode->GetPoint().X] = eMapNode::Open;
        //次のノードへ
        tempNode = tempNode->GetPreviousNode();
    }

    //スタートはSにする
    Map[tempNode->GetPoint().Y][tempNode->GetPoint().X] = eMapNode::Start;

    //マップの描画
    for(auto &y : Map){
        for(auto &x : y) std::cout << GetMapChip(x);
        std::cout << std::endl;
    }

    for(auto &n : openNodes) if(n != nullptr) delete n;
    for(auto &n : closedNodes) if(n != nullptr) delete n;
    openNodes.clear();
    closedNodes.clear();
    
    return 0;
}