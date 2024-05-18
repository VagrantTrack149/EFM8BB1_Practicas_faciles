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
       //Desactivar el watchdog timer
        //OBLIGATORIO
        MOV WDTCN, #0DEH;
        MOV WDTCN, #0ADH;
        MOV R0, #0FFH;
        ESPERA1:
          DJNZ R0, ESPERA1;
        //INICIALIZAR Y CONFIGURAR P1 Y P0
        ORL P1MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
        ORL P1MDOUT, #0F0H; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
        ORL P1SKIP, #0FFH; //TODAS LAS TERMINALES SON IGNORADAS POR EL CROSSBAR

        ORL P0MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES SALIDAS
        ORL P0MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
        ORL P0SKIP, #0FFH;
        //ORL P2MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
        ORL P2MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
        //ORL P2SKIP, #0FFH;
        ORL XBR2, #040H;
        LCALL INIPIX;
        LCALL CLEAN;

        MOV R0,#00H;
        MOV DPTR,#Reg0;
        MOV R4,#00H; //CONTADOR
        MOV 030H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #00H;
        LCALL SETDIR;
        LCALL PALABRA1;


        MOV DPTR,#Reg1;
        MOV R4,#00H; //CONTADOR
        MOV 032H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #01H;
        LCALL SETDIR;
        LCALL PALABRA1;

        MOV DPTR,#Reg2;
        MOV R4,#00H; //CONTADOR
        MOV 034H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #02H;
        LCALL SETDIR;
        LCALL PALABRA1;
        MOV DPTR,#Reg3;
        MOV R4,#00H; //CONTADOR
        MOV 036H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #03H;
        LCALL SETDIR;
        LCALL PALABRA1;
        MOV DPTR,#Reg4;
        MOV R4,#00H; //CONTADOR
        MOV 038H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #04H;
        LCALL SETDIR;
        LCALL PALABRA1;

        MOV DPTR,#Reg5;
        MOV R4,#00H; //CONTADOR
        MOV 040H,#054H; //DIRECCION DE MEMORIA RAM 30H
        MOV R2, #00H;
        MOV R3, #05H;
        LCALL SETDIR;
        LCALL PALABRA1;


        AQUI:
          LJMP  AQUI;

        PALABRA1:
          MOV A,R4;
          MOVC A,@A+DPTR;
          MOV R0,A;
          LCALL ENVDATPI;
          LCALL DELAY1ms;
          INC R4;
          MOV A,R4;
          CJNE A,30H,PALABRA1;
          RET;

POSX:
      MOV A, R2;
      ORL A, #80H;
      MOV R0,A;
      RET;

POSY:
      MOV A, R3;
      ORL A, #40H;
      MOV R0,A;
      RET;

CLEAN:
       MOV R3, #00H; //Y
NEXTY:
       LCALL POSY;
       LCALL ENVCOMSPI;
       MOV R2, #00H; //X
