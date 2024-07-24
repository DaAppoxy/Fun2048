#include "../include/raylib-cpp.hpp"
#include <cstdint>
using raylib::Window;
namespace cpp = raylib;

constexpr float SCALE = 60.f;
constexpr int w = 4, h = 4;
uint64_t grid[w*h];
float XMAX,YMAX;

const cpp::Color palette[63] = {
    cpp::Color(0xffffffU),
    cpp::Color(0xf7f7eeU),
    cpp::Color(0xefeeddU),
    cpp::Color(0xe7e4ccU),
    cpp::Color(0xdfd9bbU),
    cpp::Color(0xd7cdaaU),
    cpp::Color(0xff5000U),
    cpp::Color(0xef6010U),
    cpp::Color(0xdf7021U),
    cpp::Color(0xcf8033U),
    cpp::Color(0xbf9046U),
    cpp::Color(0x998c00U),
    cpp::Color(0xaa9420U),
    cpp::Color(0xbb9c40U),
    cpp::Color(0xcca460U),
    cpp::Color(0xddac80U),
    cpp::Color(0xfff294U),
    cpp::Color(0xeee386U),
    cpp::Color(0xddd478U),
    cpp::Color(0xccc56aU),
    cpp::Color(0xbbb65cU),
    cpp::Color(0xaaa74eU),
    cpp::Color(0xede082U),
    cpp::Color(0xdbce70U),
    cpp::Color(0xc9bc5eU),
    cpp::Color(0xb7aa4cU),
    cpp::Color(0xa5983aU),
    cpp::Color(0x938628U),
    cpp::Color(0xbf0000U),
    cpp::Color(0xad0401U),
    cpp::Color(0x9b0802U),
    cpp::Color(0x890c03U),
    cpp::Color(0x771004U),
    cpp::Color(0x651405U),
    cpp::Color(0x531806U),
    cpp::Color(0x411c07U),
    cpp::Color(0xffaa00U),
    cpp::Color(0xf79908U),
    cpp::Color(0xee8810U),
    cpp::Color(0xe67718U),
    cpp::Color(0xdd6620U),
    cpp::Color(0xd55528U),
    cpp::Color(0xcc4430U),
    cpp::Color(0xd49c4dU),
    cpp::Color(0xc5995cU),
    cpp::Color(0xb6966bU),
    cpp::Color(0xa7937aU),
    cpp::Color(0x98908aU),
    cpp::Color(0xe60000U),
    cpp::Color(0xde1008U),
    cpp::Color(0xd62010U),
    cpp::Color(0xce3018U),
    cpp::Color(0xc64020U),
    cpp::Color(0xbe5028U),
    cpp::Color(0xb66030U),
    cpp::Color(0x330000U),
    cpp::Color(0x441108U),
    cpp::Color(0x552211U),
    cpp::Color(0x663319U),
    cpp::Color(0x774422U),
    cpp::Color(0x88552aU),
    cpp::Color(0x996633U),
    cpp::Color(0xaa773bU)
};

int main() {
    Window window;
    window.Init(0, 0, "Fun2048");
    XMAX = window.GetWidth();
    YMAX = window.GetHeight();

    while (!window.ShouldClose()) {
        window.BeginDrawing();
            window.ClearBackground(cpp::Color::LightGray());
            for (int y = 0; y < h; y++) {
                for (int x = 0; x < w; x++) {
                    const cpp::Rectangle rect(
                        x*SCALE + (XMAX/2.f - w*SCALE/2.f),
                        y*SCALE + (YMAX/2.f - h*SCALE/2.f),
                        SCALE,
                        SCALE
                    );
                    rect.Draw(palette[]);
                }
            }

        window.EndDrawing();
    }

    window.Close();
}

