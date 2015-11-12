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
#include <string.h>
#include "Link.h"

enum Algorithm {
	DIJKSTRA,
	PRIM,
};

class MyException {
	std::string description;
public:
	MyException(std::string desc):
		description(desc){}
	std::string What(){return description;}
	std::string Description(){return description;}
};
 
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
	std::vector<FwdTableEntry> ForwardingTableFor(uint16_t nodeId, Algorithm algorithm);
    void PrintSpanningTree(Node *);
	void PrintFwdTableEntryVector(std::vector<FwdTableEntry> vec);
	
private:
	void CreateNeighborMap();
	void CreateLinks();
	std::vector<Node*> GetReachableNodes(Node* newNode);
	Link* GetLink(Node* n1, Node* n2);
	Node* GetNode( uint16_t nodeId);
    FwdTableEntry GetLowestCostNode(std::vector<FwdTableEntry> vec);
    std::vector<FwdTableEntry> InitDjikstraTentativeVector(Node* curNode);
    std::vector<FwdTableEntry> InitPrimTentativeVector(Node* curNode);
    void UpdateTentativeVector(Node* curNode,std::vector<FwdTableEntry> *vecTent,std::vector<FwdTableEntry> vecConfirmed);
    void UpdateLinksUsedVector(Node* endNode,Link* newLink, std::vector<Link *> &vecLinksUsed);
	void PrintConfAndTent( std::vector<FwdTableEntry> vecTentative,  std::vector<FwdTableEntry> vecConf);
	bool IsNodeReachable(Node* originNode, Node* nodeInQuestion);
	bool IsNodeReachable(uint16_t originNodeId, uint16_t nodeInQuestionId);
	uint16_t GetNextHopId(Node* originNode,Node* currentNode, Node* destinationNode, std::vector<FwdTableEntry> confirmedNodes);
	std::vector<FwdTableEntry> DjikstraTableFor(uint16_t nodeId);
	std::vector<FwdTableEntry> PrimTableFor(uint16_t nodeId);    void PrintSpanningTreeFor(std::vector<Link*> vec);
};



#endif /* defined(__proj2__RoutingController__) */
