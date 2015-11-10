//
//  Node.h
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#ifndef __proj2__Node__
#define __proj2__Node__

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <cmath>

class Node {
protected:
    static uint16_t nextID;
    uint16_t id_num;
    float x;
    float y;
public:
    Node(float newX, float newY);
	uint16_t Id_num(){return id_num;}
	float X(){return x;}
	float Y(){return y;}
	float GetDistance(Node* otherNode);
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};

struct FwdTableEntry{
	uint16_t dest_id;
	float cost;
	uint16_t next_hop_id;
	FwdTableEntry(uint16_t d_id):
		dest_id(d_id),cost(HUGE_VALF),next_hop_id((uint16_t)NAN){}
	friend std::ostream& operator<<(std::ostream& os, const FwdTableEntry& entry){
		os  << "(" << entry.dest_id << "," <<entry.cost << "," << entry.next_hop_id << ")" ;
		return os;
	}
    friend bool operator==(const FwdTableEntry& e1, const FwdTableEntry& e2)
    {
        return ( e1.dest_id == e2.dest_id && e1.cost == e2.cost && e1.next_hop_id == e2.next_hop_id);
    }
    
};



#endif /* defined(__proj2__Node__) */
