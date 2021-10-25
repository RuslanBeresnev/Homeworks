#pragma once

#include <stdbool.h>

// Проверяет работу функции push(), а затем работу функции pop() на непустом стеке
bool notEmptyStackTestPassed(void);

// Проверяет работу функции pop() на пустом стеке
bool emptyStackTestPassed(void);


// Проверяет работу функции isEmpty()
bool isEmptyFunctionTestPassed(void);

// Проверяет работу функции deleteStack()
bool deleteStackFunctionTestPassed(void);

// Проверяет выполнение всех тестов
bool generalTest(void);