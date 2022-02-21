#ifndef JOB_H
#define JOB_H

class Job{
public:
    virtual ~Job() {};
    virtual void run() =0;
};

#endif