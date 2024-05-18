//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <SI_EFM8BB1_Register_Enums.h>                // SFR declarations

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
//void SiLabs_Startup (void)
//{
  // Disable the watchdog here
//}

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
  ORG 0000H
  LJMP BEGIN;
  ORG 000BH
  LJMP INT_TIMER_0;
  ORG 0080H
  BEGIN:
    MOV WDTCN, #0DEH;
    MOV WDTCN, #0ADH;
    ORL P1MDIN, #0FFH;
    ORL P1MDOUT, #0FFH;
    ORL P1SKIP, #0FFH;
    ORL XBR2, #040H;

    ORL LFO0CN, #083H;
    ANL LFO0CN, #0F2H;
    ORL LFO0CN, #080H;

    ORL CLKSEL, #077H;
    ANL CLKSEL, #0DAH;
    MOV R0, #00FH;

    ESPERA1:
      DJNZ R0, ESPERA1;

    MOV CKCON0, #04H;
    MOV TMOD, #00H;

    MOV 30H, #07H;
    MOV 29H, #96H;

    MOV TL0, 29H;
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

    SETB TCON_IT0;
    SETB TCON_TR0;
    CLR TCON_TF0;

    SETB IE_ET0;
    SETB IE_EA;
    clr P1.4;

    WAITF0:
      LJMP WAITF0;

    INT_TIMER_0:
      CLR IE_EA;
      CLR TCON_TF0;
      //CLR TCON_TR0;
      MOV TL0, 029H;
      MOV TH0, 031H;
      CPL P1.4;
      SETB IE_EA;
      //SETB TCON_TR0;
      RETI;

#pragma endasm
      while(1){}
}
