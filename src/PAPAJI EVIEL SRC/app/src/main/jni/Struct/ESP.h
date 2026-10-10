
/*
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

*/


#pragma once

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <Il2Cpp.h>
#include <Tools.h>
#include <Vector3.hpp>
#include <Color.h>
#include <Struct/main.h>
#include "obfuscate.h"
#include "Unity/unity.h"
#include "Class.h"
#include "Rect.h"
inline static int g_GlHeight, g_GlWidth;
#include "Bools.h"
bool SpeedHack = false;
bool Reset = false;
#include <math.h>
#include <stdio.h>
typedef char PACKAGENAME;
bool SniperFast = false;

template <typename T>
struct UnityArray {
    void* klass;
    void* monitor;
    void* bounds;
    int max_length;
    T vector[64]; 
};




struct DictionaryEntry {
    int hashCode;
    int next;
    void* key;
    void* value;
};

struct MyDictionary {
    void* klass;
    void* monitor;
    void* buckets;
    UnityArray<DictionaryEntry>* entries;
    int count;
};

struct sColor {
        
        float line[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        float box[4] = {45 / 255.0f, 180 / 255.0f, 45 / 255.0f, 255 / 255.0f};
        
    };
    
    sColor Color;
   
   
bool isOutsideScreen(ImVec2 pos, ImVec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

ImVec2 pushToScreenBorder(ImVec2 Pos, ImVec2 screen, int offset) {
    int x = (int) Pos.x;
    int y = (int) Pos.y;
    
    if (Pos.y < 0) {
        y = -offset;
    }
    
    if (Pos.x > screen.x) {
        x = (int) screen.x + offset;
    }
    
    if (Pos.y > screen.y) {
        y = (int) screen.y + offset;
    }
    
    if (Pos.x < 0) {
        x = -offset;
    }
    return ImVec2(x, y);
}

static float tm = 127 / 255.f;

void DrawCircleHealth(ImVec2 position, int health, int max_health, float radius) {
    float a_max = ((3.14159265359f * 2.0f));
    ImU32 healthColor = IM_COL32(45, 180, 45, 255);
    if (health <= (max_health * 0.6)) {
        healthColor = IM_COL32(180, 180, 45, 255);
    }
    if (health < (max_health * 0.3)) {
        healthColor = IM_COL32(180, 45, 45, 255);
    }
    ImGui::GetForegroundDrawList()->PathArcTo(position, radius, (-(a_max / 4.0f)) + (a_max / max_health) * (max_health - health), a_max - (a_max / 4.0f));
    ImGui::GetForegroundDrawList()->PathStroke(healthColor, ImDrawFlags_None, 4);
}



void drawText2(int x, int y, long color, const char *str, float size) {
        ImGui::GetBackgroundDrawList()->AddText(NULL, size, ImVec2(x, y), color, str);
    }


void DrawRectFilled(int x, int y, int w, int h, ImColor color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h),
                                               color, 0, 0);
}


void DrawRectFilledHealth(int x, int y, int w, int h, ImVec4 color) {
    ImGui::GetBackgroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h),
                                               ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}


void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int color, int T) {
    ImGui::GetBackgroundDrawList()->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3),
                                                   color);
}
bool IsVisible(void * player){
    if(player != NULL) {
        void *hitObj = NULL;
        

        
        Vector3 cameraLocation = Transform_GetPosition(Component_GetTransform(Camera_main()));
        Vector3 headLocation = Transform_GetPosition(Component_GetTransform(Player_GetHeadCollider(player)));
            return !Physics_Raycast(cameraLocation, headLocation, 12, &hitObj);
    }
    return false;
}


