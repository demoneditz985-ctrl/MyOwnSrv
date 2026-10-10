#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <cmath>
#include <cstdlib>

#include <xdl.h>
#include <KittyUtils.h>
#include <KittyMemory.h>
#include <Il2Cpp.h>
#include <SubstrateHook.h>
#include <CydiaSubstrate.h>
#include "Struct/Gui.hpp"
#include <Struct/main.h>
#include "fonts/FontAwesome6_solid.h"
#include "ImGui/Toggle.h"
#include "zygisk.hpp"

// ImGui internal — needed for ImRect, ImLerp
#ifndef IMGUI_DEFINE_MATH_OPERATORS
#define IMGUI_DEFINE_MATH_OPERATORS
#endif
#include "imgui_internal.h"

void hack_thread();

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jvm = vm;
    std::thread(hack_thread).detach();
    return JNI_VERSION_1_6;
}

uintptr_t ArrayOffset  = 0x10;
uintptr_t CountOffset  = 0x18;
uintptr_t ValuesOffset = 0x20;
uintptr_t PointerSize  = 0x8;

// ============================================================
//  SHADOW MODZ — DARK NEON THEME
// ============================================================
static void ShadowModzTheme()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // Window background — near-black void #050610
    colors[ImGuiCol_WindowBg]        = ImVec4(0.020f, 0.024f, 0.043f, 0.94f);
    // Child / panel — deep navy
    colors[ImGuiCol_ChildBg]         = ImVec4(0.043f, 0.051f, 0.078f, 0.72f);
    colors[ImGuiCol_PopupBg]         = ImVec4(0.031f, 0.037f, 0.059f, 0.98f);
    // Border — neon cyan
    colors[ImGuiCol_Border]          = ImVec4(0.000f, 0.860f, 1.000f, 0.85f);
    colors[ImGuiCol_BorderShadow]    = ImVec4(1.000f, 0.100f, 0.750f, 0.28f);
    colors[ImGuiCol_FrameBg]         = ImVec4(0.059f, 0.070f, 0.110f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]  = ImVec4(0.000f, 0.330f, 0.430f, 1.00f);
    colors[ImGuiCol_FrameBgActive]   = ImVec4(0.000f, 0.680f, 0.850f, 1.00f);
    colors[ImGuiCol_TitleBg]         = ImVec4(0.012f, 0.015f, 0.027f, 1.00f);
    colors[ImGuiCol_TitleBgActive]   = ImVec4(0.086f, 0.020f, 0.196f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]= ImVec4(0.012f, 0.015f, 0.027f, 0.70f);
    colors[ImGuiCol_ScrollbarBg]     = ImVec4(0.020f, 0.024f, 0.043f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]   = ImVec4(0.000f, 0.550f, 0.700f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.000f, 0.860f, 1.000f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(1.000f, 0.100f, 0.750f, 1.00f);
    colors[ImGuiCol_CheckMark]       = ImVec4(1.000f, 0.100f, 0.750f, 1.00f);
    colors[ImGuiCol_SliderGrab]      = ImVec4(0.000f, 0.900f, 1.000f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]= ImVec4(1.000f, 0.100f, 0.750f, 1.00f);
    colors[ImGuiCol_Button]          = ImVec4(0.067f, 0.078f, 0.129f, 1.00f);
    colors[ImGuiCol_ButtonHovered]   = ImVec4(0.000f, 0.300f, 0.420f, 1.00f);
    colors[ImGuiCol_ButtonActive]    = ImVec4(0.450f, 0.050f, 0.550f, 1.00f);
    colors[ImGuiCol_Header]          = ImVec4(0.196f, 0.020f, 0.451f, 0.75f);
    colors[ImGuiCol_HeaderHovered]   = ImVec4(0.000f, 0.450f, 0.600f, 0.85f);
    colors[ImGuiCol_HeaderActive]    = ImVec4(0.000f, 0.700f, 0.860f, 0.95f);
    colors[ImGuiCol_Separator]       = ImVec4(0.000f, 0.860f, 1.000f, 0.40f);
    colors[ImGuiCol_SeparatorHovered]= ImVec4(1.000f, 0.100f, 0.750f, 0.85f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.100f, 0.750f, 1.00f);
    colors[ImGuiCol_Text]            = ImVec4(0.851f, 0.941f, 1.000f, 1.00f);
    colors[ImGuiCol_TextDisabled]    = ImVec4(0.380f, 0.439f, 0.549f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]  = ImVec4(0.000f, 0.860f, 1.000f, 0.45f);
    colors[ImGuiCol_Tab]             = ImVec4(0.047f, 0.055f, 0.090f, 1.00f);
    colors[ImGuiCol_TabHovered]      = ImVec4(0.000f, 0.450f, 0.600f, 1.00f);
    colors[ImGuiCol_TabActive]       = ImVec4(0.196f, 0.020f, 0.451f, 1.00f);

    style.WindowRounding    = 16.0f;
    style.ChildRounding     = 14.0f;
    style.FrameRounding     = 12.0f;
    style.PopupRounding     = 14.0f;
    style.ScrollbarRounding = 12.0f;
    style.GrabRounding      = 12.0f;
    style.TabRounding       = 10.0f;
    style.WindowBorderSize  = 2.0f;   // thin neon edge
    style.ChildBorderSize   = 1.0f;
    style.FrameBorderSize   = 1.0f;
    style.PopupBorderSize   = 1.0f;
    style.WindowPadding     = ImVec2(14.0f, 14.0f);
    style.FramePadding      = ImVec2(10.0f, 6.0f);
    style.ItemSpacing       = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing  = ImVec2(8.0f, 6.0f);
    style.ScrollbarSize     = 10.0f;
    style.GrabMinSize       = 14.0f;
}

