int cpt=0;

int y=0; //Cordonnés y
for(int i=0;i<NMAX;i++) {

        if(Gri[i][y].Contient_pion_blanc()) {
            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;

for(int i=0;i<NMAX;i++) {

        if(Gri[i][y].Contient_pion_noir()) {
            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+1].Contient_pion_noir()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+1].Contient_pion_blanc()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+2].Contient_pion_blanc()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++) {

        if(Gri[i][y+2].Contient_pion_noir()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;

int x=0; //Cordonnés x
for(int j=0;j<NMAX;j++) {

        if(Gri[x][j].Contient_pion_blanc()) {

            cpt++;
        }

}

if(cpt==3){return 1;}

cpt=0;

for(int j=0;j<NMAX;j++) {

        if(Gri[x][j].Contient_pion_noir()) {

            cpt++;
        }


}

if(cpt==3){return 2;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+1][j].Contient_pion_noir()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+1][j].Contient_pion_blanc()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+2][j].Contient_pion_blanc()) {

            cpt++;
        }
}

if(cpt==3){return 1;}

cpt=0;


for(int j=0;j<NMAX;j++) {

        if(Gri[x+2][j].Contient_pion_noir()) {

            cpt++;
        }
}

if(cpt==3){return 2;}

cpt=0;


for(int i=0;i<NMAX;i++){
    if(Gri[i][i].Contient_pion_blanc()){
        cpt++;
    }
}

if(cpt==3){return 1;}

cpt=0;


for(int i=0;i<NMAX;i++){
    if(Gri[i][i].Contient_pion_noir()){
        cpt++;
    }
}

if(cpt==3){return 2;}

cpt=0;

int d=2;
for(int i=0;i<NMAX;i++){
    if(Gri[i][d-i].Contient_pion_blanc()){
        cpt++;
    }
}

if(cpt==3){return 1;}

cpt=0;

d=2;
for(int i=0;i<NMAX;i++){
    if(Gri[i][d-i].Contient_pion_noir()){
        cpt++;
    }
}

if(cpt==3){return 2;}

return -1;
