#ifndef HELPER_H
#define HELPER_H

//define a coordinate structure for drawing circles

#include <iostream>
#include <vector>
#include <stdexcept>
#include <QDataStream>
#include <QFile>

struct coord
{
    int x;
    int y;
    inline bool valid()
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
    inline friend void print_path(inspectionPath&);
public:
    inspectionPath() = default;
    ~inspectionPath() = default;

    inline void addInspectionPoint(coord& point, int t = -1);
    inline void removeInspectionPoint(size_t index);

    inline void operator=(const inspectionPath &path);
    std::vector<coord> path;
private:


};

void print_path(inspectionPath& path)
{
    for(auto &k : path.path)
    {
        std::cout << k.x << " and " << k.y << std::endl;
    }
}

void inspectionPath::addInspectionPoint(coord& point, int t)
{
    try {
        if(point.valid())
        {
            if(t == -1)
                path.push_back(point);
            else
                path.insert(path.begin()+t, point);
        }
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

enum flags{next_line, eof};
inline void write_coord(QDataStream& out, qint32 x, qint32 y, flags flag)
{
    switch(flag){
        case next_line:{
            out << qint32(x) << qint32(y);
            out << qint8(flag);
            break;
        }
        case eof:{
            out << qint32(x) << qint32(y);
            out << qint8(flag);
            break;
        }
    }
}

inline bool read_coord(QDataStream& in, inspectionPath& path)
{
    if(in.atEnd()) {std::cerr << "EMPTY FILE" << std::endl; return false;}
    qint32 x, y;
    qint8 flag;
    coord pt;
    while(true)
    {
        in >> x >> y >> flag;
        pt = coord{x,y};
        if(pt.valid())
            path.addInspectionPoint(pt);
        if(flag == qint8(flags::eof))
        {
            std::cout << "read ended" << std::endl;
            break;
        }
    }
    return true;
}
#endif // HELPER_H
