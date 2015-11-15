//
//  main.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//




#include "RoutingController.h"


int main(int argc, const char * argv[]) 
{
	int bork = argc;
	bork = atoi(*argv);
	bork++;
	
    std::vector<Node*> vecNodes;
    vecNodes.push_back(new Node (33.69,49.97));
    vecNodes.push_back(new Node (48.08,2.94));
    vecNodes.push_back(new Node (18.01,27.42));
    vecNodes.push_back(new Node (13.08,29.86));
    vecNodes.push_back(new Node (2.46,28.55));
    vecNodes.push_back(new Node (35.04,48.11));
    vecNodes.push_back(new Node (37.52,36.99));
    vecNodes.push_back(new Node (21.59,31.71));
    vecNodes.push_back(new Node (40.15,4.19));
    vecNodes.push_back(new Node (47.27,45.79));
    vecNodes.push_back(new Node (30.0,12.67));
    vecNodes.push_back(new Node (43.67,25.67));
    
	uint16_t maxRadius = 20;
	RoutingController routerC(maxRadius,vecNodes);
	routerC.Init();
	
	routerC.PrintNeighborMap();
	std::cout << std::endl;
	routerC.PrintLinks();
	std::cout << std::endl;
	
	
	uint16_t node7 = 7;
	std::cout << "Djikstra Forwarding Table for node: " << node7 << std::endl;
	routerC.PrintFwdTableEntryVector(routerC.ForwardingTableFor(node7,DIJKSTRA));
	uint16_t node11 = 11;
	std::cout << std::endl << "Djikstra Forwarding Table for node: " << node11 << std::endl;
	routerC.PrintFwdTableEntryVector(routerC.ForwardingTableFor(node11,DIJKSTRA));

	uint16_t node1 = 1;
	std::cout << std::endl << "Prim Forwarding Table for node: " << node1 << std::endl;
	routerC.PrintFwdTableEntryVector(routerC.ForwardingTableFor(node1,PRIM));
	std::cout << std::endl << "Prim Spanning Tree for node: " << node1 << std::endl;
    routerC.PrintSpanningTree(routerC.SpanningTreeFor(node1,PRIM));
	std::cout << std::endl << "Broadcast Forwarding totals for node: " << node1 << std::endl;
    routerC.PrintBroadcastData(node1);
	
	//routerC.ForwardingTableFor(18);
	
    return 0;
}
