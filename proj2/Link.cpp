//
//  Link.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#include "Link.h"


Link::Link(uint16_t newId, Node *newN1, Node *newN2):
	id_num(newId),node1(newN1),node2(newN2)
{
	if (node1->Id_num() > node2->Id_num())
	{
		node1 = newN2;
		node2 = newN1;
	}
	
	distance = node1->GetDistance(node2);
	cost = ( distance >= 1 ) ? pow(distance,2) : 1;
}

bool Link::ConnectedTo(Node *theNode){
	return ConnectedTo(theNode->Id_num());
}

bool Link::ConnectedTo(uint16_t nodeId){
	return (nodeId == node1->Id_num() || nodeId == node2->Id_num());
}

Node* Link::GetOtherNode(Node *theNode){
	Node* returnNode = NULL;
	if (theNode == node1)
		returnNode = node2;
	else
		returnNode = node1;
	return returnNode;
}

bool operator==(const Link& l1, const Link& l2)
{
	return ( (l1.node1 == l2.node1 && l1.node2 == l2.node2) ||
			 (l1.node1 == l2.node2 && l1.node2 == l2.node1) );
}

std::ostream& operator<<(std::ostream& os, const Link& link){
	os  << std::left 
		<< std::setw(3)<< link.id_num 
		<< *link.node1 << " -> " 
		<< *link.node2 << "   " 
		<< std::setw(7) << link.distance << ", " 
		<< std::setw(7) << link.cost;
	return os;
}