// ============================================================
//  NEON COLOUR HELPERS
// ============================================================
// hue: 0 = white, 1 = cyan, 2 = magenta, 3 = violet
static ImU32 SmNeonColor(int hue, ImU8 a)
{
    switch (hue % 4) {
        case 0:  return IM_COL32(255, 255, 255, a);
        case 1:  return IM_COL32(120, 240, 255, a);
        case 2:  return IM_COL32(255, 120, 230, a);
        default: return IM_COL32(180, 150, 255, a);
    }
}

static void SmGlowRect(ImDrawList* dl, const ImVec2& mn, const ImVec2& mx,
                       float rounding, ImU8 baseA, float pulse)
{
    for (int g = 3; g >= 1; --g) {
        ImU8 a = (ImU8)(baseA - g * 9 + (ImU8)(14.0f * pulse));
        dl->AddRect(ImVec2(mn.x - g * 2.0f, mn.y - g * 2.0f),
                    ImVec2(mx.x + g * 2.0f, mx.y + g * 2.0f),
                    IM_COL32(0, 235, 255, a), rounding + g * 2.0f, 0, 1.5f);
    }
}

// ============================================================
//  MOVING STAR BACKGROUND — parallax starfield, nebula glow, shooting stars
// ============================================================
struct SmStar { float x, y, z, r, tw, ph; int hue; };

static const int SM_STAR_COUNT = 220;
static SmStar g_smStars[SM_STAR_COUNT];
static bool   g_smStarsInit = false;
static float  g_smW = 0.0f, g_smH = 0.0f;

struct SmShooter { float x, y, vx, vy, life, maxLife; int hue; bool active; };
static SmShooter g_smShooter = { 0, 0, 0, 0, 0, 0, 0, false };
static float g_smNextShooter = 2.0f;

static void SmInitStars(float W, float H)
{
    for (int i = 0; i < SM_STAR_COUNT; ++i) {
        g_smStars[i].z   = 0.25f + (float)(rand() % 100) / 100.0f * 0.95f; // depth 0.25..1.20
        g_smStars[i].x   = (float)(rand() % 1000) / 1000.0f * W;
        g_smStars[i].y   = (float)(rand() % 1000) / 1000.0f * H;
        g_smStars[i].r   = 0.6f + g_smStars[i].z * 1.8f;
        g_smStars[i].tw  = 1.2f + (float)(rand() % 200) / 100.0f;  // twinkle speed
        g_smStars[i].ph  = (float)(rand() % 628) / 100.0f;         // twinkle phase
        g_smStars[i].hue = rand() % 4;
    }
    g_smW = W; g_smH = H; g_smStarsInit = true;
}

// Three slow-drifting neon clouds, faked with concentric soft rings.
static void SmDrawNebula(ImDrawList* dl, float W, float H, float t)
{
    const int nr[3] = {   0, 200, 120 };
    const int ng[3] = { 190,  20,  60 };
    const int nb[3] = { 255, 170, 255 };
    float shortSide = (W < H) ? W : H;

    for (int n = 0; n < 3; ++n) {
        float cx = W * (0.20f + 0.30f * n) + sinf(t * 0.10f + n * 2.1f) * W * 0.06f;
        float cy = H * (0.30f + 0.22f * (float)((n + 1) % 3)) + cosf(t * 0.08f + n * 1.7f) * H * 0.05f;
        float base = shortSide * 0.36f;
        for (int ring = 10; ring >= 1; --ring) {
            float f = (float)ring / 10.0f;
            ImU8 a = (ImU8)(11.0f * f * f);
            if (a == 0) continue;
            dl->AddCircleFilled(ImVec2(cx, cy), base * f, IM_COL32(nr[n], ng[n], nb[n], a), 20);
        }
    }
}

