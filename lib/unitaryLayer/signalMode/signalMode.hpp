#pragma once

class SIGNALgen{
private:
    bool bndMode;
public:
    SIGNALgen(){
        this->bndMode = false;
    }

    void setSignalBND(bool bnd){
        this->bndMode = bnd;
    }

    bool getSignalBND(){
        return bndMode;
    }

};
