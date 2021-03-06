#ifndef MYSQLTASK_H
#define MYSQLTASK_H

enum EMysqlError
{
    EME_ERROR = -1,
    EME_OK,
    EME_NOT_EXIST,
    EME_EXIST,
};

class CMysql;

class IMysqlTask
{
public:
    IMysqlTask(void) {};
    virtual ~IMysqlTask(void) {};

public:
    virtual void execute(CMysql* poConn) = 0;
    virtual void reply() = 0;
    virtual void release() { delete this; };
};

#endif