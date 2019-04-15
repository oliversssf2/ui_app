#ifndef HELPER_H
#define HELPER_H

//define a coordinate structure for drawing circles

#include <iostream>
#include <vector>
#include <stdexcept>

struct cood
{
    int x;
    int y;
    bool valid()
    {
        auto ret = false;
        if(x >= 0 && y >= 0)
            ret = true;
        else {
            throw std::out_of_range("INVALID COORDINATE!!! X is: " + std::to_string(x) + " Y is: " + std::to_string(y));
        }
        return ret;
    }
};

class inspectionPath
{
public:
    inspectionPath() :  path{} {}
    ~inspectionPath();

    inline void addInspectionPoint(cood& point, int t);
    inline void removeInspectionPoint(size_t index);

    inline void operator=(const inspectionPath &path);
private:
    std::vector<cood> path;

};

void inspectionPath::addInspectionPoint(cood& point, int t)
{
    try {
        if(point.valid())
            path.insert(path.begin()+t, point);
    } catch (const std::out_of_range& oor) {
        std::cerr << "Out of Range Error: " << oor.what() << '\n';
    }
}

void inspectionPath::removeInspectionPoint(size_t index)
{
    try {
        if(index >= path.size())
            throw std::out_of_range{"INVALID INDEX!!! THE INDEX IS BIGGER THAN THE SIZE OF THE VECTOR!!! YOUR NUMBER: " + std::to_string(index) + " SIZE OF VECTOR: " + std::to_string(path.size())};
        path.erase(path.begin() + index);
    }
    catch(std::out_of_range &oor){
        std::cerr << "OUT OF RANGE ERROR: " << oor.what() << '\n';
    }
}

#endif // HELPER_H