static void SmUpdateShooter(float W, float H, float dt)
{
    g_smNextShooter -= dt;
    if (!g_smShooter.active && g_smNextShooter <= 0.0f) {
        g_smShooter.active  = true;
        g_smShooter.x       = (float)(rand() % 1000) / 1000.0f * W * 0.8f;
        g_smShooter.y       = -20.0f;
        g_smShooter.vx      = 420.0f + (float)(rand() % 300);
        g_smShooter.vy      = 260.0f + (float)(rand() % 220);
        g_smShooter.maxLife = 1.10f + (float)(rand() % 60) / 100.0f;
        g_smShooter.life    = g_smShooter.maxLife;
        g_smShooter.hue     = rand() % 4;
        g_smNextShooter     = 3.00f + (float)(rand() % 400) / 100.0f;
    }

    if (!g_smShooter.active) return;

    g_smShooter.x += g_smShooter.vx * dt;
    g_smShooter.y += g_smShooter.vy * dt;
    g_smShooter.life -= dt;

    if (g_smShooter.life <= 0.0f || g_smShooter.x > W + 80.0f || g_smShooter.y > H + 80.0f) {
        g_smShooter.active = false;
    }
}

static void SmDrawShooter(ImDrawList* dl)
{
    if (!g_smShooter.active) return;

    float k   = g_smShooter.life / g_smShooter.maxLife;
    if (k < 0.0f) k = 0.0f;
    float len = 90.0f;
    float inv = 1.0f / sqrtf(g_smShooter.vx * g_smShooter.vx + g_smShooter.vy * g_smShooter.vy);
    float ux  = g_smShooter.vx * inv, uy = g_smShooter.vy * inv;
    ImVec2 head(g_smShooter.x, g_smShooter.y);

    // fading trail, brightest at the head
    const int SEG = 6;
    for (int s = 0; s < SEG; ++s) {
        float f0 = (float)s / SEG, f1 = (float)(s + 1) / SEG;
        ImVec2 a(head.x - ux * len * f0, head.y - uy * len * f0);
        ImVec2 b(head.x - ux * len * f1, head.y - uy * len * f1);
        ImU8 alpha = (ImU8)(200.0f * k * (1.0f - f0));
        dl->AddLine(a, b, SmNeonColor(g_smShooter.hue, alpha), 2.4f * (1.0f - f0) + 0.6f);
    }
    dl->AddCircleFilled(head, 1.0f + 2.6f * k, SmNeonColor(g_smShooter.hue, 240), 10);
    dl->AddCircleFilled(head, 5.0f + 6.0f * k, SmNeonColor(g_smShooter.hue, 45), 12);
}

static void DrawStarfield()
{
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    float W = ImGui::GetIO().DisplaySize.x;
    float H = ImGui::GetIO().DisplaySize.y;
    if (W < 10.0f || H < 10.0f) return;

    float dt = ImGui::GetIO().DeltaTime;
    float t  = (float)ImGui::GetTime();

    if (!g_smStarsInit || fabsf(W - g_smW) > 1.0f || fabsf(H - g_smH) > 1.0f)
        SmInitStars(W, H);

    SmDrawNebula(dl, W, H, t);

    for (int i = 0; i < SM_STAR_COUNT; ++i) {
        SmStar& s = g_smStars[i];

        // parallax drift — deeper stars move faster
        s.y += (10.0f + 46.0f * s.z) * dt;
        s.x += (4.0f  + 14.0f * s.z) * dt;
        if (s.y > H + 4.0f) { s.y = -4.0f; s.x = (float)(rand() % 1000) / 1000.0f * W; }
        if (s.x > W + 4.0f) { s.x = -4.0f; }

        float tw     = 0.55f + 0.45f * sinf(t * s.tw + s.ph);
        float depthA = 0.35f + 0.65f * ((s.z - 0.25f) / 0.95f);
        ImU8 a = (ImU8)(255.0f * tw * depthA);
        if (a < 10) a = 10;

        dl->AddCircleFilled(ImVec2(s.x, s.y), s.r, SmNeonColor(s.hue, a), 6);

        if (s.z > 0.85f) {   // bright ones get a halo + cross flare
            dl->AddCircleFilled(ImVec2(s.x, s.y), s.r * 3.4f,
                                SmNeonColor(s.hue, (ImU8)(a * 0.16f)), 8);
            float fl = s.r * 4.0f * tw;
            ImU32 fc = SmNeonColor(s.hue, (ImU8)(a * 0.45f));
            dl->AddLine(ImVec2(s.x - fl, s.y), ImVec2(s.x + fl, s.y), fc, 1.0f);
            dl->AddLine(ImVec2(s.x, s.y - fl), ImVec2(s.x, s.y + fl), fc, 1.0f);
        }
    }

    SmUpdateShooter(W, H, dt);
    SmDrawShooter(dl);
}