void DrawHealths(Rect box, float entityHealth, float maxHealth, int TeamID, const char* name, long color) {
    float x = box.x - (140 - box.w) / 2;
    float y = box.y;
    char dis[20];
    // sprintf(dis, "%0.fM", d);

    char TeamText[20];
    sprintf(TeamText, "%d", (int)TeamID);
    ImVec4 HPColor = ImVec4{1, 1, 0, 127 / 255.f}; // Màu mặc định cho máu

    if (entityHealth < maxHealth) {
        float healthPercentage = entityHealth / maxHealth;

        if (healthPercentage < 0.3f) {
            HPColor = ImVec4{0.5f, 0.0f, 0.0f, 127 / 255.f}; // Màu đỏ cho máu thấp
        } else if (healthPercentage < 0.6f) {
            HPColor = ImVec4{1, 0, 0, 127 / 255.f}; // Màu cam cho máu trung bình
        }
    }

    tm = 100.f / 255.f;
    DrawRectFilled(x - strlen(name), y - 41, 120 + strlen(name) * 2, 20, color); // Đám mây nền cho tên người chơi
    tm = 255.f / 255.f;
    DrawRectFilled(x - strlen(name), box.y - 41, 25, 20, color);
    if (strlen(TeamText) < 2) {
        drawText2(x + 6 - strlen(name), box.y - 42, ImColor(255,255,255),
                       TeamText, 18.943);//队伍ID
    } else {
        drawText2(x - strlen(name), box.y - 42, ImColor(255,255,255),
                       TeamText, 18.943);//队伍ID
    }
    drawText2(x + 28 - strlen(name), y - 43,
                   ImColor(255,255,255), name, 18.943);//玩家名称
    float maxWidth = 120; // Độ dài tối đa của thanh máu
    float healthBarWidth = entityHealth * maxWidth / maxHealth; // Độ dài thanh máu dựa trên tỷ lệ máu hiện tại và máu tối đa
    DrawRectFilledHealth(x - maxWidth / 2, y - 18, healthBarWidth, 8, HPColor);// cập nhật vị trí và kích thước của thanh máu
    drawText2(x + 125 + strlen(name), y - 43, ImColor(255,255,255), dis,18.943);//距离显示
    DrawTriangle(box.x + box.w / 2 - 10, y - 8, box.x + box.w / 2 + 15 - 10, y - 8,
                 box.x + box.w / 2 - 2, y, ImColor(255,255,255), 1);//第一个左边 第二个右边 第三个底边
}


static float SetFieldOfView = 0, GetFieldOfView = 0;

void DroneView() {
    if (GetFieldOfView == 0) {
        GetFieldOfView = get_fieldOfView();
    }
    if (SetFieldOfView > 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView + SetFieldOfView);
    }
    if (SetFieldOfView == 0 && GetFieldOfView != 0) {
        set_fieldOfView((float)GetFieldOfView);
    }
}


bool saved = false;
float savedScreenWidth = 0;
float savedScreenHeight = 0;
float active = 0.0f;
float desactive = 0.0f;

void UpdateSpeedhack() {
    if (!g_GameReady) return;
    if (Enable) {
        void* Simulation = GetSimulationTimer();
     if (Simulation != nullptr) {
   float FixedDeltaTime = GetTimer(Simulation);
            if(!saved) {
                active = FixedDeltaTime * 1.82f;
                desactive = FixedDeltaTime;
                saved = true;
            }
   if (SpeedHack) {
       if (FixedDeltaTime != active) {
                    SetTimer(Simulation, active);
    }
   }
   else {
       if (FixedDeltaTime != desactive) {
                    SetTimer(Simulation, desactive);
    }
   }
  }
 }
}

void *GetClosestEnemy() {
    float shortestDistance = 9999;
    void* closestEnemy = NULL;   
     
    void* get_MatchGame = Curent_Match();
    void* LocalPlayer = GetLocalPlayer(get_MatchGame);

    if (LocalPlayer != NULL && get_MatchGame != NULL && Enable) {
        MyDictionary* dict = *(MyDictionary**)((uintptr_t)get_MatchGame + ListPlayer);
        
        if (dict != nullptr && dict->entries != nullptr) {
            void* camera = Camera_main();
            int total = dict->count;

            for (int u = 0; u < total; u++) {
                void* Player = dict->entries->vector[u].value; 
                
                if (Player != NULL && Player != LocalPlayer && !get_isLocalTeam(Player) && !get_IsDieing(Player) && get_isVisible(Player) && get_MaxHP(Player)) {    
                    Vector3 PlayerPos = getPosition(Player);
                    Vector3 LocalPlayerPos = getPosition(LocalPlayer);
                    Vector3 pos2 = WorldToScreenPoint(camera, PlayerPos);
                    
                    bool isFov1 = isFov(Vector3(pos2.x, pos2.y), Vector3(g_GlWidth / 2, g_GlHeight / 2), Fov_Aim);
                    
                    float distance = Vector3::Distance(LocalPlayerPos, PlayerPos);
                    if (distance < Aimdis) {
                        Vector3 targetDir = Vector3::Normalized(PlayerPos - LocalPlayerPos);
                        float angle = Vector3::Angle(targetDir, GetForward(Component_GetTransform(camera))) * 100.0;             
                
                        if (angle <= Fov_Aim && isFov1 && angle < shortestDistance) {
                            shortestDistance = angle;
                            closestEnemy = Player;
                        }
                    }
                }
            }
        }
    }
    return closestEnemy;
}

float (*get_deltaTime)();
float smoothSpeedAIM = 5; 
void *MyPlayer = NULL;
bool Drone;

const float RADAR_SIZE = 200.0f; 
const ImVec2 RADAR_CENTER(100.0f, 100.0f); 




/*
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝
╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

╔══✦═══════════════════✦══╗
     MADE BY:- @SRC BY CROSS MOD
╚══✦═══════════════════✦══╝

*/
   
