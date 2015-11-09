//
//  main.cpp
//  proj2
//
//  Created by Jeff Fermon on 11/8/15.
//  Copyright (c) 2015 Jeff Fermon. All rights reserved.
//



#include <vector>
#include "Node.h"

int main(int argc, const char * argv[]) {

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

    for (std::vector<Node*>::iterator it = vecNodes.begin(); it != vecNodes.end(); it++)
    {
        std::cout << *(*it) << std::endl;
    }
    
    return 0;
}
