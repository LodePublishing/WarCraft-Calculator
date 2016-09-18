void GENETIC::Mutate()
{
void RACE::Mutate()
{
        unsigned char ta,x,y,k;
//      unsigned char tb,tmp[MAX_LENGTH];
        //length=MAX_LENGTH;
        if(length==0) return;

        for(k=0;k<2;k++)
        for(x=0;x<MAX_LENGTH;x++)
        {
                //delete one variabel entry and move
                if(((setup.GenerateBuildorder==0)||(Variabel[Build_Bv[program[x][k].order]]==1))&&(rand()%MAX_LENGTH==0))
                {
                        switch(rand()%3)
                        {
                                case 0://delete one variabel entry and move - Mehrere Schmieden/Kasernen etc. zulassen!
                                        for(y=x;y<MAX_LENGTH-1;y++)
                                                program[y][k].order=program[y+1][k].order;
                                        program[x][k].newmut=1;break;
                                case 1://add one variabel entry
                                        for(y=MAX_LENGTH-1;y>x;y--)
                                                program[y][k].order=program[y-1][k].order;
                                        program[y][k].newmut=2;
                                        y=rand()%Max_Build_Types;
                                        if(setup.GenerateBuildorder==1)
                                                while(Variabel[y]==0) y=rand()%Max_Build_Types;
                                                program[x][k].order=y;break;
                                case 2://change one entry
                                        y=rand()%Max_Build_Types;//Optimieren
                                        if(setup.GenerateBuildorder==1)
                                                while(Variabel[y]==0) y=rand()%Max_Build_Types;
                                                program[x][k].order=y;break;
                        }
                }
                else
                if(rand()%MAX_LENGTH==0)
                {
                //exchange two entries
                      y=rand()%MAX_LENGTH; //TODO: Aendern in bevorzugtes Ziel => Naehe
                        if(x!=y)
                        {
                                program[x][k].mutate=y;
                                program[y][k].mutate=x;
                                ta=program[x][k].order;
                                program[x][k].order=program[y][k].order;
                                program[y][k].order=ta;
                        }
                }
}


class GENETIC
{
	        public:
               void Mutate();
					                Program program[MAX_LENGTH][2];
							                unsigned char IP;
									                unsigned char protein[MAX_GOALS];
											                unsigned char length;

}

