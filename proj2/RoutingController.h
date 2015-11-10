//
//  RoutingController.h
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#ifndef __proj2__RoutingController__
#define __proj2__RoutingController__

#include <vector>
#include <map>
#include "Link.h"


class RoutingController {
   uint16_t m_nMaxR;
   std::vector<Node*> m_vecNodes;
   std::map<Node*,std::vector<Node*> > m_mapNodeNeighbors;
   std::vector<Link*> m_vecLinks;
  
	   
public:
    RoutingController(uint16_t newMaxR, std::vector<Node*> vecNodes):m_nMaxR(newMaxR), m_vecNodes(vecNodes)
	{}
	void Init();
	void PrintNeighborMap();
	void PrintLinks();
	void ForwardingTableFor(uint16_t nodeId);
	
private:
	void CreateNeighborMap();
	void CreateLinks();
	std::vector<Node*> GetReachableNodes(Node* newNode);
	Link* GetLink(Node* n1, Node* n2);
   
};



#endif /* defined(__proj2__RoutingController__) */
