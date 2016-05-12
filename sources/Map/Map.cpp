#include "Map.hh"
#include "PowerBomb.hh"
#include "PowerRange.hh"
#include "PowerSpeed.hh"
#include <iostream>
#include <ostream>
#include <cstdlib>
#include <ctime>

Map::Map(size_t x, size_t y)
{
  if (x >= 10 || y >= 10)
  {
    this->_x = x;
    this->_y = y;
    generate();
  }
  else
  std::cerr << "The map must at least (10, 10)" << std::endl;
}

Map::Map(const Map &other)
{
  this->_map = other._map;
}

Map &Map::operator=(const Map &other)
{
  this->_map = other._map;
  return *this;
}

std::vector<Case> &Map::operator[](const int &i)
{
    return (this->_map[i]);
}

Map::~Map()
{

}

std::vector<std::vector<Case> > Map::quarter(){
  std::srand(std::time(0));
  std::vector<std::vector<Case> > qMap((_y / 2));
  size_t nb_power_max = _x / 4;
  Case tmp_case;
  std::cout << "nb powerup max : " << nb_power_max << std::endl;
  for (size_t i = 0 ; i < (_y / 2) ; i++) {
    qMap[i].resize((_x / 2));
    for (size_t j = 0 ; j < (_x / 2); j++) {
      if (((i % 2) == 1) && ((j % 2) == 1)) {
        tmp_case._state = Case::UNBREAKABLE;
      }
      else {
        tmp_case._powerup = NULL;
        if ((std::rand() % 5) == 0 ) {
          tmp_case._state = Case::FREE;
        }
        else {
          tmp_case._state = Case::BREAKABLE;
          if ((std::rand() % 4) == 0  && nb_power_max > 0
          && (i != 0 && j != 0) && (i != 1 && j != 0)
          && (i != 1 && j != 0)) {
            if ((std::rand() % 3) == 0){
              std::cout << "Bombe " << "i: " << i << " j: " << j <<std::endl;
              tmp_case._powerup = new PowerBomb();
            }
            if ((std::rand() % 3) == 1){
              std::cout << "RANGE: " << "i: " << i << " j: " << j <<std::endl;
              tmp_case._powerup = new PowerRange();
            }
            if ((std::rand() % 3) == 2){
              std::cout << "SPEED: " << "i: " << i << " j: " << j <<std::endl;
              tmp_case._powerup = new PowerSpeed();
            }
            nb_power_max--;
          }
        }
      }
      qMap[i][j] = tmp_case;
    }
  }
  qMap[0][0]._state = Case::FREE;
  qMap[0][1]._state = Case::FREE;
  qMap[1][0]._state = Case::FREE;
  return qMap;
}

void Map::rotate(std::vector<std::vector<Case> > &qMap, size_t nb_rot){
  std::vector<std::vector<Case> > tmpMap = qMap;
  size_t y_len;
  size_t x_len;
  size_t tmp_x;

  y_len = qMap.size();
  x_len = qMap[y_len - 1].size();
  for (size_t i = 0; i < nb_rot ;  i++){
    for (size_t y = 0; y < y_len; y++){
      x_len = qMap[y].size();
      for (size_t x = 0; x < x_len; x++){
        tmp_x = (y_len - 1) - x;
        tmpMap[y][x] = qMap[tmp_x][y];
      }
    }
    qMap = tmpMap;
  }
}

void Map::symmetry(std::vector<std::vector<Case> > &qMap){
  std::vector<std::vector<Case> > tmpMap = qMap;
  size_t y_len;
  size_t x_len;
  size_t tmp_x;

  y_len = qMap.size();
  x_len = qMap[y_len - 1].size();
  for (size_t y = 0; y < y_len; y++){
    x_len = qMap[y].size();
    for (size_t x = 0; x < x_len; x++){
      tmp_x = (y_len - 1) - x;
      tmpMap[y][x] = qMap[y][tmp_x];
    }
  }
  qMap = tmpMap;
}



void Map::fill_quarter(const std::vector<std::vector<Case> > &qMap,
  std::vector<std::vector<Case> > &tmpMap,
  const size_t &posb_x, const size_t &posb_y, const size_t &pose_x, const size_t &pose_y) {
  size_t i;
  size_t j;
  size_t j_tmp;
  size_t i_tmp;
  j_tmp = 0;
  for (i = posb_y ; i < pose_y; i++) {
    i_tmp = 0;
    for (j = posb_x; j < pose_x; j++) {
      tmpMap[i][j] = qMap[j_tmp][i_tmp];
      i_tmp++;
    }
    j_tmp++;
  }
}

