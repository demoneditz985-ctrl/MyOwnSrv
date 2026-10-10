#pragma once

class Camera {
	public:
	
	static Camera *get_main() {
		Camera *(*get_main_) () = (Camera *(*)()) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("get_main"), 0));
		return get_main_();
	}
	
	Vector3 WorldToScreenPoint(Vector3 position) {
		Vector3 (*WorldToScreenPoint_)(Camera *camera, Vector3 position) = (Vector3 (*)(Camera *, Vector3)) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("WorldToScreenPoint"), 1));
		return WorldToScreenPoint_(this, position);
	}
	void set_fieldOfView(float view) {
		if(this == nullptr) return;
		void (*set_fieldOfView_)(Camera *camera, float value) = (void (*)(Camera *, float)) (IL2Cpp::Il2CppGetMethodOffset(OBFUSCATE("UnityEngine.dll"), OBFUSCATE("UnityEngine"), OBFUSCATE("Camera"), OBFUSCATE("set_fieldOfView"), 1));
	     set_fieldOfView_(this, view);
	}
};