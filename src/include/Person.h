#pragma once

#include <string>
#include <vector>

class Person {
    public:
        Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);

    private:
        int id;
        std::string name;
        int age;
        std::string gender;
        std::string occupation;
        std::vector<int> friends;
};