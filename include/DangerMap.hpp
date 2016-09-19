//
// Created by gaspar_q on 6/2/16.
//

#ifndef CPP_INDIE_STUDIO_DANGERMAP_HPP
#define CPP_INDIE_STUDIO_DANGERMAP_HPP

#include <stddef.h>

class BomberMap;

class DangerMap
{
public:
    enum State
    {
        ERROR,
        DANGEROUS,
        BLOCKED,
        SAFE,
        BONUSED
    };

public:
    DangerMap(size_t mapSize);
    DangerMap(DangerMap const &ref);
    ~DangerMap();
    DangerMap   &operator=(DangerMap const &ref);

public:
    void refresh(BomberMap *);
    DangerMap::State &at(int x, int y) throw(std::out_of_range);
    DangerMap::State &at(irr::core::vector2df const &pos);
    irr::core::vector2df    getFirstFallBackPosition(irr::core::vector2df const &from);

private:
    void addDeflagration(ABomb *bomb, irr::core::vector2df const &pos);
    void resolveDangerAt(int x, int y, BomberMap *map, std::map<irr::core::vector2df, ABomb *> &mapBombs);

public:
    size_t getSize(void) const;
    void setSize(size_t mapSize);
    void destroyMap(void);
    DangerMap::State getDangerAt(int x, int y) const;
    DangerMap::State getDangerAt(irr::core::vector2df const &pos) const;
    bool isPosValid(int x, int y) const;
    bool isPosValid(irr::core::vector2df const &pos) const;

private:
    size_t  mapSize;
    State   **dangers;
};

std::ostream    &operator<<(std::ostream &output, DangerMap const &ref);

#endif //CPP_INDIE_STUDIO_DANGERMAP_HPP
