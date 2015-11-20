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
	Link(uint16_t newId, Node *newN1, Node *newN2);
	bool ConnectedTo(Node *theNode);
	bool ConnectedTo(uint16_t nodeId);
    Node* GetOtherNode(Node *theNode);
    void GetNodes(Node* &node1, Node* &node2);
	float Cost(){return cost;}
	friend bool operator==(const Link& l1, const Link& l2);
	friend std::ostream& operator<<(std::ostream& os, const Link& link);
};


#endif /* defined(__proj2__Link__) */
