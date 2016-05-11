#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include <stddef.h>
#include "Case.h"
class Map
{
private:
   size_t _x;
   size_t _y;
   std::vector< std::vector<Case> > _map;
   std::vector<std::vector<Case> > quarter();
   void fill_quarter(const std::vector<std::vector<Case> > &qMap,
      std::vector<std::vector<Case> > &tmpMap,
      const size_t &posb_x, const size_t &posb_y,
      const size_t &pose_x, const size_t &pose_y);
   void symmetry(std::vector<std::vector<Case> > &);
   void rotate(std::vector<std::vector<Case> > &, size_t nb_rot);
   void add_empty_line(std::vector<std::vector<Case> > &tmpMap,
      const size_t &posb_y, const size_t &pose_x);
   void add_empty_columns(std::vector<std::vector<Case> > &tmpMap,
         const size_t &posb_x, const size_t &posb_y, const size_t &pose_y);
   void generate();
public:
   Map(size_t x, size_t y);
   Map(const Map &);
   Map &operator=(const Map &);
   std::vector<Case> &operator[](const int &i);
   ~Map();
   void print(); /* Debug */
   std::vector< std::vector<Case> > &getMap();
};

#endif /* !MAP_H_ */
