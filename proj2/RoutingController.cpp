//
//  RoutingController.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//

#include "RoutingController.h"


void RoutingController::Init(){
    CreateNeighborMap();
    CreateLinks();
}

void RoutingController::CreateNeighborMap()
{
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        std::vector<Node*> vecReachable = GetReachableNodes(*it);
        m_mapNodeNeighbors.insert(std::pair<Node*,std::vector<Node*> >(*it,vecReachable));
    }
}

std::vector<Node*> RoutingController::GetReachableNodes(Node* newNode)
{
    std::vector<Node*> vecNeighbors;
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        if (newNode != *it && newNode->GetDistance(*it) <= m_nMaxR)
            vecNeighbors.push_back(*it);
    }
    
    return vecNeighbors;
}

void RoutingController::PrintNeighborMap()
{
    std::cout << std::left << std::setw(2) << "Nodes" << std::endl;
    std::cout << std::left
    << std::setw(3) << "ID"
    << std::setw(6) << "XPos"
    << std::setw(6) << "YPos"
    << std::setw(2) << ":"
    << std::setw(10) << "Reachable Nodes" << std::endl;
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        std::cout << *(*it) << " : ";
        
        for (std::vector<Node*>::iterator it2 = m_mapNodeNeighbors[*it].begin(); it2 != m_mapNodeNeighbors[*it].end(); it2++)
        {
            std::cout << *(*it2) << "   ";
        }
        
        std::cout << std::endl;
    }
    
}

void RoutingController::CreateLinks()
{
    uint16_t linkNum(0);
    //get transmitting node
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        //get reachable nodes
        std::vector<Node*> vecReachableNodes = GetReachableNodes(*it);
        for (std::vector<Node*>::iterator it2 = vecReachableNodes.begin(); it2 != vecReachableNodes.end(); it2++)
        {
            Link *tmpLink = new Link(linkNum,*it,*it2);
            //verify link doesnt already exist
            bool linkExists(false);
            for (std::vector<Link*>::iterator it3 = m_vecLinks.begin(); it3 != m_vecLinks.end(); it3++)
            {
                if (*tmpLink == *(*it3))
                    linkExists = true;
            }
            if ( ! linkExists ) {
                m_vecLinks.push_back(tmpLink);
                linkNum++;
            }
        }
    }
}

void RoutingController::PrintLinks()
{
    std::cout << std::left << std::setw(2) << "Links" << std::endl;
    std::cout << std::left
    << std::setw(3)  << "ID"
    << std::setw(18) << "Node1"
    << std::setw(17) << "Node2"
    << std::setw(9)  << "Distance"
    << std::setw(10) << "Cost" <<  std::endl;
    
    for (std::vector<Link*>::iterator it = m_vecLinks.begin(); it != m_vecLinks.end(); it++)
    {
        std::cout << *(*it) << std::endl;
    }
}

