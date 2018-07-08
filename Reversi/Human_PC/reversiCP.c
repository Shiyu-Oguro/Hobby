
/*�@�l�ԁ@VS�@PC�@���@*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapio.h"
 
#define MSIZE 10
#define MCHOICE 60 //�ő�I������

//___________________________________________________________________________________
//�\���֘A

//�\������N
void renew(char map[MSIZE][MSIZE]){
	int x,y;
	
	printf("\n");
	printf("  1  2  3  4  5  6  7  8\n");
	printf("--------------------------\n");	
	
	for(y=1;y<9;y++){
		printf("%d|",y);
		for(x=1;x<9;x++){
			if(map[y][x]>1){
					printf("�� ");
			}else if(map[y][x]>0){					
				printf("�� ");
			}else if(map[y][x]<0){
				printf("�� ");
			}else{
				printf("�E ");
			}
		}
		printf("\n");
	}
}

//�u�����Ƃ�����߂����N
void MrShot(int v,int x0,int y0,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,i;
	for(i=0;i<8;i++){
		x=x0;
		y=y0;
		if(map[ y+sy[i] ][ x+sx[i] ] == -v){//����i������R�}�Ȃ�
			while(1){
				x=x+sx[i];
				y=y+sy[i];
					if(map[ y+sy[i] ][x+sx[i] ]==v){//�����̃R�}
						while(1){
							map[y][x]=v;
							if( (x==x0) && (y==y0) ){
								break;
							}
							x=x-sx[i];
							y=y-sy[i];
						}
						break;
					}else if( (map[ y+sy[i] ][x+sx[i] ]>1) || !(map[ y+sy[i] ][x+sx[i] ]) ){//�ǂ��󔒂���
						break; //�u���Ȃ�
					}
			}
			
		}
	}
}

//______________________________________________________________________________
//�������

//�T���N
int MrSearch(int v,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,hyouji=0,choice=0;
	for(x=1;x<9;x++){
		for(y=1;y<9;y++){
			hyouji=MrEight(v,x,y,map,sx,sy);//8�����N
			
			if(hyouji>0){//�u����					
				map[y][x]=2;
				choice++;
			}
		}
	}
	return choice;
}



//�W�����N
int MrEight(int v,int x0,int y0,char map[MSIZE][MSIZE],int sx[8],int sy[8])
{
	int x,y,i;
	if((map[y0][x0]==-1) || (map[y0][x0]==1)){//���łɒu����Ă���i�O�ʊO�̃R�}������j
		return 0;
	}
	for(i=0;i<8;i++){
		x=x0;
		y=y0;
		if(map[ y+sy[i] ][ x+sx[i] ] == -v){//����i������R�}�Ȃ�	
			while(1){
				x=x+sx[i];
				y=y+sy[i];
					if(map[ y+sy[i] ][x+sx[i] ]==v){//�����̃R�}��������
						return (y0*10+x0);
					}else if(map[ y+sy[i] ][x+sx[i] ]==0 || (map[ y+sy[i] ][x+sx[i] ]>1 )){//�R�}������or*or��
						break; //�u���Ȃ�
					}
			}
		}
	}
	return 0;
}

//�W�v�N
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

//�]�����Z�b�g�N
void MrResetB(char brain[MSIZE][MSIZE])
{
	int i,j;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			brain[j][i]=0;
		}
	}
}

//�}�b�v���Z�b�g�N
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

//�}�b�v�u�������N
void MrChange(char map[MSIZE][MSIZE],char brain[MSIZE][MSIZE])
{
	int i=0,j=0;
	for(j=1;j<9;j++){
		for(i=1;i<9;i++){
			brain[j][i]=map[j][i];
		}
	}
}

//�f�o�b�N�p

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
//�v�l

//����N
int MrKettei(int get,int v,char map[MSIZE][MSIZE],int sx[8],int sy[8],char brain[MSIZE][MSIZE])
{
	int i,j,x,y,V,X,nget,N=(MCHOICE*100);
	V=v;
	MrChange(map,brain);
	//for(y=1;y<9;y++){
		//for(x=1;x<9;x++){
			
			X=MrSearch(v,map,sx,sy);//�T���N�@�i���ɂ��map�͍X�V�ς݁j
			//printf("X:%d\n",X); //
			
			for(j=1;j<9;j++){//��������͔]��
				for(i=1;i<9;i++){
					MrChange(map,brain);//brain��map���㏑��
					if(map[j][i]==2){
						MrShot(V,i,j,brain,sx,sy);//�]���őł�(brain�ɑł�)
						V*=-1;//�]����Ԃ����ւ�
						nget=MrSearch(V,brain,sx,sy); //�]����brain�ɑł�������Abrain�ŒT���ׂ�
						//printf("�u����ӏ�:%d\n\n",nget);
						nget=nget*100+j*10+i;//n,x,y�̃f�[�^���\��
						if(nget<N){
							N=nget;//�ŏ��l�X�V
						}
						V=v;//���ɖ߂�
						MrResetB(brain);
					}
				}
			}

		//}
	//}
	//printf("N=%d\n",N);
	return N;//�ŏ��萔�f�[�^N��Ԃ�
}

//_________________________________________________________________________________________
void MrSinkou(int *flag,int okeru,char map[MSIZE][MSIZE])
{
	int get;
	if(!okeru){
				if(flag>0){
					*flag=0;
					puts("�p�X���܂�");
				}else{
					puts("<<<<[ �����I�� ]>>> ���݂��u����Ƃ��낪�����Ȃ���");
					get=MrSyuukei(map);
					if(get>0){
						printf("���̏���");
					}else if(get<0){
						printf("���̏���");
					}else{
						printf("��������");
					}
				}
	}
}

//�l�Ԃ̃^�[��
int Human(int hturn,int v,int sx[8],int sy[8],char map[MSIZE][MSIZE])
{
	int get,hitX,hitY;
	printf("���Ȃ��̎��:");
	if(hturn){
	puts("��");
	}else{
	puts("��");
	}
		while(1){
			puts("�łꏊ�́H X,Y:");
			scanf("%d",&hitX);
			scanf("%d",&hitY);
			get=MrEight(v,hitX,hitY,map,sx,sy); 
			printf("GET:%d\n",get);
			if(get){ /*8�����T����,���݂����*/
			MrShot(v,hitX,hitY,map,sx,sy); 
				break;
			}
		}
		return 0;
}

