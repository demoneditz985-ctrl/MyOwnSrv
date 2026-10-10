
#pragma once
//#include "Global.h"
class Vvector3 {
public:
    float X;
    float Y;
    float Z;
    Vvector3() : X(0), Y(0), Z(0) {}
    Vvector3(float x1, float y1, float z1) : X(x1), Y(y1), Z(z1) {}
    Vvector3(const Vvector3 &v);
    ~Vvector3();
};

Vvector3::Vvector3(const Vvector3 &v) : X(v.X), Y(v.Y), Z(v.Z) {}
Vvector3::~Vvector3() {}

#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))


#define Class_Input__get_touchCount (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_touchCount"))
#define Class_Input__GetTouch (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("GetTouch"), 1)
#define Class_Input__get_mousePosition (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_mousePosition"))

//Class Screen -> UnityEngine.dll
#define Class_Screen__get_width (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_width"))
#define Class_Screen__get_height (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_height"))
#define Class_Screen__get_density (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Screen"), OBFUSCATE("get_dpi"))


#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)

#define Class_Transform__GetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position_Injected"), 1)

#define Class_Transform__SetPosition Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("set_position_Injected"), 1)

#define Class_Camera__get_main (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"))
#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)

#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)


#define Class_Transform__Rotation Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_rotation"), 0)


#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
//Class Player

 #define Camera_get_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "get_fieldOfView")
#define Camera_set_fieldOfView (uintptr_t) Il2CppGetMethodOffset("UnityEngine.dll", "UnityEngine", "Camera", "set_fieldOfView", 1)

void *get_main() {
    return reinterpret_cast<void *(__fastcall *)()>(Class_Camera__get_main)();
}


float get_fieldOfView() {
    return reinterpret_cast<float(__fastcall *)(void *)>(Camera_get_fieldOfView)(get_main());
}

void *set_fieldOfView(float value) {
    return reinterpret_cast<void *(__fastcall *)(void *, float)>(Camera_set_fieldOfView)(get_main(), value);
}

static void Transform_INTERNAL_SetPosition(void *player, Vvector3 inn) {
    void (*Transform_INTERNAL_SetPosition)(void *transform, Vvector3 in) = (void (*)(void *, Vvector3))(Class_Transform__SetPosition);
    Transform_INTERNAL_SetPosition(player, inn);
}

static Quaternion GetRotation(void* player) {
    Quaternion (*_GetRotation)(void* players) = (Quaternion(*)(void *))(Class_Transform__Rotation);
    return _GetRotation(player);
}


#define Class_Camera__WorldToScreenPoint (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1)

#define Class_Component__get_transform (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
#define Class_Transform__get_position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)

#define Class_Transform__Position (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.CoreModule.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_position"), 0)

#define Class_Compent__Transform Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Component"), OBFUSCATE("get_transform"), 0)
//Class Player
#define ListPlayer (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("JMAGGLCNGIG"), OBFUSCATE("DKCLHINMMFO"))



#define EnemyUpdate (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("LateUpdate"), 0)


#define m_Timer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentGameSimulationTimer"), 0)
static void* GetSimulationTimer() {
    void* (*_GetSimulationTimer) () = reinterpret_cast<void* (*)()>(m_Timer);
    return _GetSimulationTimer();
}

#define m_GetTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("get_FixedDeltaTime"), 0)
static float GetTimer(void* timeServiceInstance) {
    using fnGetFixedDelta = float(*)(void*);
    auto _GetTimer = reinterpret_cast<fnGetFixedDelta>(m_GetTimer);
    return _GetTimer(timeServiceInstance);
}

#define m_SetTimer (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("GCommon"), OBFUSCATE("TimeService"), OBFUSCATE("UseFixedDeltaTime"), 1)
static void SetTimer(void* timeServiceInstance, float fixedDelta) {
    using fnSetFixed = void(*)(void*, float);
    auto _set_fixed = reinterpret_cast<fnSetFixed>(m_SetTimer);
    _set_fixed(timeServiceInstance, fixedDelta);
}




#define MainCam (uintptr_t) Il2CppGetFieldOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("MainCameraTransform"))


