#include <iostream>
#include <cmath>
#include "Scene.hpp"
#include "Intersection.hpp"

Scene::Scene()
{
}

Scene::~Scene()
{
  for (int i = 0; i < objects.size(); ++i)
  {
    delete objects[i];
  }

  for (int i = 0; i < lights.size(); ++i)
  {
    delete lights[i];
  }
}

void Scene::add(SceneObject *object)
{
  objects.push_back(object);
}

void Scene::addLight(Light *light)
{
  lights.push_back(light);
}

void Scene::prepare()
{
  for (int i = 0; i < objects.size(); ++i)
  {
    objects[i]->applyTransform();
  }
}

std::vector<Light *> Scene::getLights()
{
  return lights;
}

bool Scene::closestIntersection(Ray &r, Intersection &closest, CullingType culling)
{
  Intersection intersection;

  double closestDistance = -1;
  // OPTIMISATION : Utilise lengthSquared() pour les comparaisons
  double closestDistanceSquared = -1;
  Intersection closestInter;
  for (int i = 0; i < objects.size(); ++i)
  {
    if (objects[i]->intersects(r, intersection, culling))
    {
      // OPTIMISATION : Évite sqrt() en utilisant lengthSquared() pour la comparaison
      double distanceSquared = (intersection.Position - r.GetPosition()).lengthSquared();

      if (closestDistanceSquared < 0 || distanceSquared < closestDistanceSquared)
      {
        // Seulement calculer sqrt() quand on trouve une nouvelle intersection plus proche
        closestDistanceSquared = distanceSquared;
        closestDistance = sqrt(distanceSquared);
        intersection.Distance = closestDistance;
        closestInter = intersection;
      }
    }
  }
  closest = closestInter;
  return (closestDistance > -1);
}

Color Scene::raycast(Ray &r, Ray &camera, int castCount, int maxCastCount)
{

  Color pixel;

  Intersection intersection;

  if (closestIntersection(r, intersection, CULLING_FRONT))
  {
    // Add the view-ray for convenience (the direction is normalised in the constructor)
    intersection.View = (camera.GetPosition() - intersection.Position).normalize();

    if (intersection.Mat != NULL)
    {
      pixel = pixel + (intersection.Mat)->render(r, camera, &intersection, this);

      // Reflect
      if (castCount < maxCastCount & intersection.Mat->cReflection > 0)
      {
        // OPTIMISATION : reflect() retourne déjà un vecteur normalisé
        Vector3 reflectDir = r.GetDirection().reflect(intersection.Normal);
        Vector3 origin = intersection.Position + (reflectDir * COMPARE_ERROR_CONSTANT);
        Ray reflectRay = Ray::FromNormalized(origin, reflectDir);  // Pas de re-normalisation!

        pixel = pixel + raycast(reflectRay, camera, castCount + 1, maxCastCount) * intersection.Mat->cReflection;
      }
    }
  }

  return pixel;
}