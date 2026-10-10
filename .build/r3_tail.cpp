// 4-tab composite renderer
static const int SW=960, SH=540, CW=1920, CH=1080;
static unsigned char g_fb[SW*SH*4];
static unsigned char g_canvas[CW*CH*4];
static const unsigned char* g_tex; static int g_tw,g_th;
static void blend(int x,int y,float r,float g,float b,float a){
    if(x<0||y<0||x>=SW||y>=SH||a<=0)return;
    unsigned char*p=&g_fb[(y*SW+x)*4]; float ia=1-a;
    p[0]=(unsigned char)(r*255*a+p[0]*ia);p[1]=(unsigned char)(g*255*a+p[1]*ia);p[2]=(unsigned char)(b*255*a+p[2]*ia);p[3]=255;}
static void tri(const ImDrawVert&A,const ImDrawVert&B,const ImDrawVert&C,float cx0,float cy0,float cx1,float cy1){
    float minx=A.pos.x<B.pos.x?A.pos.x:B.pos.x; if(C.pos.x<minx)minx=C.pos.x;
    float miny=A.pos.y<B.pos.y?A.pos.y:B.pos.y; if(C.pos.y<miny)miny=C.pos.y;
    float maxx=A.pos.x>B.pos.x?A.pos.x:B.pos.x; if(C.pos.x>maxx)maxx=C.pos.x;
    float maxy=A.pos.y>B.pos.y?A.pos.y:B.pos.y; if(C.pos.y>maxy)maxy=C.pos.y;
    int x0=(int)floorf(minx); if(x0<(int)cx0)x0=(int)cx0; int y0=(int)floorf(miny); if(y0<(int)cy0)y0=(int)cy0;
    int x1=(int)ceilf(maxx); if(x1>(int)cx1)x1=(int)cx1; int y1=(int)ceilf(maxy); if(y1>(int)cy1)y1=(int)cy1;
    if(x0<0)x0=0; if(y0<0)y0=0; if(x1>SW)x1=SW; if(y1>SH)y1=SH;
    float d=(B.pos.y-C.pos.y)*(A.pos.x-C.pos.x)+(C.pos.x-B.pos.x)*(A.pos.y-C.pos.y); if(fabsf(d)<1e-8f)return;
    float inv=1.0f/d;
    for(int y=y0;y<y1;y++)for(int x=x0;x<x1;x++){
        float px=x+.5f,py=y+.5f;
        float w1=((B.pos.y-C.pos.y)*(px-C.pos.x)+(C.pos.x-B.pos.x)*(py-C.pos.y))*inv;
        float w2=((C.pos.y-A.pos.y)*(px-C.pos.x)+(A.pos.x-C.pos.x)*(py-C.pos.y))*inv;
        float w3=1-w1-w2; if(w1<0||w2<0||w3<0)continue;
        float u=w1*A.uv.x+w2*B.uv.x+w3*C.uv.x, v=w1*A.uv.y+w2*B.uv.y+w3*C.uv.y;
        int tx=(int)(u*g_tw); if(tx<0)tx=0; if(tx>=g_tw)tx=g_tw-1; int ty=(int)(v*g_th); if(ty<0)ty=0; if(ty>=g_th)ty=g_th-1;
        float ta=g_tex[(ty*g_tw+tx)*4+3]/255.0f;
        float cr=(w1*(A.col&0xFF)+w2*(B.col&0xFF)+w3*(C.col&0xFF))/255.0f;
        float cg=(w1*((A.col>>8)&0xFF)+w2*((B.col>>8)&0xFF)+w3*((C.col>>8)&0xFF))/255.0f;
        float cb=(w1*((A.col>>16)&0xFF)+w2*((B.col>>16)&0xFF)+w3*((C.col>>16)&0xFF))/255.0f;
        float ca=(w1*((A.col>>24)&0xFF)+w2*((B.col>>24)&0xFF)+w3*((C.col>>24)&0xFF))/255.0f;
        blend(x,y,cr,cg,cb,ca*ta);}
}
static void rasterize(ImDrawData* dd){
    for(int n=0;n<dd->CmdListsCount;n++){ const ImDrawList*cl=dd->CmdLists[n];
        const ImDrawVert*vb=cl->VtxBuffer.Data; const ImDrawIdx*ib=cl->IdxBuffer.Data;
        for(int c=0;c<cl->CmdBuffer.Size;c++){ const ImDrawCmd&cm=cl->CmdBuffer[c]; if(cm.UserCallback)continue;
            for(unsigned i=0;i<cm.ElemCount;i+=3) tri(vb[ib[cm.IdxOffset+i]],vb[ib[cm.IdxOffset+i+1]],vb[ib[cm.IdxOffset+i+2]],cm.ClipRect.x,cm.ClipRect.y,cm.ClipRect.z,cm.ClipRect.w);}}}
