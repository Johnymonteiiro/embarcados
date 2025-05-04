#ifndef SERIAL_H
#define SERIAL_H

class SERIAL
{
public:
    void begin(int taxa);
    void print(const char *text);
    void println(const char *text);
    int available();
    int read();
};

extern SERIAL Serial;

#endif
