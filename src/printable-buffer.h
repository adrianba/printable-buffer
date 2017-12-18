/*
 * Copyright 2017 Adrian Bateman (https://adebateman.org/)
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef PrintableBuffer_h
#define PrintableBuffer_h

#include <spark_wiring_print.h>

// Based on StringPrintableHelper in wiring/src/spark_wiring_string.cpp

class PrintableBuffer : public Print
{
public:
  PrintableBuffer(uint8_t *buffer, size_t bufferSize);
  inline operator const char *() { return (const char *)m_buffer; }

  // start() resets the buffer to empty
  void start();

  // Remaining returns the number of characters that can be written (leaving room for NUL terminator)
  inline size_t remaining() { return m_limit <= m_next ? 0 : (size_t)(m_limit - m_next); }

  // Overridden write methods used by Print
  virtual size_t write(const uint8_t *buffer, size_t size) override;
  virtual size_t write(uint8_t c) override;

  // Using Print.printf results in one or two buffer allocations and copy in printf_impl
  // qprintf avoids this by writing directly to the buffer
  size_t qprintf(char *format, ...);

private:
  uint8_t *m_buffer;
  uint8_t *m_next;
  uint8_t *m_limit;
};

#endif // PrintableBuffer_h