void RoutingController::ForwardingTableFor(uint16_t nodeId)
{
    std::vector<Node*>::iterator it;
    Node* currentNode = NULL;
    for (it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        if (nodeId == (*it)->Id_num() )
            currentNode = *it;
    }
    
    if ( ! currentNode ){
        std::cout << "RoutingController::ForwardingTableFor - Invalid node ID: " << nodeId << std::endl;
        return;
    }
    
    //intialize tentative list
    std::vector<FwdTableEntry> vecTentative = InitTentativeVector(currentNode);
    //std::cout << "Step 1 - Forwarding Table for node: " << nodeId << std::endl;
    std::vector<FwdTableEntry>::iterator itTent;
    /*for (itTent = vecTentative.begin(); itTent != vecTentative.end(); itTent++) {
        std::cout << *itTent << std::endl;
    }*/
    
    int iii(2);
    
    std::vector<FwdTableEntry> vecConfirmed;
    while ( ! vecTentative.empty() )
    {
        //move lowest cost to confirmed list
        FwdTableEntry lowestCostEntry = GetLowestCostNode(vecTentative);
        //std::cout << "lowest entry = " << lowestCostEntry << std::endl;
        vecConfirmed.push_back(lowestCostEntry);
        for (itTent = vecTentative.begin(); itTent != vecTentative.end(); itTent++)
        {
            if(*itTent == lowestCostEntry)
            {
                vecTentative.erase(itTent);
                break;
            }
        }
        
        /*std::cout << "Step 2 - after adding confirmed: " << nodeId << std::endl;
         for (itTent = vecConfirmed.begin(); itTent != vecConfirmed.end(); itTent++) {
         std::cout << *itTent << std::endl;
         }
         std::cout << "Step 2 - after removing from tent: " << nodeId << std::endl;
         for (itTent = vecTentative.begin(); itTent != vecTentative.end(); itTent++) {
         std::cout << *itTent << std::endl;
         }*/
        
        //update currentNode
        for (it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
        {
            if (lowestCostEntry.dest_id == (*it)->Id_num() )
                currentNode = *it;
        }
        
        //update for nearest node
        std::vector<Node*> vecReachableNodes = GetReachableNodes(currentNode);
        //iterate thru reachable nodes
        for (it = vecReachableNodes.begin(); it != vecReachableNodes.end(); it++)
        {
            //iterate thru tentative nodes
            for (itTent = vecTentative.begin(); itTent != vecTentative.end(); itTent++)
            {
                //if tentative node is reachable get the link
                if ( (*it)->Id_num() == (*itTent).dest_id )
                {
                    Link* link = GetLink(currentNode,*it);
                    if (!link){
                        std::cout << "RoutingController::ForwardingTableFor - link is null for nodes: "
                        << currentNode->Id_num() << "," << (*it)->Id_num()<< std::endl;
                        return;
                    }
                    float nTentCost = link->Cost() + lowestCostEntry.cost;
                    if( nTentCost < (*itTent).cost )
                    {
                        (*itTent).cost = nTentCost;
                        //if first pass, set next hop to selected node id
                        if (currentNode->Id_num() != nodeId) {
                            (*itTent).next_hop_id = currentNode->Id_num();
                        } else {
                            (*itTent).next_hop_id = (*itTent).dest_id;
                        }
                    }
                }
            }
        }
       /* std::cout << "Step "<< iii << std::endl;
        std::cout << "Confirmed nodes: ";
        for (itTent = vecConfirmed.begin(); itTent != vecConfirmed.end(); itTent++) {
            std::cout << *itTent ;
        }
        std::cout << std::endl;
        std::cout << "Tentative nodes: ";
        for (itTent = vecTentative.begin(); itTent != vecTentative.end(); itTent++) {
            std::cout << *itTent ;
        }
        std::cout << std::endl;
        iii++;*/
    }
    
    std::cout << "Forwarding Table for node: " << nodeId << std::endl;
    for (itTent = vecConfirmed.begin(); itTent != vecConfirmed.end(); itTent++) {
        std::cout << *itTent << std::endl;
    }
    
}

Link* RoutingController::GetLink(Node* n1, Node* n2)
{
    Link* tmpLink = NULL;
    for (std::vector<Link*>::iterator it = m_vecLinks.begin(); it != m_vecLinks.end(); it++)
    {
        if (Link(0,n1,n2) == *(*it))
            tmpLink = *it;
    }
    
    return tmpLink;
}

std::vector<FwdTableEntry> RoutingController::InitTentativeVector(Node* curNode)
{
    //populate all nodes to tentative list
    std::vector<FwdTableEntry> vecTent;
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++) {
        vecTent.push_back(FwdTableEntry((*it)->Id_num()));
    }
    
    //Set distance to current node to 0
    for (std::vector<FwdTableEntry>::iterator itTent = vecTent.begin(); itTent != vecTent.end(); itTent++)
    {
        if(curNode->Id_num() == (*itTent).dest_id)
            (*itTent).cost = 0;
    }
    
    return vecTent;
}

FwdTableEntry RoutingController::GetLowestCostNode(std::vector<FwdTableEntry> vec)
{
    FwdTableEntry lowestCostEntry((uint16_t)NAN);
    for (std::vector<FwdTableEntry>::iterator itTent = vec.begin(); itTent != vec.end(); itTent++)
    {
        if((*itTent).cost <= lowestCostEntry.cost){
            lowestCostEntry= (*itTent);
        }
    }
    return lowestCostEntry;
    
}
