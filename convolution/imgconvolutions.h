#ifndef IMGCONVOLUTIONS_H
#define IMGCONVOLUTIONS_H

class ImgConvolutions
{
public:
    enum operationList {CONV_PB3, CONV_PB5, CONV_PB7, CONV_BARTLETT3, CONV_BARTLETT5, CONV_BARTLETT7,
                        CONV_GAUSS5, CONV_PA3, CONV_PA_LPv4, CONV_PA_LPv8};
    ImgConvolutions();
};

#endif // IMGCONVOLUTIONS_H
