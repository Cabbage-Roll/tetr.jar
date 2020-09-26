#ifndef BAGS_H
#define BAGS_H


int bag_counter = 0;
int bag1[7]={};
int bag2[7]={};

///makes new second bag (7 bag buffer)
void generatebag2(){
    bag_counter=0;
    for(int i=0;i<7;i++){
        bag2[i]=rand()%7;
        for(int j=0;j<i;j++){
            if(bag2[i]==bag2[j]){
                i--;
            }
        }
    }
}

///shifts both bags
void shiftbag1(){
    if(bag_counter>6){
        generatebag2();
    }
    for(int i=0;i<6;i++){
        bag1[i]=bag1[i+1];
    }
    bag1[6]=bag2[0];
    for(int i=0;i<6;i++){
        bag2[i]=bag2[i+1];
    }
    bag_counter++;
}
#endif
