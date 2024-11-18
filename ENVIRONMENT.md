# The LeetCode C programming environment

[](https://support.leetcode.com/hc/en-us/articles/360011833974-What-are-the-environments-for-the-programming-languages)

* Compiler:  GCC 13
* Standard:  GNU11
* Optimization: -02
* Bug detection
  * Uses `AddressSanitizer`
  * Thus likely compiled under Linux
* (Most) standard library headers are included
* Can use `uthash` for hash tables
  * [](https://troydhanson.github.io/uthash/)
  * The header is included