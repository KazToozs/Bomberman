#ifndef MAP_H_
#define MAP_H_
#include <vector>
#include <stddef.h>
#include "Case.h"
class Map
{
private:
   std::vector< std::vector<Case> > map;
   std::vector<std::vector<Case> > quarter(size_t x, size_t y);
   void rotate(std::vector<std::vector<Case> > &, size_t nb_rot);
   void generate(size_t x, size_t y);
public:
   Map(size_t x, size_t y);
   Map(const Map &);
   Map &operator=(const Map &);
   ~Map();
   void print(); /* Debug */
};

#endif /* !MAP_H_ */
