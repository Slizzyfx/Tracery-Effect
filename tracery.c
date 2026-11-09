#include <stdint.h>
#include <stddef.h>

#define EXPORT __attribute__((visibility("default")))
void *memset(void *dst, int c, size_t n){ unsigned char *p=(unsigned char*)dst; for(size_t i=0;i<n;i++)p[i]=(unsigned char)c; return dst; }
static const char manifest[] = "{\"api\":1,\"id\":\"org.effectcraft.tracery\",\"name\":\"Tracery\",\"category\":\"Stylize\",\"version\":\"1.2.2\",\"author\":\"OpenAI\",\"description\":\"Region-centre tracking network with connected animated streaming lines.\",\"params\":["
"{\"id\":\"enabled\",\"name\":\"Enable Tracery\",\"type\":\"checkbox\",\"default\":true},"
"{\"id\":\"line_type\",\"name\":\"Line Type\",\"type\":\"popup\",\"options\":[\"Straight\",\"Bezier\",\"Organic\",\"Wave\",\"Spiral\",\"Mixed\"],\"default\":1},"
"{\"id\":\"line_shape\",\"name\":\"Line Shape\",\"type\":\"popup\",\"options\":[\"Smooth\",\"Angular\",\"Dashed\",\"Dotted\"],\"default\":0},"
"{\"id\":\"layout\",\"name\":\"Connection Layout\",\"type\":\"popup\",\"options\":[\"Sequential\",\"Star\",\"Full Mesh\",\"Nearest Neighbour\"],\"default\":3},"
"{\"id\":\"density\",\"name\":\"Detection Density\",\"type\":\"slider\",\"default\":9,\"min\":3,\"max\":18,\"decimals\":0},"
"{\"id\":\"threshold\",\"name\":\"Colour Threshold\",\"type\":\"slider\",\"default\":45,\"min\":0,\"max\":100,\"decimals\":0},"
"{\"id\":\"detect_color\",\"name\":\"Detection Colour\",\"type\":\"color\",\"default\":[0.2,0.8,1.0,1.0]},"
"{\"id\":\"line_color\",\"name\":\"Line Colour\",\"type\":\"color\",\"default\":[0.2,0.85,1.0,1.0]},"
"{\"id\":\"line_width\",\"name\":\"Line Width\",\"type\":\"slider\",\"default\":1.8,\"min\":0.3,\"max\":12,\"decimals\":1},"
"{\"id\":\"line_opacity\",\"name\":\"Line Opacity\",\"type\":\"slider\",\"default\":85,\"min\":0,\"max\":100,\"decimals\":0},"
"{\"id\":\"curvature\",\"name\":\"Curvature\",\"type\":\"slider\",\"default\":55,\"min\":0,\"max\":100,\"decimals\":0},"
"{\"id\":\"animation\",\"name\":\"Animation\",\"type\":\"popup\",\"options\":[\"Off\",\"Flow\",\"Stream\",\"Pulse\",\"Dash Travel\"],\"default\":2},"
"{\"id\":\"speed\",\"name\":\"Stream Speed\",\"type\":\"slider\",\"default\":1.2,\"min\":0,\"max\":5,\"decimals\":2},"
"{\"id\":\"direction\",\"name\":\"Flow Direction\",\"type\":\"angle\",\"default\":0},"
"{\"id\":\"box_size\",\"name\":\"Detection Box Size\",\"type\":\"slider\",\"default\":18,\"min\":4,\"max\":80,\"decimals\":0},"
"{\"id\":\"box_shape\",\"name\":\"Detection Box Shape\",\"type\":\"popup\",\"options\":[\"Square\",\"Rectangle\",\"Rounded\",\"Circle\",\"Corner Brackets\",\"Diamond\"],\"default\":3},"
"{\"id\":\"show_boxes\",\"name\":\"Show Detection Boxes\",\"type\":\"checkbox\",\"default\":false},"
"{\"id\":\"glow\",\"name\":\"Glow\",\"type\":\"slider\",\"default\":0,\"min\":0,\"max\":5,\"decimals\":1},"
"{\"id\":\"particles\",\"name\":\"Moving Particles\",\"type\":\"checkbox\",\"default\":true},"
"{\"id\":\"particle_size\",\"name\":\"Particle Size\",\"type\":\"slider\",\"default\":2.5,\"min\":0.5,\"max\":8,\"decimals\":1},"
"{\"id\":\"mix\",\"name\":\"Effect Amount\",\"type\":\"slider\",\"default\":100,\"min\":0,\"max\":100,\"decimals\":0},"
"{\"id\":\"connection_density\",\"name\":\"Full Mesh Density\",\"type\":\"slider\",\"default\":30,\"min\":5,\"max\":100,\"decimals\":0},"
"{\"id\":\"box_width\",\"name\":\"Detection Box Width\",\"type\":\"slider\",\"default\":100,\"min\":25,\"max\":250,\"decimals\":0},"
"{\"id\":\"box_height\",\"name\":\"Detection Box Height\",\"type\":\"slider\",\"default\":100,\"min\":25,\"max\":250,\"decimals\":0},"
"{\"id\":\"show_coordinates\",\"name\":\"Show Point Coordinates\",\"type\":\"checkbox\",\"default\":false},"
"{\"id\":\"coordinate_size\",\"name\":\"Coordinate Label Size\",\"type\":\"slider\",\"default\":1.0,\"min\":0.6,\"max\":2.5,\"decimals\":1},"
"{\"id\":\"orbit_stream\",\"name\":\"Orbiting Stream Around Character\",\"type\":\"checkbox\",\"default\":true},"
"{\"id\":\"orbit_direction\",\"name\":\"Orbit Direction\",\"type\":\"popup\",\"options\":[\"Clockwise\",\"Counterclockwise\"],\"default\":0},"
"{\"id\":\"orbit_amount\",\"name\":\"Orbit Radius\",\"type\":\"slider\",\"default\":18,\"min\":2,\"max\":60,\"decimals\":0},"
"{\"id\":\"two_links\",\"name\":\"Two Connections Per Point\",\"type\":\"checkbox\",\"default\":true}]}";
static uint8_t heap[16*1024*1024]; static uint32_t heap_used=8;
EXPORT int32_t ec_api_version(void){return 1;}
EXPORT int32_t ec_manifest_ptr(void){return (int32_t)(uintptr_t)manifest;}
EXPORT int32_t ec_manifest_len(void){return (int32_t)(sizeof(manifest)-1);}
EXPORT int32_t ec_alloc(int32_t n){ if(n<0 || (uint64_t)heap_used+(uint32_t)n>sizeof(heap)) return 0; uint32_t p=heap_used; heap_used=(heap_used+(uint32_t)n+7)&~7u; return (int32_t)(uintptr_t)(heap+p); }
static float fsin(float x){ const float PI=3.14159265358979323846f, TWO=6.2831853071795864769f; while(x>PI)x-=TWO;while(x<-PI)x+=TWO; float x2=x*x; return x*(1.0f+x2*(-0.16666667f+x2*(0.00833333f+x2*(-0.00019841f+x2*0.0000027557f))));}
static float fcos(float x){return fsin(x+1.57079632679f);}
static float clampf(float x,float a,float b){return x<a?a:(x>b?b:x);} 
static float maxf(float a,float b){return a>b?a:b;}
static void blend(float *dst,float r,float g,float b,float a){a=clampf(a,0,1); float ia=1-a; dst[0]=r*a+dst[0]*ia; dst[1]=g*a+dst[1]*ia; dst[2]=b*a+dst[2]*ia; dst[3]=a+dst[3]*ia;}
static void dot(float *px,int w,int h,float x,float y,float rad,float r,float g,float b,float a){int x0=(int)(x-rad-1),x1=(int)(x+rad+1),y0=(int)(y-rad-1),y1=(int)(y+rad+1);for(int yy=y0;yy<=y1;yy++)for(int xx=x0;xx<=x1;xx++){if(xx<0||yy<0||xx>=w||yy>=h)continue;float dx=xx+0.5f-x,dy=yy+0.5f-y,d=dx*dx+dy*dy;if(d<=rad*rad){float *p=px+((yy*w+xx)*4);blend(p,r,g,b,a);}}}
static void seg(float *px,int w,int h,float x0,float y0,float x1,float y1,float width,float r,float g,float b,float a,int style,float phase){float dx=x1-x0,dy=y1-y0;float len=maxf(1,(float)__builtin_sqrtf(dx*dx+dy*dy));int steps=(int)(len*1.25f)+1;if(steps>1800)steps=1800;for(int i=0;i<=steps;i++){float t=(float)i/steps; if(style==2 && (((int)((t*len+phase)/7))&1))continue;if(style==3 && ((int)((t*len+phase)/5))%2)continue;float x=x0+dx*t,y=y0+dy*t;dot(px,w,h,x,y,width*.5f,r,g,b,a);}}
static void curve(float *px,int w,int h,float x0,float y0,float cx,float cy,float x1,float y1,float width,float r,float g,float b,float a,int shape,float phase){float ax=x0,ay=y0;for(int i=1;i<=48;i++){float t=(float)i/48, u=1-t;float x=u*u*x0+2*u*t*cx+t*t*x1,y=u*u*y0+2*u*t*cy+t*t*y1;seg(px,w,h,ax,ay,x,y,width,r,g,b,a,shape,phase);ax=x;ay=y;}}
static unsigned char glyph(char c,int row){
 static const unsigned char d[10][5]={{7,5,5,5,7},{2,6,2,2,7},{7,1,7,4,7},{7,1,7,1,7},{5,5,7,1,1},{7,4,7,1,7},{7,4,7,5,7},{7,1,1,1,1},{7,5,7,5,7},{7,5,7,1,7}};
 if(c>='0'&&c<='9')return d[c-'0'][row];
 if(c=='X'||c=='x'){static const unsigned char a[5]={5,5,2,5,5};return a[row];}
 if(c=='Y'||c=='y'){static const unsigned char a[5]={5,5,2,2,2};return a[row];}
 if(c==':')return (row==1||row==3)?2:0;
 if(c==',')return row==4?2:0; if(c=='-')return row==2?7:0; if(c=='(')return row==0||row==4?2:4; if(c==')')return row==0||row==4?2:1; return 0;
}
static void draw_text(float *p,int w,int h,int x,int y,const char *s,float z,float r,float g,float b,float a){
 int ox=x; for(int n=0;s[n];n++){if(s[n]==' '){x+=(int)(4*z);continue;}for(int yy=0;yy<5;yy++){unsigned char bits=glyph(s[n],yy);for(int xx=0;xx<3;xx++)if(bits&(1<<(2-xx)))dot(p,w,h,x+xx*z,y+yy*z,maxf(.55f,z*.48f),r,g,b,a);}x+=(int)(4*z);} (void)ox;
}
static int append_int(char *out,int at,int value){if(value<0){out[at++]='-';value=-value;}char t[12];int n=0;do{t[n++]=(char)('0'+value%10);value/=10;}while(value&&n<11);while(n)out[at++]=t[--n];return at;}
EXPORT int32_t ec_render(int32_t pixels,int32_t width,int32_t height,int32_t params,int32_t nparams,double time,double scale){
 if(!pixels||!params||width<1||height<1||nparams<36)return 1;
 float *p=(float*)(uintptr_t)pixels; double *v=(double*)(uintptr_t)params; if(v[0]<.5)return 0;
 float density=clampf((float)v[4],3,18), threshold=clampf((float)v[5],0,100)/100.0f;
 float dr=v[6],dg=v[7],db=v[8]; float lr=v[10],lg=v[11],lb=v[12],la=v[13];
 float lw=clampf(v[14],.3f,12), opacity=clampf(v[15]/100,0,1),curv=clampf(v[16]/100,0,1);
 int ltype=(int)v[1],shape=(int)v[2],layout=(int)v[3],anim=(int)v[17];
 float speed=(float)v[18],angle=(float)v[19]*0.0174532925f,bs=clampf(v[20],4,80);
 int bshape=(int)v[21],boxes=v[22]>.5f; float glow=clampf(v[23],0,5); int particles=v[24]>.5f;
 float ps=clampf(v[25],.5,8),mix=clampf(v[26]/100,0,1);
 float mesh_density=clampf((float)v[27],5,100)/100.0f;
 float box_w=clampf((float)v[28]/100.0f,.25f,2.5f),box_h=clampf((float)v[29]/100.0f,.25f,2.5f);
 int show_coords=v[30]>.5f; float coord_size=clampf((float)v[31],.6f,2.5f);
 int orbit=v[32]>.5f, orbit_dir=(int)v[33]; float orbit_radius=clampf((float)v[34],2,60);
 /* Sample a coarse grid, then merge adjacent matching cells into detected regions. */
 int nx=(int)(density*3.0f), ny=(int)(density*3.0f*(float)height/(float)width); if(nx>36)nx=36;if(ny<3)ny=3;if(ny>36)ny=36;
 int gw=width/nx,gh=height/ny;if(gw<1||gh<1)return 0;
 unsigned char hit[1296]={0},seen[1296]={0};
 for(int gy=0;gy<ny;gy++)for(int gx=0;gx<nx;gx++){
  int x=gx*gw+gw/2,y=gy*gh+gh/2; float *q=p+((y*width+x)*4);
  float d=__builtin_fabsf(q[0]-dr)+__builtin_fabsf(q[1]-dg)+__builtin_fabsf(q[2]-db);
  hit[gy*nx+gx]=(d <= (0.12f+threshold*1.10f))?1:0;
 }
 typedef struct{float x,y;int cells,minx,miny,maxx,maxy;} Region; Region regions[64]; int count=0;
 int queue[1296];
 for(int idx=0;idx<nx*ny;idx++) if(hit[idx]&&!seen[idx]&&count<64){
  int head=0,tail=0;queue[tail++]=idx;seen[idx]=1;
  float sx=0,sy=0;Region r={0,0,0,nx,ny,-1,-1};
  while(head<tail){int z=queue[head++],gx=z%nx,gy=z/nx;int x=gx*gw+gw/2,y=gy*gh+gh/2;
   sx+=x;sy+=y;r.cells++;if(gx<r.minx)r.minx=gx;if(gy<r.miny)r.miny=gy;if(gx>r.maxx)r.maxx=gx;if(gy>r.maxy)r.maxy=gy;
   for(int oy=-1;oy<=1;oy++)for(int ox=-1;ox<=1;ox++){if((ox==0)==(oy==0))continue;int xx=gx+ox,yy=gy+oy;if(xx<0||yy<0||xx>=nx||yy>=ny)continue;int ni=yy*nx+xx;if(hit[ni]&&!seen[ni]){seen[ni]=1;queue[tail++]=ni;}}
  }
  /* Ignore isolated single-cell noise; retain larger coherent regions. */
  if(r.cells>=2){r.x=sx/r.cells;r.y=sy/r.cells;regions[count++]=r;}
 }
 /* Build real links between detected region centres. Each undirected edge is drawn once. */
 unsigned char edge[64][64]={0};
 if(count>=2){
  if(layout==0){for(int i=0;i<count-1;i++)edge[i][i+1]=edge[i+1][i]=1;}
  else if(layout==1){for(int i=1;i<count;i++)edge[0][i]=edge[i][0]=1;}
  else if(layout==2){
   /* Density-controlled mesh: each region links to its nearest K neighbours.
      At 100% this becomes a true full mesh; lower values keep the web readable. */
   int k=1+(int)((count-2)*mesh_density+0.5f); if(k>count-1)k=count-1;
   for(int i=0;i<count;i++){
    float ds[64]; int ids[64];
    for(int j=0;j<count;j++){float dx=regions[i].x-regions[j].x,dy=regions[i].y-regions[j].y;ds[j]=(i==j)?1e30f:dx*dx+dy*dy;ids[j]=j;}
    for(int a=0;a<k;a++){int best=a;for(int b=a+1;b<count;b++)if(ds[b]<ds[best])best=b;float td=ds[a];ds[a]=ds[best];ds[best]=td;int ti=ids[a];ids[a]=ids[best];ids[best]=ti;edge[i][ids[a]]=edge[ids[a]][i]=1;}
   }
  }
  else if(layout==4){for(int i=0;i<count;i++){int j=(i+1)%count;edge[i][j]=edge[j][i]=1;}}
  else {
   /* Minimum spanning tree: guarantees one connected network, unlike isolated nearest-neighbour pairs. */
   unsigned char used[64]={0};used[0]=1;
   for(int step=1;step<count;step++){float best=1e30f;int bi=-1,bj=-1;
    for(int i=0;i<count;i++)if(used[i])for(int j=0;j<count;j++)if(!used[j]){float dx=regions[i].x-regions[j].x,dy=regions[i].y-regions[j].y,d=dx*dx+dy*dy;if(d<best){best=d;bi=i;bj=j;}}
    if(bi>=0){edge[bi][bj]=edge[bj][bi]=1;used[bj]=1;}
   }
  }
 }
 /* Optional strict two-link ring: every detected point connects to its two neighbours. */
 if(v[35]>.5f && count>=3){for(int i=0;i<64;i++)for(int j=0;j<64;j++)edge[i][j]=0;for(int i=0;i<count;i++){int j=(i+1)%count;edge[i][j]=edge[j][i]=1;}}
 float phase=(float)time*speed*42.0f; float ca=fcos(angle),sa=fsin(angle);
 for(int i=0;i<count;i++)for(int j=i+1;j<count;j++)if(edge[i][j]){
  float x0=regions[i].x,y0=regions[i].y,x1=regions[j].x,y1=regions[j].y;
  float dx=x1-x0,dy=y1-y0,len=maxf(1,__builtin_sqrtf(dx*dx+dy*dy));
  float bend=(ltype==0)?0:curv*len*.22f;
  if(ltype==3)bend=curv*len*.34f;if(ltype==4)bend=curv*len*.48f;
  float wob=(ltype==2)?fsin((float)time*speed*1.7f+i*2.1f+j)*len*.08f:0;
  float cx=(x0+x1)*.5f-(dy/len)*(bend+wob),cy=(y0+y1)*.5f+(dx/len)*(bend+wob);
  if(ltype==5&&((i+j)&1))bend=0;
  float a=opacity*la*mix;
  /* Draw a subtle base connection, then a travelling dashed stream on top. */
  if(ltype==0||(ltype==5&&((i+j)&1)))seg(p,width,height,x0,y0,x1,y1,lw*.65f,lr,lg,lb,a*.35f,0,0);
  else curve(p,width,height,x0,y0,cx,cy,x1,y1,lw*.65f,lr,lg,lb,a*.35f,0,0);
  int dashstyle=(anim==0)?shape:2;
  float streamphase=(anim==0)?0.0f:-phase;
  if(glow>0){if(ltype==0)seg(p,width,height,x0,y0,x1,y1,lw+glow*2,lr,lg,lb,a*.12f,2,streamphase);else curve(p,width,height,x0,y0,cx,cy,x1,y1,lw+glow*2,lr,lg,lb,a*.12f,2,streamphase);}
  if(ltype==0||(ltype==5&&((i+j)&1)))seg(p,width,height,x0,y0,x1,y1,lw,lr,lg,lb,a,dashstyle,streamphase);
  else curve(p,width,height,x0,y0,cx,cy,x1,y1,lw,lr,lg,lb,a,dashstyle,streamphase);
  if(anim>0&&particles){float t=fsin(phase/maxf(24,len)+(float)(i+j)*.73f)*.5f+.5f,u=1-t;
   float xx=u*u*x0+2*u*t*cx+t*t*x1,yy=u*u*y0+2*u*t*cy+t*t*y1;dot(p,width,height,xx,yy,ps,lr,lg,lb,a);
  }
 }
 /* A separate perimeter stream visibly travels around the detected character/network. */
 if(orbit && count>=2 && anim>0){
  float minx=regions[0].x,maxx=minx,miny=regions[0].y,maxy=miny,cx=0,cy=0;
  for(int i=0;i<count;i++){cx+=regions[i].x;cy+=regions[i].y;if(regions[i].x<minx)minx=regions[i].x;if(regions[i].x>maxx)maxx=regions[i].x;if(regions[i].y<miny)miny=regions[i].y;if(regions[i].y>maxy)maxy=regions[i].y;}
  cx/=count;cy/=count;float rx=(maxx-minx)*.5f+orbit_radius,ry=(maxy-miny)*.5f+orbit_radius;
  if(rx<orbit_radius)rx=orbit_radius;if(ry<orbit_radius)ry=orbit_radius;
  float sign=orbit_dir? -1.0f:1.0f, op=phase*sign;
  for(int z=0;z<96;z++){float a0=(float)z*6.2831853f/96,a1=(float)(z+1)*6.2831853f/96;
   seg(p,width,height,cx+fcos(a0)*rx,cy+fsin(a0)*ry,cx+fcos(a1)*rx,cy+fsin(a1)*ry,lw,lr,lg,lb,opacity*mix*.82f,2,-op*.35f);
  }
  if(particles){float a=op*.035f;dot(p,width,height,cx+fcos(a)*rx,cy+fsin(a)*ry,ps*1.4f,lr,lg,lb,opacity*mix);}
 }
 /* Region-centre markers and boxes are tied to the same detected objects as the links. */
 for(int i=0;i<count;i++){
  float x=regions[i].x,y=regions[i].y,r=bs*.5f;dot(p,width,height,x,y,2.2f,lr,lg,lb,opacity*mix);
  if(show_coords){char label[40];int at=0;label[at++]='X';label[at++]=':';at=append_int(label,at,(int)(x+0.5f));label[at++]=' ';label[at++]='Y';label[at++]=':';at=append_int(label,at,(int)(y+0.5f));label[at]=0;draw_text(p,width,height,(int)x+6,(int)y-7,label,coord_size,lr,lg,lb,opacity*mix);}

  if(boxes){
   float raww=(regions[i].maxx-regions[i].minx+1)*gw, rawh=(regions[i].maxy-regions[i].miny+1)*gh;
   float bw=raww*box_w,bh=rawh*box_h;
   if(bshape==0){float side=maxf(bw,bh);bw=side;bh=side;}
   float x0=x-bw*.5f,y0=y-bh*.5f,x1=x+bw*.5f,y1=y+bh*.5f,a=opacity*mix;
   if(bshape==3){for(int z=0;z<48;z++){float a0=z*6.2831853f/48,a1=(z+1)*6.2831853f/48;seg(p,width,height,x+fcos(a0)*bw*.5f,y+fsin(a0)*bh*.5f,x+fcos(a1)*bw*.5f,y+fsin(a1)*bh*.5f,lw,lr,lg,lb,a,0,0);}}
   else if(bshape==4){float cx=(x0+x1)*.5f,cy=(y0+y1)*.5f,lx=bw*.18f,ly=bh*.18f;seg(p,width,height,x0,y0,x0+lx,y0,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y0,x0,y0+ly,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y0,x1-lx,y0,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y0,x1,y0+ly,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y1,x0+lx,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y1,x0,y1-ly,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y1,x1-lx,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y1,x1,y1-ly,lw,lr,lg,lb,a,0,0);}
   else if(bshape==5){seg(p,width,height,x,y0,x1,y,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y,x,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x,y1,x0,y,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y,x,y0,lw,lr,lg,lb,a,0,0);}
   else if(bshape==2){float rad=maxf(2.0f, (bw<bh?bw:bh)*.18f);float cx[4]={x1-rad,x1-rad,x0+rad,x0+rad},cy[4]={y0+rad,y1-rad,y1-rad,y0+rad};for(int c=0;c<4;c++){float start=-1.5707963f+c*1.5707963f;for(int z=0;z<8;z++){float aa=start+z*1.5707963f/8,ab=start+(z+1)*1.5707963f/8;seg(p,width,height,cx[c]+fcos(aa)*rad,cy[c]+fsin(aa)*rad,cx[c]+fcos(ab)*rad,cy[c]+fsin(ab)*rad,lw,lr,lg,lb,a,0,0);}}seg(p,width,height,x0+rad,y0,x1-rad,y0,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y0+rad,x1,y1-rad,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1-rad,y1,x0+rad,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y1-rad,x0,y0+rad,lw,lr,lg,lb,a,0,0);}
   else {seg(p,width,height,x0,y0,x1,y0,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y0,x1,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x1,y1,x0,y1,lw,lr,lg,lb,a,0,0);seg(p,width,height,x0,y1,x0,y0,lw,lr,lg,lb,a,0,0);}
  }
 }
 return 0;
}
