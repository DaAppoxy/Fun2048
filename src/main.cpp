#include "../include/raylib-cpp.hpp"
#include <cassert>
#include <cstdint>
#include <raylib.h>
#include <raymath.h>
using raylib::Window;
namespace rl = raylib;
typedef raylib::Vector2 v2;
typedef raylib::Rectangle Rect;

constexpr float SCALE = 100.f;
constexpr int w = 6, h = 6;
struct Box {
  Rect rect;
  uint64_t value;
};
Box grid[w * h];
float XMAX, YMAX;
rl::Font font;

rl::Color palette[63] = {
    rl::Color(0xffffffU),  rl::Color(190, 169, 105), rl::Color(173, 118, 66),
    rl::Color(186, 71, 0), rl::Color(185, 0, 68),    rl::Color(0xd7cdaaU),
    rl::Color(0xff5000U),  rl::Color(0xef6010U),     rl::Color(0xdf7021U),
    rl::Color(0xcf8033U),  rl::Color(0xbf9046U),     rl::Color(0x998c00U),
    rl::Color(0xaa9420U),  rl::Color(0xbb9c40U),     rl::Color(0xcca460U),
    rl::Color(0xddac80U),  rl::Color(0xfff294U),     rl::Color(0xeee386U),
    rl::Color(0xddd478U),  rl::Color(0xccc56aU),     rl::Color(0xbbb65cU),
    rl::Color(0xaaa74eU),  rl::Color(0xede082U),     rl::Color(0xdbce70U),
    rl::Color(0xc9bc5eU),  rl::Color(0xb7aa4cU),     rl::Color(0xa5983aU),
    rl::Color(0x938628U),  rl::Color(0xbf0000U),     rl::Color(0xad0401U),
    rl::Color(0x9b0802U),  rl::Color(0x890c03U),     rl::Color(0x771004U),
    rl::Color(0x651405U),  rl::Color(0x531806U),     rl::Color(0x411c07U),
    rl::Color(0xffaa00U),  rl::Color(0xf79908U),     rl::Color(0xee8810U),
    rl::Color(0xe67718U),  rl::Color(0xdd6620U),     rl::Color(0xd55528U),
    rl::Color(0xcc4430U),  rl::Color(0xd49c4dU),     rl::Color(0xc5995cU),
    rl::Color(0xb6966bU),  rl::Color(0xa7937aU),     rl::Color(0x98908aU),
    rl::Color(0xe60000U),  rl::Color(0xde1008U),     rl::Color(0xd62010U),
    rl::Color(0xce3018U),  rl::Color(0xc64020U),     rl::Color(0xbe5028U),
    rl::Color(0xb66030U),  rl::Color(0x330000U),     rl::Color(0x441108U),
    rl::Color(0x552211U),  rl::Color(0x663319U),     rl::Color(0x774422U),
    rl::Color(0x88552aU),  rl::Color(0x996633U),     rl::Color(0xaa773bU)};

bool check_is_full() {
  for (const Box &b : grid) {
    if (b.value == 0)
      return false;
  }
  return true;
}
void add_box() {
  // No smart selection for now, will implement that later
  assert(!check_is_full());
  int i = 0;
  for (;;) {
    if (grid[i].value == 0 && rand() % (w * h * 2) == 0) {
      grid[i].value = 0b1 << (rand() % 4 + 1);
      return;
    }
    i++;
    if (i >= w * h)
      i = 0;
  }
}
int last_bit_index(int n) {
  for (int i = 31; i > 0; i--) {
    if (n >> i == 1)
      return i;
  }
  return 0;
}

inline int noz(int v) {
  if (v == 0) return -1;
  return v;
}

int main() {
  Window window;
  window.Init(0, 0, "Fun2048");
  XMAX = window.GetWidth();
  YMAX = window.GetHeight();
  for (auto &b : grid) {
    b.rect = Rect{0.f, 0.f, SCALE, SCALE};
    b.value = 0;
  }
  for (auto &c : palette) {
    c.a = 255;
  }

  float t = 0.f;
    add_box();

  while (!window.ShouldClose()) {
    window.BeginDrawing();
    window.ClearBackground(rl::Color::LightGray());
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        Box &b = grid[x + y * w];
        const v2 p(x * SCALE + (XMAX - w * SCALE) / 2.f,
                   y * SCALE + (YMAX - h * SCALE) / 2.f);
        b.rect.SetPosition(b.rect.GetPosition().MoveTowards(p, 0.9f));
        if (b.value != 0) {
          b.rect.Draw(palette[last_bit_index(b.value)]);
          const char *const s = TextFormat("%lu", (unsigned long)b.value);
          const v2 m = font.MeasureText(s, SCALE / 2.f, 2.f);
          rl::DrawTextEx(font, s,
                         b.rect.GetPosition() + (v2{SCALE/2.f, SCALE/2.f} - m) / 2.f,
                         SCALE / 2.f, 2.f, WHITE);
        }
      }
    }
    int dx = rl::Keyboard::IsKeyPressed(KEY_RIGHT) -
             rl::Keyboard::IsKeyPressed(KEY_LEFT);
    int dy = rl::Keyboard::IsKeyPressed(KEY_DOWN) -
             rl::Keyboard::IsKeyPressed(KEY_UP);
    if (dx || dy) {
      for (int y = (dy > 0 ? h-1 : 0); (dy > 0) ? (y >= 0) : (y < h); y -= noz(dy)) {
        for (int x = (dx > 0 ? w-1 : 0); (dx > 0) ? (x >= 0) : (x < w); x -= noz(dx)) {
          if (grid[x+y*w].value == 0)
            continue;
          int tx = x, ty = y;
          while (
            grid[(tx + dx) + (ty + dy)*w].value == 0
          && tx + dx >= 0 && tx + dx < w
          && ty + dy >= 0 && ty + dy < h
          ) {
            tx += dx;
            ty += dy;
          }
          if (
            tx + dx >= 0 && tx + dx < w
          && ty + dy >= 0 && ty + dy < h
          ) {
            if (
              grid[tx + dx + (ty+dy)*w].value != 0
            &&grid[tx + dx + (ty+dy)*w].value == grid[(x) + (y)*w].value
            ) {
              grid[tx + dx + (ty+dy)*w].value <<= 1;
              grid[x + y*w].value = 0;
              continue;
            }
          }
          if (x == tx && y == ty) continue;
          grid[(tx) + (ty)*w] = grid[(x) + (y)*w];
          grid[(x) + (y)*w].value = 0;
        }
      }
      add_box();
    }
    DrawCircleV(v2{cosf(t)*30.f + XMAX/2.f, sinf(t)*30.f + YMAX - 40.f}, 10.f, rl::Color::Red());
    window.EndDrawing();
    t += GetFrameTime();
  }

  window.Close();
}