void Map::add_empty_line(std::vector<std::vector<Case> > &tmpMap,
  const size_t &posb_y, const size_t &pose_x){
    for (size_t i = 0; i < pose_x; i++){
      tmpMap[posb_y][i]._state = Case::FREE;
    }
  }

void Map::add_empty_columns(std::vector<std::vector<Case> > &tmpMap,
       const size_t &posb_x, const size_t &posb_y, const size_t &pose_y){
         for (size_t i = posb_y; i < pose_y; i++) {
           tmpMap[i][posb_x]._state = Case::FREE;
         }
         return ;
       }

void Map::generate() {
  std::vector<std::vector<Case> > qMap;
  std::vector<std::vector<Case> > tmpMap(_y, std::vector<Case>(_x));
  std::cout << "I will generate a map (" << _x << ", " << _y << ")" << std::endl;
  qMap = quarter();

  fill_quarter(qMap, tmpMap, 0, 0, (_x / 2), (_y / 2));
  symmetry(qMap);
  if (_x % 2 || _y % 2) {
    add_empty_columns(tmpMap, (_x / 2), 0, (_y / 2));
    fill_quarter(qMap, tmpMap, ((_x / 2) + 1), 0, _x, ((_y / 2)));
    rotate(qMap, 3);
    symmetry(qMap);
    rotate(qMap, 3);
    symmetry(qMap);
    add_empty_line(tmpMap, (_y / 2), _x);
    fill_quarter(qMap, tmpMap, 0, (_y / 2) + 1, (_x / 2), _y);
    rotate(qMap, 3);
    add_empty_columns(tmpMap, (_x / 2), (_y / 2), _y);
    fill_quarter(qMap, tmpMap, ((_x / 2) + 1), (_y / 2) + 1, _x, _y);
  }
  else{
    fill_quarter(qMap, tmpMap, (_x / 2), 0, _x, (_y / 2));
    rotate(qMap, 2);
    fill_quarter(qMap, tmpMap, 0, (_y / 2), (_x / 2), _y);
    rotate(qMap, 3);
    symmetry(qMap);
    rotate(qMap, 3);
    fill_quarter(qMap, tmpMap, (_x / 2), (_y / 2), _x, _y);
  }
  this->_map = tmpMap;
}

void Map::print()
{
  std::vector<std::vector<Case> >::iterator it_y;
  std::vector<Case>::iterator it_x;

  std::string blue = "\033[34m\033[44m";
  std::string bold = "\033[1m";
  std::string dim = "\033[90m\033[100m";
  std::string black = "\033[30m\033[40m";
  std::string light = "\033[37m\033[47m";
  std::string green = "\033[42m";
  std::string cyan = "\033[96m\033[106m";
  std::string red= "\033[31m\033[41m";
  std::string yellow = "\033[93m\033[103m";
  std::string magenta = "\033[95m\033[105m";
  std::string def = "\033[39m\033[0m";
  for (it_y = _map.begin(); it_y != _map.end(); it_y++){
    for (it_x = (*it_y).begin(); it_x != (*it_y).end(); it_x++ ){
      if ((*it_x)._powerup != NULL)
      {
        if ((*it_x)._powerup->get_type() == SPEEDUP)
        std::cout << green << "S " << def;
        if ((*it_x)._powerup->get_type() == RANGEUP)
        std::cout << green << "R " << def;
        if ((*it_x)._powerup->get_type() == BOMBUP)
        std::cout << green << "B " << def;
      }
      else {
        if ((*it_x)._state == Case::BREAKABLE){
          std::cout << light << (*it_x)._state << " " << def;
        }
        else if ((*it_x)._state == Case::UNBREAKABLE){
          std::cout << magenta <<(*it_x)._state << " " << def;
        }
        else if ((*it_x)._state == Case::EXPLODING){
          std::cout << yellow <<(*it_x)._state << " " << def;
        }
        else if ((*it_x)._state == Case::TAKEN){
          std::cout << cyan <<(*it_x)._state << " " << def;
        }
        else if ((*it_x)._state == Case::BOMB){
          std::cout << red <<(*it_x)._state << " " << def;
        }
        else{
          std::cout << black << (*it_x)._state << " " << def;
        }
      }
    }
    std::cout << std::endl;
  }
}

std::vector< std::vector<Case> > &Map::getMap()
{
  return (this->_map);
}
