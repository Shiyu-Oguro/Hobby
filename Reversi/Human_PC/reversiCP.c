
/*　人間　VS　PC　改　*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapio.h"
 
#define MSIZE 10
#define MCHOICE 60 //最大選択肢数

//___________________________________________________________________________________
//表示関連

//表示する君
void renew(char map[MSIZE][MSIZE]){
	int x,y;
	
	printf("\n");
	printf("  1  2  3  4  5  6  7  8\n");
	printf("--------------------------\n");	
	
	for(y=1;y<9;y++){
		printf("%d|",y);
		for(x=1;x<9;x++){
			if(map[y][x]>1){
					printf("＊ ");
			}else if(map[y][x]>0){					
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
void MrShot(int v,int x0,int y0,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,i;
	for(i=0;i<8;i++){
		x=x0;
		y=y0;
		if(map[ y+sy[i] ][ x+sx[i] ] == -v){//方向iが相手コマなら
			while(1){
				x=x+sx[i];
				y=y+sy[i];
					if(map[ y+sy[i] ][x+sx[i] ]==v){//自分のコマ
						while(1){
							map[y][x]=v;
							if( (x==x0) && (y==y0) ){
								break;
							}
							x=x-sx[i];
							y=y-sy[i];
						}
						break;
					}else if( (map[ y+sy[i] ][x+sx[i] ]>1) || !(map[ y+sy[i] ][x+sx[i] ]) ){//壁か空白か＊
						break; //置けない
					}
			}
			
		}
	}
}

//______________________________________________________________________________
//事務作業

//探す君
int MrSearch(int v,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,hyouji=0,choice=0;
	for(x=1;x<9;x++){
		for(y=1;y<9;y++){
			hyouji=MrEight(v,x,y,map,sx,sy);//8方向君
			
			if(hyouji>0){//置ける					
				map[y][x]=2;
				choice++;
			}
		}
	}
	return choice;
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
					}else if(map[ y+sy[i] ][x+sx[i] ]==0 || (map[ y+sy[i] ][x+sx[i] ]>1 )){//コマが無いor*or壁
						break; //置けない
					}
			}
		}
	}
	return 0;
}

//集計君
int MrSyuukei(char map[MSIZE][MSIZE])
{
	int i,j,kekka=0;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			kekka+=map[j][i];
		}
	}
	return kekka;
}

//脳内リセット君
void MrResetB(char brain[MSIZE][MSIZE])
{
	int i,j;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			brain[j][i]=0;
		}
	}
}

//マップリセット君
void MrResetM(char map[MSIZE][MSIZE])
{
	int i,j;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			if(map[j][i]==2){

				map[j][i]=0;
			}
		}
	}
}

//マップ置き換え君
void MrChange(char map[MSIZE][MSIZE],char brain[MSIZE][MSIZE])
{
	int i=0,j=0;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			brain[j][i]=map[j][i];
		}
	}
}

//デバック用

void kakuni(char brain[MSIZE][MSIZE])
{
	int x,y;
	for(y=1;y<9;y++){
		for(x=1;x<9;x++){
			printf("%d ",brain[y][x]);
		}
		putchar('\n');
	}
}

//________________________________________________________________________________________________________________
//思考

//決定君
int MrKettei(int get,int v,char map[MSIZE][MSIZE],int sx[8],int sy[8],char brain[MSIZE][MSIZE])
{
	int i,j,x,y,V,X,nget,N=(MCHOICE*100);
	V=v;
	MrChange(map,brain);
	//for(y=1;y<9;y++){
		//for(x=1;x<9;x++){
			
			X=MrSearch(v,map,sx,sy);//探す君　（←によりmapは更新済み）
			//printf("X:%d\n",X); //
			
			for(j=1;j<9;j++){//ここより先は脳内
				for(i=1;i<9;i++){
					MrChange(map,brain);//brainにmapを上書き
					if(map[j][i]==2){
						MrShot(V,i,j,brain,sx,sy);//脳内で打つ(brainに打つ)
						V*=-1;//脳内手番を入れ替え
						nget=MrSearch(V,brain,sx,sy); //脳内はbrainに打ったから、brainで探すべき
						//printf("置ける箇所:%d\n\n",nget);
						nget=nget*100+j*10+i;//n,x,yのデータを構成
						if(nget<N){
							N=nget;//最小値更新
						}
						V=v;//元に戻す
						MrResetB(brain);
					}
				}
			}

		//}
	//}
	//printf("N=%d\n",N);
	return N;//最小手数データNを返す
}

//_________________________________________________________________________________________
void MrSinkou(int *flag,int okeru,char map[MSIZE][MSIZE])
{
	int get;
	if(!okeru){
				if(flag>0){
					*flag=0;
					puts("パスします");
				}else{
					puts("<<<<[ 試合終了 ]>>> お互い置けるところが無くなった");
					get=MrSyuukei(map);
					if(get>0){
						printf("●の勝ち");
					}else if(get<0){
						printf("○の勝ち");
					}else{
						printf("引き分け");
					}
				}
	}
}

//人間のターン
int Human(int hturn,int v,int sx[8],int sy[8],char map[MSIZE][MSIZE])
{
	int get,hitX,hitY;
	printf("あなたの手番:");
	if(hturn){
	puts("○");
	}else{
	puts("●");
	}
		while(1){
			puts("打つ場所は？ X,Y:");
			scanf("%d",&hitX);
			scanf("%d",&hitY);
			get=MrEight(v,hitX,hitY,map,sx,sy); 
			printf("GET:%d\n",get);
			if(get){ /*8方向探して,存在すれば*/
			MrShot(v,hitX,hitY,map,sx,sy); 
				break;
			}
		}
		return 0;
}

