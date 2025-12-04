#include "test_utils.h"
#include "SceneLoader.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Image.hpp"
#include <chrono>
#include <iostream>

// Test simple : vérifier que le rendu s'exécute et génère une image
void test_render_generates_image() {
    std::cout << "  Loading scene..." << std::endl;
    auto [scene, camera, image] = SceneLoader::Load("../../scenes/two-spheres-on-plane.json");

    ASSERT_TRUE(scene != nullptr, "Scene loaded");
    ASSERT_TRUE(camera != nullptr, "Camera loaded");
    ASSERT_TRUE(image != nullptr, "Image loaded");

    std::cout << "  Rendering " << image->width << "x" << image->height << " pixels..." << std::endl;

    // Mesurer le temps de rendu
    auto begin = std::chrono::high_resolution_clock::now();
    camera->render(*image, *scene);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::cout << "  Render time: " << (elapsed.count() / 1000.0) << " seconds" << std::endl;

    // Vérifier que l'image contient des pixels non noirs (sanity check)
    bool has_content = false;
    for (unsigned int y = 0; y < image->height && !has_content; y += image->height / 10) {
        for (unsigned int x = 0; x < image->width && !has_content; x += image->width / 10) {
            Color pixel = image->getPixel(x, y);
            if (pixel.r > 0.01 || pixel.g > 0.01 || pixel.b > 0.01) {
                has_content = true;
            }
        }
    }

    ASSERT_TRUE(has_content, "Image contains visible content");

    // Sauvegarder l'image
    std::string outfile = "test_output.png";
    image->writeFile(outfile);
    std::cout << "  Image saved: " << outfile << std::endl;

    delete scene;
    delete camera;
    delete image;
}

int main() {
    std::cout << "\n=== End-to-End Simple Test ===" << std::endl;
    std::cout << "This test renders a scene and verifies the image is generated." << std::endl;
    std::cout << std::endl;

    RUN_TEST("RenderGeneratesImage", test_render_generates_image);

    return TEST_SUMMARY();
}