//PC�̃^�[��
int PC(int hturn,int v,int sx[8],int sy[8],char map[MSIZE][MSIZE],char brain[MSIZE][MSIZE],int *flag)
{	
	int get;
	printf("PC�̎��:");
	if(!hturn){
	puts("��");
	}else{
	puts("��");
	}
		get=MrKettei(get,v,map,sx,sy,brain);//����N����N���������Ă���
		printf("�ł�����:%d,%d\n",get%10,get/10%10);
		if( !get ){
			MrSinkou(&flag,get,map);
			return 0;
		}
		//printf("PC���u���Ƃ���:%d,%d\n",(get%10),(get/10%10));
		MrShot(v,(get%10),(get/10%10),map,sx,sy);//�f�[�^�𕪉����āA�Ԃ�
		MrResetM(map);					
		MrResetB(brain);
		return 0;
}

//_________________________________________________________________________________________

int main(){//��ԁA�ł�����A

	int v=1,hitY,hitX,get,okeru,flag=1,turn,hturn;
	int sx[8]={1,1,0,-1,-1,-1,0,1};
	int sy[8]={0,1,1,1,0,-1,-1,-1};
	char map[MSIZE][MSIZE]={0};
	char brain[MSIZE][MSIZE]={0};

	read_map_file("map1.csv",map);
	puts("���ꂩ��΋ǂ��n�߂܂��B");
	puts("[ ���Ȃ��i�l�ԁj�̎�Ԃ�I�� ] ��U(��):1 ��U(��):0");
	scanf("%d",&turn);
	if(!turn){//��U
		hturn=0;
	}else{//��U
		hturn=1;
	}

		if(hturn==1){//��U�Ȃ�	
			while(1){
				v=-1;
				renew(map);/*�X�V*/
				okeru=MrSearch(v,map,sx,sy);//�T���N
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=Human(hturn,v,sx,sy,map);//Human
				renew(map);
				
				v=1;
				okeru=MrSearch(v,map,sx,sy);//�T���N
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=PC(hturn,v,sx,sy,map,brain,&flag);//PC
			}
		}else{//��U�Ȃ�
			while(1){
				v=-1;
				renew(map);/*�X�V*/
				okeru=MrSearch(v,map,sx,sy);//�T���N
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=PC(hturn,v,sx,sy,map,brain,&flag);//PC
				renew(map);
				
				v=1;
				okeru=MrSearch(v,map,sx,sy);//�T���N
				MrResetM(map);
				MrSinkou(&flag,okeru,map);
				get=Human(hturn,v,sx,sy,map);			
				}
		}
 return 0;

}
