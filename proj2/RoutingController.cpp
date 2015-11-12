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

void  RoutingController::PrintSpanningTreeFor(std::vector<Link*> vecSpanTreeLinks)
{
    
    std::cout << std::left << std::setw(2) << "Links" << std::endl;
    std::cout << std::left
    << std::setw(3)  << "ID"
    << std::setw(18) << "Node1"
    << std::setw(17) << "Node2"
    << std::setw(9)  << "Distance"
    << std::setw(10) << "Cost" <<  std::endl;
    
    for (std::vector<Link*>::iterator it = vecSpanTreeLinks.begin(); it != vecSpanTreeLinks.end(); it++)
    {
        std::cout << *(*it) << std::endl;
    }
    
   /*
    std::vector<FwdTableEntry> tmpFwdTable = fwdTable;
    std::vector<Link *> vecSpanTreeLinks;
    Node *originNode = NULL;
    
    int iii(0);
    while( ! tmpFwdTable.empty() && iii < 15)
    {
        FwdTableEntry lowestCostEntry = GetLowestCostNode(tmpFwdTable);
        Node* currentDestNode = GetNode( lowestCostEntry.dest_id );
        if ( ! currentDestNode ){
            throw MyException("RoutingController::PrintSpanningTreeFor - Invalid node ID: " );
        }
        
        //if current node cost is 0 its the origin
        if ( lowestCostEntry.cost == 0 )
        {
            std::cout << "cost is 0. Found origin." << std::endl;
            originNode = currentDestNode;
            
            
        }
        //check if node directly connected to origin
        else if (lowestCostEntry.dest_id == lowestCostEntry.next_hop_id)
        {
            std::cout << "node " << lowestCostEntry.dest_id << " connected to origin." << std::endl;
            vecSpanTreeLinks.push_back(GetLink(originNode, currentDestNode));
        }
        else
        {
            Node *nextHopNode = GetNode(lowestCostEntry.next_hop_id);
            if ( IsNodeReachable(lowestCostEntry.dest_id, lowestCostEntry.next_hop_id))
            {
                std::cout << "node " << lowestCostEntry.dest_id
                << " directly connected to next hop node "
                << lowestCostEntry.next_hop_id << std::endl;
                
                vecSpanTreeLinks.push_back(GetLink(nextHopNode, currentDestNode));
            }
            else
            {
                std::cout << "node " << lowestCostEntry.dest_id
                << " not directly connected to next hop node "
                << lowestCostEntry.next_hop_id << std::endl;
                for (std::vector<Link *>::iterator itLink = vecSpanTreeLinks.begin(); itLink != vecSpanTreeLinks.end(); itLink++)
                {
                    Link* curLink = *itLink;
                    if (curLink){
                        // if currentLink is connected to nexthop node &
                        // the other node of the link is connected to current node
                        if ( curLink->ConnectedTo(nextHopNode) &&
                            GetLink(currentDestNode, curLink->GetOtherNode(nextHopNode)) )
                        {
                            vecSpanTreeLinks.push_back(GetLink(currentDestNode, curLink->GetOtherNode(nextHopNode)));
                        }
                    }
                }
            }
        }
        
        //remove this entry in vector
        std::cout << "tmpFwdTable.size: "<< tmpFwdTable.size() <<std::endl;
        for (std::vector<FwdTableEntry>::iterator it = tmpFwdTable.begin(); it != tmpFwdTable.end(); it++)
        {
            if((*it).dest_id == lowestCostEntry.dest_id)
            {
                tmpFwdTable.erase(it);
                it--;
            }
        }
        
        std::cout << std::left << std::setw(2) << "Links" << std::endl;
        std::cout << std::left
        << std::setw(3)  << "ID"
        << std::setw(18) << "Node1"
        << std::setw(17) << "Node2"
        << std::setw(9)  << "Distance"
        << std::setw(10) << "Cost" <<  std::endl;
        
        for (std::vector<Link*>::iterator it = vecSpanTreeLinks.begin(); it != vecSpanTreeLinks.end(); it++)
        {
            std::cout << *(*it) << std::endl;
        }
 
        iii++;
    }
    
    std::cout << std::left << std::setw(2) << "Links" << std::endl;
    std::cout << std::left
    << std::setw(3)  << "ID"
    << std::setw(18) << "Node1"
    << std::setw(17) << "Node2"
    << std::setw(9)  << "Distance"
    << std::setw(10) << "Cost" <<  std::endl;
    
    for (std::vector<Link*>::iterator it = vecSpanTreeLinks.begin(); it != vecSpanTreeLinks.end(); it++)
    {
        std::cout << *(*it) << std::endl;
    }
    
    
    
    return;
*/
}

    
std::vector<FwdTableEntry> RoutingController::ForwardingTableFor(uint16_t nodeId, Algorithm algorithm)
{
    switch (algorithm )
    {
        case DIJKSTRA:
            return DjikstraTableFor(nodeId);
        case PRIM:
            return PrimTableFor(nodeId);
        default:
            return std::vector<FwdTableEntry>();
    }
    
}

