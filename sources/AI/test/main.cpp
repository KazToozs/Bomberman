/*
** main.cpp for cpp_indie_studio in /home/toozs-_c/rendu/second_year/C++/cpp_indie_studio/sources/AI/test
**
** Made by toozs-_c
** Login   <toozs-_c@epitech.net>
**
** Started on  Mon May 09 17:31:18 2016 toozs-_c
// Last update Thu May 12 17:26:54 2016 toozs-_c
*/

#include "Map.hh"
#include "Case.h"
#include <iostream>
#include "../../Player/include/Game.hh"
extern "C" {
# include "lua.h"
# include "lauxlib.h"
# include "lualib.h"
}
#include "../LuaBridge/LuaBridge.h"
// #include "../LuaBridge/lua_typed_enums.h"
//
// void                make_table(lua_State *L, std::vector<std::vector<Case>> map)
// {
//     lua_pushnumber(L, map.size());
//     lua_setglobal(L, "map_y");
//     lua_newtable(L);
//     int newTable = lua_gettop(L);
//     int index = 1;
//     for (int y = 0; y < map.size(); y++)
//     {
//       for (int x = 0; x < map[y].size(); x++)
//       {
//         lua_pushnumber(L, map[y][x]._state);
//         lua_rawseti(L, -2, index);
//         ++index;
//       }
//     }
//     lua_setglobal(L, "map");
// }
//
// void            do_action(std::vector<std::vector<Case>> map)
// {
//   lua_State* L = luaL_newstate();
//   luaL_openlibs(L);
//   int r = luaL_loadfile(L, "./luascript.lua");
//   make_table(L, map);
//   if (r == 0)
//   {
//     r = lua_pcall(L, 0, 0, 0);
//   }
//   luabridge::LuaRef s = luabridge::getGlobal(L, "testString");
//   std::string luaString = s.cast<std::string>();
//   std::cout << luaString << std::endl;
//   // lua_close(L);
// }
//
// int	                                main()
// {
//   Game                              *m;
//   std::vector< std::vector<Case> >  map;
//
//   m = new Game(4, 0, 20);
//   m->init();
//   map = m->get_map()->getMap();
//   do_action(map);
//   return (0);
// }

int             main()
{
  Game          *game;

  game = new Game(4, 0, 20);
  std::cout << "lol" << std::endl;
  
  game->init();
  std::cout << "lol" << std::endl;

  game->get_map()->print();
  std::cout << "lol" << std::endl;
  game->start();
}
