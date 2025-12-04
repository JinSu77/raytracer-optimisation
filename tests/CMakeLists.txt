# Test utilities library
add_library(test_utils STATIC test_utils.cpp)
target_include_directories(test_utils PUBLIC
    "${PROJECT_SOURCE_DIR}/src/raymath"
    "${PROJECT_SOURCE_DIR}/src/rayimage"
    "${PROJECT_SOURCE_DIR}/src/rayscene"
)

# ========================================
# TESTS UNITAIRES
# ========================================

# Unit test for Vector3
add_executable(test_vector3 test_vector3.cpp)
target_link_libraries(test_vector3 test_utils raymath)
target_include_directories(test_vector3 PRIVATE
    "${PROJECT_SOURCE_DIR}/src/raymath"
)
add_test(NAME Vector3Tests COMMAND test_vector3)

# Unit test for Sphere
add_executable(test_sphere test_sphere.cpp)
target_link_libraries(test_sphere test_utils rayscene rayimage raymath lodepng)
target_include_directories(test_sphere PRIVATE
    "${PROJECT_SOURCE_DIR}/src/raymath"
    "${PROJECT_SOURCE_DIR}/src/rayscene"
)
add_test(NAME SphereTests COMMAND test_sphere)

# ========================================
# TESTS END-TO-END
# ========================================

# Simple end-to-end test (just verifies image is generated)
add_executable(test_e2e_simple test_e2e_simple.cpp)
target_link_libraries(test_e2e_simple
    test_utils
    rayscene
    rayimage
    raymath
    lodepng
)
target_include_directories(test_e2e_simple PRIVATE
    "${PROJECT_SOURCE_DIR}/src/raymath"
    "${PROJECT_SOURCE_DIR}/src/rayimage"
    "${PROJECT_SOURCE_DIR}/src/rayscene"
)
add_test(NAME E2E_Simple COMMAND test_e2e_simple)

# ========================================
# TESTS DE COMPARAISON D'IMAGES
# ========================================

# Image comparison test (detects visual regressions)
add_executable(test_image_comparison test_image_comparison.cpp)
target_link_libraries(test_image_comparison
    test_utils
    rayscene
    rayimage
    raymath
    lodepng
)
target_include_directories(test_image_comparison PRIVATE
    "${PROJECT_SOURCE_DIR}/src/raymath"
    "${PROJECT_SOURCE_DIR}/src/rayimage"
    "${PROJECT_SOURCE_DIR}/src/rayscene"
)
add_test(NAME ImageComparison COMMAND test_image_comparison)

# ========================================
# TEST D'ÉCHEC INTENTIONNEL (pour démonstration)
# ========================================

add_executable(test_intentional_fail test_intentional_fail.cpp)
target_link_libraries(test_intentional_fail test_utils raymath)
add_test(NAME IntentionalFailTest COMMAND test_intentional_fail)
set_tests_properties(IntentionalFailTest PROPERTIES WILL_FAIL TRUE)
