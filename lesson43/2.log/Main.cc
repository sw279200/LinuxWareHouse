#include<iostream>
#include"Log.hpp"

int main()
{
    Log log;
    log.Enable(Classfile);
    log.LogMessage(DEBUG,"hello,%s,%d,%f\n","linux",6,3.14);
    log.LogMessage(INFO,"hello,%s,%d,%f\n","linux",7,3.14);
    log.LogMessage(WARNING,"hello,%s,%d,%f\n","linux",8,3.14);
    log.LogMessage(ERROR,"hello,%s,%d,%f\n","linux",9,3.14);
    log.LogMessage(FATAL,"hello,%s,%d,%f\n","linux",10,3.14);
    log.LogMessage(DEBUG,"hello,%s,%d,%f\n","linux",6,3.14);
    log.LogMessage(INFO,"hello,%s,%d,%f\n","linux",7,3.14);
    log.LogMessage(WARNING,"hello,%s,%d,%f\n","linux",8,3.14);
    log.LogMessage(ERROR,"hello,%s,%d,%f\n","linux",9,3.14);
    log.LogMessage(FATAL,"hello,%s,%d,%f\n","linux",10,3.14);
    log.LogMessage(DEBUG,"hello,%s,%d,%f\n","linux",6,3.14);
    log.LogMessage(INFO,"hello,%s,%d,%f\n","linux",7,3.14);
    log.LogMessage(WARNING,"hello,%s,%d,%f\n","linux",8,3.14);
    log.LogMessage(ERROR,"hello,%s,%d,%f\n","linux",9,3.14);
    log.LogMessage(FATAL,"hello,%s,%d,%f\n","linux",10,3.14);
    return 0;
}