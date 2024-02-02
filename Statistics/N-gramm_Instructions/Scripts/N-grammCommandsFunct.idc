#include <idc.idc>

static main()
{
	auto f;
	auto a,b;
	auto Fstart;
	auto tmp;
	auto prev;
	auto preva;

Wait();
f=fopen("e:\\temp\\commands_from_exe.txt","w");

a=GetEntryPoint(GetEntryOrdinal(0));
a=SegStart(a);

b=SegEnd(a);
//a=NextHead(0,BADADDR);
while(a!=b){
    if(isCode(GetFlags(a))){
    if (PrevFunction(a)==BADADDR){
        prev=NextHead(0,BADADDR);
    }else{prev=PrevFunction(a);}
    Fstart=NextFunction(prev);
    
    if ((FindFuncEnd(a)>=Fstart)&&(FindFuncEnd(a)-Fstart<7)){
//	Message("%x\n",a);
        a=NextHead(a,BADADDR);
        continue;
    }
    if (
        (a==Fstart)&&("push"==GetMnem(a)) ){
    a=NextHead(a,BADADDR);    
    a=NextHead(a,BADADDR);
    }
    
    
   fprintf(f,"%s %s %s +\n", GetMnem(a), GetOpnd(a,0),GetOpnd(a,1));

        if (NextHead(a,BADADDR)==FindFuncEnd(a)){
                fprintf(f,"***\n");
		Message("func %x\n",a);
	
        }
    }
    preva=a;
    a=NextHead(a,BADADDR);
	if (preva==a){
		a=b;
	}          
}
Message("ok\n");
fclose(f);
Exit(0);
}