// ============================================================
//  IN-WINDOW STARFIELD (drawn behind the widgets, clipped to the panel)
// ============================================================
struct SmWinStar { float fx, fy, z, r, tw, ph; int hue; };

static const int SM_WIN_STARS = 130;
static SmWinStar g_smWin[SM_WIN_STARS];
static bool g_smWinInit = false;

static void DrawWindowStars(ImDrawList* dl, const ImVec2& wp, const ImVec2& ws)
{
    if (ws.x < 10.0f || ws.y < 10.0f) return;

    float t  = (float)ImGui::GetTime();
    float dt = ImGui::GetIO().DeltaTime;

    if (!g_smWinInit) {
        for (int i = 0; i < SM_WIN_STARS; ++i) {
            g_smWin[i].fx  = (float)(rand() % 1000) / 1000.0f;
            g_smWin[i].fy  = (float)(rand() % 1000) / 1000.0f;
            g_smWin[i].z   = 0.25f + (float)(rand() % 100) / 100.0f * 0.95f;
            g_smWin[i].r   = 0.5f + g_smWin[i].z * 1.3f;
            g_smWin[i].tw  = 1.4f + (float)(rand() % 180) / 100.0f;
            g_smWin[i].ph  = (float)(rand() % 628) / 100.0f;
            g_smWin[i].hue = rand() % 4;
        }
        g_smWinInit = true;
    }

    dl->PushClipRect(wp, ImVec2(wp.x + ws.x, wp.y + ws.y), true);

    for (int i = 0; i < SM_WIN_STARS; ++i) {
        SmWinStar& s = g_smWin[i];

        s.fy += (0.010f + 0.035f * s.z) * dt;
        s.fx += (0.004f + 0.012f * s.z) * dt;
        if (s.fy > 1.0f) { s.fy -= 1.0f; s.fx = (float)(rand() % 1000) / 1000.0f; }
        if (s.fx > 1.0f) { s.fx -= 1.0f; }

        ImVec2 p(wp.x + s.fx * ws.x, wp.y + s.fy * ws.y);
        float tw = 0.5f + 0.5f * sinf(t * s.tw + s.ph);
        ImU8 a = (ImU8)(200.0f * tw * (0.40f + 0.60f * s.z));
        if (a < 6) a = 6;

        dl->AddCircleFilled(p, s.r, SmNeonColor(s.hue, a), 6);
        if (s.z > 0.80f)
            dl->AddCircleFilled(p, s.r * 3.0f, SmNeonColor(s.hue, (ImU8)(a * 0.18f)), 8);
    }

    // faint neon link lines from the cursor to nearby stars
    ImVec2 cur = ImGui::GetIO().MousePos;
    for (int i = 0; i < SM_WIN_STARS; ++i) {
        ImVec2 p(wp.x + g_smWin[i].fx * ws.x, wp.y + g_smWin[i].fy * ws.y);
        float dx = cur.x - p.x, dy = cur.y - p.y;
        float d  = sqrtf(dx * dx + dy * dy);
        if (d < 90.0f) {
            float o = 1.0f - d / 90.0f;
            dl->AddLine(cur, p, IM_COL32(0, 230, 255, (ImU8)(85.0f * o)), 1.0f);
        }
    }

    dl->PopClipRect();
}

// ============================================================
//  NEON TAB BUTTON
// ============================================================
static bool NeonTab(const char* label, bool active)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    float padX = 20.0f, h = 34.0f;
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size(label_size.x + padX * 2.0f, h);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

    ImGui::ItemSize(bb, 0.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    ImDrawList* dl = window->DrawList;
    float r = h * 0.5f;
    float t = (float)ImGui::GetTime();
    float pulse = 0.5f + 0.5f * sinf(t * 3.2f);

    if (active)
        SmGlowRect(dl, bb.Min, bb.Max, r, 46, pulse);

    ImU32 bg = active ? IM_COL32(12, 28, 50, 235)
             : hovered ? IM_COL32(10, 20, 34, 200)
                       : IM_COL32(7, 10, 20, 185);
    dl->AddRectFilled(bb.Min, bb.Max, bg, r);

    ImU32 edge = active ? IM_COL32(0, 240, 255, 255)
               : hovered ? IM_COL32(255, 60, 200, 205)
                         : IM_COL32(90, 120, 170, 150);
    dl->AddRect(bb.Min, bb.Max, edge, r, 0, active ? 2.2f : 1.4f);

    ImVec2 txt(bb.Min.x + (size.x - label_size.x) * 0.5f,
               bb.Min.y + (size.y - label_size.y) * 0.5f);
    if (active) {
        dl->AddText(ImVec2(txt.x, txt.y + 1.0f), IM_COL32(0, 235, 255, 70), label);
        dl->AddText(ImVec2(txt.x, txt.y + 2.0f), IM_COL32(0, 235, 255, 34), label);
    }
    ImU32 tc = active ? IM_COL32(190, 250, 255, 255)
             : hovered ? IM_COL32(255, 190, 245, 255)
                       : IM_COL32(150, 165, 195, 255);
    dl->AddText(txt, tc, label);

    if (active) {   // neon underline accent
        float uw = label_size.x * (0.6f + 0.4f * pulse);
        dl->AddLine(ImVec2(bb.Min.x + (size.x - uw) * 0.5f, bb.Max.y - 5.0f),
                    ImVec2(bb.Min.x + (size.x + uw) * 0.5f, bb.Max.y - 5.0f),
                    IM_COL32(255, 40, 200, 235), 2.0f);
    }

    return pressed;
}

