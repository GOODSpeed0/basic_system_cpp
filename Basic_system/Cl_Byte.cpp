//
//  Cl_Byte.cpp
//  Basic_system
//
//  Created by Daniel on 2020/2/27.
//  Copyright © 2020 Daniel. All rights reserved.
//



#include "Cl_Byte.hpp"
#include "Header.h"



class Byte{


    
public:
    
    inline void set_open() {
        used = true;
    }
    inline void set_closed() {
        contents = {0, 0, 0, 0, 0, 0, 0, 0};
        used = false;
    }
    
    const ostream &show_contents(ostream &os) const;
    Byte & change_contents(const short &ix, bool new_item);
    
    
public:
    vector<bool> contents = {0, 0, 0, 0, 0, 0, 0, 0};
    const short sz = 8;
    bool used = false;
    int address = 0;
    
};


// 这部分有点问题

//class Byte_mgt{
//public:
//    void set_open(Byte bt);
//    void set_closed(Byte bt);
//    void change_contents(Byte bt, const short &ix, bool new_item);
//};
//
//
//inline
//void Byte_mgt::set_open(Byte bt){
//    bt.used = 1;
//}
//
//inline
//void Byte_mgt::set_closed(Byte bt){
//    for (auto val : bt.contents){
//        val = false;
//    }
//    bt.used = 0;
//}
//
//
//
//
//inline
//void Byte_mgt::change_contents(Byte bt, const short &ix, bool new_item){
//    if (ix < 8 && ix >= 0)
//        bt.contents[ix] = new_item;
//}

inline
const ostream &Byte::show_contents(ostream &os) const {
    os << contents[0] << " "
       << contents[1] << " "
       << contents[2] << " "
       << contents[3] << " "
       << contents[4] << " "
       << contents[5] << " "
       << contents[6] << " "
       << contents[7] << " "
       << "\t"
       << address << "\t"
       << (used ? "used" : "unused") << endl;
    return os;
}


inline
Byte & Byte::change_contents(const short &ix, bool new_item){
    if (ix < 8 && ix >= 0)
        contents[ix] = new_item;
        if (used == false)
            set_open();
    return *this;
}
