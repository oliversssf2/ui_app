#ifndef HELPER_H
#define HELPER_H

#define a coordinate structure for drawing circles

#include <iostream>
#include <vector>

struct cood
{
    int x;
    int y;
};

class inspectionPath
{
public:
    inspectionPath();
    ~inspectionPath();

    void addInspectionPoint(cood& point);
    void removeInspectionPoint(size_t index);

    void operator=(const inspectionPath &path);
private:
    std::vector<cood> path {};
};


#endif // HELPER_H
