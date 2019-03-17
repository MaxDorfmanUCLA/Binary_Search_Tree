//
//  main.cpp
//  HW710B
//
//  Created by Max Dorfman on 3/7/17.
//  Copyright © 2017 Max Dorfman. All rights reserved.
//

#include "BinarySearchTree.h"
#include<ctime>
#include<iostream>

int main(){
    std::srand(std::time(nullptr)); // seed
    bst::Tree t1; // empty tree
    for (size_t i = 0; i < 10; ++i) // add 10 random double's from 0 to 1
        t1.insert(static_cast<double>(std::rand()) / RAND_MAX);
    std::cout << "Elements: "; // and print the elements
    for (auto itr = t1.begin(); itr != t1.end(); ++itr)
        std::cout << *itr << " ";
    std::cout << std::endl;
    std::cout << "Count of elements: " << t1.size() << std::endl; // count elements in t1
    
    bst::Tree t2 = t1; // t2 is a copy of t1
    double low, up; // lower and upper bounds for value removal
    std::cout << "Enter lower and upper values for removal: ";
    std::cin >> low >> up; // read in values
    
    auto itr = t1.begin();
    
    while (itr != t1.end()){ // while not at the end
        if ((low <= *itr) && (*itr <= up)){ // check if node value in range
            t1.erase(itr); // if so, erase it
            itr = t1.begin(); // and go back to the beginning
            continue; // repeat the loop, ignoring the increment
        }
        ++itr; // if not in range then increment the iterator
    }
    
    // List all the elements of the two trees
    std::cout << "t1 and t2 elements: " << std::endl;
    for (auto itr = t1.begin(); itr != t1.end(); ++itr)
        std::cout << *itr << " ";
    std::cout << std::endl;
    for (auto itr = t2.begin(); itr != t2.end(); ++itr)
        std::cout << *itr << " ";
    
    std::cout << std::endl;
    t2 = std::move(bst::Tree()); // move a default Tree
    std::cout << "t2 size now: " << t2.size() << std::endl;
    t2.insert(3.14); t2.insert(100); // add two numbers
    if (t2.find(3.14) == t2.begin()) // check if 3.14 in collection and if first
        std::cout << "3.14 first item!" << std::endl;
    
    std::cin.get();
    std::cin.get();
    
    return 0;
}