// ============================================================
//  NEON TOGGLE
// ============================================================
void NeonToggle(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return;

    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    float h = 24.0f;
    float w = 48.0f;
    float radius = h * 0.5f;

    ImVec2 pos = window->DC.CursorPos;
    ImRect bb(pos, ImVec2(pos.x + w, pos.y + h));
    ImGui::ItemSize(bb, 0.0f);
    if (!ImGui::ItemAdd(bb, id)) return;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    static float anim = 0.0f;
    anim = ImLerp(anim, *v ? 1.0f : 0.0f, ImGui::GetIO().DeltaTime * 14.0f);

    ImDrawList* dl = window->DrawList;
    float t = (float)ImGui::GetTime();
    float pulse = 0.5f + 0.5f * sinf(t * 4.0f);

    ImU32 bg = *v ? IM_COL32(0, 200, 240, 235) : IM_COL32(18, 22, 34, 255);
    dl->AddRectFilled(bb.Min, bb.Max, bg, radius);
    dl->AddRect(bb.Min, bb.Max,
                *v ? IM_COL32(0, 240, 255, 255) : IM_COL32(70, 85, 120, 255),
                radius, 0, 2.0f);

    if (*v)
        SmGlowRect(dl, bb.Min, bb.Max, radius, 44, pulse);

    // Knob — dark core with a neon rim
    float knob_x = bb.Min.x + radius + (w - h) * anim;
    ImVec2 knob_center(knob_x, bb.Min.y + radius);
    dl->AddCircleFilled(knob_center, radius - 3.0f, IM_COL32(8, 12, 22, 255), 24);
    dl->AddCircle(knob_center, radius - 3.0f,
                  *v ? IM_COL32(0, 240, 255, 255) : IM_COL32(110, 125, 160, 255), 24, 2.0f);
    dl->AddCircleFilled(knob_center, 2.5f,
                        *v ? IM_COL32(255, 60, 210, 255) : IM_COL32(70, 80, 110, 255), 12);

    // Energy spark trailing the knob while ON
    if (*v && anim > 0.9f) {
        float wag = sinf(t * 6.0f) * 3.0f;
        ImVec2 sp(bb.Max.x - 3.0f, bb.Min.y - 1.0f);
        dl->AddLine(sp, ImVec2(sp.x + 5.0f + wag, sp.y - 7.0f), IM_COL32(0, 235, 255, 220), 2.0f);
        dl->AddLine(ImVec2(sp.x + 5.0f + wag, sp.y - 7.0f),
                    ImVec2(sp.x + 1.0f + wag, sp.y - 12.0f), IM_COL32(255, 60, 210, 220), 2.0f);
    }

    // Label
    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (h - label_size.y) * 0.5f);
    ImGui::TextColored(*v ? ImVec4(0.60f, 0.98f, 1.00f, 1.00f)
                          : ImVec4(0.72f, 0.78f, 0.88f, 1.00f), "%s", label);
}

