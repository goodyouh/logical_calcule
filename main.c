#include <stdio.h>
#include "logical.h"

// 两层宏定义，确保宏展开后再字符串化
#define STRINGIFY_HELPER(x)     #x
#define STRINGIFY(x)            STRINGIFY_HELPER(x)

#define PATTERN1                1&1
#define PATTERN2                1|0
#define PATTERN3                !1
#define PATTERN4                0|0
#define PATTERN5                1&0
#define PATTERN6                !(1&0)|1
#define PATTERN7                1&(0|1)
#define PATTERN8                !(1|0)&1
#define PATTERN9                !((1&1)|0)
#define PATTERN10               (1|0)&(1&1)
#define PATTERN11               !((1|0)&(1&0))
#define PATTERN12               !((1&1)|!(0|1))
#define PATTERN13               ((1|0)&1)|!(1&0)
#define PATTERN14               !((1|1)&(0|1))|1
#define PATTERN15               !((1&0)|!(1|1)&(0|1))
#define PATTERN16               !((1|0)&(1&0)|!(1&1))
#define PATTERN17               !((1&1)|!(0|1)&(1|0))
#define PATTERN18               ((1|0)&1)|!(1&0)&((1&1)|0)
#define PATTERN19               !((1|1)&(0|1)|!(1&0))&(1|0)
#define PATTERN20               !((1&0)|!(1|1)&(0|1)|1)&(1|0)

#define PATTERN                 PATTERN19
#define PATTERNSTR              STRINGIFY(PATTERN)



void main(){
        char                            pattern[] = PATTERNSTR;
        char*                           pcur = pattern;
        printf("%s = %d    Native:%d\n", pattern, logical_calculus(str2logical(pcur)), PATTERN);
}