NEXTX:
       LCALL POSX;
       LCALL ENVCOMSPI;
       MOV R0,#00H; //LIMPIA
       LCALL ENVDATPI;
       INC R2;
       CJNE R2,#054H,NEXTX;
       INC R3;
       CJNE R3,#007,NEXTY;
       RET;

 SETDIR:
       LCALL POSX;
       LCALL ENVCOMSPI;
       LCALL POSY;
       LCALL ENVCOMSPI;
       RET;

 MOSI:
          CLR P0.3; //CLK <-0
          MOV A,R0;
          MOV R1,#08H;
          CICLO7:
            RLC A;
            LCALL DELAY1ms;
            MOV P0.4,C;
            SETB P0.3;
            LCALL DELAY1ms;
            CLR P0.3;
            DJNZ R1,CICLO7;
          RET;

       ENVCOMSPI:
         CLR P0.0;
         LCALL DELAY1ms;
         CLR P0.1;
         LCALL DELAY1ms;
         LCALL MOSI;
         LCALL DELAY1ms;
         SETB P0.0;
         RET;

       ENVDATPI:
         CLR P0.0;
         LCALL DELAY1ms;
         SETB P0.1;
         LCALL DELAY1ms;
         LCALL MOSI;
         LCALL DELAY1ms;
         SETB P0.0;
         RET;

       INIPIX:
           SETB P0.0;
           SETB P0.1;
           SETB P0.3;
           SETB P0.4;
           SETB P0.2;
           //ORL P0, #1FH;
           CLR P0.2;
           LCALL DELAY250ms;
           SETB P0.2;
           MOV R0, #21H;
           LCALL ENVCOMSPI;
           MOV R0, #0EFH;
           LCALL ENVCOMSPI;
           MOV R0, #04H;
           LCALL ENVCOMSPI;
           MOV R0, #012H;
           LCALL ENVCOMSPI;
           MOV R0, #20H;
           LCALL ENVCOMSPI;
           MOV R0, #08H;
           LCALL ENVCOMSPI;
           MOV R0, #0CH;
           LCALL ENVCOMSPI;
           LCALL  DELAY250ms;
       RET;


        DELAY1ms:
           MOV R6, #03H;
           AQUI2: MOV R7, #0FFH;
             AQUI1:
               NOP;
               DJNZ R7, AQUI1;
               NOP;
               DJNZ R6, AQUI2;
               RET;

        DELAY250ms:
           MOV R5, #0FAH;
           AQUI3:
                LCALL DELAY1ms;
                DJNZ R5, AQUI3;
                RET;



                Reg5: DB 000H, 000H, 080H, 080H, 001H, 001H, 003H, 002H, 004H, 008H, 000H, 000H, 000H, 010H, 020H, 040H, 0E0H, 0C0H, 000H, 000H, 001H, 001H, 001H, 001H, 001H, 003H, 003H, 003H, 003H, 007H, 00FH, 01FH, 007H, 00FH, 0FCH, 0F8H, 0E3H, 0FDH, 00FH, 00BH, 017H, 03FH, 07FH, 07FH, 0FFH, 0FFH, 0FFH, 0FFH, 07FH, 07FH, 03CH, 038H, 000H, 000H, 080H, 0E0H, 078H, 040H, 020H, 030H, 010H, 018H, 008H, 004H, 004H, 002H, 000H, 080H, 082H, 081H, 0C0H, 080H, 080H, 0E0H, 0C0H, 0C0H, 0F0H, 0E0H, 0F0H;
                Reg4: DB 000H, 030H, 040H, 080H, 080H, 000H, 000H, 000H, 000H, 002H, 004H, 008H, 00BH, 006H, 00CH, 000H, 010H, 01FH, 01FH, 09FH, 09FH, 09FH, 09FH, 0DFH, 0DFH, 0DFH, 0DFH, 0DEH, 0FEH, 0FFH, 0FFH, 0FFH, 0FAH, 09CH, 00CH, 088H, 0C8H, 0E0H, 000H, 000H, 000H, 080H, 080H, 080H, 080H, 0C0H, 0E0H, 0FCH, 0DCH, 09EH, 09FH, 09FH, 01FH, 01FH, 01FH, 00FH, 018H, 00CH, 00EH, 003H, 010H, 010H, 008H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 080H, 0C0H, 060H, 038H, 007H, 00FH, 01FH, 03FH, 0FFH;
                Reg3: DB 004H, 000H, 001H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 0F0H, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 09EH, 09FH, 09FH, 09FH, 09FH, 00BH, 006H, 006H, 006H, 004H, 000H, 000H, 000H, 000H, 002H, 002H, 002H, 003H, 001H, 005H, 005H, 006H, 016H, 017H, 01FH, 01FH, 08FH, 0EFH, 0E6H, 0F6H, 015H, 004H, 006H, 00EH, 00EH, 006H, 006H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 001H, 003H, 007H, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH;
                Reg2: DB 000H, 000H, 000H, 080H, 080H, 000H, 070H, 04FH, 03EH, 061H, 000H, 020H, 021H, 03FH, 01FH, 01FH, 01FH, 00EH, 00FH, 08FH, 0FFH, 0FFH, 0F7H, 0E7H, 044H, 0C8H, 080H, 080H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 080H, 080H, 0C0H, 0C0H, 0E0H, 070H, 0F8H, 0FEH, 08FH, 08FH, 00FH, 00FH, 01FH, 01FH, 03FH, 03FH, 03FH, 03FH, 038H, 070H, 07FH, 07FH, 07FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FEH, 0FCH, 0F8H, 0F8H, 0E0H, 0E0H;
                Reg1: DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 0F8H, 006H, 0C0H, 030H, 00CH, 0FFH, 0FCH, 0F0H, 0C0H, 030H, 0C7H, 09FH, 0FFH, 0FFH, 0FFH, 0BFH, 00FH, 06FH, 077H, 07FH, 070H, 078H, 029H, 023H, 017H, 01FH, 017H, 007H, 00FH, 01FH, 01FH, 01FH, 01FH, 01FH, 03FH, 03FH, 02FH, 05FH, 07FH, 07FH, 077H, 037H, 00FH, 037H, 03FH, 01FH, 09FH, 0FEH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0EFH, 01FH, 007H, 03FH, 0FFH, 0FEH, 0FEH, 0FDH, 0F5H, 0E5H, 0C9H, 00BH, 013H, 013H, 023H, 026H, 026H, 0D7H;
                Reg0: DB 000H, 000H, 000H, 000H, 000H, 000H, 000H, 000H, 001H, 0C0H, 033H, 00CH, 003H, 011H, 000H, 000H, 07EH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 07FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0EFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FDH, 0FBH, 0F7H, 0EFH, 0DFH, 0BFH, 07FH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FFH, 0FEH, 0FCH, 0FCH, 0F8H, 0F8H, 0F0H, 0E3H, 0E1H, 0E1H, 0C3H, 0C1H, 081H, 081H, 001H, 001H, 007H, 00FH, 00FH, 05DH;


         #pragma endasm
}
