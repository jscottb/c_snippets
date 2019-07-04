/*
**  BIPORT.C - Port TC/TC++/BC++ code using register pseudovariables
**
**  public domain by Bob Stout
*/

#include "biport.h"

union  REGS  BIP_regs_;
struct SREGS BIP_sregs_;

unsigned _pascal geninterrupt(int int_no)
{
      int86x(int_no, &BIP_regs_, &BIP_regs_, &BIP_sregs_);
      return BIP_regs_.x.ax;
}
