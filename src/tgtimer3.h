#ifndef TGTIMER3_H
#define TGTIMER3_H
#include <Arduino.h>


#define MAX_DT_NO_PRE 4 // ((1000*0xFFFF) / F_CPU)

class TgTimer3
{
public:
  TgTimer3();
   enum Prescaler {P1 = 1, P8 = 8,P64 = 64, P256 = 256, P1024 = 1024};
   enum Mode {Normal,CTC_OCR};
     void set_mode(Mode);
   void set_prescaler(Prescaler);
   void set_fq_ocr(double fq);
   void set_dt_ocr(uint32_t dt);
   void set_ovf_interrupt(bool);
   void set_ocr_interrupt(bool);
   typedef void (*INT_FP)();
   void set_ocr_interrupt(INT_FP);
   void set_ovf_interrupt(INT_FP);
   static INT_FP ovf_int_f;
   static INT_FP ocr_int_f;

   //static void (*ovf_int_f)();




};




#endif
