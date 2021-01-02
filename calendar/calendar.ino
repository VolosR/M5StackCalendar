int n=7;
#include <M5Core2.h>
#include "calc.h"
#include "7seg20.h"

#define orange 0xFC64
#define dark 0x02F3
#define darkOrange 0xC18A
#define red 0xFC7F
#define purple 0xC18A
#define light 0xCF3E


RTC_TimeTypeDef RTCtime;
RTC_DateTypeDef RTCDate;

int posX2[4];
int n2=4;
int boxSize2=45;
int space2=3;
int start2=25;
String math2="";
float numbers2[3]={0,0,0};
int fase2=0;
char buttons2[4][4]={{'7','4','1','0'},{'8','5','2','.'},{'9','6','3','='},{'/','*','-','+'}};
char operation2=' ';
bool irq2 = false;

String cs="";
String t="";
String h="";
String m="";
String s="";
String d="";
String cd="";
String days2[7]={"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};

int th,tm,ts=0;
int f=0;


int posX[7];

int boxSize=26;
int space=2;
int start=21;


String days[7]={"Mo","Tu","We","Th","Fr","Sa","Su"};
int monthsDays[12]={31,28,31,30,31,30,31,31,30,31,30,31};
int startDay[12]={5,1,1,4,6,2,4,7,3,5,1,3};
String monthNames[12]={"January","February","March","April","May","June","July","August","September","October","November","December"};


void setup()
{
M5.begin();
M5.Lcd.fillScreen(TFT_WHITE);
M5.Lcd.setSwapBytes(true);
   
}

int pres=1;
int chosen=0;
bool moode=0;
bool calcStarted=0;
bool calendarStarted=0;
void loop()
{
  flushTime();
  TouchPoint_t pos= M5.Touch.getPressPoint();
  int y=pos.y;
  int x=pos.x;

    if(x>240)
     moode=!moode;
    if(moode==0){
    if(calendarStarted==0)
    startCalendar();
    if (y>0) {
       if(pres==1)
        {
          if(x>120 && x<230){
          pres=0;
          chosen++;
        if(chosen==12)
        chosen=0;}

          if(x<=120){
          pres=0;
          chosen--;
        if(chosen==-1)
        chosen=11;}

        fill(chosen);
        }
            }



    else {pres=1;}}

    if(moode==1)
    { 
      if(calcStarted==0)
      startCalc();
      if (pos.x>0) {
       if(pos.y>0 && pos.y<40)
       resetCalc();
       if(pres==1)
       for(int i=0;i<n2;i++)
          for(int j=0;j<n2;j++)
          {
            if(pos.x>posX2[j] && pos.x<posX2[j]+boxSize2 && pos.y>posX2[i]+22 && pos.y<posX2[i]+boxSize2+22 ){
            M5.Lcd.fillRoundRect(posX2[j],posX2[i]+22,boxSize2,boxSize2,4,darkOrange);



         if(buttons2[j][i]=='0' || buttons2[j][i]=='1' || buttons2[j][i]=='2' || buttons2[j][i]=='3' || buttons2[j][i]=='4' || buttons2[j][i]=='5' || buttons2[j][i]=='6' || buttons2[j][i]=='7' || buttons2[j][i]=='8' || buttons2[j][i]=='9' || buttons2[j][i]=='.' ){
         if(math2.length()<7){
         M5.Lcd.fillRoundRect(posX2[0],3,188,40,4,dark);
         math2=math2+String(buttons2[j][i]);
         }}

         if(buttons2[j][i]=='+' || buttons2[j][i]=='-' || buttons2[j][i]=='*' || buttons2[j][i]=='/' ){
           M5.Lcd.setTextColor(light,orange);
          if(numbers2[0]==0)
          numbers2[0]=math2.toFloat();

           math2="";
          operation2=buttons2[j][i];
          M5.Lcd.fillRoundRect(posX2[0],3,188,40,4,dark);
         }

         if(buttons2[j][i]=='=' ){

          numbers2[1]=math2.toFloat();
          if(operation2=='+')
          numbers2[2]=numbers2[0]+numbers2[1];

          if(operation2=='-')
          numbers2[2]=numbers2[0]-numbers2[1];

          if(operation2=='*')
          numbers2[2]=numbers2[0]*numbers2[1];

          if(operation2=='/')
          numbers2[2]=numbers2[0]/numbers2[1];

          numbers2[0]=numbers2[2];
          int check2=numbers2[2]*100.00;
          if(check2%100==0){
          math2=String(int(numbers2[2]));}
          else{
          math2=String(numbers2[2]);}
          M5.Lcd.fillRoundRect(posX2[0],3,188,40,4,dark);
         }

           bool decimal=false;


          int check2=math2.toFloat()*100.00;
          if(check2%100==0){
          decimal=false;}
          else{
          decimal=true;}

            M5.Lcd.setFreeFont(&DSEG7_Classic_Bold_30);
            M5.Lcd.setTextColor(light,dark); //.............................................
            if(decimal==true)
            M5.Lcd.drawString(math2,30,8);
            else
            M5.Lcd.drawString(math2,30,8);

            pres=0;
            pos.x=0;
            pos.y=0;


            M5.Lcd.setTextFont(4);

    if(j<3 && i <3 ){
       M5.Lcd.setTextColor(light,dark);
       M5.Lcd.fillRoundRect(posX2[j],posX2[i]+22,boxSize2,boxSize2,4,dark);}
    else
    {
    M5.Lcd.setTextColor(light,darkOrange);
    M5.Lcd.fillRoundRect(posX2[j],posX2[i]+22,boxSize2,boxSize2,4,darkOrange);}
   
    
    
    M5.Lcd.drawString(String(buttons2[j][i]), posX2[j]+16, posX2[i]+34);

    M5.Lcd.setTextFont(4);

            }
            }
    }else {pres=1;}
}

}

void fill(int x){
  M5.Lcd.setTextColor(dark,WHITE);
  M5.Lcd.setTextFont(4);
  M5.Lcd.drawString("<",posX[0],8);
  M5.Lcd.drawString(">",posX[6],8);
  M5.Lcd.setTextFont(2);
  M5.Lcd.fillRect(50,6,130,34,WHITE);
  M5.Lcd.drawString(monthNames[x]+" ",50,12,4);
  M5.Lcd.setTextColor(TFT_WHITE);

  int curr=0;
    for(int i=0;i<n;i++)
    for(int j=0;j<n;j++){

    if(i==0){
    M5.Lcd.fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,darkOrange);
    M5.Lcd.drawString(days[j],posX[j]+6,posX[i]+4+20);

    }
    else{
    curr++;
    M5.Lcd.fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,TFT_WHITE);
    if(curr>=startDay[x])  {
    int n=curr-startDay[x]+1;
    if(n<=monthsDays[x]){
    M5.Lcd.fillRoundRect(posX[j],posX[i]+20,boxSize,boxSize,2,dark);
    M5.Lcd.drawString(String(n),posX[j]+6,posX[i]+4+20);}

     }
     }

  }}



  void flushTime(){
    M5.Lcd.setTextColor(dark,WHITE);
    M5.Rtc.GetTime(&RTCtime);
    M5.Rtc.GetDate(&RTCDate);
   
    h=String(RTCtime.Hours);
    if(h.length()<2)
    h="0"+h;

    m=String(RTCtime.Minutes);
    if(m.length()<2)
    m="0"+m;
    String n=h+":"+m+"  ";

    s=String(RTCtime.Seconds);
    if(s.length()<2)
    s="0"+s;
   
     if(n!=t){
     M5.Lcd.drawString(n,240,10,4);
     t=n;
     M5.Lcd.drawString("BAT: "+String(M5.Axp.GetBatVoltage())+"V",240,223,2);
    }
     
     
     if(cs!=s){
     M5.Lcd.setTextColor(purple,WHITE);   
     M5.Lcd.drawString(s+"  ",240,40,7);
     
     cs=s;
     ts++;
     if(ts==60){ts=0; tm++;}
     if(tm==60){tm=0; th++;}
     if(th==24){tm=0; th=0; ts=0;}
    // M5.Lcd.drawString(String(th)+":"+String(tm)+":"+String(ts)+"    ",0,100,4);
    }

    d=String(RTCDate.Date)+"/"+String(RTCDate.Month);
    if(d!=cd)
      {
      M5.Lcd.setTextColor(dark,WHITE);
      M5.Lcd.drawString(d+"  ",240,96,4);
     
      
      M5.Lcd.setTextColor(purple,WHITE);
       M5.Lcd.drawString(String(RTCDate.Year)+"  ",240,120,4);
        M5.Lcd.setTextColor(BLACK,WHITE);
         M5.Lcd.drawString(days2[RTCDate.WeekDay]+"  ",240,142,2);

         
        
       cd=d;
      }
}

