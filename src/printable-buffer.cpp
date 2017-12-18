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

#include "printable-buffer.h"
#include <stdarg.h>
#include <stdio.h>

PrintableBuffer::PrintableBuffer(uint8_t *buffer, size_t bufferSize)
    : m_buffer(buffer)
{
    // m_limit points to the last writeable byte in the buffer
    m_limit = m_buffer + bufferSize - 1;
    start();
}

void PrintableBuffer::start()
{
    m_next = m_buffer;
    if (m_next <= m_limit)
    {
        *m_next = '\0';
    }
}

size_t PrintableBuffer::write(const uint8_t *buffer, size_t size)
{
    size_t r = remaining();
    if (r == 0)
    {
        size = 0;
    }
    else
    {
        if (size > r)
        {
            size = r;
        }
        memcpy(m_next, buffer, size);
        m_next += size;
        *m_next = '\0';
    }
    return size;
}

size_t PrintableBuffer::write(uint8_t c)
{
    if (m_next < m_limit) // need to leave room for nul terminator
    {
        *m_next = c;
        m_next++;
        *m_next = '\0';
        return 1;
    }
    return 0;
}

size_t PrintableBuffer::qprintf(char *format, ...)
{
    // Print limited by space remaining (+1 for NUL terminator if we have room)
    va_list marker;
    va_start(marker, format);
    size_t r = remaining();
    size_t n = vsnprintf((char *)m_next, r > 0 ? (r + 1) : 0, format, marker);
    va_end(marker);

    // Advance current pointer (n will be the number of chars that _would_ have been written)
    m_next += n;
    if (m_next > m_limit)
    {
        m_next = m_limit;
    }
    return n;
}