std::vector<FwdTableEntry> RoutingController::DjikstraTableFor(uint16_t nodeId)
{
    //initialize currentNode to our starting node
    Node* startingNode = GetNode( nodeId );
    if ( ! startingNode ){
        throw MyException("RoutingController::ForwardingTableFor - Invalid node ID: " );
    }
    
    //intialize tentative list
    std::vector<FwdTableEntry> vecTentative = InitDjikstraTentativeVector(startingNode);
    std::vector<FwdTableEntry> vecConfirmed;
    std::vector<Link *> vecLinksUsed;
    
    while ( ! vecTentative.empty() )
    {
        //move lowest cost to confirmed list
        FwdTableEntry lowestCostEntry = GetLowestCostNode(vecTentative);
        vecConfirmed.push_back(lowestCostEntry);
        for (std::vector<FwdTableEntry>::iterator itTent = vecTentative.begin();
             itTent != vecTentative.end(); itTent++)
        {
            if( *itTent == lowestCostEntry )
            {
                vecTentative.erase(itTent);
                break;
            }
        }
        
        //update currentNode
        Node* currentNode = GetNode( lowestCostEntry.dest_id );
        if ( ! currentNode ){
            throw MyException("RoutingController::ForwardingTableFor - Invalid node ID: " );
        }
        
        //update for nearest node by adding nodes not in current or in confirmed
        UpdateTentativeVector(currentNode,&vecTentative,vecConfirmed);
        
        //iterate thru tentative nodes
        for (std::vector<FwdTableEntry>::iterator itTent = vecTentative.begin();
             itTent != vecTentative.end(); itTent++)
        {
            if (IsNodeReachable(currentNode->Id_num(), (*itTent).dest_id))
            {
                //if tentative node is reachable get the link info
                Node *endNode = GetNode((*itTent).dest_id);
                Link* link = GetLink(currentNode,endNode);
                if (!link){
                    throw MyException("RoutingController::ForwardingTableFor - link is null for nodes: ");
                }
                
                float nTentCost = link->Cost() + lowestCostEntry.cost;
                if( nTentCost < (*itTent).cost )
                {
                    (*itTent).cost = nTentCost;
                    
                    //determine next hop id
                    (*itTent).next_hop_id = GetNextHopId(startingNode,currentNode, endNode, vecConfirmed);
                    UpdateLinksUsedVector(endNode, link, vecLinksUsed);
                }
            }
        }
    }
    
    PrintSpanningTreeFor(vecLinksUsed);
    
    return vecConfirmed;
}

