/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "Arduino.h"
#include "pins_vcp.h"

#ifdef __cplusplus
extern "C" {
#endif

void pinMode(uint32_t Pin, uint32_t PinMode)
{
   pinCFG(Pin, PinMode);
}

void digitalWrite(uint32_t Pin, uint32_t PinValue)
{
  pinSET(Pin, PinValue);
}

int digitalRead(uint32_t Pin)
{
  return pinREAD(Pin); 
}

void digitalToggle(uint32_t Pin)
{
  digitalToggleFast(digitalPinToPinName(Pin));
}

#ifdef __cplusplus
}
#endif
