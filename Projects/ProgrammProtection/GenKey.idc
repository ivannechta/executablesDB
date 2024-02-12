#include <idc.idc>

static main(){

auto a;
auto i;
auto size;              
auto f;
auto prev;
auto Fstart;
auto addition;
f=fopen("e:\\temp\\key.ini","w");


a=AskAddr (0,"Введите адрес функции");
size=AskLong (0,"Введите размер");
	fprintf(f,"%c%c%c%c",(a)&255,(a>>8)&255,(a>>16)&255,(a>>24)&255);
	fprintf(f,"%c%c%c%c",(size)&255,(size>>8)&255,(size>>16)&255,(size>>24)&255);


addition=0; //Дополнительные байты к длине (страховка от детерминированных кусков программы).
    prev=PrevFunction(a);
    Fstart=NextFunction(prev);
	if (a<=Fstart+3){
		addition=addition+3;
	}
	while(Fstart<=a+size){	
	   if(FindFuncEnd(Fstart)<=a+size){
	    	   addition=addition+3+1;
	    	   Fstart=FindFuncEnd(Fstart);	
	   }
	   Fstart=NextFunction(Fstart);
		if (Fstart<=a+size){
			addition=addition+3;			
		}
						
	}
	for (i=a;i<a+size+addition;i++){
		fprintf(f,"%c", Byte(i));	
	}
Message("ok\n");
fclose(f);
}