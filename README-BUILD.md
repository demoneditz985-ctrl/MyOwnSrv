# SHADOW MODZ — FULL SOURCE (red/black menu, crash-fixed, Android 16 ready)

Everything needed to build your own copy of the mod menu APK.

## What's inside
- `src/PAPAJI EVIEL SRC/`  — complete Android project
  - `app/src/main/jni/`    — native source: `Main.cpp` (ImGui menu + hooks),
    `Struct/` (ESP, bools, class offsets), `Unity/` + `MukkuXZaru/` (il2cpp SDK),
    `imgui/`, `Dobby/`, `KittyMemory/`, `xdl/`
  - `app/src/main/java/…`  — loader app (prebuilt resources, label "Zygisk")
- `.github/workflows/build-apk.yml` — one-push APK builder (NDK build + sign)
- `red_ui_source.cpp` — the red/black UI code as one standalone reference file
- `preview/shadow-modz-alltabs.png` — how the menu looks (all 4 tabs)

## Build method 1 — GitHub (easiest, no PC setup)
1. Upload this whole folder as a new GitHub repo (keep `.github/`).
2. Push any commit. The workflow installs JDK 17 + NDK r25, builds `libVM.so`
   (arm64-v8a + armeabi-v7a), assembles, zipaligns and signs the APK,
   uploads it as artifact `ShadowModz.apk` and commits `release/ShadowModz.apk`.
3. Download from **Actions → run → Artifacts**, or `git pull` and take
   `release/ShadowModz.apk`.

## Build method 2 — local PC
1. Install: JDK 17, Android SDK, NDK `25.2.9519653`, build-tools `34.0.0`.
2. Case-compat symlinks (repo uses mixed-case includes):
   ```
   cd "src/PAPAJI EVIEL SRC/app/src/main/jni"
   ln -sfn imgui ImGui
   ln -sfn Dobby dobby
   ln -sfn Unity.h Unity/unity.h
   ln -sfn Il2Cpp.h MukkuXZaru/IL2CppSDKGenerator/Il2cpp.h
   ```
3. Build the native lib (do it in a path WITHOUT spaces, e.g. /tmp/vmbuild):
   ```
   ndk-build NDK_PROJECT_PATH=. APP_BUILD_SCRIPT=jni/Android.mk \
     APP_ABI="arm64-v8a armeabi-v7a" APP_PLATFORM=android-21 \
     NDK_LIBS_OUT=libs NDK_OUT=obj
   ```
   copy `libs/*/libVM.so` into `app/src/main/jniLibs/*/`.
4. Assemble the APK (gradle or AIDE), then:
   ```
   zipalign -f 4 app.apk aligned.apk
   keytool -genkeypair -keystore ks -storepass android -keypass android \
     -alias mod -dname CN=mod -validity 3650 -keyalg RSA
   apksigner sign --ks ks --ks-pass pass:android --key-pass pass:android aligned.apk
   ```

## Make it your own
- Menu look: `jni/Main.cpp` (red theme block at the top of the UI section,
  also copied in `red_ui_source.cpp`) — colors in `ShadowModzTheme()`,
  header text in `RedHeader()`.
- Features/toggles: `jni/Struct/Bools.h` + tab bodies in `jni/Main.cpp`.
- ESP drawing: `jni/Struct/ESP.h`.

Use only on games you own / for learning. Floating menu hooks eglSwapBuffers;
all il2cpp calls are guarded so a non-matching game just runs without mods.
