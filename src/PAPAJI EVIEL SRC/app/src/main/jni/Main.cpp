#include <android/log.h>
#include <unistd.h>
#include <thread>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <cstdio>

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
//  SHADOW MODZ — RED / BLACK THEME (Hollow style)
// ============================================================
static void ShadowModzTheme()
{
    ImGuiStyle &style = ImGui::GetStyle();
    ImVec4 *colors = style.Colors;

    // Window background — pure black
    colors[ImGuiCol_WindowBg]        = ImVec4(0.016f, 0.016f, 0.016f, 0.97f);
    colors[ImGuiCol_ChildBg]         = ImVec4(0.030f, 0.010f, 0.010f, 0.80f);
    colors[ImGuiCol_PopupBg]         = ImVec4(0.030f, 0.010f, 0.010f, 0.98f);
    // Border — red
    colors[ImGuiCol_Border]          = ImVec4(0.900f, 0.050f, 0.050f, 0.90f);
    colors[ImGuiCol_BorderShadow]    = ImVec4(0.400f, 0.000f, 0.000f, 0.30f);
    colors[ImGuiCol_FrameBg]         = ImVec4(0.060f, 0.015f, 0.015f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]  = ImVec4(0.300f, 0.030f, 0.030f, 1.00f);
    colors[ImGuiCol_FrameBgActive]   = ImVec4(0.550f, 0.050f, 0.050f, 1.00f);
    colors[ImGuiCol_TitleBg]         = ImVec4(0.016f, 0.016f, 0.016f, 1.00f);
    colors[ImGuiCol_TitleBgActive]   = ImVec4(0.100f, 0.010f, 0.010f, 1.00f);
    colors[ImGuiCol_TitleBgCollapsed]= ImVec4(0.016f, 0.016f, 0.016f, 0.70f);
    colors[ImGuiCol_ScrollbarBg]     = ImVec4(0.016f, 0.016f, 0.016f, 1.00f);
    colors[ImGuiCol_ScrollbarGrab]   = ImVec4(0.600f, 0.030f, 0.030f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.850f, 0.050f, 0.050f, 1.00f);
    colors[ImGuiCol_ScrollbarGrabActive]  = ImVec4(1.000f, 0.100f, 0.100f, 1.00f);
    colors[ImGuiCol_CheckMark]       = ImVec4(1.000f, 0.100f, 0.100f, 1.00f);
    colors[ImGuiCol_SliderGrab]      = ImVec4(0.900f, 0.050f, 0.050f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]= ImVec4(1.000f, 0.150f, 0.150f, 1.00f);
    colors[ImGuiCol_Button]          = ImVec4(0.550f, 0.020f, 0.020f, 1.00f);
    colors[ImGuiCol_ButtonHovered]   = ImVec4(0.800f, 0.050f, 0.050f, 1.00f);
    colors[ImGuiCol_ButtonActive]    = ImVec4(1.000f, 0.100f, 0.100f, 1.00f);
    colors[ImGuiCol_Header]          = ImVec4(0.450f, 0.020f, 0.020f, 0.80f);
    colors[ImGuiCol_HeaderHovered]   = ImVec4(0.650f, 0.040f, 0.040f, 0.90f);
    colors[ImGuiCol_HeaderActive]    = ImVec4(0.850f, 0.060f, 0.060f, 1.00f);
    colors[ImGuiCol_Separator]       = ImVec4(0.800f, 0.050f, 0.050f, 0.50f);
    colors[ImGuiCol_SeparatorHovered]= ImVec4(1.000f, 0.100f, 0.100f, 0.90f);
    colors[ImGuiCol_SeparatorActive] = ImVec4(1.000f, 0.100f, 0.100f, 1.00f);
    colors[ImGuiCol_Text]            = ImVec4(1.000f, 0.130f, 0.130f, 1.00f);
    colors[ImGuiCol_TextDisabled]    = ImVec4(0.450f, 0.200f, 0.200f, 1.00f);
    colors[ImGuiCol_TextSelectedBg]  = ImVec4(0.800f, 0.050f, 0.050f, 0.50f);
    colors[ImGuiCol_Tab]             = ImVec4(0.050f, 0.015f, 0.015f, 1.00f);
    colors[ImGuiCol_TabHovered]      = ImVec4(0.600f, 0.040f, 0.040f, 1.00f);
    colors[ImGuiCol_TabActive]       = ImVec4(0.850f, 0.060f, 0.060f, 1.00f);

    style.WindowRounding    = 10.0f;
    style.ChildRounding     = 10.0f;
    style.FrameRounding     = 10.0f;
    style.PopupRounding     = 10.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding      = 8.0f;
    style.TabRounding       = 8.0f;
    style.WindowBorderSize  = 2.0f;   // red edge
    style.ChildBorderSize   = 2.0f;
    style.FrameBorderSize   = 2.0f;
    style.PopupBorderSize   = 2.0f;
    style.WindowPadding     = ImVec2(12.0f, 12.0f);
    style.FramePadding      = ImVec2(10.0f, 6.0f);
    style.ItemSpacing       = ImVec2(10.0f, 8.0f);
    style.ItemInnerSpacing  = ImVec2(8.0f, 6.0f);
    style.ScrollbarSize     = 10.0f;
    style.GrabMinSize       = 14.0f;
}

