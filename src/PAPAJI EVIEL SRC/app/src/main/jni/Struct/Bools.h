bool Enable;
inline bool g_GameReady = false;
int AimCheck = 0;
int AimType = 0;
int AimWhen = 1;
bool AimActivar,AimCrouch;
float AimDistance;
bool esp;
float Size = 1000;
float AimDis;
float MoveSpeed;
bool Tele;
bool check_move = false;
int countEnemy = 0;
// Hack Toggles  


bool isInsideFOV(int x, int y) {
    if (!Size)
        return true;

    int circle_x = g_GlWidth / 2;
    int circle_y = g_GlHeight / 2;
    int rad = Size;
    return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

void *enemyPlayer = NULL;;
void *myPlayer = NULL;
bool aimskill;
            
ImColor Esp_Box = ImColor(255,255,255,229);
ImColor Esp_Grad1 = ImColor(255,255,255,229);
ImColor Esp_Grad2 = ImColor(255,255,255,229);
ImColor Esp_3DBox = ImColor(255,255,255,229);
ImColor Esp_Fled = ImColor(255,255,255,150);
ImColor Esp_Text = ImColor(255,255,255,229);
ImColor Esp_Dist = ImColor(255,255,255,229);
ImColor Esp_Filed = ImColor(255,255,255,150);
ImColor Esp_Skel = ImColor(0255,255,255,150);
ImColor Esp_He= ImColor(255,255,255,150);
ImColor Hp = ImColor(0, 255, 0); 
ImColor White = ImColor(255, 255, 255); 


ImColor die = ImColor(255,0,0);
ImColor hp = ImColor(0,255,0,255);




const char* dir[] = {"None","Fire","Scope"};
int is_SpeedTime;
float visual_circle_size,visual_circle_stroke,visual_lined_size,visual_lined_stroke,visual_esp_line = 1,visual_esp_box = 1,visual_esp_boxth = 1,visual_esp_box_filedth = 1,visual_esp_box_filed = 1,visual_esp_skel = 1;
int visual_esp_line_type = 0;
float Fov_Aim,Aimdis;
bool Aimbot;
std::string int_to_string(int num)
{
     std::string str = std::to_string(num);
     return str;
}


bool isFov(Vector3 vec1, Vector3 vec2, int radius) {
    int x = vec1.x;
    int y = vec1.y;

    int x0 = vec2.x;
    int y0 = vec2.y;
    if ((pow(x - x0, 2) + pow(y - y0, 2) ) <= pow(radius, 2)) {
        return true;
    } else {
        return false;
    }
}
