//
//  Node.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#include "Node.h"

uint16_t Node::nextID = 0;

Node::Node(float newX, float newY):
x(newX), y(newY)
{
    id_num = ++nextID;
}


std::ostream& operator<<(std::ostream& os, const Node& node)
{
    os << node.id_num << "," << node.x << "," << node.y;
    return os;
}