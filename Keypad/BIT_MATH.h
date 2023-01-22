#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(var, bit)   (var |= (1 << bit))
#define CLR_BIT(var, bit)   (var &= (~(1 << bit)))
#define TOG_BIT(var, bit)   (var ^= (1 << bit))
#define GET_BIT(var, bit)   ((var >> bit) & 1)

#define MATH_PLUS		'+'
#define MATH_MINUS		'-'
#define MATH_MULTIPLY	'*'
#define MATH_DIVIDE		'/'

#endif
