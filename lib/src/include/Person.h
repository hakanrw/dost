#pragma once

#include <string>
#include <vector>
#include <ostream>

class Person {
    public:
        Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);

        int getId();
        void setId(int id);

        std::string getName();
        void setName(std::string name);

        int getAge();
        void setAge(int id);

        std::string getGender();
        void setGender(std::string gender);

        std::string getOccupation();
        void setOccupation(std::string occupation);

        friend std::ostream& operator<<(std::ostream& os, const Person& person); // print

    private:
        int id;
        std::string name;
        int age;
        std::string gender;
        std::string occupation;
        std::vector<int> friends;
};