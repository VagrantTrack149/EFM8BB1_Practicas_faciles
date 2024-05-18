//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                // SFR declarations

unsigned char TL0_M0;
unsigned char TH0_M0;

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void silabs_startup(void){
  //Disable the watchdog timer
  #pragma asm
    MOV WDTCN,#0DEH;
    MOV WDTCN, #0ADH;
  #pragma endasm
}

void Port_config(void){
  #pragma asm
    ORL P1MDIN, #0FFH;
        ORL P1MDOUT, #0FFH;
        ORL P1SKIP, #0FFH;
        ORL XBR2, #040H;
    MOV P1,#0FFH;
  #pragma endasm
}
void Clock_config(void){
  #pragma asm
  //Divisor
  ORL LFO0CN, #083H;
      ANL LFO0CN, #0F2H;
      ORL LFO0CN, #080H;
  //Reloj de 80
  ORL CLKSEL, #077H;
      ANL CLKSEL, #0DAH;
      MOV R0, #00FH;

      ESPERA1:
          DJNZ R0, ESPERA1;
  #pragma endasm
}


void T0_MODE0(void){
  #pragma asm
  MOV CKCON0, #04H;
  MOV TMOD, #00H;
  SETB TCON_IT0; //SETB TCON,ITO; //SETB TCON.0;
  CLR TCON_TF0;//CLR TCON,TF0; //CLR TCON.5;
  #pragma endasm
}

void T0_MODE0_Precarga(unsigned char TH0_M0_1, unsigned char TL0_M0_1){
  TH0_M0 = TH0_M0_1;
  TL0_M0 = TL0_M0_1;
  #pragma asm
    MOV 30H, TL0_M0;
        MOV 29H, TH0_M0;
        MOV TL0, TL0_M0;
        MOV A, 29H;
        SWAP A;
        RR A;
        ANL A, #07H;
        MOV 31H, A;
        MOV A, 30H;
        RL A;
        RL A;
        RL A;
        ORL 31H, A;
        MOV TH0, 31H;
  #pragma endasm
}

void T0_MODE0_START(void){
  TCON_TF0=0;
  TCON_TR0=1;
}

void Rutina_inte_T0(void){
  IE_EA=0;
  TCON_TF0=0;
  #pragma asm
    CPL P1.4;
    MOV TL0,029H;
    MOV TH0,031H;
  #pragma endasm
  IE_EA=1;
}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
// Note: the software watchdog timer is not disabled by default in this
// example, so a long-running program will reset periodically unless
// the timer is disabled or your program periodically writes to it.
//
// Review the "Watchdog Timer" section under the part family's datasheet
// for details. To find the datasheet, select your part in the
// Simplicity Launcher and click on "Data Sheet".
//-----------------------------------------------------------------------------
int main (void)
{
#pragma asm
    ORG 000H;
      LJMP BEGIN;
    ORG 00BH;
      LJMP INT_TIMER_0;
    ORG 0080H;
      BEGIN:
#pragma endasm
        silabs_startup();
        Port_config();
        Clock_config();
        T0_MODE0();
        T0_MODE0_Precarga(0x07,0x96);
        IE_ET0=1;
        IE_EA=1;
        T0_MODE0_START();
        #pragma asm
        SETB P1.4;
        WAITF0:
          LJMP WAITF0;
        INT_TIMER_0:
          LCALL Rutina_inte_T0;
        RETI;
        #pragma endasm
        while(1){}
}


