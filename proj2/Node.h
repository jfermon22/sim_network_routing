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


class Node {
    static uint16_t nextID;
    uint16_t id_num;
    float x;
    float y;
public:
    Node(float newX, float newY);
    friend std::ostream& operator<<(std::ostream& os, const Node& node);
};



#endif /* defined(__proj2__Node__) */
