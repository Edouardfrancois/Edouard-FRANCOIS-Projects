/*
** EPITECH PROJECT, 2022
** *
** File description:
** main
*/

#include <cstddef>
#include <iostream>
#include <cstring>
#include <fcntl.h>
#include <string>
#include <sstream>

#include "boostrap.hpp"

class entity {
    public:
        explicit entity(std::size_t h) {
            this->_val = h;
        }
        ~entity() {}
        std::size_t _val;
};

int main()
{
    sparse_array<entity> list;
    sparse_array<entity> blank;

    for (int i = 0; i < 10; ++i) {
        list.insert_at(i, entity(i));
        std::cout << list.at(i)._val << std::endl;
    }
    std::cout << "---etape 1------------------------------" << std::endl;
    std::cout << "---INSERT in place of-------------------" << std::endl;
    list.insert_at(3, entity(66));
    //list.erase(5);
    for (int i = 0; i < list.size(); ++i) {
        std::cout << list.at(i)._val << std::endl;
    }
    std::cout << "---etape 2------------------------------" << std::endl;
    std::cout << "---insert in blank leaving empty spaces-" << std::endl;
    for (int i = 0; i < 3; ++i) {
        std::cout << "before size " << blank.size() << std::endl;
        blank.insert_at(3 * i, entity(66));
        std::cout << "after size " << blank.size() << std::endl;
        std::cout << "assigned at " << i * 3 << std::endl;
    }
    std::cout << "---checking output----------------------" << std::endl;
    for (int i = 0; i < blank.size(); ++i) {
            try
            {
                /* code */
                std::cout << blank.at(i)._val << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
    }
    std::cout << "---TESTING insert_at END----------------" << std::endl;
    std::cout << "---etape 1------------------------------" << std::endl;
    
    sparse_array<entity> emplaced_l;
    
    for (int i = 0; i < 10; ++i) {
        emplaced_l.emplace_at(i, i);
        std::cout << emplaced_l.at(i)._val << std::endl;
    }
    std::cout << "---etape 2------------------------------" << std::endl;

    emplaced_l.emplace_at(3, 66);
    std::cout << "emplacing 66 at 3..." << std::endl;
    for (int i = 0; i < 10; ++i) {
        //emplaced_l.emplace_at(i, i);
        std::cout << emplaced_l.at(i)._val << std::endl;
    }

    std::cout << "---etape 3------------------------------" << std::endl;
    std::cout << "emplacing with blank spaces..." << std::endl;

    sparse_array<entity> emplaced_with_blank;
    
    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0) {
            emplaced_with_blank.emplace_at(i, i);
        }
    }
    std::cout << "emplaced at 0: " << emplaced_with_blank.at(0)._val << std::endl;
    std::cout << "emplaced at 3: " << emplaced_with_blank.at(3)._val << std::endl;
    std::cout << "emplaced at 6: " << emplaced_with_blank.at(6)._val << std::endl;
    std::cout << "emplaced at 9: " << emplaced_with_blank.at(9)._val << std::endl;

    std::cout << "getting a blank (1)..." << std::endl;
    try {
        std::cout << "emplaced at 1: " << emplaced_with_blank.at(1)._val << std::endl;
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    std::cout << "---TESTING insert_at END----------------" << std::endl;
    std::cout << "---etape 1: REGISTRY--------------------" << std::endl;
    registry regis;

    {
        std::vector<std::string> names = {"Pierre", "Mayeul", "Soheil", "Edouard", "Ferdinant", "Yacyne", "Pyer", "Girostade", "la Soeur de Mayeul", "J2O Chengdu"};
        /*sparse_array<entity> r1 = */regis.register_component<entity>(); //return ref de sparse array
        /*sparse_array<std::string> r2 = */regis.register_component<std::string>();
        std::cout << "---r2 ...---" << std::endl;
        for (int i = 0; i < 10; ++i) {
            std::ostringstream oss;
            oss << "I hate " << names.at(i);
            regis.get_components<std::string>().insert_at(i, oss.str());
            std::cout << regis.get_components<std::string>().at(i) << std::endl;
            oss.clear();
        }
        std::cout << "---r1 ...---" << std::endl;
        for (int i = 0; i < 10; ++i) {
            regis.get_components<entity>().insert_at(i, entity(i));
            std::cout << regis.get_components<entity>().at(i)._val << std::endl;
        }
    }
    std::cout << "--- GETTING REGISTRY... ---" << std::endl;
        {
        sparse_array<entity> getted1 = regis.get_components<entity>();

        //std::cout << getted1.size() << std::endl; 
        for (int i = 0; i < getted1.size(); ++i) {
            std::cout << getted1.at(i)._val << std::endl;
        }

        sparse_array<std::string> getted2 = regis.get_components<std::string>();

        for (int i = 0; i < getted2.size(); ++i) {
            std::cout << getted2.at(i) << std::endl;
        }
    }

    std::cout << "--- END HATE... ---" << std::endl;
    {
        Entity ent(2);

        regis.kill_entity(ent);

        std::cout << "--- Killed ENT printing... ---" << std::endl;
        sparse_array<entity> getted1 = regis.get_components<entity>();

        //std::cout << getted1.size() << std::endl; 
        for (int i = 0; i < getted1.size(); ++i) {
            try
            {
                /* code */
                std::cout << getted1.at(i)._val << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }

        sparse_array<std::string> getted2 = regis.get_components<std::string>();

        for (int i = 0; i < getted2.size(); ++i) {
            try
            {
                /* code */
                std::cout << getted2.at(i) << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
    }
    //std::cout <<  << std::endl;
}