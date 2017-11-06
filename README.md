# collatz
App created on hackyeah hackathon

Collatz conjecture is said to be one of problems in mathematics too hard to prove it. "It concerns a sequence defined as follows: start with any positive integer n. Then each term is obtained from the previous term as follows: if the previous term is even, the next term is one half the previous term. Otherwise, the next term is 3 times the previous term plus 1. The conjecture is that no matter what value of n, the sequence will always reach 1." ~ Wikipedia

The task was to find k for which we need to apply collatz function most times in a given range of numbers.
As the competition was 24h long I precalculated needed steps for first 100 million numbers, stored it in a file and then used that to speed up further calculations. I also took into account one simple thing. If we say find our k with max needed steps in the first half of range then there is certainly 2k in the second half. So in the second half there is a number which needs one more step. That way we don't need to check first half of the range.
I could speed up searching by using more than one thread, but I didn't want to lose time trying to do that. Also my laptop was heating too much already.

I suggest compiling it with -O3, and remember that precalculated steps are stored in a file which has ~400MB.


I'll probably work on that code more and make more optimizations in my free time.
