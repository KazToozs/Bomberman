/*
** Case.h for  in /home/msa_m/Epitech/tek2/C++/cpp_indie_studio/sources/core
**
** Made by Matheo MSA
** Login   <msa_m@epitech.net>
**
** Started on  Wed Apr 27 17:32:54 2016 Matheo MSA
** Last update Wed May  4 14:11:47 2016 Jules Palluau
*/

#ifndef CASE_H_
#define CASE_H_

#include "../Player/include/IPowerup.hh"

struct Case {

enum State{
  FREE,
  UNBREAKABLE,
  BREAKABLE,
  TAKEN,
  BOMB,
  EXPLODING
};

IPowerup *_powerup;
  State  _state;
};

#endif
