//
// Created by Grisha on 11.10.2021.
//

#include "gtest/gtest.h"
#include "myDynamicArray.h"
#include "random"

#define testCount 100
#define maxSize 1000
#define maxValue 100'000

TEST(DynamicArray, Recap) {
    newDynamicArray<int> dynamicArray;
    for (int i = 0; i < testCount; i++) {
        size_t cap = random()%maxSize;
        dynamicArray.recap(cap);
        ASSERT_EQ(dynamicArray.getCapacity(), cap);
    }
}

TEST(DynamicArray, Resize) {
    newDynamicArray<int> dynamicArray;
    size_t maxCap = 0;
    for (int i = 0; i < testCount; i++) {
        size_t size = random()%maxSize;
        if (maxCap < size)
            maxCap = size;
        dynamicArray.resize(size);
        ASSERT_EQ(dynamicArray.getSize(), size);
        ASSERT_EQ(dynamicArray.getCapacity(), maxCap);
    }
}

TEST(DynamicArray, Constructors) {
    const int defVal = 5;
    newDynamicArray<int> dynamicArray1(size_t(maxSize), defVal);
    ASSERT_EQ(dynamicArray1.getSize(), maxSize);
    ASSERT_EQ(dynamicArray1.getCapacity(), maxSize);
    for (int i = 0; i < dynamicArray1.getSize(); i++) {
        EXPECT_EQ(dynamicArray1[i], defVal);
    }


    constexpr int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    constexpr int size = sizeof(arr) / sizeof(int);
    newDynamicArray<int> dynamicArray2(arr, sizeof(arr) / sizeof(int));
    ASSERT_EQ(dynamicArray2.getSize(), size);
    ASSERT_EQ(dynamicArray2.getCapacity(), size);
    for (int i = 0; i < dynamicArray2.getSize(); i++) {
        EXPECT_EQ(dynamicArray2[i], i + 1);
    }

    newDynamicArray<int> dynamicArray3(dynamicArray2);
    ASSERT_EQ(dynamicArray2.getSize(), dynamicArray3.getSize());
    ASSERT_EQ(dynamicArray2.getCapacity(), dynamicArray3.getCapacity());
    for (int i = 0; i < dynamicArray3.getSize(); i++) {
        EXPECT_EQ(dynamicArray2[i], dynamicArray3[i]);
    }
}

TEST(DynamicArray, GetSet) {
    newDynamicArray<int> dynamicArray(size_t(maxSize), 0);
    for (size_t i = 0; i < dynamicArray.getSize(); i++) {
        EXPECT_EQ(dynamicArray[i], 0);
        int val = random()%maxValue;
        dynamicArray.set(val, i);
        EXPECT_EQ(dynamicArray[i], val);
        EXPECT_THROW(dynamicArray.set(val, maxSize*(i+1)), newDynamicArray<int>::indexOutOfRange);
        EXPECT_THROW(dynamicArray.get(maxSize*(i+1)), newDynamicArray<int>::indexOutOfRange);
    }
}