std::vector<FwdTableEntry> RoutingController::PrimTableFor(uint16_t nodeId)
{
    //initialize currentNode to our starting node
    Node* startingNode = GetNode( nodeId );
    if ( ! startingNode ){
        throw MyException("RoutingController::ForwardingTableFor - Invalid node ID: " );
    }
    
    //intialize tentative list
    std::vector<FwdTableEntry> vecTentative = InitPrimTentativeVector(startingNode);
    std::vector<FwdTableEntry> vecConfirmed;
    std::vector<Link *> vecLinksUsed;
    
    while ( ! vecTentative.empty() )
    {
        //move lowest cost to confirmed list
        FwdTableEntry lowestCostEntry = GetLowestCostNode(vecTentative);
        vecConfirmed.push_back(lowestCostEntry);
        for (std::vector<FwdTableEntry>::iterator itTent = vecTentative.begin();
             itTent != vecTentative.end(); itTent++)
        {
            if( *itTent == lowestCostEntry )
            {
                vecTentative.erase(itTent);
                break;
            }
        }
        
        //update currentNode
        Node* currentNode = GetNode( lowestCostEntry.dest_id );
        if ( ! currentNode ){
            throw MyException("RoutingController::ForwardingTableFor - Invalid node ID: " );
        }
        
        //update for nearest node
        std::vector<Node*> vecReachableNodes = GetReachableNodes(currentNode);
        
        //iterate thru reachable nodes
        for (std::vector<Node*>::iterator it = vecReachableNodes.begin();
             it != vecReachableNodes.end(); it++)
        {
            //iterate thru tentative nodes
            for (std::vector<FwdTableEntry>::iterator itTent = vecTentative.begin();
                 itTent != vecTentative.end(); itTent++)
            {
                //if tentative node is reachable get the link info
                if ( (*it)->Id_num() == (*itTent).dest_id )
                {
                    Link* link = GetLink(currentNode,*it);
                    if (!link){
                        throw MyException("RoutingController::ForwardingTableFor - link is null for nodes: ");
                    }
                    
                    float nTentCost = link->Cost() + lowestCostEntry.cost;
                    if( nTentCost < (*itTent).cost )
                    {
                        (*itTent).cost = nTentCost;
                        
                        //determine next hop id
                        (*itTent).next_hop_id = GetNextHopId(startingNode,currentNode, *it, vecConfirmed);
                        Node *endNode = GetNode((*itTent).dest_id);
                        UpdateLinksUsedVector(endNode, link, vecLinksUsed);
                    }
                }
            }
        }
    }
    PrintSpanningTreeFor(vecLinksUsed);
    return vecConfirmed;
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

std::vector<FwdTableEntry> RoutingController::InitPrimTentativeVector(Node* curNode)
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

std::vector<FwdTableEntry> RoutingController::InitDjikstraTentativeVector(Node* curNode)
{
    //populate origin tentative list
    std::vector<FwdTableEntry> vecTent;
    vecTent.push_back(FwdTableEntry((curNode)->Id_num()));
    
    //Set distance to origin node to 0
    (*(vecTent.begin())).cost = 0;
    
    return vecTent;
}

void RoutingController::UpdateTentativeVector(Node* curNode,std::vector<FwdTableEntry> *vecTent,std::vector<FwdTableEntry> vecConfirmed)
{
    std::vector<Node*> vecReachableNodes = GetReachableNodes(curNode);
    for (std::vector<Node*>::iterator it = vecReachableNodes.begin(); it != vecReachableNodes.end(); it++)
    {
        bool entryExists(false);
        FwdTableEntry tmpEntry((*it)->Id_num());
        for (std::vector<FwdTableEntry>::iterator itTent = vecTent->begin(); itTent != vecTent->end(); itTent++ )
        {
            if ((*itTent).dest_id == tmpEntry.dest_id )
                entryExists = true;
        }
        for (std::vector<FwdTableEntry>::iterator itCnf = vecConfirmed.begin(); itCnf != vecConfirmed.end(); itCnf++ )
        {
            if ((*itCnf).dest_id == tmpEntry.dest_id )
                entryExists = true;
        }
        
        if ( ! entryExists)
            vecTent->push_back(tmpEntry);
    }
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

Node* RoutingController::GetNode( uint16_t nodeId )
{
    Node* node = NULL;
    for (std::vector<Node*>::iterator it = m_vecNodes.begin(); it != m_vecNodes.end(); it++)
    {
        if (nodeId == (*it)->Id_num() )
            node = *it;
    }
    
    return node;
}

void RoutingController::PrintFwdTableEntryVector(std::vector<FwdTableEntry> vec)
{
    for (std::vector<FwdTableEntry>::iterator it = vec.begin();
         it != vec.end(); it++) {
        std::cout << *it << std::endl;
    }
}

bool RoutingController::IsNodeReachable(Node* originNode, Node* nodeInQuestion)
{
    std::vector<Node*> vecReachableNodes = GetReachableNodes(originNode);
    for (std::vector<Node*>::iterator it = vecReachableNodes.begin(); it != vecReachableNodes.end(); it++)
    {
        if (  nodeInQuestion == (*it) )
            return true;
    }
    
    return false;
}

bool RoutingController::IsNodeReachable(uint16_t originNodeId, uint16_t nodeInQuestionId)
{
    return IsNodeReachable(GetNode(originNodeId),GetNode(nodeInQuestionId));
}

uint16_t RoutingController::GetNextHopId(Node* originNode, Node* currentNode, Node* destinationNode, std::vector<FwdTableEntry> confirmedNodes)
{
    if( originNode == destinationNode )
        return 0;
    else if( IsNodeReachable(originNode,currentNode) )
        return currentNode->Id_num();
    else if ( IsNodeReachable(originNode,destinationNode) )
        return destinationNode->Id_num();
    else
    {
        for ( std::vector<FwdTableEntry>::iterator it = confirmedNodes.begin(); it != confirmedNodes.end(); it++ )
        {
            if( currentNode->Id_num() == (*it).dest_id )
                return (*it).next_hop_id;
        }
        return (uint16_t)NAN;
    }
    
}

void RoutingController::PrintConfAndTent( std::vector<FwdTableEntry> vecConfirmed,  std::vector<FwdTableEntry> vecTentative)
{
    std::cout << "Step "<< std::endl;
    std::cout << "Confirmed nodes: " << std::endl;
    PrintFwdTableEntryVector(vecConfirmed);
    std::cout << std::endl;
    std::cout << "Tentative nodes: " << std::endl;
    PrintFwdTableEntryVector(vecTentative);
    std::cout << std::endl;
}


void RoutingController::UpdateLinksUsedVector(Node* endNode, Link* link, std::vector<Link *> &vecLinksUsed)
{
    for (std::vector<Link*>::iterator it = vecLinksUsed.begin(); it != vecLinksUsed.end(); it++)
    {
        //link is connected to the destination node, remove it and replace it with the new link.
       if ((*it)->ConnectedTo(endNode))
       {
           vecLinksUsed.erase(it);
           vecLinksUsed.insert(it,link);
           return;
       }
    }
    
    vecLinksUsed.push_back(link);
}