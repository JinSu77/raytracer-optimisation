#pragma once

#include <iostream>
#include "Vector3.hpp"

class Ray
{
private:
  Vector3 position;
  Vector3 direction;

public:
  Ray();
  Ray(Vector3 pos, Vector3 dir);
  ~Ray();

  // OPTIMISATION : Crée un Ray avec une direction déjà normalisée (évite sqrt)
  static Ray FromNormalized(Vector3 pos, Vector3 normalizedDir);

  Vector3 GetPosition();
  void SetPosition(Vector3 &pos);

  Vector3 GetDirection();
  void SetDirection(Vector3 &pos);

  friend std::ostream &operator<<(std::ostream &_stream, Ray &vec);
};
