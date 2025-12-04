#include <iostream>
#include <cmath>
#include "Sphere.hpp"
#include "../raymath/Vector3.hpp"

Sphere::Sphere(double r) : SceneObject(), radius(r)
{
}

Sphere::~Sphere()
{
}

void Sphere::applyTransform()
{
  Vector3 c;
  this->center = this->transform.apply(c);
}

// OPTIMISATION : Fonction countPrimes() supprimée
// Cette fonction était inutile et appelée à chaque intersection,
// ce qui ralentissait considérablement le raytracer.

bool Sphere::intersects(Ray &r, Intersection &intersection, CullingType culling)
{
  // Vector from ray origin to center of sphere
  Vector3 OC = center - r.GetPosition();

  // Project OC onto the ray
  Vector3 OP = OC.projectOn(r.GetDirection());

  // If the OP vector is pointing in the opposite direction of the ray
  // ... then it is behind the ray origin, ignore the object
  if (OP.dot(r.GetDirection()) <= 0)
  {
    return false;
  }

  // P is the corner of the right-angle triangle formed by O-C-P
  Vector3 P = r.GetPosition() + OP;

  // Is the length of CP greater than the radius of the circle ? If yes, no intersection!
  Vector3 CP = P - center;
  double distance = CP.length();
  if (distance > radius)
  {
    return false;
  }

  // Calculate the exact point of collision: P1
  double a = sqrt(radius * radius - distance * distance);
  double t = OP.length() - a;
  // double t = OP.length() - (a * 0.8);
  Vector3 P1 = r.GetPosition() + (r.GetDirection() * t);

  // Pre-calculate some useful values for rendering
  intersection.Position = P1;
  intersection.Mat = this->material;
  intersection.Normal = (P1 - center).normalize();

  // OPTIMISATION : countPrimes() supprimée - fonction inutile qui ralentissait

  return true;
}
