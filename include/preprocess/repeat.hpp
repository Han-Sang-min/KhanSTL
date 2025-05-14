#ifndef PREPROCESS_REPEAT_HPP
#define PREPROCESS_REPEAT_HPP

#define KHAN_PP_CAT(a, b) KHAN_PP_CAT_I(a, b)
#define KHAN_PP_CAT_I(a, b) a##b

#define KHAN_PP_REPEAT(count, macro, data) \
    KHAN_PP_CAT(KHAN_PP_REPEAT_, count)(macro, data)

#define KHAN_PP_REPEAT_0(macro, data)
#define KHAN_PP_REPEAT_1(macro, data) macro(, 0, data)
#define KHAN_PP_REPEAT_2(macro, data) KHAN_PP_REPEAT_1(macro, data) macro(, 1, data)
#define KHAN_PP_REPEAT_3(macro, data) KHAN_PP_REPEAT_2(macro, data) macro(, 2, data)
#define KHAN_PP_REPEAT_4(macro, data) KHAN_PP_REPEAT_3(macro, data) macro(, 3, data)
#define KHAN_PP_REPEAT_5(macro, data) KHAN_PP_REPEAT_4(macro, data) macro(, 4, data)
#define KHAN_PP_REPEAT_6(macro, data) KHAN_PP_REPEAT_5(macro, data) macro(, 5, data)
#define KHAN_PP_REPEAT_7(macro, data) KHAN_PP_REPEAT_6(macro, data) macro(, 6, data)
#define KHAN_PP_REPEAT_8(macro, data) KHAN_PP_REPEAT_7(macro, data) macro(, 7, data)
#define KHAN_PP_REPEAT_9(macro, data) KHAN_PP_REPEAT_8(macro, data) macro(, 8, data)
#define KHAN_PP_REPEAT_10(macro, data) KHAN_PP_REPEAT_9(macro, data) macro(, 9, data)


#endif // PREPROCESS_REPEAT_HPP