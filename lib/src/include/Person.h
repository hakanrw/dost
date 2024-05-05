#pragma once

#include <string>
#include <vector>
#include <ostream>

class Person {
    public:
        Person(int id, std::string name, int age, std::string gender, std::string occupation, std::vector<int> friends);

        int getId() const;
        void setId(int id);

        std::string getName() const;
        void setName(std::string name);

        int getAge() const;
        void setAge(int id);

        std::string getGender() const;
        void setGender(std::string gender);

        std::string getOccupation() const;
        void setOccupation(std::string occupation);

        std::vector<int> getFriends() const;
        void removeFriend(int id);

        std::string getSimpleString() const;
        friend std::ostream& operator<<(std::ostream& os, const Person& person); // print

    private:
        int id;
        std::string name;
        int age;
        std::string gender;
        std::string occupation;
        std::vector<int> friends;
};