// ============================================================
//  RED COLOUR HELPERS
// ============================================================
// hue: 0 = white, 1 = bright red, 2 = deep red, 3 = ember orange
static ImU32 SmNeonColor(int hue, ImU8 a)
{
    switch (hue % 4) {
        case 0:  return IM_COL32(255, 255, 255, a);
        case 1:  return IM_COL32(255,  60,  60, a);
        case 2:  return IM_COL32(220,  20,  20, a);
        default: return IM_COL32(255, 120,  70, a);
    }
}

static void SmGlowRect(ImDrawList* dl, const ImVec2& mn, const ImVec2& mx,
                       float rounding, ImU8 baseA, float pulse)
{
    for (int g = 3; g >= 1; --g) {
        ImU8 a = (ImU8)(baseA - g * 9 + (ImU8)(14.0f * pulse));
        dl->AddRect(ImVec2(mn.x - g * 2.0f, mn.y - g * 2.0f),
                    ImVec2(mx.x + g * 2.0f, mx.y + g * 2.0f),
                    IM_COL32(255, 30, 30, a), rounding + g * 2.0f, 0, 1.5f);
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
        g_smStars[i].z   = 0.25f + (float)(rand() % 100) / 100.0f * 0.95f;
        g_smStars[i].x   = (float)(rand() % 1000) / 1000.0f * W;
        g_smStars[i].y   = (float)(rand() % 1000) / 1000.0f * H;
        g_smStars[i].r   = 0.6f + g_smStars[i].z * 1.8f;
        g_smStars[i].tw  = 1.2f + (float)(rand() % 200) / 100.0f;
        g_smStars[i].ph  = (float)(rand() % 628) / 100.0f;
        g_smStars[i].hue = rand() % 4;
    }
    g_smW = W; g_smH = H; g_smStarsInit = true;
}

