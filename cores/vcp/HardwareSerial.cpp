/*
  HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
*/

#include <stdio.h>
#include "Arduino.h"
#include "HardwareSerial.h"

// Constructors ////////////////////////////////////////////////////////////////
HardwareSerial::HardwareSerial()
{
  (void)UART_Close(UART_DEBUG_CH);
  (void)UART_Open(UART_DEBUG_CH, GIC_PRIORITY_NO_MEAN, 115200UL, UART_POLLING_MODE,
                  UART_CTSRTS_OFF, 2U, WORD_LEN_8, DISABLE_FIFO, TWO_STOP_BIT_OFF, 
                  PARITY_SPACE, 0UL); 
}

// HardwareSerial::HardwareSerial(uint8_t Ch, uint32_t Baudrate)
// {
//   ucCh = Ch;
//   uiBaudrate = Baudrate;
// }

// Public Methods //////////////////////////////////////////////////////////////

void HardwareSerial::begin(uint32 baud)
{
  (void)UART_Close(UART_DEBUG_CH);
  (void)UART_Open(UART_DEBUG_CH, GIC_PRIORITY_NO_MEAN, baud, UART_POLLING_MODE,
                  UART_CTSRTS_OFF, 2U, WORD_LEN_8, DISABLE_FIFO, TWO_STOP_BIT_OFF, 
                  PARITY_SPACE, 0UL);  
}

size_t HardwareSerial::write(const uint8_t *buffer, size_t size)
{
  size_t ret = size;
  UART_Write(UART_DEBUG_CH, buffer, size);
  return ret; 
}

size_t HardwareSerial::write(uint8_t c)
{
  size_t ret = 0;

  uint8_t b = c + 48;
  UART_Write(UART_DEBUG_CH, (const uint8_t *)&b, 1UL);

  return ret;
}

size_t HardwareSerial::write(const char *str)
{
  size_t ret = 0;

  if (str == NULL) {
    return 0;
  }
  UART_Write(UART_DEBUG_CH, (const uint8_t *)str, strlen(str));

  return ret;
}

size_t HardwareSerial::print(const __FlashStringHelper *ifsh)
{
  return print(reinterpret_cast<const char *>(ifsh));
}

size_t HardwareSerial::print(const String &s)
{
  return write(s.c_str(), s.length());
}

// size_t HardwareSerial::print(uint8_t c)
// {
//   return write(c);
// }

size_t HardwareSerial::print(const char *str)
{  
  return write(str);
}

size_t HardwareSerial::print(char c)
{
  return write(c);
}

size_t HardwareSerial::print(unsigned char b, int base)
{
  return print((unsigned long) b, base);
}

size_t HardwareSerial::print(int n, int base)
{
  return print((long) n, base);
}

size_t HardwareSerial::print(unsigned int n, int base)
{
  return print((unsigned long) n, base);
}

size_t HardwareSerial::print(long n, int base)
{
  if (base == 0) {
    return write(n);
  } else if (base == 10) {
    if (n < 0) {
      int t = print('-');
      n = -n;
      return printNumber(n, 10) + t;
    }
    return printNumber(n, 10);
  } else {
    return printNumber(n, base);
  }
}

size_t HardwareSerial::print(unsigned long n, int base)
{
  if (base == 0) {
    return write(n);
  } else {
    return printNumber(n, base);
  }
}

size_t HardwareSerial::print(float n, int digits)
{
  return printFloat(n, digits);
}

size_t HardwareSerial::println(void)
{
  return write("\r\n");
}

size_t HardwareSerial::println(uint8_t c)
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t HardwareSerial::println(const char c[])
{
  size_t n = print(c);
  n += println();
  return n;
}

size_t HardwareSerial::println(int num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t HardwareSerial::println(long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t HardwareSerial::println(unsigned long num, int base)
{
  size_t n = print(num, base);
  n += println();
  return n;
}

size_t HardwareSerial::println(float num, int digits)
{
  size_t n = print(num, digits);
  n += println();
  return n;
}

// Private Methods 

size_t HardwareSerial::printNumber(unsigned long n, uint8_t base)
{
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  char *str = &buf[sizeof(buf) - 1];

  *str = '\0';

  if (base < 2) {
    base = 10;
  }
  
  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    *--str = c < 10 ? c + '0' : c + 'A' - 10;
  } while (n);

  return write(str);
}

// FAST IMPLEMENTATION FOR ULL
size_t HardwareSerial::printULLNumber(unsigned long long n64, uint8_t base)
{
  // if limited to base 10 and 16 the bufsize can be 20
  char buf[64];
  uint8_t i = 0;
  uint8_t innerLoops = 0;

  // prevent crash if called with base == 1
  if (base < 2) {
    base = 10;
  }

  // process chunks that fit in "16 bit math".
  uint16_t top = 0xFFFF / base;
  uint16_t th16 = 1;
  while (th16 < top) {
    th16 *= base;
    innerLoops++;
  }

  while (n64 > th16) {
    // 64 bit math part
    uint64_t q = n64 / th16;
    uint16_t r = n64 - q * th16;
    n64 = q;

    // 16 bit math loop to do remainder. (note buffer is filled reverse)
    for (uint8_t j = 0; j < innerLoops; j++) {
      uint16_t qq = r / base;
      buf[i++] = r - qq * base;
      r = qq;
    }
  }

  uint16_t n16 = n64;
  while (n16 > 0) {
    uint16_t qq = n16 / base;
    buf[i++] = n16 - qq * base;
    n16 = qq;
  }

  size_t bytes = i;
  for (; i > 0; i--) {
    write((char)(buf[i - 1] < 10 ?
                 '0' + buf[i - 1] :
                 'A' + buf[i - 1] - 10));
  }
  return bytes;
}

template <class T>
size_t HardwareSerial::printFloat(T number, uint8_t digits)
{
  size_t n = 0;

  if (isnan(number)) {
    return print("nan");
  }
  if (isinf(number)) {
    return print("inf");
  }
  if (number > 4294967040.0) {
    return print("ovf");  // constant determined empirically
  }
  if (number < -4294967040.0) {
    return print("ovf");  // constant determined empirically
  }

  // Handle negative numbers
  if (number < 0.0) {
    n += print("-" /*'-'*/);
    number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  T rounding = 0.5;
  for (uint8_t i = 0; i < digits; ++i) {
    rounding /= 10.0;
  }

  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  T remainder = number - (T)int_part;
  n += print(int_part);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    n += print( "."/*'.'*/);
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0) {
    remainder *= 10.0;
    unsigned int toPrint = (unsigned int)remainder;
    n += print(toPrint);
    remainder -= toPrint;
  }

  return n;
}
