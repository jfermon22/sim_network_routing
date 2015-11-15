//
//  Node.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#include "Node.h"

#include <iomanip>

uint16_t Node::nextID = 0;

Node::Node(float newX, float newY):
x(newX), y(newY)
{
    id_num = ++nextID;
}

float Node::GetDistance(Node* otherNode)
{
	float dist = pow((x - otherNode->X()),2) + pow((y - otherNode->Y()),2);
	return sqrt(dist);
}

std::ostream& operator<<(std::ostream& os, const Node& node)
{
    os  << std::left 
		<< std::setw(2) << node.id_num << " " 
		<< std::setw(5) << node.x << "," 
		<< std::setw(5) << node.y;
    return os;
}