#define Match (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("GameFacade"), OBFUSCATE("CurrentMatch"), 0)

#define Local (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW"), OBFUSCATE("UIHudDetectorController"), OBFUSCATE("GetLocalPlayer"), 0)


#define Visible (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsVisible"), 0)

#define Team (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalTeammate"), 1)

#define Die (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDieing"), 0)

#define CurHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_CurHP"), 0)


#define MaxHP (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_MaxHP"), 0)

#define Name (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_NickName"), 0)

#define Aim (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("SetAimRotation"), 2)
#define Scope (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsSighting"),0 )

#define Fire (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsFiring"), 0)

#define LocalBool (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("IsLocalPlayer"), 0)

#define CarLocal (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("VehicleIAmIn"), 0)

#define GetCar (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_IsDriver"), 0)

#define Head (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHeadTF"), 0)

#define ForWard (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Transform"), OBFUSCATE("get_forward"), 0)


#define CharGet (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("mscorlib.dll"), OBFUSCATE("System"), OBFUSCATE("String"), OBFUSCATE("get_Chars"), 1)

#define Team (uintptr_t) Il2CppGetMethodOffset("Assembly-CSharp.dll", "COW.GamePlay", "Player", "IsLocalTeammate", 1)
#define m_ShortIDToPlayers (uintptr_t) Il2CppGetFieldOffset("Assembly-CSharp.dll", "COW.GamePlay", "JMAGGLCNGIG", "DKCLHINMMFO")

#define Raycast (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("IPBGFJNGLOH"), OBFUSCATE("FFLLOGJDGOJ"), 4)

static bool Physics_Raycast(Vector3 start, Vector3 end, unsigned int flag, void* hitInfo) {
    auto _Physics_Raycast = (bool(*)(Vector3, Vector3, unsigned int, void*))(Raycast);
    return _Physics_Raycast(start, end, flag, hitInfo);
}

#define Hip (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("GetHipTF"), 0)

#define HeadColider (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("Assembly-CSharp.dll"), OBFUSCATE("COW.GamePlay"), OBFUSCATE("Player"), OBFUSCATE("get_HeadCollider"), 0)

#define Time (uintptr_t) Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Time"), OBFUSCATE("get_deltaTime"), 0)
static void *GetHipPositions(void *player) {
    void *(*_GetHipPositions)(void *players) = (void*(*)(void *))(Hip);
     return _GetHipPositions(player);
}
 Vector3 get_position(void *player) {
    Vector3 (*_get_position)(void *players) = (Vector3 (*)(void *))(Class_Transform__Position);
    return _get_position(player);
}

static Vector3 GetHipPosition(void* player) {
    return get_position(GetHipPositions(player));
}

static void *Player_GetHeadCollider(void *player) {
    void *(*_Player_GetHeadCollider)(void *players) = (void *(*)(void *))(HeadColider);
    return _Player_GetHeadCollider(player);
}


static void *GetLocalPlayer(void* Game) {
    void *(*_GetLocalPlayer)(void *match) = (void *(*)(void *))(Local);
    return _GetLocalPlayer(Game);
}

static Vector3 Transform_GetPosition(void *player) {
    Vector3 out = Vector3::zero();
    void (*_Transform_GetPosition)(void *transform, Vector3 * out) = (void (*)(void *, Vector3 *))(Class_Transform__GetPosition);
    _Transform_GetPosition(player, &out);
    return out;
}


static void *Curent_Match() {
    void *(*_Curent_Match) (void *nuls) = (void *(*)(void *))(Match);
    return _Curent_Match(NULL);
}


static void *GetHeadPositions(void *player) {
    void *(*_GetHeadPositions)(void *players) = (void*(*)(void *))(Head);
     return _GetHeadPositions(player);
}

static void *Component_GetTransform(void *player) {
    void *(*_Component_GetTransform)(void *component) = (void *(*)(void *))(Class_Compent__Transform);
    return _Component_GetTransform(player);
}

