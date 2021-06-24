#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;

int main(){
    char alg[6]={0};
    int cyl_num;
    int cyl_init;
    int dir;
    int request[5000]={0};
    int moveans[5000]={0};
    int movelen;
    char tmp[5000]={0};

    printf("Disk scheduling algorithms: ");
    scanf("%s",&alg);

    printf("Number of disk cylinders: ");
    scanf("%d",&cyl_num);

    printf("Initial disk head cylinder: ");
    scanf("%d",&cyl_init);

    printf("Direction of disk head: ");
    scanf("%d",&dir);

    printf("Disk requests: ");
    scanf("%s",&tmp);

    int cur_n = 0;
    char *str = tmp;
	char *end = str;
	while(*end) {
		int n = strtol(str, &end, 10);
		
        request[cur_n] = n;
        cur_n++;
		while (*end == ',') {
			end++;
		}
		str = end;
	}

    if (strcmp(alg,"FCFS") == 0){
        cur_n = 0;

        //排班
        while(request[cur_n] != -1){
            moveans[cur_n] = request[cur_n];
            cur_n++;
        }
        moveans[cur_n] = -1;

        
    }

    if (strcmp(alg,"SSTF") == 0){
        int shortest_id;
        int shortest_len=-1;
        int cur_loc = cyl_init;
        int ans_n=0;

        //排班

        //sort
        cur_n = 0;
        while(request[cur_n] != -1){
            cur_n++;
        }
        sort(request,request + (cur_n));
        
        cur_n = 0;

        while(request[1] != -1){
            shortest_len = -1;
            cur_n = 0;


            while(request[cur_n] != -1){
                if(abs(cur_loc - request[cur_n]) <= shortest_len || shortest_len==-1){
                    if (abs(cur_loc - request[cur_n]) == shortest_len){
                        if (dir == 0){
                            shortest_len = abs(cur_loc - request[cur_n]);
                            shortest_id = cur_n;
                        }else{
                            //do nothing
                        }
                    }else{
                        shortest_len = abs(cur_loc - request[cur_n]);
                        shortest_id = cur_n;
                    }
                    
                    
                }
            
                cur_n++;
            }
            cur_loc = request[shortest_id];
            
            //add to ans
            moveans[ans_n] = request[shortest_id];
            ans_n++;
            //remove it from pool
            request[shortest_id] = request[cur_n-1];
            request[cur_n-1] = -1;

        }
        moveans[ans_n] = request[0];
        moveans[ans_n+1] = -1;


        
    }

    if (strcmp(alg,"SCAN") == 0){
        cur_n = 0;
        int tmp_n=0;
        int ans_n=0;

        //排班
        if(dir == 0){ //低到高
        
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n; //turning 包含這裡開始往上收 cur_n   >=分水嶺 or 最後一個
                    if(request[cur_n+1] == -1 && request[cur_n]<cyl_init){
                        turning = cur_n+1;
                    }

                    tmp_n = turning;

                    while(request[tmp_n] != -1){ //往上收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    if(turning != 0){ //要回頭才要到底99
                        if (moveans[ans_n-1] != cyl_num-1 || ans_n==0){
                            moveans[ans_n] = cyl_num-1;
                            ans_n++;
                        }
                    }

                    tmp_n = turning-1;

                    int rev_n=ans_n;
                    while(tmp_n != -1){//往下收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }
        }
        else{//高到低
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n-1; //turning 包含這裡開始往下收 cur_n   >=分水嶺 or 最後一個

                    //如果相等cur_n取最後一個相等的
                    while(request[turning+1] == cyl_init){
                        turning++;
                    }

                    
                    tmp_n = turning;

                    while(tmp_n != -1){//往下收
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    if(request[turning+1] !=-1){ //要回頭才要到底0 
                        if (moveans[ans_n-1] != 0 || ans_n==0){
                            moveans[ans_n] = 0;
                            ans_n++;
                        }
                    }


                    tmp_n = turning+1;
                    

                    
                    while(request[tmp_n] != -1){ //往上收
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    
                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }

        }

        
    }

    if (strcmp(alg,"LOOK") == 0){
        cur_n = 0;
        int tmp_n=0;
        int ans_n=0;

        //排班
        if(dir == 0){ //低到高
        
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n; //turning 包含這裡開始往上收 cur_n   >=分水嶺 or 最後一個
                    if(request[cur_n+1] == -1 && request[cur_n]<cyl_init){
                        turning = cur_n+1;
                    }

                    tmp_n = turning;

                    while(request[tmp_n] != -1){ //往上收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }


                    tmp_n = turning-1;

                    
                    while(tmp_n != -1){//往下收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }
        }
        else{//高到低
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n-1; //turning 包含這裡開始往下收 cur_n   >=分水嶺 or 最後一個

                    //如果相等cur_n取最後一個相等的
                    while(request[turning+1] == cyl_init){
                        turning++;
                    }

                    
                    tmp_n = turning;

                    while(tmp_n != -1){//往下收
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    


                    tmp_n = turning+1;
                    

                    
                    while(request[tmp_n] != -1){ //往上收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }

        }

        
    }

    if (strcmp(alg,"CSCAN") == 0){
        cur_n = 0;
        int tmp_n=0;
        int ans_n=0;

        //排班
        if(dir == 0){ //低到高
        
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n; //turning 包含這裡開始往上收 cur_n   >=分水嶺 or 最後一個
                    if(request[cur_n+1] == -1 && request[cur_n]<cyl_init){
                        turning = cur_n+1;
                    }

                    tmp_n = turning;

                    while(request[tmp_n] != -1){ //往上收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    if(turning != 0){ //要回頭才要到底99 -> 0 
                        if (moveans[ans_n-1] != cyl_num-1 || ans_n==0){
                            moveans[ans_n] = cyl_num-1;
                            ans_n++;
                        }

                        if(request[0] != 0){
                            moveans[ans_n] = 0;
                            ans_n++;
                        }
                        
                        
                    }

                    tmp_n = turning-1;

                    int rev_n=ans_n;
                    while(tmp_n != -1){//往下收 但要反
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    int rev_tmp[5000]={0};
                    int x = 0;
                    int i ;
                    for(i = rev_n;i<=ans_n-1;i++){
                        rev_tmp[x] = moveans[i];
                        x++;
                    }

                    reverse(rev_tmp , rev_tmp + x);

                    x = 0;
                    for(i = rev_n;i<=ans_n-1;i++){
                        moveans[i] = rev_tmp[x];
                        x++;
                    }

                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }
        }
        else{//高到低
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n-1; //turning 包含這裡開始往下收 cur_n   >=分水嶺 or 最後一個

                    //如果相等cur_n取最後一個相等的
                    while(request[turning+1] == cyl_init){
                        turning++;
                    }

                    
                    tmp_n = turning;

                    while(tmp_n != -1){//往下收
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    if(request[turning+1] !=-1){ //要回頭才要到底0 -> 99
                        if (moveans[ans_n-1] != 0 || ans_n==0){
                            moveans[ans_n] = 0;
                            ans_n++;
                        }

                        tmp_n = 0;
                        while (request[tmp_n+1]!=-1){
                            tmp_n++;
                        }

                        if(request[tmp_n] != cyl_num-1){
                            moveans[ans_n] = cyl_num-1;
                            ans_n++;
                        }
                        
                        
                    }


                    tmp_n = turning+1;
                    

                    int rev_n=ans_n;
                    while(request[tmp_n] != -1){ //往上收 但相反
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    int rev_tmp[5000]={0};
                    int x = 0;
                    int i ;
                    for(i = rev_n;i<=ans_n-1;i++){
                        rev_tmp[x] = moveans[i];
                        x++;
                    }

                    reverse(rev_tmp , rev_tmp + x);

                    x = 0;
                    for(i = rev_n;i<=ans_n-1;i++){
                        moveans[i] = rev_tmp[x];
                        x++;
                    }
                    


                    
                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }

        }

        
    }

    if (strcmp(alg,"CLOOK") == 0){
        cur_n = 0;
        int tmp_n=0;
        int ans_n=0;

        //排班
        if(dir == 0){ //低到高
        
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n; //turning 包含這裡開始往上收 cur_n   >=分水嶺 or 最後一個
                    if(request[cur_n+1] == -1 && request[cur_n]<cyl_init){
                        turning = cur_n+1;
                    }

                    tmp_n = turning;

                    while(request[tmp_n] != -1){ //往上收 
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }


                    tmp_n = turning-1;

                    int rev_n=ans_n;
                    while(tmp_n != -1){//往下收 但要反
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    int rev_tmp[5000]={0};
                    int x = 0;
                    int i ;
                    for(i = rev_n;i<=ans_n-1;i++){
                        rev_tmp[x] = moveans[i];
                        x++;
                    }

                    reverse(rev_tmp , rev_tmp + x);

                    x = 0;
                    for(i = rev_n;i<=ans_n-1;i++){
                        moveans[i] = rev_tmp[x];
                        x++;
                    }

                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }
        }
        else{//高到低
            int turning = 0;
            cur_n = 0;
            while(request[cur_n] != -1){
                cur_n++;
            }
            sort(request,request + (cur_n));
            
            cur_n = 0;
            while(request[cur_n] != -1){
                if (request[cur_n]>=cyl_init || request[cur_n+1] == -1){
                    
                    turning = cur_n-1; //turning 包含這裡開始往下收 cur_n   >=分水嶺 or 最後一個

                    //如果相等cur_n取最後一個相等的
                    while(request[turning+1] == cyl_init){
                        turning++;
                    }

                    
                    tmp_n = turning;

                    while(tmp_n != -1){//往下收
                        moveans[ans_n] = request[tmp_n];
                        tmp_n--;
                        ans_n++;
                    }

                    


                    tmp_n = turning+1;
                    

                    int rev_n=ans_n;
                    while(request[tmp_n] != -1){ //往上收 但相反
                        moveans[ans_n] = request[tmp_n];
                        tmp_n++;
                        ans_n++;
                    }

                    int rev_tmp[5000]={0};
                    int x = 0;
                    int i ;
                    for(i = rev_n;i<=ans_n-1;i++){
                        rev_tmp[x] = moveans[i];
                        x++;
                    }

                    reverse(rev_tmp , rev_tmp + x);

                    x = 0;
                    for(i = rev_n;i<=ans_n-1;i++){
                        moveans[i] = rev_tmp[x];
                        x++;
                    }
                    


                    
                    moveans[ans_n] = -1;
                    break;
                }
                cur_n++;
            }

        }

        
    }



    //總距離
    movelen = 0;
    cur_n = 0;
    while(moveans[cur_n] != -1){
        if (cur_n == 0){
            movelen +=  abs(moveans[0] - cyl_init);
        }
        if(moveans[cur_n+1] != -1){
            movelen += abs(moveans[cur_n] - moveans[cur_n+1]);
        }
        cur_n++;
    }

    printf("\nMovement: ");
    cur_n = 0;
    while(1){
        if(moveans[cur_n] == -1){
            break;
        }
        printf("%d -> ",moveans[cur_n]);
        cur_n++;
    }
    printf("END");
    printf("\nTotal len: %d",movelen);
    

    return 0;
}