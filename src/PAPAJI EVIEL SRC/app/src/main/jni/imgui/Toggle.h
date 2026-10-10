#pragma once
#include "imgui_internal.h"

void Toggle(const char* str_id, bool* v)
{
    ImVec2 p = ImGui::GetCursorScreenPos();
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    float height = 30.0f; // Set a custom height (reduce the size here)
    float width = height * 1.55f; // Width remains proportional to the height
    float radius = height * 0.50f;

    ImGui::InvisibleButton(str_id, ImVec2(width, height));
    if (ImGui::IsItemClicked())
        *v = !*v;

    float t = *v ? 1.0f : 0.0f;

    ImGuiContext& g = *GImGui;
    float ANIM_SPEED = 0.08f;
    if (g.LastActiveId == g.CurrentWindow->GetID(str_id))
    {
        float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
        t = *v ? (t_anim) : (1.0f - t_anim);
    }

    ImU32 col_bg = *v
        ? ImGui::GetColorU32(ImVec4(0.56f, 0.83f, 0.26f, 1.0f)) // Green when ON
     /*   ImGui::GetColorU32(ImVec4(0.0f, 0.7f, 1.0f, 1.0f));    */
            : ImGui::GetColorU32(ImVec4(1.0f, 0.0f, 0.0f, 1.0f));  // Real Red when OFF
        
        

    draw_list->AddRectFilled(p, ImVec2(p.x + width, p.y + height), col_bg, height * 0.5f);
    draw_list->AddCircleFilled(ImVec2(p.x + radius + t * (width - radius * 2.0f), p.y + radius), radius - 1.5f, IM_COL32(255, 255, 255, 255));

    // Display the toggle label without ON/OFF text
    ImGui::SameLine();
    ImGui::Text("%s", str_id);
}