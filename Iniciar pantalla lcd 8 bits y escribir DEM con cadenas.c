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
         ORL P1MDOUT, #0FFH; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P1SKIP, #0FFH; //TODAS LAS TERMINALES SON IGNORADAS POR EL CROSSBAR
         ORL P0MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         ORL P0MDOUT, #00H; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         ORL P0SKIP, #0FFH;
         //ORL P2MDIN, #0FFH; //TODAS LAS TERMINALES COMO DIGITALES
         //ORL P2MDOUT, #00H; //TODAS LAS TERMINALES COMO SALIDAS PUSH-PULL
         //ORL P2SKIP, #0FFH;
         ORL XBR2, #040H;

        LCALL INILCD;

        //MOV R0, #044H; //D
        //LCALL LCDDAT;
        //LCALL DELAY1ms;
        //MOV R0,#045H; //E
        //LCALL LCDDAT;
        //LCALL DELAY1ms;
        //MOV R0, #04DH; //M
        //LCALL LCDDAT;
        //LCALL DELAY1ms;
        MOV DPTR,#CAD1;
        MOV R4,#00H; //CONTADOR
        MOV 030H,#03H; //DIRECCION DE MEMORIA RAM 30H
        LCALL PALABRA1;

        MOV DPTR,#CAD2;
        MOV R4, #00H;
        MOV 030H, #03H;
        MOV R0, #0C0H;
        LCALL LCDINS;
        LCALL DELAY1ms;
        LCALL PALABRA1;
        RUT:
            LJMP RUT;

        PALABRA1:
          MOV A,R4;
          MOVC A,@A+DPTR;
          MOV R0,A;
          LCALL LCDDAT;
          LCALL DELAY1ms;
          INC R4;
          MOV A,R4;
          CJNE A, 30H,PALABRA1;
          RET;


        INILCD:
          LCALL DELAY250ms;
          MOV R0, #030H;
          LCALL LCDINS;
          LCALL DELAY250ms;
          MOV R0, #030H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #030H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #038H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #038H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #08H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #01H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0, #06H;
          LCALL LCDINS;
          LCALL DELAY1ms;
          MOV R0,#0EH;
          LCALL LCDINS;
          LCALL DELAY1ms;
          RET;

        LCDDAT:
          CLR P2.0;
          LCALL DELAY1ms;
          SETB P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          LCALL DELAY1ms;
          MOV P0, R0;
          LCALL DELAY1ms;
          CLR P2.0;
          LCALL DELAY1ms;
          RET;

        LCDINS:
          CLR P2.0;
          LCALL DELAY1ms;
          CLR P2.1;
          LCALL DELAY1ms;
          SETB P2.0;
          LCALL DELAY1ms;
          MOV P0, R0;
          LCALL DELAY1ms;
          CLR P2.0;
          LCALL DELAY1ms;
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
         DELAY1s:
           MOV R4, #04H;  // Cargar R5 con 4 en decimal (250 * 4ms = 1s)
           AQUI4:
                LCALL DELAY250ms;
                DJNZ R4, AQUI4;
                RET;
         CAD1:DB 044H,045H,04DH;
         CAD2:DB 044H,045H,04DH;
         #pragma endasm

}