static Vector3 WorldToScreenPoint(void *WorldCam, Vector3 WorldPos) {
    Vector3 (*_WorldToScreenScene)(void* Camera, Vector3 position) = (Vector3 (*)(void*, Vector3)) (Class_Camera__WorldToScreenPoint);
    return _WorldToScreenScene(WorldCam, WorldPos);
}


static void *Camera_main() {
    void *(*_Camera_main)(void *nuls) = (void *(*)(void *))(Class_Camera__get_main);
    return _Camera_main(nullptr);
}


static bool get_isVisible(void *player) {
    bool (*_get_isVisible)(void *players) = (bool (*)(void *))(Visible);
    return _get_isVisible(player);
}

static bool get_isLocalTeam(void *player) {
    bool (*_get_isLocalTeam)(void *players) = (bool (*)(void *))(Team);
    return _get_isLocalTeam(player);
}

static bool get_IsDieing(void *player) {
    bool (*_get_die)(void *players) = (bool (*)(void *))(Die);
    return _get_die(player);
}

static int GetHp(void* player) {
    int (*_GetHp)(void* players) = (int(*)(void *))(CurHP);
    return _GetHp(player);
}

static int get_MaxHP(void* enemy) {
    int (*_get_MaxHP)(void* player) = (int(*)(void *))(MaxHP);
    return _get_MaxHP(enemy);
}

static monoString* get_NickName(void *player) {
    monoString* (*_get_NickName)(void *players) = (monoString * (*)(void *))(Name);
    return _get_NickName(player);
}

static Vector3 GetForward(void *player) {
    Vector3 (*_GetForward)(void *players) = (Vector3 (*)(void *))(ForWard);
    return _GetForward(player);
}


static bool IsLocal(void *player) {
    bool (*_isMe)(void *players) = (bool (*)(void *))(LocalBool);
    return _isMe(player);
}
   
 static void *GetLocalCar(void *playerCar) {
    void *(*_Player_get_local)(void *Player) = (void *(*)(void *))(CarLocal);
    return _Player_get_local(playerCar);
    
    
}
static bool IsDriver(void *player) {
    bool (*_IsDriver)(void *players) = (bool (*)(void *))(GetCar);
    return _IsDriver(player);
}        
           


static void set_aim(void *player, Quaternion look) {
    void (*_set_aim)(void *players, Quaternion lock) = (void (*)(void *, Quaternion))(Aim);
    _set_aim(player, look);
}

char get_Chars(monoString *str, int index){
    char (*_get_Chars)(monoString *str, int index) = (char (*)(monoString *, int))(CharGet);
    return _get_Chars(str, index);
}

static bool get_IsSighting(void *player) {
    bool (*_get_IsSighting)(void *players) = (bool (*)(void *))(Scope);
    return _get_IsSighting(player);
}

static bool get_IsFiring(void *player) {
    bool (*_get_IsFiring)(void *players) = (bool (*)(void *))(Fire);
    return _get_IsFiring(player);
}


static bool get_isLocalTeam(void *player, bool isCheckSocial3pEffect) {
    bool (*_get_isLocalTeam)(void *, bool) = (bool (*)(void *, bool))(Team);
    return _get_isLocalTeam(player, isCheckSocial3pEffect);
}


Vector3 getPosition(void *transform) {
    return get_position(Component_GetTransform(transform));
}   

static Vector3 GetHeadPosition(void* player) {
    return get_position(GetHeadPositions(player));
}

static Vector3 CameraMain(void* player){
    return get_position(*(void**) ((uint64_t) player + MainCam));
}


Vector3 get_mousePosition(void *_this) {
	Vector3 (*_get_mousePosition)(void *_this) = (Vector3 (*)(void *)) (Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Input"), OBFUSCATE("get_mousePosition"), 0));
	return _get_mousePosition(_this);
}



int get_width() {
    return reinterpret_cast<int(__fastcall *)()>(Class_Screen__get_width)();
}

int get_height() {
    return reinterpret_cast<int(__fastcall *)()>(Class_Screen__get_height)();
}

float get_density() {
    return reinterpret_cast<float(__fastcall *)()>(Class_Screen__get_density)();
}









