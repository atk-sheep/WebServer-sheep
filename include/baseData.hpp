#ifndef BASEDATA_HPP_
#define BASEDATA_HPP_

class baseData
{
private:
    /* data */
public:
    baseData(/* args */);
    ~baseData();

    virtual void handler() = 0;
};

#endif