# permutations
#在windows10, vs2012 上编译通过
#四个文件分别实现了字典序法、递增进制数法、递减进制数法、邻位兑换法四中全排列方法
#每种方法有两种接口：permutation（int range）和 permutation（vector<int> v0, int order); 第一种接口输出range长度的所有全排列，例如#permutation（2）输出“01”“10”,第二种接口输出v0前（order<0）或者后（order>0）order位的排列。
#第二种接口功能上有一定的创新，对于排列的基不限于从0开始，也不限于相邻的数字，其可以实现输出“354678”前第30个排列这样的功能
