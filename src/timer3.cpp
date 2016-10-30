#include <timer3.h>

ISR(TIMER3_OVF_vect) {
    if (Timer3::ovf_int_f) Timer3::ovf_int_f();
}
ISR(TIMER3_COMPA_vect) {
  if (Timer3::ocr_int_f) Timer3::ocr_int_f();
}

Timer3::Timer3()
{

}

Timer3::INT_FP Timer3::ovf_int_f = NULL;
Timer3::INT_FP Timer3::ocr_int_f = NULL;


void Timer3::set_mode(Timer3::Mode m)
{
  switch (m) {
    case Normal:
    TCCR3A &= ~(1<<WGM30) & ~(1<<WGM31);
    TCCR3B &= ~(1<<WGM32) & ~(1<<WGM33);
    case CTC_OCR:
  TCCR3A &= ~(1<<WGM30) & ~(1<<WGM31);
  TCCR3B |= (1<<WGM32);
  TCCR3B &= ~(1<<WGM33);
  break;
    default:
    //TODO handle
    break;
  }
}

void Timer3::set_dt_ocr(uint32_t dt)
{

  if (dt < (MAX_DT_NO_PRE*P1) )
  {
   OCR3A = dt *(F_CPU/(1000*P1));
   if (OCR3A < 500) OCR3A = 500;
   set_prescaler(P1);
  }
  else if (dt < (MAX_DT_NO_PRE*P8) )
  {
    OCR3A = dt *(F_CPU/(1000*P8));
   set_prescaler(P8);
  }
  else if (dt < (MAX_DT_NO_PRE*P64) )
  {
    OCR3A = dt *(F_CPU/( ( uint32_t(1000) * uint32_t(P64) )));
   set_prescaler(P64);
  }
  else if (dt < (MAX_DT_NO_PRE*P256) )
  {
     OCR3A = dt *(F_CPU/( ( uint32_t(1000) * uint32_t(P256) ) ) );
   set_prescaler(P256);
  }
  else if (dt < (MAX_DT_NO_PRE*P1024) )
  {
    OCR3A = dt *(F_CPU/( ( uint32_t(1000) * uint32_t(P1024) )));
   set_prescaler(P1024);
  }
  else
  {
    OCR3A = 0xFFFF;
    set_prescaler(P1024);
  }
}

void Timer3::set_fq_ocr(double fq)
{
  /*
  if(fq>244) {
  OCR3A = F_CPU/ ((long)(P1*fq)) - 1;
}
else if (fq>122) {
  OCR3A = F_CPU/ ((long)(P2*fq)) - 1;
}
else if (fq>30.5) {
  OCR3A = F_CPU / ((long)(P8*fq)) - 1;
}
else if (fq>3.82) {
  OCR3A = F_CPU / ((long)(P8*fq)) - 1;
}
else if (fq>0.96) {
  OCR3A = F_CPU / ((long)(P8*fq)) - 1;
}
*/

}

void Timer3::set_prescaler(Timer3::Prescaler p)
{
  switch (p) {
    case P1:
  TCCR3B |= (1<<CS30);
  TCCR3B &= ~(1<<CS32) & ~(1<<CS31);
  break;
  case P8:
  TCCR3B |=  (1<<CS31) ;
  TCCR3B &= ~(1<<CS32) & ~(1<<CS30);
  break;
  case P64:
  TCCR3B |=  (1<<CS32) | (1<<CS31) ;
  TCCR3B &= ~(1<<CS32);
  break;
  case P256:
  TCCR3B |=  (1<<CS32) ;
  TCCR3B &= ~(1<<CS31) & ~(1<<CS30);
  break;
  case P1024:
  TCCR3B |=  (1<<CS32) | (1<<CS30);
  TCCR3B &= ~(1<<CS31);
  break;
  default:
  //TODO handle
    break;
  }
}

void Timer3::set_ovf_interrupt(Timer3::INT_FP fp ){
  ovf_int_f = fp;
}

void Timer3::set_ovf_interrupt(bool b) {
  if(b) TIMSK3 |= (1<<TOIE3);
  else TIMSK3 &= ~(1<<TOIE3);
}

void Timer3::set_ocr_interrupt(Timer3::INT_FP fp ){
  ocr_int_f = fp;
}

void Timer3::set_ocr_interrupt(bool b) {
  if(b) TIMSK3 |= (1<<OCIE3A);
  else TIMSK3 &= ~(1<<OCIE3A);
}
