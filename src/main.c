#include "util/mutil.h"
#include <stdio.h>
#include <stdlib.h>
//#include "raylib.h"
#include <raylib.h>
#include <math.h>
F t = 0; I score;
F getZ(F x, F y){R  sin(x+y+t);}
Camera camera = { 0 };
Model model;
Texture2D texture;
typedef struct { Vector3 position; Vector3 velocity; float radius; Color color; } Ball;
V quit(){
   UnloadTexture(texture);
   UnloadModel(model);   
   CloseWindow();
}
V caminit(){camera.position = (Vector3){ 9.10f, 45.0f, 0.00f };camera.target = (Vector3){ 1.3f, 5.0f, 0.0f };
   camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };camera.fovy = 45.0f;camera.projection = CAMERA_PERSPECTIVE;}
V wininit(){
   SetTraceLogLevel(LOG_ERROR);
   CON I screenWidth = 800; CON I screenHeight = 800;
   //   SetConfigFlags(FLAG_WINDOW_RESIZABLE);
   SetConfigFlags(FLAG_MSAA_4X_HINT);
   InitWindow(screenWidth, screenHeight, "corn_healing_blade");
   SetTargetFPS(60);
}
I play=0;
#define  planeS 32 //view planme size
#define  planeH 12 //view planme size
#define pfS 11 //playfieldsize
Vector3 mapPosition ={ (F)-planeS/2, 0.0f, (F)-planeS/2 };
V terraininit(){
   Image image = GenImagePerlinNoise(1*(pfS+1),1*( pfS+1), 50, 50, 8.0f);
   ImageColorTint(&image, GREEN);
   Mesh mesh = GenMeshHeightmap(image, (Vector3){ planeS, planeH, planeS});
   model = LoadModelFromMesh(mesh);
   model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
   UnloadImage(image);             
}
V Render(){
   BeginDrawing();
   ClearBackground((Color){19,014,07,255});
   BeginMode3D(camera);
   if(play){ DrawModel(model,mapPosition , 1.f, WHITE); }
   EndMode3D();
   if(play){
      char sc[100];
      sprintf(sc, "Score: %d",score);
      //sprintf(char *, const char *, ...)
      DrawText(sc,GetScreenWidth()/2-10*6 , 15, 50, WHITE);
   }else{
      DrawText("press <<ENTER>> to play", GetScreenWidth()/2-30*6, GetScreenHeight()/2-25, 30, PINK);
      char sc[100];
      sprintf(sc, "Score: %d",score);
      if(score>0){DrawText(sc,GetScreenWidth()/2-10*10 , GetScreenHeight()/2+10, 50, WHITE);}
   }
   //DrawFPS(10, 10);
   EndDrawing();
}
I board[pfS*pfS];
I head[3]={10,10,3};//x,y,len,speed
I fruit[2]={10,10};//x,y,len,speed
I dir = 3;
I spd = 7;
I spdT=0;
V newFruit(){
   fruit[0]=rand()%pfS;
   fruit[1]=rand()%pfS;
   if(board[fruit[0]+
      fruit[1]*pfS]>0){newFruit();};

}

I ndir=0;
V reset(){
   for(int x = 0; x < pfS;x++){
      for(int y = 0; y < pfS;y++){board[x+y*pfS]=0;}}

   head[0]=10;
   head[1]=10;
   head[2]=3;
   dir = 3;
   ndir=dir;
   spd = 7;
   spdT=0;
   newFruit();
   score=0;
}
V Tick(){
   //dir=(I)t%4;
   t+=.1;
   spdT+=1;

   //UnloadImageColors(c);
   if(IsKeyPressed(KEY_ENTER) && !play){
      play=true;
      reset();
   }

   if(IsKeyPressed(KEY_UP)&&dir%2!=1){ ndir=1; }
   if(IsKeyPressed(KEY_DOWN)&&dir%2!=1){ ndir=3; }
   if(IsKeyPressed(KEY_RIGHT)&&dir%2!=0){ ndir=0; }
   if(IsKeyPressed(KEY_LEFT)&&dir%2!=0){ ndir=2; }
   if(spdT%spd==0&&play){
      dir=ndir;
      head[0]+=(dir-2)%2;
      head[1]+=(dir-1)%2 ;
      if(head[0]>=pfS){head[0]=0;}
      if(head[1]>=pfS){head[1]=0;}
      if(head[0]<0){head[0]=pfS-1;}
      if(head[1]<0){head[1]=pfS-1;}
      if(board[head[0]+head[1]*pfS]>0){ play=false; }
      if(head[0]==fruit[0]&&head[1]==fruit[1]){score++;newFruit(); head[2]+=1; }
      board[head[0]+head[1]*pfS]=head[2];

      Image image = GenImagePerlinNoise(pfS, pfS, 50, 50, 3.0f);
      ImageColorTint(&image, GREEN);
      Color * c = LoadImageColors(image);
      for(int x = 0; x < pfS;x++){
         for(int y = 0; y < pfS;y++){
            if(board[x+y*pfS]>0){
               c[x+y*pfS]=(Color){255,124,255,255 };
               board[x+y*pfS]-=1;
            }
         }};
      c[fruit[0]+fruit[1]*pfS]=(Color){254,25,25,255 };
      Image ii = (Image){c,pfS ,pfS,1, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8};
      texture = LoadTextureFromImage(ii);
      model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
      UnloadImage(ii);
   }
}
V loop(){ W(!WindowShouldClose()){Tick();Render();}}
V init(){
   wininit();
   caminit(); 
   terraininit();
   newFruit();
}
I main(){init(); loop();}