// fake globals mirroring Bools.h
static bool Aimbot=true, Enable=true, SniperFast=true, Reset=false, SpeedHack=false;
static int AimWhen=0; static float Fov_Aim=150.0f, Aimdis=300.0f;
static const char* dir[]={"NEAREST","FARTHEST"};
struct CfgESP { bool Line=true,Box=true,Distancia=true,Jarak=false,Health=true; };
struct Cfg { CfgESP ESP; } Config;
static ImVec4 colorLine(1,0.2f,0.2f,1), colorBox(1,1,1,1);
static void scene(int tab){
    for(int i=0;i<SW*SH;i++){g_fb[i*4]=2;g_fb[i*4+1]=2;g_fb[i*4+2]=2;g_fb[i*4+3]=255;}
    ShadowModzTheme(); DrawStarfield();
    ImGui::SetNextWindowPos(ImVec2(SW*0.5f,SH*0.5f),ImGuiCond_Always,ImVec2(0.5f,0.5f));
    ImGui::SetNextWindowSize(ImVec2(SW*0.66f,SH*0.78f),ImGuiCond_Always);
    if(ImGui::Begin("SHADOW MODZ",nullptr,ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoCollapse)){
        DrawWindowStars(ImGui::GetWindowDrawList(),ImGui::GetCursorScreenPos(),ImGui::GetContentRegionAvail());
        RedHeader();
        if(NeonTab("AIM",tab==0)){} ImGui::SameLine();
        if(NeonTab("ESP",tab==1)){} ImGui::SameLine();
        if(NeonTab("CATCH",tab==2)){} ImGui::SameLine();
        if(NeonTab("MISC",tab==3)){}
        ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
        ImGui::BeginChild("##TabContent", ImVec2(0, ImGui::GetContentRegionAvail().y - 78.0f), false, ImGuiWindowFlags_NoBackground);
        if(tab==0){
            ModRow("Enable AimBot",&Aimbot);
            ImGui::Combo("##AimDir",&AimWhen,dir,2);
            ImGui::SliderFloat("FOV",&Fov_Aim,0,500,"%.f");
            ImGui::SliderFloat("Distance",&Aimdis,0,1000,"%.f");
        } else if(tab==1){
            ModRow("Enable ESP",&Enable);
            ModRow("ESP LINE",&Config.ESP.Line); ImGui::SameLine();
            ImGui::ColorEdit4("##LineColor",(float*)&colorLine,ImGuiColorEditFlags_NoInputs);
            ModRow("ESP BOX",&Config.ESP.Box); ImGui::SameLine();
            ImGui::ColorEdit4("##BoxColor",(float*)&colorBox,ImGuiColorEditFlags_NoInputs);
            ModRow("ESP NAME",&Config.ESP.Distancia);
            ModRow("ESP DISTANCE",&Config.ESP.Jarak);
            ModRow("ESP HEALTH",&Config.ESP.Health);
        } else if(tab==2){
            ModRow("Sniper Fast",&SniperFast);
            ModRow("Reset Acc",&Reset);
        } else {
            ModRow("Speedhack",&SpeedHack);
            ImGui::Spacing();
            ImGui::TextColored(ImVec4(1.00f,0.25f,0.25f,1.0f),"</> Dev: SHADOW MODZ");
            ImGui::TextColored(ImVec4(0.85f,0.85f,0.85f,1.0f),"TELEGRAM: @ShadowModz");
        }
        ImGui::EndChild();
        ImGui::Spacing(); ImGui::Separator(); ImGui::Spacing();
        float w2=(ImGui::GetContentRegionAvail().x-12)*0.5f;
        if(NeonCloseButton("HIDE",w2)){} ImGui::SameLine(0,12); if(NeonCloseButton("CLOSE",w2)){}
    }
    ImGui::End();
    ImGui::Render();
    rasterize(ImGui::GetDrawData());
}
int main(){
    ImGui::CreateContext(); ImGuiIO&io=ImGui::GetIO(); io.DisplaySize=ImVec2((float)SW,(float)SH); io.MousePos=ImVec2(-1,-1);
    io.Fonts->AddFontDefault(); int tw,th; io.Fonts->GetTexDataAsRGBA32((unsigned char**)&g_tex,&tw,&th); g_tw=tw;g_th=th;
    for(int t=0;t<4;t++){
        for(int f=0;f<150;f++){ io.DeltaTime=1/60.0f; io.MouseDown[0]=false; ImGui::NewFrame(); scene(t); }
        int ox=(t%2)*SW, oy=(t/2)*SH;
        for(int y=0;y<SH;y++)for(int x=0;x<SW;x++){
            unsigned char*dst=&g_canvas[((oy+y)*CW+ox+x)*4]; unsigned char*src=&g_fb[(y*SW+x)*4];
            dst[0]=src[0];dst[1]=src[1];dst[2]=src[2];dst[3]=255;}
    }
    FILE*fp=fopen("/home/user/MyOwnSrv/preview/shadow-modz-alltabs.rgba","wb"); fwrite(g_canvas,1,sizeof(g_canvas),fp); fclose(fp);
    printf("wrote composite\n"); return 0;
}
