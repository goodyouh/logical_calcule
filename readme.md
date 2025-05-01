# 字符串计算逻辑运算

## 现有调试方法
修改代码中的宏 PATTERN，以提供多个参考例子
```
#define PATTERN                 PATTERN13
#define PATTERNSTR              STRINGIFY(PATTERN)

void main(){
        char                    pattern[] = PATTERNSTR;
        char*                   pcur = pattern;
        printf("%s = %d    Native:%d\n", pattern, logical_calculus(str2logical(pcur)), PATTERN);
}
```
会输出如下结果
```
((1|0)^1)|!(1&0) = 1    Native:1
```

## 后续功能开发
- 关键词逻辑匹配 例如 a&b