void resetCalc(){
  for(int i=0;i<3;i++)
  numbers2[i]=0;
  math2="";
   M5.Lcd.fillRoundRect(posX2[0],3,188,40,4,dark);
 

  }

  void startCalendar()
  {
     M5.Lcd.fillRect(0,0,239,239,WHITE);
    M5.Lcd.setTextFont(2);
    M5.Lcd.pushImage(240,160,64,64,calc[moode]);
    for(int i=0;i<n;i++)
    posX[i]=(start+(i*boxSize)+(space*i));
    fill(0);
    M5.Lcd.setTextColor(0xB71F);

    calendarStarted=1;
    calcStarted=0;
   
    }

  void startCalc()
  {
        calcStarted=1;
        calendarStarted=0;
        resetCalc();
        M5.Lcd.fillRect(0,0,239,239,WHITE);
        M5.Lcd.pushImage(240,160,64,64,calc[moode]);
     M5.Lcd.setTextColor(light);
     M5.Lcd.drawString("0",180,8,4);
     M5.Lcd.setTextFont(4);
   for(int i=0;i<n2;i++)
   posX2[i]=(start2+(i*boxSize2)+(space2*i));
   M5.Lcd.fillRoundRect(posX2[0],3,188,40,4,dark);

   for(int i=0;i<n2;i++)
    for(int j=0;j<n2;j++){

    if(j<3 && i <3 )
    M5.Lcd.fillRoundRect(posX2[i],posX2[j]+22,boxSize2,boxSize2,4,dark);
    else
    M5.Lcd.fillRoundRect(posX2[i],posX2[j]+22,boxSize2,boxSize2,4,darkOrange);
    M5.Lcd.drawString(String(buttons2[i][j]), posX2[i]+16, posX2[j]+34);
    
    }}