// ============================================================
//  MOD MENU ROW (52px, rounded, neon orb icon + toggle)
// ============================================================
static bool ModRow(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiID id = window->GetID(label);
    ImVec2 pos = window->DC.CursorPos;
    float avail = ImGui::GetContentRegionAvail().x;
    if (avail < 100.0f) avail = 300.0f;
    ImVec2 size(avail, 52.0f);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(bb, 4.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    ImDrawList* dl = window->DrawList;
    float t = (float)ImGui::GetTime();
    float pulse = 0.5f + 0.5f * sinf(t * 3.0f);

    ImU32 bg = hovered ? IM_COL32(18, 30, 50, 215) : IM_COL32(9, 13, 24, 190);
    dl->AddRectFilled(bb.Min, bb.Max, bg, 26.0f);

    ImU32 edge = *v     ? IM_COL32(0, 235, 255, 235)
               : hovered ? IM_COL32(255, 60, 200, 205)
                         : IM_COL32(70, 90, 130, 150);
    dl->AddRect(bb.Min, bb.Max, edge, 26.0f, 0, *v ? 2.2f : 1.5f);
    if (*v)
        SmGlowRect(dl, bb.Min, bb.Max, 26.0f, 34, pulse);

    // Neon orb icon with a rotating arc
    ImVec2 icon_c(bb.Min.x + 30.0f, bb.Min.y + 26.0f);
    ImU32 ic = *v ? IM_COL32(0, 240, 255, 255) : IM_COL32(110, 130, 170, 255);
    dl->AddCircleFilled(icon_c, 4.5f, ic, 16);
    dl->AddCircle(icon_c, 9.0f,
                  *v ? IM_COL32(255, 40, 200, 225) : IM_COL32(70, 90, 130, 200), 24, 1.6f);
    float a0 = t * (*v ? 2.4f : 0.6f);
    dl->PathArcTo(icon_c, 13.0f, a0, a0 + 1.5f, 12);
    dl->PathStroke(*v ? IM_COL32(0, 240, 255, 205) : IM_COL32(80, 100, 140, 160), 0, 1.8f);
    if (*v)
        dl->AddCircleFilled(icon_c, 16.0f, IM_COL32(0, 220, 255, (ImU8)(26 + 20 * pulse)), 20);

    // Label
    dl->AddText(ImVec2(bb.Min.x + 55.0f, bb.Min.y + 18.0f),
                *v ? IM_COL32(195, 250, 255, 255) : IM_COL32(180, 190, 215, 255), label);

    // Right-side toggle
    float sw = 48.0f, sh = 24.0f;
    ImVec2 tpos(bb.Max.x - sw - 14.0f, bb.Min.y + (52.0f - sh) * 0.5f);
    ImU32 tbg = *v ? IM_COL32(0, 200, 240, 235) : IM_COL32(24, 28, 42, 255);
    dl->AddRectFilled(tpos, ImVec2(tpos.x + sw, tpos.y + sh), tbg, sh * 0.5f);
    dl->AddRect(tpos, ImVec2(tpos.x + sw, tpos.y + sh),
                *v ? IM_COL32(0, 240, 255, 255) : IM_COL32(70, 85, 120, 255), sh * 0.5f, 0, 1.5f);
    float knob_x = tpos.x + sh * 0.5f + (sw - sh) * (*v ? 1.0f : 0.0f);
    ImVec2 knob_c(knob_x, tpos.y + sh * 0.5f);
    dl->AddCircleFilled(knob_c, sh * 0.5f - 2.0f, IM_COL32(8, 12, 22, 255), 20);
    dl->AddCircle(knob_c, sh * 0.5f - 2.0f,
                  *v ? IM_COL32(0, 240, 255, 255) : IM_COL32(110, 125, 160, 255), 20, 1.6f);
    dl->AddCircleFilled(knob_c, 2.5f,
                        *v ? IM_COL32(255, 60, 210, 255) : IM_COL32(70, 80, 110, 255), 12);

    return pressed;
}

// ============================================================
//  NEON CLOSE BUTTON
// ============================================================
static bool NeonCloseButton(const char* label)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiID id = window->GetID(label);
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size(140.0f, 44.0f);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(bb, 4.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    ImDrawList* dl = window->DrawList;
    float pulse = 0.5f + 0.5f * sinf((float)ImGui::GetTime() * 3.4f);

    ImU32 bg = hovered ? IM_COL32(62, 0, 32, 235) : IM_COL32(32, 0, 20, 210);
    dl->AddRectFilled(bb.Min, bb.Max, bg, 22.0f);

    for (int g = 2; g >= 1; --g)
        dl->AddRect(ImVec2(bb.Min.x - g * 2.5f, bb.Min.y - g * 2.5f),
                    ImVec2(bb.Max.x + g * 2.5f, bb.Max.y + g * 2.5f),
                    IM_COL32(255, 40, 190, (ImU8)(24 - g * 8 + 12 * pulse)),
                    22.0f + g * 2.5f, 0, 1.5f);

    dl->AddRect(bb.Min, bb.Max,
                hovered ? IM_COL32(255, 90, 215, 255) : IM_COL32(255, 40, 190, 220),
                22.0f, 0, 2.4f);

    ImVec2 ts = ImGui::CalcTextSize(label);
    ImVec2 tp(bb.Min.x + (size.x - ts.x) * 0.5f, bb.Min.y + (size.y - ts.y) * 0.5f);
    dl->AddText(ImVec2(tp.x, tp.y + 1.0f), IM_COL32(255, 40, 190, 90), label);
    dl->AddText(tp, IM_COL32(255, 235, 250, 255), label);
    return pressed;
}

// ============================================================
//  LEGACY TOGGLE (kept, used for Speed Timer)
// ============================================================
void Zxcmukku(const char* label, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 24.0f;
    float width = 48.0f;
    float radius = height * 0.50f;
    ImGuiID id = ImGui::GetID(label);

    ImGui::InvisibleButton(label, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *v = !*v;
    float lastAnimPos = ImGui::GetStateStorage()->GetFloat(id, *v ? 1.0f : 0.0f);
    float animPos = ImLerp(lastAnimPos, *v ? 1.0f : 0.0f, ImGui::GetIO().DeltaTime * 12.0f);
    ImGui::GetStateStorage()->SetFloat(id, animPos);

    bool hovered = ImGui::IsItemHovered();

    ImVec4 col_off = ImVec4(0.070f, 0.086f, 0.133f, 1.0f); // deep navy
    ImVec4 col_on  = ImVec4(0.000f, 0.860f, 1.000f, 1.0f); // neon cyan

    if (hovered) {
        col_off.x += 0.05f; col_off.y += 0.05f; col_off.z += 0.05f;
    }

    ImU32 bg_col = ImGui::GetColorU32(ImLerp(col_off, col_on, animPos));
    ImU32 circle_col = IM_COL32(255, 255, 255, 255);
    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), bg_col, radius);
    draw_list->AddRect(p, ImVec2(p.x + width, p.y + height),
                       IM_COL32(0, 240, 255, 255), radius, 0, 1.5f);
    float knob_radius = radius - 3.0f;
    float start_x = p.x + radius;
    float end_x = p.x + width - radius;
    float knob_x = ImLerp(start_x, end_x, animPos);
    draw_list->AddCircleFilled(ImVec2(knob_x, p.y + radius), knob_radius + 1.0f,
                               IM_COL32(0, 0, 0, 50));
    draw_list->AddCircleFilled(ImVec2(knob_x, p.y + radius), knob_radius, circle_col);
    // Neon core dot
    draw_list->AddCircleFilled(ImVec2(knob_x + 3.0f, p.y + radius + 1.0f), 2.5f,
                               IM_COL32(255, 60, 210, 235), 12);

    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (height / 4));
    ImGui::Text("%s", label);
}