static void SmDrawNebula(ImDrawList* dl, float W, float H, float t)
{
    const int nr[3] = { 160, 120,  90 };
    const int ng[3] = {  10,   0,   0 };
    const int nb[3] = {  15,   5,   0 };
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
        g_smShooter.hue     = 1 + rand() % 2;
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

    const int SEG = 6;
    for (int s = 0; s < SEG; ++s) {
        float f0 = (float)s / SEG, f1 = (float)(s + 1) / SEG;
        ImVec2 a(head.x - ux * len * f0, head.y - uy * len * f1 * 0.0f - uy * len * f0 * 0.0f);
        a = ImVec2(head.x - ux * len * f0, head.y - uy * len * f0);
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

        s.y += (10.0f + 46.0f * s.z) * dt;
        s.x += (4.0f  + 14.0f * s.z) * dt;
        if (s.y > H + 4.0f) { s.y = -4.0f; s.x = (float)(rand() % 1000) / 1000.0f * W; }
        if (s.x > W + 4.0f) { s.x = -4.0f; }

        float tw     = 0.55f + 0.45f * sinf(t * s.tw + s.ph);
        float depthA = 0.35f + 0.65f * ((s.z - 0.25f) / 0.95f);
        ImU8 a = (ImU8)(255.0f * tw * depthA);
        if (a < 10) a = 10;

        dl->AddCircleFilled(ImVec2(s.x, s.y), s.r, SmNeonColor(s.hue, a), 6);

        if (s.z > 0.85f) {
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
        ImU8 a = (ImU8)(190.0f * tw * (0.40f + 0.60f * s.z));
        if (a < 6) a = 6;

        dl->AddCircleFilled(p, s.r, SmNeonColor(s.hue, a), 6);
        if (s.z > 0.80f)
            dl->AddCircleFilled(p, s.r * 3.0f, SmNeonColor(s.hue, (ImU8)(a * 0.18f)), 8);
    }

    // faint red link lines from the cursor to nearby stars
    ImVec2 cur = ImGui::GetIO().MousePos;
    for (int i = 0; i < SM_WIN_STARS; ++i) {
        ImVec2 p(wp.x + g_smWin[i].fx * ws.x, wp.y + g_smWin[i].fy * ws.y);
        float dx = cur.x - p.x, dy = cur.y - p.y;
        float d  = sqrtf(dx * dx + dy * dy);
        if (d < 90.0f) {
            float o = 1.0f - d / 90.0f;
            dl->AddLine(cur, p, IM_COL32(255, 40, 40, (ImU8)(85.0f * o)), 1.0f);
        }
    }

    dl->PopClipRect();
}

// ============================================================
//  HEADER BANNER (like the reference shot)
// ============================================================
static void RedHeader()
{
    float w = ImGui::GetContentRegionAvail().x;

    const char* title = "MODDED BY SHADOW MODZ";
    ImVec2 ts = ImGui::CalcTextSize(title);
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* dl = ImGui::GetWindowDrawList();

    // faux-bold red title, centred
    ImVec2 tp(p.x + (w - ts.x) * 0.5f, p.y);
    dl->AddText(ImVec2(tp.x + 1.0f, tp.y), IM_COL32(120, 0, 0, 255), title);
    dl->AddText(tp, IM_COL32(255, 30, 30, 255), title);
    ImGui::Dummy(ImVec2(w, ts.y + 4.0f));

    // subscribe line: red "Subscribe" + white rest
    const char* a = "Subscribe";
    const char* b = "  YouTube | Shadow Modz";
    ImVec2 as = ImGui::CalcTextSize(a);
    ImVec2 bs = ImGui::CalcTextSize(b);
    float sx = p.x + (w - (as.x + bs.x)) * 0.5f;
    dl->AddText(ImVec2(sx, tp.y + ts.y + 4.0f), IM_COL32(255, 30, 30, 255), a);
    dl->AddText(ImVec2(sx + as.x, tp.y + ts.y + 4.0f), IM_COL32(255, 255, 255, 255), b);
    ImGui::Dummy(ImVec2(w, bs.y + 8.0f));
}

// ============================================================
//  RED TAB BAR BUTTON
// ============================================================
static bool NeonTab(const char* label, bool active)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    float padX = 18.0f, h = 32.0f;
    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size(label_size.x + padX * 2.0f, h);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));

    ImGui::ItemSize(bb, 0.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);

    ImDrawList* dl = window->DrawList;
    float r = 6.0f;

    ImU32 bg = active ? IM_COL32(210, 10, 10, 255)
             : hovered ? IM_COL32(60, 5, 5, 235)
                       : IM_COL32(20, 2, 2, 220);
    dl->AddRectFilled(bb.Min, bb.Max, bg, r);
    dl->AddRect(bb.Min, bb.Max,
                active ? IM_COL32(255, 60, 60, 255) : IM_COL32(200, 20, 20, 200),
                r, 0, active ? 2.2f : 1.5f);

    ImVec2 txt(bb.Min.x + (size.x - label_size.x) * 0.5f,
               bb.Min.y + (size.y - label_size.y) * 0.5f);
    dl->AddText(txt, active ? IM_COL32(255, 255, 255, 255)
                            : IM_COL32(255, 60, 60, 255), label);
    return pressed;
}

