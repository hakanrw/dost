#pragma once

#include <string>
#include <vector>
#include <ostream>

class Person {
    public:
        Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);

        friend std::ostream& operator<<(std::ostream& os, const Person& person); // print

    private:
        int id;
        std::string name;
        int age;
        std::string gender;
        std::string occupation;
        std::vector<int> friends;
};