// ============================================================
//  BYPASS STUBS (kept from original)
// ============================================================
void(*Bypass1)(void* _this);
void _Bypass1(void* _this) { return; }

void(*Bypass2)(void* _this);
void _Bypass2(void* _this) { return; }

void (*BYPAS)() = 0;
void _BYPAS(void* unk) { return; }

// ============================================================
//  IL2CPP / MAIN
// ============================================================
uintptr_t il2cpp_base = 0;
void *getRealAddr(ulong offset) {
    return reinterpret_cast<void*>(il2cpp_base + offset);
};

namespace Settings {
    static int Tab = 1;
}

bool clearMousePos = true;
bool initImGui = false;

// ============================================================
//  HOOK: eglSwapBuffers (MAIN UI)
// ============================================================
inline EGLBoolean (*old_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);
inline EGLBoolean hook_eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
    eglQuerySurface(dpy, surface, EGL_WIDTH, &g_GlWidth);
    eglQuerySurface(dpy, surface, EGL_HEIGHT, &g_GlHeight);

    if (!g_IsSetup) {
        prevWidth = g_GlWidth;
        prevHeight = g_GlHeight;
        SetupImgui();
        g_IsSetup = true;
    }

    static bool isTouching = false;
    static float touchStartTime = 0.0f;

    // Apply Shadow Modz dark-neon theme every frame
    ShadowModzTheme();

    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(g_GlWidth, g_GlHeight);
    ImGui::NewFrame();

    // ---- Touch input ----
    int touchCount = ((int (*)())(Class_Input__get_touchCount))();
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields(*)(int))(Class_Input__GetTouch))(0);
        float reverseY = io.DisplaySize.y - touch.m_Position.fields.y;
        io.MousePos = ImVec2(touch.m_Position.fields.x, reverseY);
        if (!isTouching) touchStartTime = ImGui::GetTime();
        io.MouseDown[0] = true;
        isTouching = true;
    } else {
        if (isTouching && (ImGui::GetTime() - touchStartTime < 0.06f)) {
            io.MouseDown[0] = true;
        } else {
            UpdateSpeedhack();
            io.MouseDown[0] = false;
            isTouching = false;
        }
    }

    // ---- ESP ----
    DrawESP(g_GlWidth, g_GlHeight);

    // ---- Background: moving neon starfield ----
    DrawStarfield();

    // ---- Speed Hack floating mini window ----
    {
        ImVec2 screenCenter = ImGui::GetMainViewport()->GetCenter();
        ImVec2 screenSize   = ImGui::GetMainViewport()->Size;
        ImVec2 pos(screenCenter.x, screenCenter.y + screenSize.y * 0.30f);
        ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver, ImVec2(0.5f, 0.5f));
        ImGui::SetNextWindowBgAlpha(0.0f);
        if (ImGui::Begin("Speed Hack", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoSavedSettings))
        {
            NeonToggle("SPEED TIMER", &SpeedHack);
        }
        ImGui::End();
    }

    // ---- Main Shadow Modz menu ----
    ImGui::SetNextWindowSize(ImVec2((float)g_GlWidth * 0.62f,
                                    (float)g_GlHeight * 0.72f),
                             ImGuiCond_Once);
    if (ImGui::Begin("SHADOW MODZ", nullptr,
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoCollapse))
    {
        // ---- In-window moving starfield (drawn behind the widgets) ----
        DrawWindowStars(ImGui::GetWindowDrawList(),
                        ImGui::GetCursorScreenPos(),
                        ImGui::GetContentRegionAvail());

        static int activeTab = 0;

        // Tabs — neon pill style
        if (NeonTab("AIM",   activeTab == 0)) activeTab = 0;
        ImGui::SameLine();
        if (NeonTab("ESP",   activeTab == 1)) activeTab = 1;
        ImGui::SameLine();
        if (NeonTab("CATCH", activeTab == 2)) activeTab = 2;
        ImGui::SameLine();
        if (NeonTab("MISC",  activeTab == 3)) activeTab = 3;

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // ===== AIM =====
        if (activeTab == 0) {
            ModRow("Enable AimBot", &Aimbot);
            ImGui::Combo("##AimDir", &AimWhen, dir, IM_ARRAYSIZE(dir));
            ImGui::SliderFloat("FOV",      &Fov_Aim, 0.0f, 500.0f,  "%.f");
            ImGui::SliderFloat("Distance", &Aimdis,  0.0f, 1000.0f, "%.f");
        }
        // ===== ESP =====
        else if (activeTab == 1) {
            ModRow("Enable ESP", &Enable);
            ModRow("ESP LINE",     &Config.ESP.Line);
            ImGui::SameLine();
            ImGui::ColorEdit4("##LineColor", (float*)&colorLine,
                              ImGuiColorEditFlags_NoInputs);
            ModRow("ESP BOX",      &Config.ESP.Box);
            ImGui::SameLine();
            ImGui::ColorEdit4("##BoxColor",  (float*)&colorBox,
                              ImGuiColorEditFlags_NoInputs);
            ModRow("ESP NAME",     &Config.ESP.Distancia);
            ModRow("ESP DISTANCE", &Config.ESP.Jarak);
            ModRow("ESP HEALTH",   &Config.ESP.Health);
        }
        // ===== CATCH =====
        else if (activeTab == 2) {
            ModRow("Sniper Fast", &SniperFast);
            ModRow("Reset Acc",   &Reset);
        }
        // ===== MISC =====
        else {
            ModRow("Speedhack", &SpeedHack);
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(0.00f, 0.92f, 1.00f, 1.0f), "</> Dev: SHADOW MODZ");
            ImGui::TextColored(ImVec4(1.00f, 0.35f, 0.85f, 1.0f), "TELEGRAM: @ShadowModz");
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Close button centered
        float ww = ImGui::GetWindowWidth();
        ImGui::SetCursorPosX((ww - 140.0f) * 0.5f);
        if (NeonCloseButton("CLOSE")) {
            // Apna close logic yahan — e.g. ShowMenu = false;
        }
    }
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    return old_eglSwapBuffers(dpy, surface);
}