// ============================================================
//  RED TOGGLE (kept for the floating SPEED TIMER row)
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

    ImU32 bg = *v ? IM_COL32(210, 10, 10, 255) : IM_COL32(30, 30, 30, 255);
    dl->AddRectFilled(bb.Min, bb.Max, bg, radius);
    dl->AddRect(bb.Min, bb.Max,
                *v ? IM_COL32(255, 60, 60, 255) : IM_COL32(120, 120, 120, 255),
                radius, 0, 2.0f);

    float knob_x = bb.Min.x + radius + (w - h) * anim;
    ImVec2 knob_center(knob_x, bb.Min.y + radius);
    dl->AddCircleFilled(knob_center, radius - 3.0f, IM_COL32(255, 255, 255, 255), 24);

    ImGui::SameLine();
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (h - label_size.y) * 0.5f);
    ImGui::TextColored(*v ? ImVec4(1.00f, 0.25f, 0.25f, 1.00f)
                          : ImVec4(0.85f, 0.85f, 0.85f, 1.00f), "%s", label);
}

// ============================================================
//  MOD MENU ROW — outlined rounded button "NAME: ON/OFF" (reference style)
// ============================================================
static bool ModRow(const char* label, bool* v)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiID id = window->GetID(label);
    ImVec2 pos = window->DC.CursorPos;
    float avail = ImGui::GetContentRegionAvail().x;
    if (avail < 100.0f) avail = 300.0f;
    ImVec2 size(avail, 46.0f);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(bb, 4.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    if (pressed) *v = !*v;

    ImDrawList* dl = window->DrawList;

    ImU32 bg = *v     ? IM_COL32(60, 4, 4, 235)
             : hovered ? IM_COL32(35, 2, 2, 220)
                       : IM_COL32(12, 1, 1, 210);
    dl->AddRectFilled(bb.Min, bb.Max, bg, 23.0f);
    dl->AddRect(bb.Min, bb.Max,
                *v ? IM_COL32(255, 50, 50, 255) : IM_COL32(200, 20, 20, 220),
                23.0f, 0, 2.0f);

    char buf[128];
    snprintf(buf, sizeof(buf), "%s: %s", label, *v ? "ON" : "OFF");
    ImVec2 ts = ImGui::CalcTextSize(buf);
    ImVec2 tp(bb.Min.x + (size.x - ts.x) * 0.5f, bb.Min.y + (size.y - ts.y) * 0.5f);
    dl->AddText(tp, *v ? IM_COL32(255, 80, 80, 255) : IM_COL32(230, 30, 30, 255), buf);

    return pressed;
}

// ============================================================
//  BOTTOM BUTTONS — black box, white text (HIDE / CLOSE)
// ============================================================
static bool NeonCloseButton(const char* label, float width = -1.0f)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems) return false;

    ImGuiID id = window->GetID(label);
    ImVec2 pos = window->DC.CursorPos;
    float wdt = width > 0.0f ? width : ImGui::GetContentRegionAvail().x;
    ImVec2 size(wdt, 44.0f);
    ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
    ImGui::ItemSize(bb, 4.0f);
    if (!ImGui::ItemAdd(bb, id)) return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held);
    ImDrawList* dl = window->DrawList;

    dl->AddRectFilled(bb.Min, bb.Max,
                      hovered ? IM_COL32(40, 4, 4, 255) : IM_COL32(8, 8, 8, 250), 6.0f);
    dl->AddRect(bb.Min, bb.Max, IM_COL32(200, 20, 20, 220), 6.0f, 0, 2.0f);

    ImVec2 ts = ImGui::CalcTextSize(label);
    dl->AddText(ImVec2(bb.Min.x + (size.x - ts.x) * 0.5f,
                       bb.Min.y + (size.y - ts.y) * 0.5f),
                IM_COL32(255, 255, 255, 255), label);
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