float x,y;
float enemy1 = 2.0f;


#include <string>
ImVec4 colorTextBackground = ImVec4(0, 0, 0, 255); 
ImVec4 colorBox = ImVec4(1.0f, 0.0f, 0.0f, 0.5f);       
ImVec4 colorHealth = ImVec4(0.0f, 1.0f, 0.0f, 1.0f); 
ImVec4 colorDistance = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); 
ImVec4 colorLine = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);        
ImVec4 colorHexagono = ImVec4(150 / 255.0f, 0, 255 / 255.0f, 1.0f);
ImVec4 colorMenuText = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);


void* CurrentMatch = nullptr;
void* closestEnemy = nullptr;
void* LocalPlayer = nullptr;


float aimSmoothness = 0.1f;

inline void DrawAIMBOT(float screenWidth, float screenHeight) {
     
}

inline void DrawESP(float screenWidth, float screenHeight) {
    if (!g_GameReady) return;
 ImDrawList*draw = ImGui::GetBackgroundDrawList();
    if (!draw) return;   
    
/// CROSS MODS
         
if (Aimbot) {
      
void* CurrentMatch = Curent_Match();
void* closestEnemy = GetClosestEnemy();
void* LocalPlayer = GetLocalPlayer(CurrentMatch);

if (closestEnemy != NULL && LocalPlayer != NULL && CurrentMatch != NULL) {
    Vector3 EnemyLocation = GetHeadPosition(closestEnemy);
    Vector3 PlayerLocation = CameraMain(LocalPlayer);
    Quaternion PlayerLook = GetRotationToLocation(EnemyLocation, 0.1f, PlayerLocation);
    bool IsScopeOn = get_IsSighting(LocalPlayer);
    bool IsFiring = get_IsFiring(LocalPlayer);

    
  
   
  
    if (AimWhen == 0) {
        set_aim(LocalPlayer, PlayerLook);
    }
    else if (AimWhen == 1 && IsFiring) {
        set_aim(LocalPlayer, PlayerLook);
    }
    else if (AimWhen == 2 && IsScopeOn) {
        set_aim(LocalPlayer, PlayerLook);
    }
    
}
}


if (Enable) {
    void* current_Match = Curent_Match();
    void* local_player = GetLocalPlayer(current_Match);
         
    if (local_player && current_Match) {
        MyDictionary* players = *(MyDictionary**)((uintptr_t)current_Match + ListPlayer);
        void* camera = Camera_main();

        if (players && players->entries && camera) {
            int total = players->count;
            for (int u = 0; u < total; u++) {
                void* closestEnemy = players->entries->vector[u].value;

                if (closestEnemy && closestEnemy != local_player && get_isVisible(closestEnemy) && !get_isLocalTeam(closestEnemy)) {
                    Vector3 Toepos = getPosition(closestEnemy);
                    Vector3 Toeposi = WorldToScreenPoint(camera, Toepos);
                    if (Toeposi.z < 1) continue;
						
                    Vector3 HeadPos = Toepos + Vector3(0, 1.9f, 0);
                    Vector3 HeadPosition = WorldToScreenPoint(camera, HeadPos);
                    if (HeadPosition.z < 1) continue;

                     float distance = Vector3::Distance(getPosition(local_player), Toepos);                     				 					 
					 float Height = abs(HeadPosition.y - Toeposi.y) * 1.09f;
                     float Width = Height * 0.55f;                                                    
				     Rect rect = Rect(HeadPosition.x - Width / 2.f, screenHeight - HeadPosition.y, Width, Height);																																			
					
             if (Config.ESP.Health) {           
             long clr = ImColor(0,255,0,255);               
                                
              if (GetHp(closestEnemy) <= (get_MaxHP(closestEnemy) * 0.6)) {
                clr = ImColor(255, 255, 0, 255);
          }
              
              if (GetHp(closestEnemy) < (get_MaxHP(closestEnemy) * 0.3)) {
                clr = ImColor(255, 0, 0, 255);
        }
             int xx = rect.x + rect.w + 2;
             int yy = rect.y;
            draw->AddRectFilled(ImVec2(xx, yy), ImVec2(xx + 5, yy + rect.h), ImColor(0, 0, 0, 255));        
            draw->AddRectFilled(ImVec2(xx + 1, yy + rect.h - (rect.h * ((float)GetHp(closestEnemy) / get_MaxHP(closestEnemy)))), ImVec2(xx + 4, yy + rect.h),clr);                                        
        }
  
    
    
                
                            if (Config.ESP.Line) {
                                draw->AddLine(ImVec2(screenWidth / 2.0f, 10), ImVec2(HeadPosition.x, screenHeight - HeadPosition.y), ImColor(colorLine), 1.0f);
                            }

                          
                            if (Config.ESP.Box) {

                               draw->AddRect(ImVec2(rect.x, rect.y), ImVec2(rect.x + rect.w, rect.y + rect.h), ImColor(colorBox), 5.0f, 0, 1.7f);
                          }
    
if (Config.ESP.Distancia) {
    monoString* Nick = get_NickName(closestEnemy);
    std::string names;
    if (Nick != nullptr) {
        int nick_Len = Nick->getLength();
        for (int i = 0; i < nick_Len; i++) {
            char32_t data = get_Chars(Nick, i);
            names += data;
        }
    }
    std::string distanceText = names;
    ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
    ImVec2 textPos(rect.x + rect.w / 2.0f - textSize.x / 2.0f, rect.y - textSize.y - 10);

    draw->AddRectFilled(ImVec2(textPos.x - 5, textPos.y - 5), ImVec2(textPos.x + textSize.x + 5, textPos.y + textSize.y + 5), ImColor(colorTextBackground), 5.0f);
    draw->AddText(textPos, ImColor(colorDistance), distanceText.c_str());
}
if (Config.ESP.Jarak) {
    monoString* Nick = get_NickName(closestEnemy);
    std::string names;
    if (Nick != nullptr) {
    int nick_Len = Nick->getLength();
    for (int i = 0; i < nick_Len; i++) {
        char32_t data = get_Chars(Nick, i);
        names += data;
    }
    }
    std::string distanceText = "" + std::to_string((int)distance) + "m";
    ImVec2 textSize = ImGui::CalcTextSize(distanceText.c_str());
    ImVec2 textPos(rect.x + rect.w / 2.0f - textSize.x / 2.0f, rect.y + rect.h + 10);
    draw->AddRectFilled(ImVec2(textPos.x - 5, textPos.y - 5), ImVec2(textPos.x + textSize.x + 5, textPos.y + textSize.y + 5), ImColor(colorTextBackground), 5.0f);
    draw->AddText(textPos, ImColor(colorDistance), distanceText.c_str());                                }
                            }
                        }
                    }
                }
            }
        }
   
    