// ============================================================
//  STARTUP
// ============================================================
typedef unsigned long DWORD;
static uintptr_t libBase;

inline void StartGUI() {
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (ptr_eglSwapBuffer != nullptr) {
        DobbyHook((void *)ptr_eglSwapBuffer, (void *)hook_eglSwapBuffers,
                  (void **)&old_eglSwapBuffers);
        LOGD("GUI started successfully");
    }
}

void hack_thread() {
    sleep(5);
    pid_t pid = getpid();
    LOGD("Hack Thread initiated for PID: %i", pid);

    do {
        il2cpp_base = get_module_base(pid, "libil2cpp.so");
        sleep(1);
    } while (il2cpp_base == 0);

    LOGD("libil2cpp.so found at address: 0x%" PRIxPTR, il2cpp_base);
    Il2CppAttach();

    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),
                                    OBFUSCATE("COW"),
                                    OBFUSCATE("GameConfig"),
                                    OBFUSCATE("get_ResetGuest"), 0),
              (void *) ResetGuest, (void **) &_ResetGuest);

    DobbyHook(Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),
                                    OBFUSCATE("COW.GamePlay"),
                                    OBFUSCATE("Weapon"),
                                    OBFUSCATE("IsContinuousGen"), 0),
              (void *) IsContinuousGen, (void **) &_IsContinuousGen);

    StartGUI();
}
