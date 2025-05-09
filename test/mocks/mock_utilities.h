#ifndef MOCK_UTILITIES_H
#define MOCK_UTILITIES_H

#include "utilities.h"
#include <gmock/gmock.h>

class MockUtilities : public Utilities {
public:
    MOCK_METHOD(bool, isPair, (int number), (const));  
};

#endif // MOCK_UTILITIES_H