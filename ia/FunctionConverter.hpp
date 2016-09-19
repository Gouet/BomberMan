//
// Created by gaspar_q on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_FUNCTIONCONVERTER_HPP
#define CPP_INDIE_STUDIO_FUNCTIONCONVERTER_HPP

#include <stddef.h>
#include <iostream>

namespace FunctionConverter
{
    template <typename fptrType, typename methodType, typename objType, typename ... Types>
    fptrType    methodToFptr(objType &obj, methodType fptmeth)
    {
        unsigned char   *fptmedump = (unsigned char *)&fptmeth;
        unsigned char   *objhexdump = (unsigned char *)&obj;
        fptrType        retFptr;
        unsigned char   *retFptrdump = (unsigned char *)&retFptr;

        std::cout << sizeof(fptmeth) << std::endl;
        for (size_t i = 0, len = sizeof(fptmeth); i < len; ++i)
        {
            if (i < 8)
            {
                std::cout << "i: " << i << std::endl;
                retFptrdump[i] = fptmedump[i];
            }
            else
            {
                std::cout << "i - 8: " << i - 8 << std::endl;
                retFptrdump[i] = objhexdump[i - 8];
            }
            std::cout << len << std::endl;
        }
        return (retFptr);
    }
};

#endif //CPP_INDIE_STUDIO_FUNCTIONCONVERTER_HPP
