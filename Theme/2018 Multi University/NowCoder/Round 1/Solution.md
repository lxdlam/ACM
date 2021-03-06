# A. Monotonic Matrix

考虑01和12分界线方案即可。

这两条线都是从$(n,0)$到$(0,m)$的线，根据题目描述这两条线是不相交但是可重合的线，考虑其中的一条线我们可以直接套用Lindström–Gessel–Viennot定理，而两条线的方案我们可以平移其中一条来达到去重边的目的就可以直接套这个定理了。

对于两点间方案的计数，可以考虑如下描述：对于路径序列，里面必定包含两部分元素：一部分是横向路径，一部分是纵向路径，横向路径为$m$列的升序排列，纵向也如此，那么实际上就是这样的排列方案技术。考虑路径长度为$n+m$，那么我们只需要确定其中一部分即可确定另一部分，选择其中$m$个空位来安排横向路径，剩下的$n$个空位的方案也就唯一确定了，所以方案数为$\binom{n+m}{n}=\binom{n+m}{m}$。

列出行列式计算即可。

同题型补题：

- [x] CF 348D
- [ ] HDU 5852