static bool g_MenuHidden = false;

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

    // ---- Touch input (guarded: never call an unresolved il2cpp method) ----
    static uintptr_t s_touchCountFn = 0, s_getTouchFn = 0;
    static bool s_touchResolved = false;
    if (!s_touchResolved && g_il2cppReady) {
        s_touchCountFn = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"),
                        OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"), 0);
        s_getTouchFn   = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"),
                        OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1);
        s_touchResolved = (s_touchCountFn != 0 && s_getTouchFn != 0);
    }
    int touchCount = s_touchResolved ? ((int (*)())s_touchCountFn)() : 0;
    if (touchCount > 0) {
        UnityEngine_Touch_Fields touch = ((UnityEngine_Touch_Fields(*)(int))s_getTouchFn)(0);
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

    if (g_MenuHidden) {
        ImGui::SetNextWindowPos(ImVec2(20.0f, 20.0f), ImGuiCond_FirstUseEver);
        ImGui::SetNextWindowBgAlpha(0.0f);
        if (ImGui::Begin("##ShadowFloat", nullptr,
            ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_AlwaysAutoResize |
            ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings))
        {
            if (NeonCloseButton("MOD", 90.0f)) g_MenuHidden = false;
        }
        ImGui::End();
    }
    if (!g_MenuHidden) {
    // ---- Main Shadow Modz menu ----
    ImGui::SetNextWindowSize(ImVec2((float)g_GlWidth * 0.62f,
                                    (float)g_GlHeight * 0.72f),
                             ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(),
                            ImGuiCond_Always, ImVec2(0.5f, 0.5f));
    if (ImGui::Begin("SHADOW MODZ", nullptr,
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoCollapse))
    {
        DrawWindowStars(ImGui::GetWindowDrawList(),
                        ImGui::GetCursorScreenPos(),
                        ImGui::GetContentRegionAvail());

        RedHeader();

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

        // HIDE / CLOSE bottom buttons
        float w2 = (ImGui::GetContentRegionAvail().x - 12.0f) * 0.5f;
        if (NeonCloseButton("HIDE", w2)) g_MenuHidden = true;
        ImGui::SameLine(0.0f, 12.0f);
        if (NeonCloseButton("CLOSE", w2)) g_MenuHidden = true;
    }
    ImGui::End();
    } // if (!g_MenuHidden)

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
    void *ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib64/libEGL.so", "eglSwapBuffers");
    if (ptr_eglSwapBuffer == nullptr)
        ptr_eglSwapBuffer = DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers");
    if (ptr_eglSwapBuffer == nullptr) {
        void *h = dlopen("libEGL.so", RTLD_NOW);
        if (h) ptr_eglSwapBuffer = dlsym(h, "eglSwapBuffers");
    }
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

    int waits = 0;
    do {
        il2cpp_base = get_module_base(pid, "libil2cpp.so");
        if (il2cpp_base == 0) sleep(1);
    } while (il2cpp_base == 0 && ++waits < 30);

    if (il2cpp_base != 0) {
        LOGD("libil2cpp.so found at address: 0x%" PRIxPTR, il2cpp_base);
        Il2CppAttach();
        if (g_il2cppReady) {
            uintptr_t off1 = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),
                                        OBFUSCATE("COW"), OBFUSCATE("GameConfig"),
                                        OBFUSCATE("get_ResetGuest"), 0);
            if (off1) DobbyHook((void *)off1, (void *)ResetGuest, (void **)&_ResetGuest);
            uintptr_t off2 = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"),
                                        OBFUSCATE("COW.GamePlay"), OBFUSCATE("Weapon"),
                                        OBFUSCATE("IsContinuousGen"), 0);
            if (off2) DobbyHook((void *)off2, (void *)IsContinuousGen, (void **)&_IsContinuousGen);
            uintptr_t offT = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"),
                                        OBFUSCATE("UnityEngine"), OBFUSCATE("Input"),
                                        OBFUSCATE("get_touchCount"), 0);
            uintptr_t offC = (uintptr_t)Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"),
                                        OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"),
                                        OBFUSCATE("get_main"), 0);
            g_GameReady = (off1 && off2 && offT && offC);
        }
    } else {
        LOGD("libil2cpp.so not found - running menu-only mode");
    }
    LOGD("game-ready=%d", (int)g_GameReady);
    StartGUI();
}
