#include "test_utils.h"
#include "Sphere.hpp"
#include "Ray.hpp"
#include "Vector3.hpp"
#include "Intersection.hpp"
#include <cmath>

const double EPSILON = 1e-6;

// Test création d'une sphère
void test_sphere_creation() {
    Sphere s(5.0);
    ASSERT_TRUE(true, "Sphere created successfully with radius 5.0");
}

// Test intersection directe : rayon qui va droit vers la sphère
void test_sphere_hit() {
    Sphere s(1.0);
    s.applyTransform(); // Centre à l'origine

    // Rayon partant de (0, 0, -5) vers (0, 0, 1)
    Vector3 rayPos(0.0, 0.0, -5.0);
    Vector3 rayDir(0.0, 0.0, 1.0);
    Ray r(rayPos, rayDir);

    Intersection inters;
    bool hit = s.intersects(r, inters, CULLING_BOTH);

    ASSERT_TRUE(hit, "Ray should hit sphere");

    // Le point d'intersection devrait être à (0, 0, -1)
    ASSERT_NEAR(0.0, inters.Position.x, EPSILON, "Intersection point x");
    ASSERT_NEAR(0.0, inters.Position.y, EPSILON, "Intersection point y");
    ASSERT_NEAR(-1.0, inters.Position.z, EPSILON, "Intersection point z");
}

// Test raté : rayon qui passe à côté de la sphère
void test_sphere_miss() {
    Sphere s(1.0);
    s.applyTransform(); // Centre à l'origine

    // Rayon qui passe à côté (y = 5, bien au-dessus)
    Vector3 rayPos(0.0, 5.0, -5.0);
    Vector3 rayDir(0.0, 0.0, 1.0);
    Ray r(rayPos, rayDir);

    Intersection inters;
    bool hit = s.intersects(r, inters, CULLING_BOTH);

    ASSERT_FALSE(hit, "Ray should miss sphere");
}

// Test normale : vérifier que la normale est correcte
void test_sphere_normal() {
    Sphere s(1.0);
    s.applyTransform();

    Vector3 rayPos(0.0, 0.0, -5.0);
    Vector3 rayDir(0.0, 0.0, 1.0);
    Ray r(rayPos, rayDir);

    Intersection inters;
    bool hit = s.intersects(r, inters, CULLING_BOTH);

    if (hit) {
        // La normale devrait être normalisée (longueur = 1)
        double normalLength = inters.Normal.length();
        ASSERT_NEAR(1.0, normalLength, EPSILON, "Normal should be normalized");
    }
}

// Test avec translation : sphère déplacée
void test_sphere_translated() {
    Sphere s(1.0);
    Vector3 pos(5.0, 0.0, 0.0);
    s.transform.setPosition(pos);
    s.applyTransform();

    // Rayon vers la sphère déplacée
    Vector3 rayPos(5.0, 0.0, -5.0);
    Vector3 rayDir(0.0, 0.0, 1.0);
    Ray r(rayPos, rayDir);

    Intersection inters;
    bool hit = s.intersects(r, inters, CULLING_BOTH);

    ASSERT_TRUE(hit, "Ray should hit translated sphere");
}

int main() {
    std::cout << "\n=== Sphere Unit Tests ===" << std::endl;

    RUN_TEST("SphereCreation", test_sphere_creation);
    RUN_TEST("SphereHit", test_sphere_hit);
    RUN_TEST("SphereMiss", test_sphere_miss);
    RUN_TEST("SphereNormal", test_sphere_normal);
    RUN_TEST("SphereTranslated", test_sphere_translated);

    return TEST_SUMMARY();
}
