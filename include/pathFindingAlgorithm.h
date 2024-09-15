#ifndef PATHFINDINGALGORITHM_H
#define PATHFINDINGALGORITHM_H

#include "grid.h"
#include <vector>

class PathFindingAlgorithm {
public:
    virtual void reset() = 0;
    virtual void initialize(const Grid& grid) = 0;
    virtual bool iterate(Grid& grid) = 0;
    virtual bool isFinished() const = 0;
    virtual std::vector<std::pair<int,int>> shortestPath() = 0;
};

#endif // PATHFINDINGALGORITHM_H