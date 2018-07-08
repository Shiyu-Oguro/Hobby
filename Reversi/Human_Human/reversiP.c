/*人間VS人間*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapio.h"
 
#define MSIZE 10


//表示する君
void renew(char map[MSIZE][MSIZE]){
	int x,y;
	
	printf("\n");
	printf("  1  2  3  4  5  6  7  8\n");
	printf("--------------------------\n");	
	
	for(y=1;y<9;y++){
		printf("%d|",y);
		for(x=1;x<9;x++){
			if(map[y][x]>0){					
				printf("● ");
			}else if(map[y][x]<0){
				printf("○ ");
			}else{
				printf("・ ");
			}
		}
		printf("\n");
	}
}

//置いたところをめくるよ君
void MrShot(int v,int x0,int y0,char map[MSIZE][MSIZE],int sx[8],int sy[8],int a)
{
	int x,y,i;
	for(i=0;i<8;i++){
		x=x0;
		y=y0;
		if(map[ y+sy[i] ][ x+sx[i] ] == -v){//方向iが相手コマなら
			while(1){
				x=x+sx[i];
				y=y+sy[i];
					if(map[ y+sy[i] ][x+sx[i] ]==v){//自分のコマがあった
						while(1){
							map[y][x]=v;
							if( (x==a%10) && (y==a/10) ){
								break;
							}			
							x=x-sx[i];
							y=y-sy[i];
						}
						break;
					}else if(map[ y+sy[i] ][x+sx[i] ]==9){//壁
						break; //置けない
					}
			}
		}
	}
}

int MrSyuukei(char map[MSIZE][MSIZE])
{
	int i,j,kekka=0;
	for(i=1;i<9;i++){
		for(j=1;j<9;j++){
			kekka+=map[i][j];
		}
	}
	return kekka;
}

//________________________________________________________________________________________________________________


//探す君
int MrSearch(int v,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,hyouji=0,kekka=0;
	for(x=1;x<9;x++){
		for(y=1;y<9;y++){
			hyouji=MrEight(v,x,y,map,sx,sy);
			kekka+=hyouji;
		}
	}
	return kekka;
}



//８方向君
int MrEight(int v,int x0,int y0,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,i;
	if((map[y0][x0]==-1) || (map[y0][x0]==1)){//すでに置かれている（０位外のコマがある）
		return 0;
	}
	for(i=0;i<8;i++){
		x=x0;
		y=y0;
		if(map[ y+sy[i] ][ x+sx[i] ] == -v){//方向iが相手コマなら	
			while(1){
				x=x+sx[i];
				y=y+sy[i];
					if(map[ y+sy[i] ][x+sx[i] ]==v){//自分のコマがあった
						return (y0*10+x0);
					}else if(map[ y+sy[i] ][x+sx[i] ]==0 || (map[ y+sy[i] ][x+sx[i] ]>1 )){//コマが無いor壁
						break; //置けない
					}
			}
		}
	}
	//puts("置けないよ");
	return 0;
}

//________________________________________________________________________________________________________________



int main(){
	int v=1,hitY,hitX,get,okeru,flag=1;
	int sx[8]={1,1,0,-1,-1,-1,0,1};
	int sy[8]={0,1,1,1,0,-1,-1,-1};
	char map[MSIZE][MSIZE]={0};

	read_map_file("map1.csv",map);
	puts("これから対局を始めます。");
	
	while(1){//ゲーム自体はループしている
		v*=-1;
		okeru=MrSearch(v,map,sx,sy);	
		renew(map);/*更新*/
		printf("手番:");
		if(v<0){
			puts("○");
		}else{
			puts("●");	
		}
		

		if(okeru<1){
			if(flag>0){
				flag=0;
				puts("置くところ無いよ。パスするよ");
				continue;
			}else{
				puts("<<<<[ 試合終了 ]>>> お互い置けるところが無くなったよ。");
				get=MrSyuukei(map);
				if(get>0){
					printf("○の勝ち");
				}else if(get<0){
					printf("×の勝ち");
				}else{
					printf("引き分け");
				}
				return 0;
			}
		}
		
		while(1){
					puts("打つ場所は？ X,Y:");
					scanf("%d",&hitX);
					scanf("%d",&hitY);
					get=MrEight(v,hitX,hitY,map,sx,sy); 
					printf("GET:%d\n",get);
					if(get){ /*8方向探して,存在すれば*/
						MrShot(v,hitX,hitY,map,sx,sy,get); 
						//renew(map);
						break;
					}
		}
	}
	
 return 0;

}