//PCのターン
int PC(int hturn,int v,int sx[8],int sy[8],char map[MSIZE][MSIZE],char brain[MSIZE][MSIZE],int *flag)
{	
	int get;
	printf("PCの手番:");
	if(!hturn){
	puts("○");
	}else{
	puts("●");
	}
		get=MrKettei(get,v,map,sx,sy,brain);//決定君からNがかえってくる
		printf("打った所:%d,%d\n",get%10,get/10%10);
		if( !get ){
			MrSinkou(&flag,get,map);
			return 0;
		}
		//printf("PCが置くところ:%d,%d\n",(get%10),(get/10%10));
		MrShot(v,(get%10),(get/10%10),map,sx,sy);//データを分解して、返す
		MrResetM(map);					
		MrResetB(brain);
		return 0;
}

//_________________________________________________________________________________________

int main(){//手番、打った手、

	int v=1,hitY,hitX,get,okeru,flag=1,turn,hturn;
	int sx[8]={1,1,0,-1,-1,-1,0,1};
	int sy[8]={0,1,1,1,0,-1,-1,-1};
	char map[MSIZE][MSIZE]={0};
	char brain[MSIZE][MSIZE]={0};

	read_map_file("map1.csv",map);
	puts("これから対局を始めます。");
	puts("[ あなた（人間）の手番を選択 ] 先攻(○):1 後攻(●):0");
	scanf("%d",&turn);
	if(!turn){//後攻
		hturn=0;
	}else{//先攻
		hturn=1;
	}

		if(hturn==1){//先攻なら	
			while(1){
				v=-1;
				renew(map);/*更新*/
				okeru=MrSearch(v,map,sx,sy);//探す君
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=Human(hturn,v,sx,sy,map);//Human
				renew(map);
				
				v=1;
				okeru=MrSearch(v,map,sx,sy);//探す君
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=PC(hturn,v,sx,sy,map,brain,&flag);//PC
			}
		}else{//後攻なら
			while(1){
				v=-1;
				renew(map);/*更新*/
				okeru=MrSearch(v,map,sx,sy);//探す君
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=PC(hturn,v,sx,sy,map,brain,&flag);//PC
				renew(map);
				
				v=1;
				okeru=MrSearch(v,map,sx,sy);//探す君
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=Human(hturn,v,sx,sy,map);			
				}
		}
 return 0;

}
