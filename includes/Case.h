/*
** Case.h for  in /home/msa_m/Epitech/tek2/C++/cpp_indie_studio/sources/core
**
** Made by Matheo MSA
** Login   <msa_m@epitech.net>
**
** Started on  Wed Apr 27 17:32:54 2016 Matheo MSA
** Last update Mon May 09 22:39:18 2016 toozs-_c
*/

#ifndef CASE_H_
#define CASE_H_

#include "IPowerup.hh"

struct Case {
  enum State {
    FREE,        /* 0 */
    UNBREAKABLE, /* 1 */
    BREAKABLE,   /* 2 */
    TAKEN,       /* 3 */
    BOMB,        /* 4 */
    EXPLODING,   /* 5 */
    NOPE
  };

  IPowerup *_powerup;
  State _state;
};

#endif
