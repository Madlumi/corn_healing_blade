#pragma once
#include <stdbool.h>

typedef int    I;
typedef bool   B;
typedef float  F;
typedef double D;
typedef void   V;
typedef char   C;
typedef char*  S;
I sign(int x) { return (x > 0) - (x < 0); }


#define CON const
#define ST static
#define R return 


#define SW switch
#define CA(x,y) case x: y; break;
#define BR break
#define IN(x,l,h) ((l)<=(x)&&(x)<=(h))
#define eif else if
#define el else
#define W(x) while((x))
#define FOR(n,x) {for(int i=0;i<n;++i){x;}}
#define FORX(n,a) {for(int x=0;x<n;++x){a;}}
#define FORY(n,a) {for(int y=0;y<n;++y){a;}}

#define FORR(n,x) {for(int i=n-1;i>=0;--i){x;}}
#define FORYX(yN,xN,a) {for(int y=0;y<yN;++y){for(int x=0;x<xN;++x){a;}}}
#define FORIJ(iN,jN,a) {for(int i=0;i<iN;++i){for(int j=0;j<jN;++j){a;}}}

#define FORSYX(N,a) {for(int y=0;y<N;++y){for(int x=0;x<N;++x){a;}}}
#define FORSIJ(N,a) {for(int i=0;i<N;++i){for(int j=0;j<N;++j){a;}}}

#define FOR_RYX(yN,xN,a) {for(int y=yN-1;y>=0;--y){for(int x=0;x<xN;++x){a;}}}