bool (*_IsContinuousGen)(void *instance) = nullptr;
bool IsContinuousGen(void *instance) {
    if (instance != NULL && Enable && SniperFast) {
        return true;
    }
    return _IsContinuousGen(instance);
}

bool(*_ResetGuest)(void* _this);
bool ResetGuest(void* _this){
    if (_this != NULL) {
        if (Reset) {
            return true; 
            remove(OBFUSCATE("/storage/emulated/0/com.garena.msdk/guest100067.dat"));
        }
    }
}

    
 
bool(*Bypass)(void* bypass); 
bool _Bypass(void* bypass) { 
   return false;
}



// HINDI - 

// CREDIT - ZARU X MUKKU JISNE CREDIT HATATA USKI MAA KA BHOSDA. RANDI K LADKO TUMHARI MAA KA BHOSDA FAD DUNGA AGAR CREDIT HATA DO.



//ENGLISH - 

// CREDIT - ZARU X MUKKU IF YOU REMOVE THE CREDIT THEN YOU ARE THE REAL SON OF THE BITCH. DON'T EVER STEAL OUR CREDITS YOU MFS

// HINDI - 

// CREDIT - ZARU X MUKKU JISNE CREDIT HATATA USKI MAA KA BHOSDA. RANDI K LADKO TUMHARI MAA KA BHOSDA FAD DUNGA AGAR CREDIT HATA DO.



//ENGLISH - 

// CREDIT - ZARU X MUKKU IF YOU REMOVE THE CREDIT THEN YOU ARE THE REAL SON OF THE BITCH. DON'T EVER STEAL OUR CREDITS YOU MFS


// HINDI - 

// CREDIT - ZARU X MUKKU JISNE CREDIT HATATA USKI MAA KA BHOSDA. RANDI K LADKO TUMHARI MAA KA BHOSDA FAD DUNGA AGAR CREDIT HATA DO.



//ENGLISH - 

// CREDIT - ZARU X MUKKU IF YOU REMOVE THE CREDIT THEN YOU ARE THE REAL SON OF THE BITCH. DON'T EVER STEAL OUR CREDITS YOU MFS


// HINDI - 

// CREDIT - ZARU X MUKKU JISNE CREDIT HATATA USKI MAA KA BHOSDA. RANDI K LADKO TUMHARI MAA KA BHOSDA FAD DUNGA AGAR CREDIT HATA DO.



//ENGLISH - 

// CREDIT - ZARU X MUKKU IF YOU REMOVE THE CREDIT THEN YOU ARE THE REAL SON OF THE BITCH. DON'T EVER STEAL OUR CREDITS YOU MFS