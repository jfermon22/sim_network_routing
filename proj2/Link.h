//
//  Link.h
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#ifndef __proj2__Link__
#define __proj2__Link__

#include "Node.h"
#include <cmath>
#include <iomanip>

class Link {
	uint16_t id_num;
	Node* node1;
	Node* node2;
	float distance;
	float cost;
public:
	Link(uint16_t newId, Node *newN1, Node *newN2):
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
	float Cost(){return cost;}
	
	friend bool operator==(const Link& l1, const Link& l2)
	{
		return ( (l1.node1 == l2.node1 && l1.node2 == l2.node2) ||
				 (l1.node1 == l2.node2 && l1.node2 == l2.node1) );
	}

	friend std::ostream& operator<<(std::ostream& os, const Link& link){
		os  << std::left 
			<< std::setw(3)<< link.id_num 
			<< *link.node1 << " -> " 
			<< *link.node2 << "   " 
			<< std::setw(7) << link.distance << ", " 
			<< std::setw(7) << link.cost;
		return os;
	}
};


#endif /* defined(__proj2__Link__) */
