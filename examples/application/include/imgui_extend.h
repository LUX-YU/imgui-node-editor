#pragma once
#include <imgui.h>

namespace ImGui
{
    void          BeginHorizontal(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void          BeginHorizontal(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void          BeginHorizontal(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    void          EndHorizontal();
    void          BeginVertical(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void          BeginVertical(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    void          BeginVertical(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    void          EndVertical();
    void          Spring(float weight = 1.0f, float spacing = -1.0f);
    void          SuspendLayout();
    void          ResumeLayout();
}